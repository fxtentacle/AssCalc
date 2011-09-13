// calc.cpp : Defines the entry point for the console application.
//


char *g_thisStr="";

#include "stdafx.h"

#include "..\def_out\LexCalc.h"
#include "..\def_out\LexCalc_tab.h"
//#include "..\def_out\srcread_tab.h"
extern YYSTYPE src_lval;

extern "C" int calc_parse( );
extern "C" void calc_restart( FILE *input_file );
extern "C" void *calc__scan_string( const char *str );

void *loc_calc__scan_string( const char *str )
{
//	char tmp[8192];
//	strcpy( tmp, str );
	FILE *f = 0;
	fopen_s(&f, str, "rt" );
	calc_restart( f ); 
	calc_parse();
	fclose(f);
	return 0;
}

int loc_calc_parse( )
{
	return calc_parse();
}

char scrname[512]="";
long g_curPass=-1;
long g_curPassHeader=-1;


typedef void (__cdecl* scan_file_fncp)( FILE *input_file );
typedef void* (__cdecl* scan_str_fncp)( const char *str );
typedef int (__cdecl* calc_parse_fncp)(  );

typedef bool (__cdecl* bHasPass_fncp)( int num );
typedef void (__cdecl* CallPass_fncp)( char *fnam, scan_file_fncp sffp, scan_str_fncp ssfp, calc_parse_fncp cpfp );

bHasPass_fncp bHasPass=0; 
CallPass_fncp CallPass=0;

#ifdef _DEBUG
#define LOCAL_FILE
#endif


bool localfx_bHasPass_fnc( int num );
void localfx_CallPass_fnc( char *fnam, scan_file_fncp sffp, scan_str_fncp ssfp, calc_parse_fncp cpfp );


#ifdef LOCAL_FILE

typedef struct{
	char FName[256];
	char *String;
}haCacheFile;

haCacheFile lCf[256];
int nCf=0;

	bool bHasPass_fnc( int num )
	{
		char ttmp[512];
		FILE *ff = 0;
		sprintf_s( ttmp, 512, "p%dh.txt", num );
		fopen_s( &ff, ttmp, "rt" );
		if( ff )
		{
			fclose(ff);
			return 1;
		}
		return 0;
	}

	char *GetCf( char *name )
	{
		for( int i=0;i<nCf;i++ )
		{
			if( !strcmp( lCf[i].FName, name ) )
				return lCf[i].String;
		}
		return 0;
	}

	void CallPass_fnc( char *fnam, scan_file_fncp sffp, scan_str_fncp ssfp, calc_parse_fncp cpfp )
	{
		char *cf=GetCf( fnam );
		if( cf )
		{
			calc__scan_string( cf );
			cpfp();
		}
		else
		{
			FILE *f=0;
			fopen_s( &f, fnam, "rt" );
			if( !f )return;
			fseek( f, 0, SEEK_END );
			int siz=ftell(f);
			lCf[nCf].String=new char[siz+16];
			fseek(f,0,SEEK_SET);
			fread( lCf[nCf].String, siz, 1, f );
			fclose(f);

			strcpy_s( lCf[nCf].FName, 256, fnam );

//			sffp( f );
			calc__scan_string( lCf[nCf].String );
			cpfp();

			nCf++;
		}
	}

	void initFuncPtr()
	{
		bHasPass=bHasPass_fnc;
		CallPass=CallPass_fnc;
	}
#else

	#ifdef HA_SIMPLEFX
		void initFuncPtr()
		{
			printf( "\n\nFX Brought to you by:\nTentacle\nFX Designed by:\nTomo-Chan\n\n\n\n" );
			bHasPass=localfx_bHasPass_fnc;
			CallPass=localfx_CallPass_fnc;
		}
	#else
		void initFuncPtr()
		{
			HMODULE hm=LoadLibrary( "ass_effects.dll" );
			bHasPass=(bHasPass_fncp)GetProcAddress( hm, "bHasPass" );
			CallPass=(CallPass_fncp)GetProcAddress( hm, "CallPass" );
		}
	#endif

#endif


char lLoopFiles[256][256]={"",};
int lLoopNum[256]={0,};
int lLoopNum2[256]={1,};
int nLoopFiles=0;

extern "C" void set_identifier( calc_type name, double v );


int curLoopfileNum=-1;
extern "C" void KillThisLoop()
{
	if( curLoopfileNum<0 )return;
	lLoopNum[curLoopfileNum]=0;
	lLoopNum2[curLoopfileNum]=0;
}

int do_once() 
{
	nLoopFiles=0;

	if( g_curPassHeader )
		sprintf_s( scrname, 512, "p%dh.txt", g_curPass );
	else
		sprintf_s( scrname, 512, "p%d.txt", g_curPass );

	CallPass( scrname, calc_restart, loc_calc__scan_string, loc_calc_parse );

	int i;
	for( i=0;i<nLoopFiles;i++ )
	{
		curLoopfileNum=i;
		for( int nl=0;nl<lLoopNum[i];nl++ )
		{
			for( int nl2=0;nl2<lLoopNum2[i];nl2++ )
			{
				calc_type ct;
				strcpy_s( ct.name, 256, "loopvar" );
				set_identifier( ct, nl );			
				
				calc_type ct2;
				strcpy_s( ct2.name, 256, "loopvar2" );
				set_identifier( ct2, nl2 );			
				
				sprintf_s( scrname, 512, "%s", lLoopFiles[i] );

				CallPass( scrname, calc_restart, loc_calc__scan_string, loc_calc_parse );
			}
		}
	}

	curLoopfileNum=-1;

    return i;
}

char *g_tmp;
char *g_tmp_after;
char *g_tmpHeader;
char g_tmpComplete[2048];
char g_tmpNoComment[2048];

extern "C" char *calc_text;
extern "C" int calc_error(char* errstr) {
        printf("\n\n-= outError: %s\n-= in file: %s\n-= at:%s", errstr,scrname, calc_text);
 		_getch();
       return 1;
}

extern "C" char *src_text;
extern "C" int src_error(char* errstr) {
        printf("\n\n-= inError: %s\n-= at:%s\n-= line:%s", errstr,src_text,g_tmp);
		_getch();
        return 1;
}

extern "C" void* alloca( size_t siz )
{
	return malloc( siz );
}

extern "C" FILE *foutt=0;

double times[2];
double ltimes[2];
double ltimes2[2];
double wtimes[2];
char lstr[2048];
char str[2048];
char style[128];
char commentStr[128];

char sizeStrSoFar[4096]="";
#include <stdlib.h>

extern "C" void rand_ins( char* name, double t )
{
	int mr=strlen( name );
	int ll=(int)(t+0.5);
	char tmp[4096];
	for( int i=0;i<ll;i++ )
	{
		tmp[i]=name[rand()%mr];
	}
}

extern "C" void loop_file( char* name, double t, double t2=1 )
{
	strcpy_s( lLoopFiles[nLoopFiles], 256, name );
	lLoopNum[nLoopFiles]=(int)(t+0.5);
	lLoopNum2[nLoopFiles]=(int)(t2+0.5);
	nLoopFiles++;
}

void print_style_item( char *name );

extern "C" void print_identifier( char* name )
{
	if( name[strlen(name)-1]=='\n' )
		name[strlen(name)-1]=0;
	if( !strcmp(name,"text") )
		fprintf( foutt, "%s", g_thisStr );
	if( !strcmp(name,"text_reks") )
	{
		char tmp[4096];
		strcpy_s( tmp, 4096, g_thisStr );
		if( tmp[strlen(tmp)-1]==' ' )
			tmp[strlen(tmp)-1]=0;  //vob sub doesnt use ' ' at line end

		if( tmp[strlen(tmp)-2]==-127 && tmp[strlen(tmp)-1]==64 )
			tmp[strlen(tmp)-2]=0;  //vob sub doesnt use ' ' at line end;  \81\40 is a kanji wide ' '

		fprintf( foutt, "%s", tmp );
	}
	if( !strcmp( name, "comment_str" ) )
		fprintf( foutt, "%s", commentStr );

	if( !strcmp(name,"textsofar") )
		fprintf( foutt, "%s", sizeStrSoFar );
	if( !strcmp(name,"textafter") )
		fprintf( foutt, "%s", g_tmp_after );

	if( !strcmp(name,"text_copy") )
		fprintf( foutt, "%s", g_tmp );
	if( !strcmp(name,"text_all") )
	{
		fprintf( foutt, "%s", g_tmpNoComment );
	}
	if( !strcmp(name,"header_copy") )
		fprintf( foutt, "%s", g_tmpHeader );
	if( !strcmp(name,"complete_copy") )
		fprintf( foutt, "%s", g_tmpComplete );

	if( !strncmp( name, "style", 5 ) )
		print_style_item( name );
}


extern "C" double get_identifier( calc_type name );


double lHSV_Color[4][256][3];
double lHSV_Time[4][256][2];
int nHSV_CT[4];

char *getStyleColorPtr( int which );

int ColoringAt( int sc, bool bor=0, double or=0 )
{
	if( nHSV_CT[sc]==0 )
	{
		fprintf( foutt, "%s", getStyleColorPtr(sc+1) );
		return -1;
	}

	calc_type n;
	strcpy_s( n.name, 2048, "fetchtime" );
	double ft=get_identifier( n );
	if( bor )ft=or;

	int li=0;
	double r,g,b;
	for( int i=0;i<nHSV_CT[sc];i++ )
	{
		if( lHSV_Time[sc][i][0]>ft )break;

		if( lHSV_Time[sc][i][1]>=ft && lHSV_Time[sc][i][0]<=ft )
		{
			double a1=(ft-lHSV_Time[sc][i][0])/(lHSV_Time[sc][i][1]-lHSV_Time[sc][i][0]);
			double a2=1-a1;
			r=a1*lHSV_Color[sc][i][0]+a2*lHSV_Color[sc][li][0];
			g=a1*lHSV_Color[sc][i][1]+a2*lHSV_Color[sc][li][1];
			b=a1*lHSV_Color[sc][i][2]+a2*lHSV_Color[sc][li][2];
			li=i;
			goto write_me;
		}
		li=i;
	}

	r=lHSV_Color[sc][li][0];
	g=lHSV_Color[sc][li][1];
	b=lHSV_Color[sc][li][2];

write_me:
	DWORD c=0;
	c|=((DWORD)r);
	c<<=8;
	c|=((DWORD)g);
	c<<=8;
	c|=((DWORD)b);
	fprintf( foutt, "%6.6X", c );

	return li;
}

void WriteCAt( int sc, int i )
{
	double r,g,b;
	r=lHSV_Color[sc][i][0];
	g=lHSV_Color[sc][i][1];
	b=lHSV_Color[sc][i][2];
	DWORD c=0;
	c|=((DWORD)r);
	c<<=8;
	c|=((DWORD)g);
	c<<=8;
	c|=((DWORD)b);
	fprintf( foutt, "%6.6X", c );
}

extern "C" void ColoringOff( double scd, double off )
{
	int sc=(int)(scd+0.5);

	sc--;

	fprintf( foutt, "{\\%dc&H",sc+1 );
	int si=ColoringAt(sc,1,off);
	fprintf( foutt, "&}" );

	if( si==nHSV_CT[sc]-1 )
	{
		if( nHSV_CT[sc]==0 || lHSV_Time[sc][si][1]<off )
			return; //no more color fx
	}

	if( off<lHSV_Time[sc][si][1] )
	{

	//t to end of current block
		fprintf( foutt, "{\\t(0,%d,\\%dc&H", (long)(1000*(lHSV_Time[sc][si][1]-off)), sc+1 );
		WriteCAt( sc, si );
		fprintf( foutt, "&)}" );
	}

	si++;

	for( si;si<nHSV_CT[sc];si++ )
	{
		fprintf( foutt, "{\\t(%d,%d,\\%dc&H",  (long)(1000*(lHSV_Time[sc][si][0]-off)), (long)(1000*(lHSV_Time[sc][si][1]-off)), sc+1 );
		WriteCAt( sc, si );
		fprintf( foutt, "&)}" );
	}
}


void GenCKey( char *txt, double t1, double t2, int which=1 )
{
	long i;
	DWORD c;
	if( sscanf_s( txt, "%dc&H%x&", &i, &c )!=2 )
	{
		sscanf_s( txt, "%x", &c );
		i=which;
	}

	double r=(c&0xFF0000)>>16;
	double g=(c&0xFF00)>>8;
	double b=(c&0xFF);

	i--;

	int s=nHSV_CT[i];

	lHSV_Time[i][s][0]=t1+wtimes[0];
	lHSV_Time[i][s][1]=t2+wtimes[0];

	lHSV_Color[i][s][0]=r;
	lHSV_Color[i][s][1]=g;
	lHSV_Color[i][s][2]=b;

	nHSV_CT[i]++;
}

extern "C" void CheckComment( char *txt )
{
	if( txt[1]=='%' )
	{
		if( txt[2]=='%' )
		{
			char tre[2048];
			strcpy_s( tre, 2048, txt+3 );
			if( tre[strlen(tre)-1]=='}' )tre[strlen(tre)-1]=0;
			strcat_s( tre, 2048, "\n" );
			calc__scan_string( tre );
			calc_parse( );
		}
		else
		{
			strcpy_s( commentStr, 128, txt );
			strcpy_s( commentStr+1, 127, commentStr+2 );
		}
	}
	if( txt[1]=='\\' )
	{
		if( txt[2]>='1' && txt[2]<='4' && txt[3]=='c' )
		{
			GenCKey( txt+2, -1, -1 );
		}
		if( txt[2]=='t' )
		{
			if( strstr( txt+2, "\\" )[2]=='c' )
			{
				long nn;
				sscanf_s( strstr( txt+2, "\\" )+1, "%d", &nn );
				if( nHSV_CT[nn-1]==0 )
				{
					GenCKey( getStyleColorPtr(nn), -1, -1, nn );
				}

				long l1,l2;
				sscanf_s( txt+4, "%d,%d,", &l1, &l2 );
				
				GenCKey( strstr( txt+2, "\\" )+1, ((double)l1)*0.001, ((double)l2)*0.001 );
			}
		}
		if( txt[2]=='m' && txt[3]=='o' && txt[4]=='v' && txt[5]=='e' )
		{
			long x,y;
			sscanf_s( txt, "{\\move(%d,%d", &x, &y );
			calc_type nam;
			strcpy_s( nam.name, 2048, "scriptposx" );
			set_identifier( nam, x );
			strcpy_s( nam.name, 2048, "scriptposy" );
			set_identifier( nam, y );
		}
		if( txt[2]=='p' && txt[3]=='o' && txt[4]=='s' )
		{
			long x,y;
			sscanf_s( txt, "{\\pos(%d,%d", &x, &y );
			calc_type nam;
			strcpy_s( nam.name, 2048, "scriptposx" );
			set_identifier( nam, x );
			strcpy_s( nam.name, 2048, "scriptposy" );
			set_identifier( nam, y );
		}
	}
}


extern "C" int textlock_identifier( char* name )
{
	if( name[strlen(name)-1]=='\n' )name[strlen(name)-1]=0;
	if( !strcmp(name,g_thisStr) )
		return 1;
	if( g_thisStr[0]==0 )
	{
		if( strstr( g_tmp, name ) )
			return 1;
	}
	return 0;
}

extern "C" int textfind_identifier( char* name )
{
	if( name[strlen(name)-1]=='\n' )name[strlen(name)-1]=0;
	if( strstr( g_tmp, name ) )
		return 1;
	return 0;
}

extern "C" int stylelock_identifier( char* name )
{
	if( name[strlen(name)-1]=='\n' )name[strlen(name)-1]=0;
	if( strstr( style, name ) )
		return 1;
	return 0;
}

extern "C" void print_time_of( double t )
{
	double t1,t2,t3;
	t1=floor(t/(60*60));
	t-=t1*60*60;
	t2=floor(t/(60));
	t-=t2*60;
	t3=t;
	fprintf( foutt, "%01.0f:%02.0f:%2.2f", t1,t2,t3 );
}

extern "C" void print_pos_of( double t )
{
	int i=(int)(t+0.5);
	fprintf( foutt, "%d", i );
}

extern "C" void print_char_of( double t )
{
	int i=(int)(t+0.5);
	fprintf( foutt, "%c", i );
}

extern "C" void print_hex_of( double t )
{
	int i=(int)(t+0.5);
	fprintf( foutt, "%x", i );
}

extern "C" void print_color_of( double t )
{
	int i=(int)(t+0.5);
	fprintf( foutt, "%6.6x", i );
}

extern "C" void print_tval_of( double t )
{
	int i=(int)(t*1000+0.5);
	fprintf( foutt, "%d", i );
}

int nthThisLine;
int nthThisLineAll;
int nChrThisLine;
int nChrThisLineAll;
int lnSizeThisLine;
int nSizeThisLine;
int nSizeThisOne;
int nSizeThisLineAll;
int bFirstOne;
int bLastOne;

int bSylF=1;
int bWordF=1;
int bWordL=1;
int nthWord=0;

int nAfterLastSpace=0;

long haGetSizThisOne();
long haGetYSizThisOne();


extern "C" double get_rand()
{
	return (double)rand()/(double)RAND_MAX;
}


class hAVar{
public:
	int n;
	int nM;
	double *lI;

	hAVar()
	{
		n=0;
		nM=16;
		lI=(double*)malloc( sizeof( double ) * nM );
	}

	void Set( int i, double v )
	{
		if( i<0 || i>(2<<16) )return;

		if( i>=nM )
		{
			nM=i+16;
			nM-=nM%8;
			lI=(double*)realloc( lI, sizeof( double ) * nM );
		}
		lI[i]=v;
		if( i>n )n=i;
	}

	double Get( int i )
	{
		if( i<0 || i>n || i>=nM )return 0;
		return lI[i];
	}
};
char lAVarN[256][256];
hAVar	lAVarV[256];
int		nAVar=0;

extern "C" double get_identifier_arr( calc_type name, double ind )
{
	for( int i=0;i< nAVar;i++ )
	{
		if( !strcmp( lAVarN[i], name.name ) )
		{
			return lAVarV[i].Get( (int)(ind+0.5) );
		}
	}
	return 0;
}

extern "C" void set_identifier_arr( calc_type name, double v, double ind )
{
	int i;
	for( i=0;i< nAVar;i++ )
	{
		if( !strcmp( lAVarN[i], name.name ) )
		{
			lAVarV[i].Set( (int)(ind+0.5), v );
			return;
		}
	}
	lAVarV[i].Set( (int)(ind+0.5), v );
	strcpy_s( lAVarN[nAVar], 256, name.name );
	nAVar++;
}

extern "C" double find_index_arr( calc_type name, double vx )
{
	hAVar *cv=0;
	for( int i=0;i< nAVar;i++ )
	{
		if( !strcmp( lAVarN[i], name.name ) )
		{
			cv=& lAVarV[i];
		}
	}
	if(!cv)return 0;

	for( int i=0;i<cv->n;i++ )
	{
		if( vx<cv->lI[i] )return (double)(i-1);
	}
	return cv->n-1;
}



bool bPixbufUpToDate=0;
bool bBorderbufUpToDate=0;


char lVarN[256][256];
double	lVarV[256];
int		nVar=0;

extern "C" double get_identifier( calc_type name )
{
	if( !strcmp(name.name,"ntstart") )return times[0];
	if( !strcmp(name.name,"ntend") )return times[1];

	if( !strcmp(name.name,"tstart") )return ltimes[0];
	if( !strcmp(name.name,"tend") )return ltimes[1];

	if( !strcmp(name.name,"ltstart") )return ltimes2[0];
	if( !strcmp(name.name,"ltend") )return ltimes2[1];

	if( !strcmp(name.name,"wtstart") )return wtimes[0];
	if( !strcmp(name.name,"wtend") )return wtimes[1];

	if( !strcmp(name.name,"nth") )return nthThisLine;
	if( !strcmp(name.name,"nthall") )return nthThisLineAll;

	if( !strcmp(name.name,"nchr") )return nChrThisLine;
	if( !strcmp(name.name,"nchrall") )return nChrThisLineAll;

	if( !strcmp(name.name,"nsiz") )return nSizeThisLine;
	if( !strcmp(name.name,"lnsiz") )return lnSizeThisLine;
	if( !strcmp(name.name,"nsizthisone") )return haGetSizThisOne();
	if( !strcmp(name.name,"nysizthisone") )return haGetYSizThisOne();
	if( !strcmp(name.name,"nsizall") )return nSizeThisLineAll;

	if( !strcmp(name.name,"bfirstone") )return bFirstOne;
	if( !strcmp(name.name,"blastone") )return bLastOne;

	if( !strcmp(name.name,"bsylf") )return bSylF;

	if( !strcmp(name.name,"nafterlastspace") )return nAfterLastSpace;
	if( !strcmp(name.name,"bwordf") )return bWordF;
	if( !strcmp(name.name,"bwordl") )return bWordL;
	if( !strcmp(name.name,"nthword") )return nthWord;

	if( !strcmp(name.name,"rand") )return get_rand();

	for( int i=0;i< nVar;i++ )
	{
		if( !strcmp( lVarN[i], name.name ) )
		{
			return lVarV[i];
		}
	}
	return 0;
}

extern "C" void set_identifier( calc_type name, double v )
{
	for( int i=0;i< nVar;i++ )
	{
		if( !strcmp( lVarN[i], name.name ) )
		{
			lVarV[i]=v;
			return;
		}
	}
	lVarV[nVar]=v;
	strcpy_s( lVarN[nVar], 256, name.name );
	nVar++;
}


extern "C" int src_parse( );
extern "C" void src__scan_string( char *input );

extern "C" void DoIt1( double t1, double t2 );
extern "C" void DoIt2( double t1 );
extern "C" void DoIt3( char *txt );

char fontmatchus[512];
bool bHasBeenDone;
void haGetSiz();

bool bCharwise=0;
bool bDoubleCharwise=0;
bool bSpacefix=0;
bool bSkipSpace=0;

void ParseStyle( char *tmp );


char headerMEMFile[16384];
int nFilesSplit=0;

void DoIt3Real();

extern char *asciiArt;
extern char *asciiArt2;

int main( int argc, char *argv[ ] )
{
	initFuncPtr();

	printf( "ASS Scripter   -   (c) 2004 Hajo Krabbenhoeft aka Tentacle\n" );
	printf( "2011 modified by Hajo Krabbenhoeft for OutlawJonas\n" );
	printf( "%s\n", asciiArt );
	printf( "\nFree to use, no guarantees and do not modify or bug me about it\nUsage:\n Get a .ass script with only {\\K}'s or Comments in it (no effects) \n and drag it on proggy\n");

	
	FILE *f=0;

#ifndef LOCAL_FILE
	char tttrtr[512];
	GetModuleFileName( 0, tttrtr, 510 );
	int tt=strlen(tttrtr)-1;
	while( tttrtr[tt]!='\\' && tttrtr[tt]!='/' && tt>=0 )tt--;
	tttrtr[tt]=0;
	SetCurrentDirectory( tttrtr );
#endif

	if( argv&&argv[0]&&argv[1] )
	{
		f = 0;
		if( argv[2] )
			fopen_s( &f, argv[2], "rt" );
		if( !f )
			fopen_s( &f, argv[1], "rt" );
	}
	if( !f )
		fopen_s( &f, "src.txt", "rt" );

	bool bSplit=0;

	if( argv[0] && argv[1] && argv[2] && !strcmp( argv[1], "split" ) )
		bSplit=1;

	FILE *addfile=0;

	if( bSplit )
	{
		foutt=0;
		fopen_s( &foutt,  "out_000.ass", "wt" );
		nFilesSplit=1;

		addfile=0;
		fopen_s( &addfile, "addfile.vcf", "wt" );
		fprintf( addfile, "VirtualDub.video.filters.Clear();\n" );
		fprintf( addfile, "VirtualDub.video.filters.Add(\"TextSub 2.23\");\n" );
		fprintf( addfile, "VirtualDub.video.filters.instance[%d].Config(\"out_%3.3d.ass\", 1, \"25.00000\");\n",0,0 );
	}
	else
	{
		foutt=0;
		fopen_s( &foutt, "out.ass", "wt" );
	}
	
	if( !f )
	{
		printf( "No input file." );
		_getch();
		return -1;
	}
	while(!feof(f) )
	{
		char tmp[4096];

		if( bSplit && ftell(foutt)>1024*1024*3 )
		{
			fclose(foutt);

			sprintf_s( tmp, 4096, "out_%3.3d.ass", nFilesSplit );
			foutt=0;
			fopen_s( &foutt, tmp, "wt" );

			fprintf( addfile, "VirtualDub.video.filters.Add(\"TextSub 2.23\");\n" );
			fprintf( addfile, "VirtualDub.video.filters.instance[%d].Config(\"out_%3.3d.ass\", 1, \"25.00000\");\n",nFilesSplit,nFilesSplit );

			fputs( headerMEMFile, foutt );

			nFilesSplit++;
		}

		if( !fgets( tmp, 4096, f ) )break;
		if( !strncmp( tmp, "Style: ", 7 ) )
		{
			char tmp2[4096];
			strcpy_s( tmp2, 4096, tmp );
			ParseStyle( tmp2 );
		}
		
		strcpy_s(g_tmpComplete, 2048,tmp);
		g_tmpHeader=tmp;
		if( !strncmp( tmp, "Dialogue:", 9 ) )
		{//Dialogue: 1,0:00:38.53,0:00:41.62,OpKHM,OP,0000,0000,0000,,bla 
			double t1,t2,t3, v1, v2; 
			char *c=tmp+10;
			do{ c++; }while( c[-1]!=',' );
			sscanf_s( c, "%lf:%lf:%lf", &t1,&t2,&t3 ); 
			v1=t3+t2*60+t1*60*60;
			do{ c++; }while( c[-1]!=',' );
			sscanf_s( c, "%lf:%lf:%lf", &t1,&t2,&t3 ); 
			v2=t3+t2*60+t1*60*60;
			do{ c++; }while( c[-1]!=',' );
			char *c2=c;
			do{ c++; }while( c[0]!=',' );
			c[0]=0;
			c++;
			strcpy_s( style, 128, c2 );
			do{ c++; }while( c[-1]!=',' );
			do{ c++; }while( c[-1]!=',' );
			do{ c++; }while( c[-1]!=',' );
			do{ c++; }while( c[-1]!=',' );
			do{ c++; }while( c[-1]!=',' );
			c[strlen(c)-1]=0;
			g_tmp=c;

			g_tmpNoComment[0]=0;
			int ll=strlen(g_tmp);
			int cpos=0,cpos2;
			while( cpos<ll && cpos>=0 )
			{
				cpos2=strstr(g_tmp+cpos,"{")-g_tmp;
				if( cpos2<0 )
				{
				//	cpos=cpos2;
					break;
				}
				strncat_s(g_tmpNoComment, 2048,g_tmp+cpos,cpos2-cpos);
				cpos=strstr(g_tmp+cpos2,"}")-g_tmp+1;
			}
			if( cpos>=0 )
				strcat_s(g_tmpNoComment, 2048,g_tmp+cpos);

			DoIt1( v1,v2 );
		//	printf( "%s\n", c );
			printf( "." );
			nthThisLineAll=0;
			nChrThisLineAll=0;
			nSizeThisLineAll=0;
			lnSizeThisLine=0;
			fontmatchus[0]=0;
			commentStr[0]=0;
			for( int i=0;i<256;i++ )
			{
				bHasBeenDone=1;

				if( bHasPass( i ) )
				{
					g_curPass=i;

					//before starting each script round, reset flags
					bCharwise=0;
					bDoubleCharwise=0;
					bSkipSpace=0;
					fontmatchus[0]=0;

					nHSV_CT[0]=0;
					nHSV_CT[1]=0;
					nHSV_CT[2]=0;
					nHSV_CT[3]=0;

					bFirstOne=1;
					bLastOne=0;
					nthWord=0;
					bWordF=1;
					bWordL=1;

					g_curPassHeader=1;
					DoIt1( v1,v2 );
					do_once(); //call do once here because we want no text handling in header, just plain script exec

					g_curPassHeader=0;
					DoIt1( v1,v2 );
					//sprintf( scrname, "p%d.txt", i );
					src__scan_string( c );
					if( src_parse() )return -2;

					bLastOne=1;
					strcpy_s( lstr, 2048, str );
					DoIt2( 0 );
					DoIt3Real();
				}else break;
				nthThisLineAll=nthThisLine;
				nChrThisLineAll=nChrThisLine;
				nSizeThisLineAll=nSizeThisLine;
			}
		}else
		{
			if( strncmp( tmp, "Comment:", 8 ) )
			{
				fputs( tmp, foutt );
				strcat_s( headerMEMFile, 16384, tmp );
				strcat_s( headerMEMFile, 16384, "\n" );
			}
		}
	}
	fclose(f);

	f=0;
	fopen_s( &f, "incbin.txt", "rt" );
	if(f)
	{
		while(!feof(f) )
		{
			char tmp[4096];
			if( !fgets( tmp, 4096, f ) )break;
			fputs( tmp, foutt );
		}
	}

	fclose(foutt);

	if( addfile )
		fclose(addfile);

	printf( "\n\nDone.\n");
	_getch();
	return 1;
}


bool bFirstSet;
bool bFirstCall;
extern "C" void DoIt1( double t1, double t2 )
{
	lstr[0]=0;
	str[0]=0;
	times[0]=t1;
	times[1]=t1;
	wtimes[0]=t1;
	wtimes[1]=t2;
	ltimes[0]=t1;
	ltimes[1]=t1;
	ltimes2[0]=t1;
	ltimes2[1]=t1;
	bFirstSet=1;
	bFirstCall=1;
	nthThisLine=0;
	nChrThisLine=0;
	nSizeThisLine=0;
	lnSizeThisLine=0;
	sizeStrSoFar[0]=0;
}

extern "C" void DoIt2( double t1 )
{

	if( !bHasBeenDone )
		DoIt3("");

	bHasBeenDone=0;

	ltimes2[0]=ltimes[0];
	ltimes2[1]=ltimes[1];
	ltimes[0]=times[0];
	ltimes[1]=times[1];

	if( !bFirstSet )
		times[0]=times[1];
	else bFirstSet=0;
	times[1]=times[0]+t1;
}

char sizeStrNew[256];

bool flag_no_K_insert=0;

void DoIt3Work( char *txt )
{
	bPixbufUpToDate=0;
	bBorderbufUpToDate=0;
	g_thisStr=txt;

	if( strlen( txt ) )
	{
		if( !bSkipSpace  ||  !(txt[0]==' ' && txt[1]==0) )
			do_once();
	}
	else 
	{
		if( ltimes[1]-ltimes[0] > 0.0000001 )
		{
			if( fontmatchus[0]==0 && !flag_no_K_insert )
			{// if we're using fontmatch to split to pieces, karaoke wont work anyway
				fprintf( foutt, "{\\k");
				print_tval_of( (ltimes[1]-ltimes[0])*0.1 );
				fprintf( foutt, "}");
			}
		}
	}
	nChrThisLine+=strlen( txt );
	strcat_s( sizeStrSoFar, 4096, txt );
	strcpy_s( sizeStrNew, 256, txt );
	lnSizeThisLine=nSizeThisLine;
	haGetSiz();
}


void DoIt3Real()
{

	int l=strlen( lstr );

	if( l>0 )
	{
		bWordF=bWordL;
		bWordL=0;
	}

	for( int i=0;i<l;i++ )
	{
		if( lstr[i]==' ' )
		{
			nAfterLastSpace=0;
			bWordL=1;
		}
	}

	g_tmp_after=strstr(g_tmp,lstr)+strlen(lstr);
	if( !bCharwise && !bDoubleCharwise )
		DoIt3Work( lstr );
	else
	{
		int templ=bWordL;

		int l=strlen( lstr );
		for( int i=0;i<l;i+=(bDoubleCharwise+1) )
		{
			if( lstr[i]=='\\' && (lstr[i+1]=='n' || lstr[i+1]=='N') )
			{
				strcat_s( sizeStrSoFar, 4096, "\\n" );
				i+=1-bDoubleCharwise;
				continue;
			}
			char tmp[4]={0,};
			tmp[0]=lstr[i];
			if( bDoubleCharwise && tmp[0]!=' ' )
				tmp[1]=lstr[i+1];

			g_tmp_after=strstr(g_tmp,lstr)+i+1;

			bWordL=0;
			if( bDoubleCharwise )
			{
				if( i==l-2 )
					bWordL=templ;
			}
			else
			{
				if( i==l-1 )
					bWordL=templ;
			}

			bSylF= i==0?1:0;

			DoIt3Work( tmp );

			bWordF=0; //after first char this isnt first animore
		}
	}
	nAfterLastSpace++;
	nthThisLine++;
	
	if( l>0 )
		bFirstOne=0;

	if( bWordL )nthWord++;
}


extern "C" void DoIt3( char *txt )
{
	bHasBeenDone=1;

	strcpy_s( lstr, 2048, str );
	strcpy_s( str, 2048, txt );
	if( !bFirstCall )DoIt3Real();
	else bFirstCall=0;
}


char StyleNames[512][512];
char StyleFonts[512][512];

char StyleColor1[512][512];
char StyleColor2[512][512];
char StyleColor3[512][512];
char StyleColor4[512][512];

long StyleSizes[512];
long StyleBold[512];
long StyleItalic[512];
long StyleXScale[512];
long StyleYScale[512];
long StyleEncoding[512];
int nStyle=0;

//Format: Name, Fontname, Fontsize, PrimaryColour, SecondaryColour, OutlineColour, BackColour, Bold, Italic, Underline, StrikeOut, ScaleX, ScaleY, Spacing, Angle, BorderStyle, Outline, Shadow, Alignment, MarginL, MarginR, MarginV, Encoding
void ParseStyle( char *tmp )
{
	char *c=tmp;
	char *n=tmp;
	while( n[0]!=' ' )n++;
	n[0]=0;
	n++;
	c=n;
	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	strcpy_s( StyleNames[nStyle], 512, c );
	c=n;
	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	strcpy_s( StyleFonts[nStyle],512, c );
	c=n;
	sscanf_s( c, "%d", &StyleSizes[nStyle] );

	while( n[0]!=',' )n++;
	n++;
	c=n;

	char ttt[256];

	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	strcpy_s( ttt, 256, c );
	c=n;
	strcpy_s( StyleColor1[nStyle], 512, ttt+4 ); //&H00

	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	strcpy_s( ttt, 256, c );
	c=n;
	strcpy_s( StyleColor2[nStyle], 512, ttt+4 ); //&H00

	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	strcpy_s( ttt, 256, c );
	c=n;
	strcpy_s( StyleColor3[nStyle],512, ttt+4 ); //&H00

	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	strcpy_s( ttt, 256, c );
	c=n;
	strcpy_s( StyleColor4[nStyle],512, ttt+4 ); //&H00


	sscanf_s( c, "%d", &StyleBold[nStyle] );
	if( StyleBold[nStyle] )StyleBold[nStyle]=1;

	while( n[0]!=',' )n++;
	n++;
	c=n;
	sscanf_s( c, "%d", &StyleItalic[nStyle] );
	if( StyleItalic[nStyle] )StyleItalic[nStyle]=1;

	for( int i=0;i<3;i++ )
	{
		while( n[0]!=',' )n++;
		n++;
	}
	c=n;
	sscanf_s( c, "%d", &StyleXScale[nStyle] );

	while( n[0]!=',' )n++;
	n++;

	c=n;
	sscanf_s( c, "%d", &StyleYScale[nStyle] );

	for( int i=0;i<10;i++ )
	{
		while( n[0]!=',' )n++;
		n++;
	}
	c=n;
	sscanf_s( c, "%d", &StyleEncoding[nStyle] );
	
	nStyle++;
}

extern "C" void set_flag( char* name )
{
	if( !strcmp( name, "charwise" ) )
		bCharwise=1;
	if( !strcmp( name, "doublecharwise" ) )
		bDoubleCharwise=1;
	if( !strcmp( name, "spacefix" ) )
		bSpacefix=1;
	if( !strcmp( name, "skipspace" ) )
		bSkipSpace=1;
	if( !strcmp( name, "no_k_ins" ) )
		flag_no_K_insert=1;
}

extern "C" void fontmatchuse( char* name )
{
	strcpy_s( fontmatchus, 512, name );
	if( !strcmp(fontmatchus,"auto" ) )
	{
		for( int s=0;s<nStyle;s++ )
		{
			if( !strcmp( StyleNames[s], style) )
			{
				sprintf_s( fontmatchus, 512, "%d,%d,%d,%s", StyleSizes[s],StyleItalic[s],400+600*StyleBold[s],StyleFonts[s] );
				break;
			}
		}
	}
}

char *getStyleColorPtr( int w )
{
	char stylesrch[512];
	strcpy_s( stylesrch, 512,style );
	for( int s=0;s<nStyle;s++ )
	{
		if( !strcmp( StyleNames[s], stylesrch) )
		{
			if( w==1 )return StyleColor1[s];
			if( w==2 )return StyleColor2[s];
			if( w==3 )return StyleColor3[s];
			if( w==4 )return StyleColor4[s];
		}
	}
	return 0;
}


void print_style_item( char *name )
{
	if( !strcmp(name,"style") )
		fprintf( foutt, "%s", style );
	else
	{
		char stylesrch[512];
		strcpy_s( stylesrch, 512,style );
		if( strstr(name,"." ) )
		{
			strcpy_s( stylesrch, 512, strstr(name,"." )+1 );
			strstr(name,"." )[0]=0;
		}
		for( int s=0;s<nStyle;s++ )
		{
			if( !strcmp( StyleNames[s], stylesrch) )
			{
				if( !strcmp(name,"stylecolor1") )
					fprintf( foutt, "%s", StyleColor1[s] );
				if( !strcmp(name,"stylecolor2") )
					fprintf( foutt, "%s", StyleColor2[s] );
				if( !strcmp(name,"stylecolor3") )
					fprintf( foutt, "%s", StyleColor3[s] );
				if( !strcmp(name,"stylecolor4") )
					fprintf( foutt, "%s", StyleColor4[s] );
				if( !strcmp(name,"stylesize") )
					fprintf( foutt, "%d", StyleSizes[s] );
				if( !strcmp(name,"stylecolor1@") )
					ColoringAt(0);
				if( !strcmp(name,"stylecolor2@") )
					ColoringAt(1);
				if( !strcmp(name,"stylecolor3@") )
					ColoringAt(2);
				if( !strcmp(name,"stylecolor4@") )
					ColoringAt(3);
				break;
			}
		}
	}
}




#include "windows.h"
#include <locale.h>
#include <mbctype.h>

LOGFONT lfi;

int __stdcall CALLBACK EnumFontFamProc(
  const LOGFONT *lpelf,    // logical-font data
  const TEXTMETRIC *lpntm,  // physical-font data
  DWORD FontType,        // type of font
  LPARAM lParam          // application-defined data
)
{
	 lfi = *lpelf; 
	return 1;
}



long haGSDraw_sx,haGSDraw_sy;
char clrStr[]="                                                                                                                                                                  " ;
long haGSDraw( char *sizeStrSoFarins, HDC myDCUse=0, bool needBorder=0 )
{
//we need to set locale:
	int charset=ANSI_CHARSET;
	int xsc=100;
	int ysc=100;
	int st;
	for( st=0;st<nStyle;st++ )
	{
		if( !strcmp( StyleNames[st], style) )
		{
			charset = StyleEncoding[st];
			xsc=StyleXScale[st];
			ysc=StyleYScale[st];
			break;
		}
	}

	if( st==nStyle )
	{
		//no matching style
		printf( "\nno style found: %s\n", style );

		haGSDraw_sx=0;
		haGSDraw_sy=0;
		return 0;
	}
//setlocale( LC_ALL, "German" );

//	char * slr=setlocale(LC_ALL, "jpn");
//	_setmbcp( _MB_CP_LOCALE );

//	PAINTSTRUCT ps;
	long i,h, wi;
	sscanf_s( fontmatchus, "%d,%d,%d,", &h, &i, &wi );
	char *c=fontmatchus;
	while( *c!=',' )c++;c++;
	while( *c!=',' )c++;c++;
	while( *c!=',' )c++;c++;

	HDC hdc;
	if( myDCUse==0 )
		hdc = GetDC( 0 );
	else
		hdc=myDCUse;
	
	SetMapMode(hdc, MM_TEXT);

//	int hei;

//	hei = -MulDiv((int)(h+0.5), GetDeviceCaps(hdc, LOGPIXELSY), 72);


	LOGFONTA lf;

	memset(&lf, 0, sizeof(lf));

	strcpy_s( lf.lfFaceName, 32, c );

	lf.lfCharSet = charset;

	lf.lfHeight = (LONG)(h+0.5);
	lf.lfOutPrecision = OUT_TT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = ANTIALIASED_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
	lf.lfEscapement = lf.lfOrientation = 0;

	lf.lfWeight = wi;
	lf.lfItalic = (BYTE)i;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;


//	EnumFonts( hdc, c, EnumFontFamProc, 0 );
	HFONT f=CreateFontIndirectA( &lf );
	RECT r;
	r.left=0;
	r.top=0;
	r.right=0;
	r.bottom=0;
//	strcat( sizeStrSoFarins, " " );
	SelectObject( hdc, f );
		DrawTextA( hdc, clrStr, strlen(clrStr), &r, DT_CALCRECT );
		DrawTextA( hdc, clrStr, strlen(clrStr), &r, 0 );
		SIZE s;
		GetTextExtentPoint32A( hdc, sizeStrSoFarins, strlen(sizeStrSoFarins), &s);
//		DrawText( hdc, sizeStrSoFarins, strlen(sizeStrSoFarins), &r, DT_CALCRECT );
		haGSDraw_sx=(long)((s.cx)*float( (xsc-100)*1+100 )/100.f+0.5f);
		haGSDraw_sy=(long)((s.cy)*float( (ysc-100)*1+100 )/100.f+0.5f);

		r.right=r.left+s.cx;
		r.bottom=r.top+s.cy;

		if( needBorder )
		{
			SetBkMode(hdc, TRANSPARENT); 
			BeginPath(hdc); 
		}

		DrawTextA( hdc, sizeStrSoFarins, strlen(sizeStrSoFarins), &r, 0 );

		if( needBorder )
		{
			CloseFigure(hdc);
			EndPath(hdc); 
		}
/*
BeginPath(hdc); 
TextOut(hdc, r.left, r.top, sizeStrSoFarins, strlen(sizeStrSoFarins) ); 
EndPath(hdc); 
 
GetRgnBox(PathToRegion(hdc), &r );
		DrawText( hdc, sizeStrSoFarins, strlen(sizeStrSoFarins), &r, 0 );
*/
	if( myDCUse==0 )
		ReleaseDC( 0, hdc );

	DeleteObject( f );

//setlocale( LC_ALL, "English" );

	return haGSDraw_sx;
}



void haGetSiz()
{

//	nSizeThisLine=0;
	if( !strlen(fontmatchus) )
		return;
/*
	if( !strlen(sizeStrNew) )return;

	nSizeThisLine+=haGSDraw( sizeStrNew );
*/

	if( !strlen(sizeStrSoFar) )return;

	nSizeThisLine=haGSDraw( sizeStrSoFar );


//		m_width = (int)(m_style.fontScaleX/100*m_width + 4) >> 3;

//	nSizeThisLine=(int)(800/100*nSizeThisLine + 4) >> 3;


	FILE *f;
	f=0;
	fopen_s( &f, "sizetable.txt", "at" );
	fprintf( f, "|%s| : %d\n", sizeStrSoFar, nSizeThisLine );
	fclose(f);

//	getch();
}


long haGetSizThisOne()
{
	if( !strlen(fontmatchus) )
		return 0;
	if( !strlen(g_thisStr) )
		return 0;
	char tmp[4096];
	strcpy_s( tmp, 4096, g_thisStr );
	if( tmp[strlen(tmp)-1]==' ' )
		tmp[strlen(tmp)-1]=0;  //vob sub doesnt use ' ' at line end

	if( tmp[strlen(tmp)-2]==-127 && tmp[strlen(tmp)-1]==64 )
		tmp[strlen(tmp)-2]=0;  //vob sub doesnt use ' ' at line end;  \81\40 is a kanji wide ' '

	nSizeThisOne=haGSDraw( tmp );//-nSizeThisLine;
	FILE *f;
	f=0;
	fopen_s( &f, "sizetable.txt", "at" );
	fprintf( f, "|%s| -> |%s| : %d\n", g_thisStr, tmp, nSizeThisOne );
	fclose(f);
	return nSizeThisOne;
}

long haGetYSizThisOne()
{
	if( !strlen(fontmatchus) )
		return 0;
	if( !strlen(g_thisStr) )
		return 0;
	char tmp[4096];
	strcpy_s( tmp, 4096, g_thisStr );
	if( tmp[strlen(tmp)-1]==' ' )
		tmp[strlen(tmp)-1]=0;  //vob sub doesnt use ' ' at line end

	if( tmp[strlen(tmp)-2]==-127 && tmp[strlen(tmp)-1]==64 )
		tmp[strlen(tmp)-2]=0;  //vob sub doesnt use ' ' at line end;  \81\40 is a kanji wide ' '

	haGSDraw( tmp );//-nSizeThisLine;
	FILE *f;
	f=0;
	fopen_s( &f, "sizetabley.txt", "at" );
	fprintf( f, "|%s| -> |%s| : %d\n", g_thisStr, tmp, haGSDraw_sy );
	fclose(f);
	return haGSDraw_sy;
}

byte pixBuf[1024][1024];
long pixBuf_sx,pixBuf_sy;

extern "C" double get_pixbuf( double vx, double vy )
{
	int ix=(int)(vx+0.5);
	int iy=(int)(vy+0.5);

	if( !bPixbufUpToDate )
	{
		if( !strlen(fontmatchus) )
			return 0;
		if( !strlen(g_thisStr) )
			return 0;
		char tmp[4096];
		strcpy_s( tmp, 4096, g_thisStr );
		if( tmp[strlen(tmp)-1]==' ' )
			tmp[strlen(tmp)-1]=0;  //vob sub doesnt use ' ' at line end

		if( tmp[strlen(tmp)-2]==-127 && tmp[strlen(tmp)-1]==64 )
			tmp[strlen(tmp)-2]=0;  //vob sub doesnt use ' ' at line end;  \81\40 is a kanji wide ' '

		HDC hdc;
		hdc = GetDC( 0 );
		haGSDraw( tmp,hdc );
		pixBuf_sx=haGSDraw_sx;
		pixBuf_sy=haGSDraw_sy;
		for( int y=0;y<pixBuf_sy;y++ )
		{
			for( int x=0;x<pixBuf_sx;x++ )
			{
				if( GetPixel( hdc, x,y ) > 0 )
					pixBuf[x][y]=0;
				else
					pixBuf[x][y]=1;
			}
		}
		ReleaseDC( 0, hdc );

		bPixbufUpToDate=1;
	}

	if( ix<0 )return 0;
	if( iy<0 )return 0;
	if( ix>=pixBuf_sx )return 0;
	if( iy>=pixBuf_sy )return 0;

	return (double)pixBuf[ix][iy];

}





char lTextIndex[256][256]={0};

extern "C" void TextindexStore( double ind )
{
	if( ind<0 || ind>255 )return;
	strcpy_s( lTextIndex[ (int)( ind+0.5f ) ], 256, g_thisStr );
}

extern "C" void TextindexGet( double ind )
{
	if( ind<0 || ind>255 )return;
	fprintf( foutt, "%s", lTextIndex[ (int)( ind+0.5f ) ] );
}





typedef struct{
	POINT p;
	float a;
}borderSortedPt;

int borderSortFnc( const void *arg1, const void *arg2 )
{
   if( ((borderSortedPt *)arg1)->a > ((borderSortedPt *)arg2)->a )return 1;
   if( ((borderSortedPt *)arg1)->a < ((borderSortedPt *)arg2)->a )return -1;
   return 0;
}

borderSortedPt	borderLSorted[2048];
int				borderNSorted=0;

byte borderBuf[1024][1024];
long borderBuf_sx,borderBuf_sy;


#define gid(a)  (strcpy_s( name.name, sizeof(name.name), a )?get_identifier( name ):0)
#define sid(a,b)  (strcpy_s( name.name, sizeof(name.name), a )?set_identifier( name,b ):0)


double hablock( double a,  double l, double h )
{
	while( a<l )
		a+=1;
	while( a>h )
		a-=1;
	return a;
}

extern "C" void PrintBorderline( double a1, double a2 )
{
	if( !bBorderbufUpToDate )
	{
		borderNSorted=0;

		if( !strlen(fontmatchus) )
			return;
		if( !strlen(g_thisStr) )
			return;
		char tmp[4096];
		strcpy_s( tmp, 4096, g_thisStr );
		if( tmp[strlen(tmp)-1]==' ' )
			tmp[strlen(tmp)-1]=0;  //vob sub doesnt use ' ' at line end

		if( tmp[strlen(tmp)-2]==-127 && tmp[strlen(tmp)-1]==64 )
			tmp[strlen(tmp)-2]=0;  //vob sub doesnt use ' ' at line end;  \81\40 is a kanji wide ' '

		HDC hdc;
		hdc = GetDC( 0 );
		haGSDraw( tmp,hdc, 1 );
		StrokePath(hdc);
		borderBuf_sx=haGSDraw_sx;
		borderBuf_sy=haGSDraw_sy;

		for( int y=0;y<borderBuf_sy;y++ )
		{
			for( int x=0;x<borderBuf_sx;x++ )
			{
				if( GetPixel( hdc, x,y ) > 0 )
					borderBuf[x][y]=0;
				else
				{
					borderBuf[x][y]=1;
					borderLSorted[ borderNSorted ].p.x=x;
					borderLSorted[ borderNSorted ].p.y=y;
					borderLSorted[ borderNSorted ].a=(float) hablock(atan2( y-borderBuf_sy*0.5, x-borderBuf_sx*0.5 )/(2*3.1415926535897)+0.5, 0,1);
					borderNSorted++;
				}
			}
		}
		ReleaseDC( 0, hdc );

		qsort( borderLSorted, borderNSorted, sizeof(borderSortedPt), borderSortFnc );

		bBorderbufUpToDate=1;
	}

	a1=hablock( a1, 0,1 );
	a2=hablock( a2, 0,1 );

	bool bInvert=0;

	if( a1>a2 )
	{
		double t=a1;
		a1=a2;
		a2=t;
		bInvert=1;
	}

	for( int i=0;i<borderNSorted;i++ )
	{
		if( (borderLSorted[i].a>=a1 && borderLSorted[i].a<a2)!=bInvert )
		{
			calc_type name;

			fprintf( foutt, "\nDialogue: 1," );
			print_time_of( gid( "tborderpartstart" ) );
			fprintf( foutt, "," );
			print_time_of( gid( "tborderpartend" ) );
			fprintf( foutt, "," );
			print_identifier( "style" );
			fprintf( foutt, "_border,,0000,0000,0000,," );

			fprintf( foutt, "{\\fad(" );
			print_tval_of( gid( "tborderpartfadein" ) );
			fprintf( foutt, "," );
			print_tval_of( gid( "tborderpartfadeout" ) );
			fprintf( foutt, ")}" );

			int xPos=(int)gid("borderpartposx");
			int yPos=(int)gid("borderpartposy");

			int xpr=(int)( borderLSorted[ i ].p.x - gid("nsizthisone")*0.5 );
			int ypr=(int)( borderLSorted[ i ].p.y - gid("nysizthisone")*0.5 );

			int xpr2=xpr;
			int ypr2=ypr;

			xpr*=(int)gid("borderpartxsc");
			ypr*=(int)gid("borderpartysc");

			xpr+=(int)gid("borderpartxof");
			ypr+=(int)gid("borderpartyof");

			fprintf( foutt, "{\\an5\\move(" );
			print_pos_of( xPos+xpr );
			fprintf( foutt, "," );
			print_pos_of( yPos+ypr );
			fprintf( foutt, "," );
			print_pos_of( xPos+xpr2 );
			fprintf( foutt, "," );
			print_pos_of( yPos+ypr2 );
			fprintf( foutt, "," );
			print_tval_of( gid( "tborderpartmovestart" ) );
			fprintf( foutt, "," );
			print_tval_of( gid( "tborderpartmoveend" ) );
			fprintf( foutt, ")}" );

			fprintf( foutt, "{\\p2}m -1 -1 l 2 -1 2 2 -1 2 c {\\p0}" );
		}
	}
}




bool localfx_bHasPass_fnc( int num )
{
	if( num<2 )return 1;
	else return 0;
}

void localfx_CallPass_fnc( char *fnam, scan_file_fncp sffp, scan_str_fncp ssfp, calc_parse_fncp cpfp )
{
	calc_type name;

	if( !strcmp(fnam,"p0h.txt") )
	{
		fontmatchuse("auto" );
		if( !stylelock_identifier( "engsub" ) )return;
		fprintf( foutt, "\nDialogue: 1," );
		print_time_of( gid( "wtstart" ) );
		fprintf( foutt, "," );
		print_time_of( gid( "wtend" ) );
		fprintf( foutt, "," );
		print_identifier( "style" );
		fprintf( foutt, ",OP,0000,0000,0000,," );
		fprintf( foutt, "{\\fad(200,200)}" );
		fprintf( foutt, "{\\be1}" );
	}
	if( !strcmp(fnam,"p0.txt") )
	{
		if( !stylelock_identifier( "engsub" ) )return;
		print_identifier( "text" );
	}


	if( !strcmp(fnam,"p1h.txt") )
	{
		if( !stylelock_identifier( "japro" ) )return;
		bCharwise=1;
		fontmatchuse("auto" );
	}


	if( !strcmp(fnam,"p1.txt") )
	{
		if( !stylelock_identifier( "japro" ) )return;
		double curx=gid("nsiz")-gid("nsizall")*0.5+gid("nsizthisone")*0.5+320;
		double cury=45;

		sid( "curx", curx );
		sid( "cury", cury );

		fprintf( foutt, "\nDialogue: 200," );
		print_time_of( gid( "wtstart" )+(gid( "nsiz" )-gid( "nsizall" ))*0.01 );
		fprintf( foutt, "," );
		print_time_of( gid( "tstart" ) );
		fprintf( foutt, ",OP,0000,0000,0000,," );
		fprintf( foutt, "{\\fad(100,0)}" );
		fprintf( foutt, "{\\be1}" );
		fprintf( foutt, "{\\an2\\pos(" );
		print_pos_of( curx );
		fprintf( foutt, "," );
		print_pos_of( cury );
		fprintf( foutt, ")}" );
		print_identifier( "text" );

		double curtime=( ( gid("tend") - gid("tstart") ) * ( ( gid("rand")*0.2 ) + 0.8 ) ) + gid("tstart");

		fprintf( foutt, "\nDialogue: 200," );
		print_time_of( gid( "tstart" ) );
		fprintf( foutt, "," );
		print_time_of( curtime );
		fprintf( foutt, ",OP,0000,0000,0000,," );
		fprintf( foutt, "{\\be1}" );
		fprintf( foutt, "{\\an2\\pos(" );
		print_pos_of( curx );
		fprintf( foutt, "," );
		print_pos_of( cury );
		fprintf( foutt, ")}" );

		fprintf( foutt, "{\\3c&H" );
		print_identifier( "stylecolor2" );
		fprintf( foutt, "&)\\t(\\3c&H" );
		print_identifier( "stylecolor3" );
		fprintf( foutt, "&)}" );

		print_identifier( "text" );

		loop_file( "p1char.txt", 6 );

	}


	if( !strcmp(fnam,"p1char.txt") )
	{		
		double curx=gid("curx");
		double cury=gid("cury");
		double thisdur=gid("rand")*0.3;
		double nextx=curx+(((gid("rand")*10)-5)*thisdur*8);
		double nexty=cury+(thisdur*60);
		double fadeS=gid("loopvar")/6.0;
		if( fadeS<0 )fadeS=0;if(fadeS>1)fadeS=1;
		double fadeE=(gid("loopvar")+1)/6.0;
		if( fadeE<0 )fadeE=0;if(fadeE>1)fadeE=1;

		fprintf( foutt, "\nDialogue: " );
		print_pos_of( 100-gid("loopvar") );
		fprintf( foutt, "," );
		print_time_of( gid( "curtime" ) );
		fprintf( foutt, "," );
		print_time_of( gid( "curtime" )+thisdur );
		fprintf( foutt, ",OP,0000,0000,0000,," );
		fprintf( foutt, "{\\fad(100,0)}" );
		fprintf( foutt, "{\\be1}" );
		fprintf( foutt, "{\\frx180}" );

		fprintf( foutt, "{\\an2\\move(" );
		print_pos_of( curx );
		fprintf( foutt, "," );
		print_pos_of( cury );
		fprintf( foutt, "," );
		print_pos_of( nextx );
		fprintf( foutt, "," );
		print_pos_of( nexty );
		fprintf( foutt, ")}" );

		fprintf( foutt, "{\\fade(" );
		print_pos_of( fadeS*255 );
		fprintf( foutt, "," );
		print_pos_of( fadeS*255 );
		fprintf( foutt, "," );
		print_pos_of( fadeE*255 );
		fprintf( foutt, ",0,0,0," );
		print_tval_of( thisdur );
		fprintf( foutt, ")}" );

		print_identifier( "text" );

		double nct=gid("curtime")+thisdur;
		sid("curtime",nct);
		sid("curx",nextx);
		sid("cury",nexty);


	}
}

