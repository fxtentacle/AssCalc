// calc.cpp : Defines the entry point for the console application.
//


wchar_t *g_thiswcs=L"";

#include "stdafx.h"

#include "..\def_out\LexCalc.h"
#include "..\def_out\LexCalc_tab.h"
//#include "..\def_out\srcread_tab.h"
extern YYSTYPE src_lval;

extern "C" int calc_parse( );
extern "C" void calc_restart( FILE *input_file );
extern "C" void *calc__scan_wcsing( const wchar_t *wcs );

void *loc_calc__scan_wcsing( const wchar_t *wcs )
{
//	wchar_t tmp[8192];
//	wcscpy( tmp, wcs );
	FILE *f = 0;
	_wfopen_s(&f, wcs, L"rt" );
	calc_restart( f ); 
	calc_parse();
	fclose(f);
	return 0;
}

int loc_calc_parse( )
{
	return calc_parse();
}

wchar_t scrname[512]=L"";
long g_curPass=-1;
long g_curPassHeader=-1;


typedef void (__cdecl* scan_file_fncp)( FILE *input_file );
typedef void* (__cdecl* scan_wcs_fncp)( const wchar_t *wcs );
typedef int (__cdecl* calc_parse_fncp)(  );

typedef bool (__cdecl* bHasPass_fncp)( int num );
typedef void (__cdecl* CallPass_fncp)( wchar_t *fnam, scan_file_fncp sffp, scan_wcs_fncp ssfp, calc_parse_fncp cpfp );

bHasPass_fncp bHasPass=0; 
CallPass_fncp CallPass=0;

#ifdef _DEBUG
#define LOCAL_FILE
#endif


bool localfx_bHasPass_fnc( int num );
void localfx_CallPass_fnc( wchar_t *fnam, scan_file_fncp sffp, scan_wcs_fncp ssfp, calc_parse_fncp cpfp );


#ifdef LOCAL_FILE

typedef struct{
	wchar_t FName[256];
	wchar_t *wcsing;
}haCacheFile;

haCacheFile lCf[256];
int nCf=0;

	bool bHasPass_fnc( int num )
	{
		wchar_t ttmp[512];
		FILE *ff = 0;
		swprintf_s( ttmp, 512, L"p%dh.txt", num );
		_wfopen_s( &ff, ttmp, L"rt" );
		if( ff )
		{
			fclose(ff);
			return 1;
		}
		return 0;
	}

	wchar_t *GetCf( wchar_t *name )
	{
		for( int i=0;i<nCf;i++ )
		{
			if( !wcscmp( lCf[i].FName, name ) )
				return lCf[i].wcsing;
		}
		return 0;
	}

	void CallPass_fnc( wchar_t *fnam, scan_file_fncp sffp, scan_wcs_fncp ssfp, calc_parse_fncp cpfp )
	{
		wchar_t *cf=GetCf( fnam );
		if( cf )
		{
			calc__scan_wcsing( cf );
			cpfp();
		}
		else
		{
			FILE *f=0;
			_wfopen_s( &f, fnam, L"rt" );
			if( !f )return;
			fseek( f, 0, SEEK_END );
			int siz=ftell(f);
			lCf[nCf].wcsing=new wchar_t[siz+16];
			fseek(f,0,SEEK_SET);
			fread( lCf[nCf].wcsing, siz, 1, f );
			fclose(f);

			wcscpy_s( lCf[nCf].FName, 256, fnam );

//			sffp( f );
			calc__scan_wcsing( lCf[nCf].wcsing );
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
			printf( L"\n\nFX Brought to you by:\nTentacle\nFX Designed by:\nTomo-Chan\n\n\n\n" );
			bHasPass=localfx_bHasPass_fnc;
			CallPass=localfx_CallPass_fnc;
		}
	#else
		void initFuncPtr()
		{
			HMODULE hm=LoadLibrary( L"ass_effects.dll" );
			bHasPass=(bHasPass_fncp)GetProcAddress( hm, L"bHasPass" );
			CallPass=(CallPass_fncp)GetProcAddress( hm, L"CallPass" );
		}
	#endif

#endif


wchar_t lLoopFiles[256][256]={L"",};
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
		swprintf_s( scrname, 512, L"p%dh.txt", g_curPass );
	else
		swprintf_s( scrname, 512, L"p%d.txt", g_curPass );

	CallPass( scrname, calc_restart, loc_calc__scan_wcsing, loc_calc_parse );

	int i;
	for( i=0;i<nLoopFiles;i++ )
	{
		curLoopfileNum=i;
		for( int nl=0;nl<lLoopNum[i];nl++ )
		{
			for( int nl2=0;nl2<lLoopNum2[i];nl2++ )
			{
				calc_type ct;
				wcscpy_s( ct.name, 256, L"loopvar" );
				set_identifier( ct, nl );			
				
				calc_type ct2;
				wcscpy_s( ct2.name, 256, L"loopvar2" );
				set_identifier( ct2, nl2 );			
				
				swprintf_s( scrname, 512, L"%s", lLoopFiles[i] );

				CallPass( scrname, calc_restart, loc_calc__scan_wcsing, loc_calc_parse );
			}
		}
	}

	curLoopfileNum=-1;

    return i;
}

wchar_t *g_tmp;
wchar_t *g_tmp_after;
wchar_t *g_tmpHeader;
wchar_t g_tmpComplete[2048];
wchar_t g_tmpNoComment[2048];

extern "C" wchar_t *calc_text;
extern "C" int calc_error(wchar_t* errwcs) {
        printf(L"\n\n-= outError: %s\n-= in file: %s\n-= at:%s", errwcs,scrname, calc_text);
 		_getch();
       return 1;
}

extern "C" wchar_t *src_text;
extern "C" int src_error(wchar_t* errwcs) {
        printf(L"\n\n-= inError: %s\n-= at:%s\n-= line:%s", errwcs,src_text,g_tmp);
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
wchar_t lwcs[2048];
wchar_t wcs[2048];
wchar_t style[128];
wchar_t commentwcs[128];

wchar_t sizewcsSoFar[4096]=L"";
#include <stdlib.h>

extern "C" void rand_ins( wchar_t* name, double t )
{
	int mr=wcslen( name );
	int ll=(int)(t+0.5);
	wchar_t tmp[4096];
	for( int i=0;i<ll;i++ )
	{
		tmp[i]=name[rand()%mr];
	}
}

extern "C" void loop_file( wchar_t* name, double t, double t2=1 )
{
	wcscpy_s( lLoopFiles[nLoopFiles], 256, name );
	lLoopNum[nLoopFiles]=(int)(t+0.5);
	lLoopNum2[nLoopFiles]=(int)(t2+0.5);
	nLoopFiles++;
}

void print_style_item( wchar_t *name );

extern "C" void print_identifier( wchar_t* name )
{
	if( name[wcslen(name)-1]=='\n' )
		name[wcslen(name)-1]=0;
	if( !wcscmp(name,L"text") )
		fwprintf( foutt, L"%s", g_thiswcs );
	if( !wcscmp(name,L"text_reks") )
	{
		wchar_t tmp[4096];
		wcscpy_s( tmp, 4096, g_thiswcs );
		if( tmp[wcslen(tmp)-1]==' ' )
			tmp[wcslen(tmp)-1]=0;  //vob sub doesnt use ' ' at line end

		if( tmp[wcslen(tmp)-2]==-127 && tmp[wcslen(tmp)-1]==64 )
			tmp[wcslen(tmp)-2]=0;  //vob sub doesnt use ' ' at line end;  \81\40 is a kanji wide ' '

		fwprintf( foutt, L"%s", tmp );
	}
	if( !wcscmp( name, L"comment_wcs" ) )
		fwprintf( foutt, L"%s", commentwcs );

	if( !wcscmp(name,L"textsofar") )
		fwprintf( foutt, L"%s", sizewcsSoFar );
	if( !wcscmp(name,L"textafter") )
		fwprintf( foutt, L"%s", g_tmp_after );

	if( !wcscmp(name,L"text_copy") )
		fwprintf( foutt, L"%s", g_tmp );
	if( !wcscmp(name,L"text_all") )
	{
		fwprintf( foutt, L"%s", g_tmpNoComment );
	}
	if( !wcscmp(name,L"header_copy") )
		fwprintf( foutt, L"%s", g_tmpHeader );
	if( !wcscmp(name,L"complete_copy") )
		fwprintf( foutt, L"%s", g_tmpComplete );

	if( !wcsncmp( name, L"style", 5 ) )
		print_style_item( name );
}


extern "C" double get_identifier( calc_type name );


double lHSV_Color[4][256][3];
double lHSV_Time[4][256][2];
int nHSV_CT[4];

wchar_t *getStyleColorPtr( int which );

int ColoringAt( int sc, bool bor=0, double or=0 )
{
	if( nHSV_CT[sc]==0 )
	{
		fwprintf( foutt, L"%s", getStyleColorPtr(sc+1) );
		return -1;
	}

	calc_type n;
	wcscpy_s( n.name, 2048, L"fetchtime" );
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
	fwprintf( foutt, L"%6.6X", c );

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
	fwprintf( foutt, L"%6.6X", c );
}

extern "C" void ColoringOff( double scd, double off )
{
	int sc=(int)(scd+0.5);

	sc--;

	fwprintf( foutt, L"{\\%dc&H",sc+1 );
	int si=ColoringAt(sc,1,off);
	fwprintf( foutt, L"&}" );

	if( si==nHSV_CT[sc]-1 )
	{
		if( nHSV_CT[sc]==0 || lHSV_Time[sc][si][1]<off )
			return; //no more color fx
	}

	if( off<lHSV_Time[sc][si][1] )
	{

	//t to end of current block
		fwprintf( foutt, L"{\\t(0,%d,\\%dc&H", (long)(1000*(lHSV_Time[sc][si][1]-off)), sc+1 );
		WriteCAt( sc, si );
		fwprintf( foutt, L"&)}" );
	}

	si++;

	for( si;si<nHSV_CT[sc];si++ )
	{
		fwprintf( foutt, L"{\\t(%d,%d,\\%dc&H",  (long)(1000*(lHSV_Time[sc][si][0]-off)), (long)(1000*(lHSV_Time[sc][si][1]-off)), sc+1 );
		WriteCAt( sc, si );
		fwprintf( foutt, L"&)}" );
	}
}


void GenCKey( wchar_t *txt, double t1, double t2, int which=1 )
{
	long i;
	DWORD c;
	if( swscanf_s( txt, L"%dc&H%x&", &i, &c )!=2 )
	{
		swscanf_s( txt, L"%x", &c );
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

extern "C" void CheckComment( wchar_t *txt )
{
	if( txt[1]=='%' )
	{
		if( txt[2]=='%' )
		{
			wchar_t tre[2048];
			wcscpy_s( tre, 2048, txt+3 );
			if( tre[wcslen(tre)-1]=='}' )tre[wcslen(tre)-1]=0;
			wcscat_s( tre, 2048, L"\n" );
			calc__scan_wcsing( tre );
			calc_parse( );
		}
		else
		{
			wcscpy_s( commentwcs, 128, txt );
			wcscpy_s( commentwcs+1, 127, commentwcs+2 );
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
			if( wcswcs( txt+2, L"\\" )[2]=='c' )
			{
				long nn;
				swscanf_s( wcswcs( txt+2, L"\\" )+1, L"%d", &nn );
				if( nHSV_CT[nn-1]==0 )
				{
					GenCKey( getStyleColorPtr(nn), -1, -1, nn );
				}

				long l1,l2;
				swscanf_s( txt+4, L"%d,%d,", &l1, &l2 );
				
				GenCKey( wcswcs( txt+2, L"\\" )+1, ((double)l1)*0.001, ((double)l2)*0.001 );
			}
		}
		if( txt[2]=='m' && txt[3]=='o' && txt[4]=='v' && txt[5]=='e' )
		{
			long x,y;
			swscanf_s( txt, L"{\\move(%d,%d", &x, &y );
			calc_type nam;
			wcscpy_s( nam.name, 2048, L"scriptposx" );
			set_identifier( nam, x );
			wcscpy_s( nam.name, 2048, L"scriptposy" );
			set_identifier( nam, y );
		}
		if( txt[2]=='p' && txt[3]=='o' && txt[4]=='s' )
		{
			long x,y;
			swscanf_s( txt, L"{\\pos(%d,%d", &x, &y );
			calc_type nam;
			wcscpy_s( nam.name, 2048, L"scriptposx" );
			set_identifier( nam, x );
			wcscpy_s( nam.name, 2048, L"scriptposy" );
			set_identifier( nam, y );
		}
	}
}


extern "C" int textlock_identifier( wchar_t* name )
{
	if( name[wcslen(name)-1]=='\n' )name[wcslen(name)-1]=0;
	if( !wcscmp(name,g_thiswcs) )
		return 1;
	if( g_thiswcs[0]==0 )
	{
		if( wcswcs( g_tmp, name ) )
			return 1;
	}
	return 0;
}

extern "C" int textfind_identifier( wchar_t* name )
{
	if( name[wcslen(name)-1]=='\n' )name[wcslen(name)-1]=0;
	if( wcswcs( g_tmp, name ) )
		return 1;
	return 0;
}

extern "C" int stylelock_identifier( wchar_t* name )
{
	if( name[wcslen(name)-1]=='\n' )name[wcslen(name)-1]=0;
	if( wcswcs( style, name ) )
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
	fwprintf( foutt, L"%01.0f:%02.0f:%2.2f", t1,t2,t3 );
}

extern "C" void print_pos_of( double t )
{
	int i=(int)(t+0.5);
	fwprintf( foutt, L"%d", i );
}

extern "C" void print_char_of( double t )
{
	int i=(int)(t+0.5);
	fwprintf( foutt, L"%c", i );
}

extern "C" void print_hex_of( double t )
{
	int i=(int)(t+0.5);
	fwprintf( foutt, L"%x", i );
}

extern "C" void print_color_of( double t )
{
	int i=(int)(t+0.5);
	fwprintf( foutt, L"%6.6x", i );
}

extern "C" void print_tval_of( double t )
{
	int i=(int)(t*1000+0.5);
	fwprintf( foutt, L"%d", i );
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
wchar_t lAVarN[256][256];
hAVar	lAVarV[256];
int		nAVar=0;

extern "C" double get_identifier_arr( calc_type name, double ind )
{
	for( int i=0;i< nAVar;i++ )
	{
		if( !wcscmp( lAVarN[i], name.name ) )
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
		if( !wcscmp( lAVarN[i], name.name ) )
		{
			lAVarV[i].Set( (int)(ind+0.5), v );
			return;
		}
	}
	lAVarV[i].Set( (int)(ind+0.5), v );
	wcscpy_s( lAVarN[nAVar], 256, name.name );
	nAVar++;
}

extern "C" double find_index_arr( calc_type name, double vx )
{
	hAVar *cv=0;
	for( int i=0;i< nAVar;i++ )
	{
		if( !wcscmp( lAVarN[i], name.name ) )
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


wchar_t lVarN[256][256];
double	lVarV[256];
int		nVar=0;

extern "C" double get_identifier( calc_type name )
{
	if( !wcscmp(name.name,L"ntstart") )return times[0];
	if( !wcscmp(name.name,L"ntend") )return times[1];

	if( !wcscmp(name.name,L"tstart") )return ltimes[0];
	if( !wcscmp(name.name,L"tend") )return ltimes[1];

	if( !wcscmp(name.name,L"ltstart") )return ltimes2[0];
	if( !wcscmp(name.name,L"ltend") )return ltimes2[1];

	if( !wcscmp(name.name,L"wtstart") )return wtimes[0];
	if( !wcscmp(name.name,L"wtend") )return wtimes[1];

	if( !wcscmp(name.name,L"nth") )return nthThisLine;
	if( !wcscmp(name.name,L"nthall") )return nthThisLineAll;

	if( !wcscmp(name.name,L"nchr") )return nChrThisLine;
	if( !wcscmp(name.name,L"nchrall") )return nChrThisLineAll;

	if( !wcscmp(name.name,L"nsiz") )return nSizeThisLine;
	if( !wcscmp(name.name,L"lnsiz") )return lnSizeThisLine;
	if( !wcscmp(name.name,L"nsizthisone") )return haGetSizThisOne();
	if( !wcscmp(name.name,L"nysizthisone") )return haGetYSizThisOne();
	if( !wcscmp(name.name,L"nsizall") )return nSizeThisLineAll;

	if( !wcscmp(name.name,L"bfirstone") )return bFirstOne;
	if( !wcscmp(name.name,L"blastone") )return bLastOne;

	if( !wcscmp(name.name,L"bsylf") )return bSylF;

	if( !wcscmp(name.name,L"nafterlastspace") )return nAfterLastSpace;
	if( !wcscmp(name.name,L"bwordf") )return bWordF;
	if( !wcscmp(name.name,L"bwordl") )return bWordL;
	if( !wcscmp(name.name,L"nthword") )return nthWord;

	if( !wcscmp(name.name,L"rand") )return get_rand();

	for( int i=0;i< nVar;i++ )
	{
		if( !wcscmp( lVarN[i], name.name ) )
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
		if( !wcscmp( lVarN[i], name.name ) )
		{
			lVarV[i]=v;
			return;
		}
	}
	lVarV[nVar]=v;
	wcscpy_s( lVarN[nVar], 256, name.name );
	nVar++;
}


extern "C" int src_parse( );
extern "C" void src__scan_wcsing( wchar_t *input );

extern "C" void DoIt1( double t1, double t2 );
extern "C" void DoIt2( double t1 );
extern "C" void DoIt3( wchar_t *txt );

wchar_t fontmatchus[512];
wchar_t textEncoding[512];
bool bHasBeenDone;
void haGetSiz();

bool bCharwise=0;
bool bDoubleCharwise=0;
bool bSpacefix=0;
bool bSkipSpace=0;

void ParseStyle( wchar_t *tmp );


wchar_t headerMEMFile[16384];
int nFilesSplit=0;

void DoIt3Real();

extern wchar_t *asciiArt;
extern wchar_t *asciiArt2;

int main( int argc, wchar_t *argv[ ] )
{
	initFuncPtr();

	printf( L"ASS Scripter   -   (c) 2004 Hajo Krabbenhoeft aka Tentacle\n" );
	printf( L"2011 modified by Hajo Krabbenhoeft for OutlawJonas\n" );
	printf( L"%s\n", asciiArt );
	printf( L"\nFree to use, no guarantees and do not modify or bug me about it\nUsage:\n Get a .ass script with only {\\K}'s or Comments in it (no effects) \n and drag it on proggy\n");

	
	FILE *f=0;

#ifndef LOCAL_FILE
	wchar_t tttrtr[512];
	GetModuleFileName( 0, tttrtr, 510 );
	int tt=wcslen(tttrtr)-1;
	while( tttrtr[tt]!='\\' && tttrtr[tt]!='/' && tt>=0 )tt--;
	tttrtr[tt]=0;
	SetCurrentDirectory( tttrtr );
#endif

	if( argv&&argv[0]&&argv[1] )
	{
		f = 0;
		if( argc >= 4 )
			_wfopen_s( &f, argv[4], L"rt" );
		else if( argc >= 2 )
			_wfopen_s( &f, argv[2], L"rt" );
		if( !f )
			_wfopen_s( &f, argv[1], L"rt" );
	}
	if( !f )
		_wfopen_s( &f, L"src.txt", L"rt" );

	bool bSplit=0;

	if( argc >= 2 && !wcscmp( argv[1], L"split" ) )
		bSplit=1;

	if( argc >= 4 && !wcscmp( argv[2], L"encoding" ) ) {
		wcscpy_s(textEncoding, 512, argv[3]);
	} else wcscpy_s(textEncoding, 512, L"UTF8");

	FILE *addfile=0;

	if( bSplit )
	{
		foutt=0;
		_wfopen_s( &foutt,  L"out_000.ass", L"wt" );
		nFilesSplit=1;

		addfile=0;
		_wfopen_s( &addfile, L"addfile.vcf", L"wt" );
		fwprintf( addfile, L"VirtualDub.video.filters.Clear();\n" );
		fwprintf( addfile, L"VirtualDub.video.filters.Add(\"TextSub 2.23\");\n" );
		fwprintf( addfile, L"VirtualDub.video.filters.instance[%d].Config(\"out_%3.3d.ass\", 1, \"25.00000\");\n",0,0 );
	}
	else
	{
		foutt=0;
		_wfopen_s( &foutt, L"out.ass", L"wt" );
	}
	
	if( !f )
	{
		printf( L"No input file." );
		_getch();
		return -1;
	}
	while(!feof(f) )
	{
		if( bSplit && ftell(foutt)>1024*1024*3 )
		{
			fclose(foutt);

			wchar_t tmp[4096];
			swprintf_s( tmp, 4096, L"out_%3.3d.ass", nFilesSplit );
			foutt=0;
			_wfopen_s( &foutt, tmp, L"wt" );

			fwprintf( addfile, L"VirtualDub.video.filters.Add(\"TextSub 2.23\");\n" );
			fwprintf( addfile, L"VirtualDub.video.filters.instance[%d].Config(\"out_%3.3d.ass\", 1, \"25.00000\");\n",nFilesSplit,nFilesSplit );

			fputs( headerMEMFile, foutt );

			nFilesSplit++;
		}

		wchar_t readtmp[4096];
		wchar_t tmp[4096];
		if( !fgets( readtmp, 4096, f ) )break;
		MultiByteToWideChar(CP_UTF8, 0, readtmp, 4096, tmp, 4096);

		if( !wcsncmp( tmp, L"Style: ", 7 ) )
		{
			wchar_t tmp2[4096];
			wcscpy_s( tmp2, 4096, tmp );
			ParseStyle( tmp2 );
		}
		
		wcscpy_s(g_tmpComplete, 2048,tmp);
		g_tmpHeader=tmp;
		if( !wcsncmp( tmp, L"Dialogue:", 9 ) )
		{//Dialogue: 1,0:00:38.53,0:00:41.62,OpKHM,OP,0000,0000,0000,,bla 
			double t1,t2,t3, v1, v2; 
			wchar_t *c=tmp+10;
			do{ c++; }while( c[-1]!=',' );
			swscanf_s( c, L"%lf:%lf:%lf", &t1,&t2,&t3 ); 
			v1=t3+t2*60+t1*60*60;
			do{ c++; }while( c[-1]!=',' );
			swscanf_s( c, L"%lf:%lf:%lf", &t1,&t2,&t3 ); 
			v2=t3+t2*60+t1*60*60;
			do{ c++; }while( c[-1]!=',' );
			wchar_t *c2=c;
			do{ c++; }while( c[0]!=',' );
			c[0]=0;
			c++;
			wcscpy_s( style, 128, c2 );
			do{ c++; }while( c[-1]!=',' );
			do{ c++; }while( c[-1]!=',' );
			do{ c++; }while( c[-1]!=',' );
			do{ c++; }while( c[-1]!=',' );
			do{ c++; }while( c[-1]!=',' );
			c[wcslen(c)-1]=0;
			g_tmp=c;

			g_tmpNoComment[0]=0;
			int ll=wcslen(g_tmp);
			int cpos=0,cpos2;
			while( cpos<ll && cpos>=0 )
			{
				cpos2=wcswcs(g_tmp+cpos,L"{")-g_tmp;
				if( cpos2<0 )
				{
				//	cpos=cpos2;
					break;
				}
				wcsncat_s(g_tmpNoComment, 2048,g_tmp+cpos,cpos2-cpos);
				cpos=wcswcs(g_tmp+cpos2,L"}")-g_tmp+1;
			}
			if( cpos>=0 )
				wcscat_s(g_tmpNoComment, 2048,g_tmp+cpos);

			DoIt1( v1,v2 );
		//	printf( L"%s\n", c );
			printf( L"." );
			nthThisLineAll=0;
			nChrThisLineAll=0;
			nSizeThisLineAll=0;
			lnSizeThisLine=0;
			fontmatchus[0]=0;
			commentwcs[0]=0;
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
					//sprintf( scrname, L"p%d.txt", i );
					src__scan_wcsing( c );
					if( src_parse() )return -2;

					bLastOne=1;
					wcscpy_s( lwcs, 2048, wcs );
					DoIt2( 0 );
					DoIt3Real();
				}else break;
				nthThisLineAll=nthThisLine;
				nChrThisLineAll=nChrThisLine;
				nSizeThisLineAll=nSizeThisLine;
			}
		}else
		{
			if( wcsncmp( tmp, L"Comment:", 8 ) )
			{
				fputs( tmp, foutt );
				wcscat_s( headerMEMFile, 16384, tmp );
				wcscat_s( headerMEMFile, 16384, L"\n" );
			}
		}
	}
	fclose(f);

	f=0;
	_wfopen_s( &f, L"incbin.txt", L"rt" );
	if(f)
	{
		while(!feof(f) )
		{
			wchar_t tmp[4096];
			if( !fgets( tmp, 4096, f ) )break;
			fputs( tmp, foutt );
		}
	}

	fclose(foutt);

	if( addfile )
		fclose(addfile);

	printf( L"\n\nDone.\n");
	_getch();
	return 1;
}


bool bFirstSet;
bool bFirstCall;
extern "C" void DoIt1( double t1, double t2 )
{
	lwcs[0]=0;
	wcs[0]=0;
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
	sizewcsSoFar[0]=0;
}

extern "C" void DoIt2( double t1 )
{

	if( !bHasBeenDone )
		DoIt3(L"");

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

wchar_t sizewcsNew[256];

bool flag_no_K_insert=0;

void DoIt3Work( wchar_t *txt )
{
	bPixbufUpToDate=0;
	bBorderbufUpToDate=0;
	g_thiswcs=txt;

	if( wcslen( txt ) )
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
				fwprintf( foutt, L"{\\k");
				print_tval_of( (ltimes[1]-ltimes[0])*0.1 );
				fwprintf( foutt, L"}");
			}
		}
	}
	nChrThisLine+=wcslen( txt );
	wcscat_s( sizewcsSoFar, 4096, txt );
	wcscpy_s( sizewcsNew, 256, txt );
	lnSizeThisLine=nSizeThisLine;
	haGetSiz();
}


void DoIt3Real()
{

	int l=wcslen( lwcs );

	if( l>0 )
	{
		bWordF=bWordL;
		bWordL=0;
	}

	for( int i=0;i<l;i++ )
	{
		if( lwcs[i]==' ' )
		{
			nAfterLastSpace=0;
			bWordL=1;
		}
	}

	g_tmp_after=wcswcs(g_tmp,lwcs)+wcslen(lwcs);
	if( !bCharwise && !bDoubleCharwise )
		DoIt3Work( lwcs );
	else
	{
		int templ=bWordL;

		int l=wcslen( lwcs );
		for( int i=0;i<l;i+=(bDoubleCharwise+1) )
		{
			if( lwcs[i]=='\\' && (lwcs[i+1]=='n' || lwcs[i+1]=='N') )
			{
				wcscat_s( sizewcsSoFar, 4096, L"\\n" );
				i+=1-bDoubleCharwise;
				continue;
			}
			wchar_t tmp[4]={0,};
			tmp[0]=lwcs[i];
			if( bDoubleCharwise && tmp[0]!=' ' )
				tmp[1]=lwcs[i+1];

			g_tmp_after=wcswcs(g_tmp,lwcs)+i+1;

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

			bWordF=0; //after first wchar_t this isnt first animore
		}
	}
	nAfterLastSpace++;
	nthThisLine++;
	
	if( l>0 )
		bFirstOne=0;

	if( bWordL )nthWord++;
}


extern "C" void DoIt3( wchar_t *txt )
{
	bHasBeenDone=1;

	wcscpy_s( lwcs, 2048, wcs );
	wcscpy_s( wcs, 2048, txt );
	if( !bFirstCall )DoIt3Real();
	else bFirstCall=0;
}


wchar_t StyleNames[512][512];
wchar_t StyleFonts[512][512];

wchar_t StyleColor1[512][512];
wchar_t StyleColor2[512][512];
wchar_t StyleColor3[512][512];
wchar_t StyleColor4[512][512];

long StyleSizes[512];
long StyleBold[512];
long StyleItalic[512];
long StyleXScale[512];
long StyleYScale[512];
long StyleEncoding[512];
int nStyle=0;

//Format: Name, Fontname, Fontsize, PrimaryColour, SecondaryColour, OutlineColour, BackColour, Bold, Italic, Underline, wcsikeOut, ScaleX, ScaleY, Spacing, Angle, BorderStyle, Outline, Shadow, Alignment, MarginL, MarginR, MarginV, Encoding
void ParseStyle( wchar_t *tmp )
{
	wchar_t *c=tmp;
	wchar_t *n=tmp;
	while( n[0]!=' ' )n++;
	n[0]=0;
	n++;
	c=n;
	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	wcscpy_s( StyleNames[nStyle], 512, c );
	c=n;
	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	wcscpy_s( StyleFonts[nStyle],512, c );
	c=n;
	swscanf_s( c, L"%d", &StyleSizes[nStyle] );

	while( n[0]!=',' )n++;
	n++;
	c=n;

	wchar_t ttt[256];

	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	wcscpy_s( ttt, 256, c );
	c=n;
	wcscpy_s( StyleColor1[nStyle], 512, ttt+4 ); //&H00

	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	wcscpy_s( ttt, 256, c );
	c=n;
	wcscpy_s( StyleColor2[nStyle], 512, ttt+4 ); //&H00

	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	wcscpy_s( ttt, 256, c );
	c=n;
	wcscpy_s( StyleColor3[nStyle],512, ttt+4 ); //&H00

	while( n[0]!=',' )n++;
	n[0]=0;
	n++;
	wcscpy_s( ttt, 256, c );
	c=n;
	wcscpy_s( StyleColor4[nStyle],512, ttt+4 ); //&H00


	swscanf_s( c, L"%d", &StyleBold[nStyle] );
	if( StyleBold[nStyle] )StyleBold[nStyle]=1;

	while( n[0]!=',' )n++;
	n++;
	c=n;
	swscanf_s( c, L"%d", &StyleItalic[nStyle] );
	if( StyleItalic[nStyle] )StyleItalic[nStyle]=1;

	for( int i=0;i<3;i++ )
	{
		while( n[0]!=',' )n++;
		n++;
	}
	c=n;
	swscanf_s( c, L"%d", &StyleXScale[nStyle] );

	while( n[0]!=',' )n++;
	n++;

	c=n;
	swscanf_s( c, L"%d", &StyleYScale[nStyle] );

	for( int i=0;i<10;i++ )
	{
		while( n[0]!=',' )n++;
		n++;
	}
	c=n;
	swscanf_s( c, L"%d", &StyleEncoding[nStyle] );
	
	nStyle++;
}

extern "C" void set_flag( wchar_t* name )
{
	if( !wcscmp( name, L"charwise" ) )
		bCharwise=1;
	if( !wcscmp( name, L"doublecharwise" ) )
		bDoubleCharwise=1;
	if( !wcscmp( name, L"spacefix" ) )
		bSpacefix=1;
	if( !wcscmp( name, L"skipspace" ) )
		bSkipSpace=1;
	if( !wcscmp( name, L"no_k_ins" ) )
		flag_no_K_insert=1;
}

extern "C" void use_encoding( wchar_t* name )
{
	wcscpy_s( textEncoding, 512, name );
}

extern "C" void fontmatchuse( wchar_t* name )
{
	wcscpy_s( fontmatchus, 512, name );
	if( !wcscmp(fontmatchus,L"auto" ) )
	{
		for( int s=0;s<nStyle;s++ )
		{
			if( !wcscmp( StyleNames[s], style) )
			{
				swprintf_s( fontmatchus, 512, L"%d,%d,%d,%s", StyleSizes[s],StyleItalic[s],400+600*StyleBold[s],StyleFonts[s] );
				break;
			}
		}
	}
}

wchar_t *getStyleColorPtr( int w )
{
	wchar_t stylesrch[512];
	wcscpy_s( stylesrch, 512,style );
	for( int s=0;s<nStyle;s++ )
	{
		if( !wcscmp( StyleNames[s], stylesrch) )
		{
			if( w==1 )return StyleColor1[s];
			if( w==2 )return StyleColor2[s];
			if( w==3 )return StyleColor3[s];
			if( w==4 )return StyleColor4[s];
		}
	}
	return 0;
}


void print_style_item( wchar_t *name )
{
	if( !wcscmp(name,L"style") )
		fwprintf( foutt, L"%s", style );
	else
	{
		wchar_t stylesrch[512];
		wcscpy_s( stylesrch, 512,style );
		if( wcswcs(name,L"." ) )
		{
			wcscpy_s( stylesrch, 512, wcswcs(name,L"." )+1 );
			wcswcs(name,L"." )[0]=0;
		}
		for( int s=0;s<nStyle;s++ )
		{
			if( !wcscmp( StyleNames[s], stylesrch) )
			{
				if( !wcscmp(name,L"stylecolor1") )
					fwprintf( foutt, L"%s", StyleColor1[s] );
				if( !wcscmp(name,L"stylecolor2") )
					fwprintf( foutt, L"%s", StyleColor2[s] );
				if( !wcscmp(name,L"stylecolor3") )
					fwprintf( foutt, L"%s", StyleColor3[s] );
				if( !wcscmp(name,L"stylecolor4") )
					fwprintf( foutt, L"%s", StyleColor4[s] );
				if( !wcscmp(name,L"stylesize") )
					fwprintf( foutt, L"%d", StyleSizes[s] );
				if( !wcscmp(name,L"stylecolor1@") )
					ColoringAt(0);
				if( !wcscmp(name,L"stylecolor2@") )
					ColoringAt(1);
				if( !wcscmp(name,L"stylecolor3@") )
					ColoringAt(2);
				if( !wcscmp(name,L"stylecolor4@") )
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
wchar_t clrwcs[]="                                                                                                                                                                  " ;
long haGSDraw( wchar_t *sizewcsSoFarins, HDC myDCUse=0, bool needBorder=0 )
{
//we need to set locale:
	int charset=ANSI_CHARSET;
	int xsc=100;
	int ysc=100;
	int st;
	for( st=0;st<nStyle;st++ )
	{
		if( !wcscmp( StyleNames[st], style) )
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
		printf( L"\nno style found: %s\n", style );

		haGSDraw_sx=0;
		haGSDraw_sy=0;
		return 0;
	}
//setlocale( LC_ALL, "German" );

//	wchar_t * slr=setlocale(LC_ALL, "jpn");
//	_setmbcp( _MB_CP_LOCALE );

//	PAINTstruct ps;
	long i,h, wi;
	swscanf_s( fontmatchus, L"%d,%d,%d,", &h, &i, &wi );
	wchar_t *c=fontmatchus;
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

	wcscpy_s( lf.lfFaceName, 32, c );

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
	lf.lfwcsikeOut = 0;


//	EnumFonts( hdc, c, EnumFontFamProc, 0 );
	HFONT f=CreateFontIndirectA( &lf );
	RECT r;
	r.left=0;
	r.top=0;
	r.right=0;
	r.bottom=0;
//	wcscat( sizewcsSoFarins, L" " );
	SelectObject( hdc, f );
		DrawTextA( hdc, clrwcs, wcslen(clrwcs), &r, DT_CALCRECT );
		DrawTextA( hdc, clrwcs, wcslen(clrwcs), &r, 0 );
		SIZE s;
		GetTextExtentPoint32A( hdc, sizewcsSoFarins, wcslen(sizewcsSoFarins), &s);
//		DrawText( hdc, sizewcsSoFarins, wcslen(sizewcsSoFarins), &r, DT_CALCRECT );
		haGSDraw_sx=(long)((s.cx)*float( (xsc-100)*1+100 )/100.f+0.5f);
		haGSDraw_sy=(long)((s.cy)*float( (ysc-100)*1+100 )/100.f+0.5f);

		r.right=r.left+s.cx;
		r.bottom=r.top+s.cy;

		if( needBorder )
		{
			SetBkMode(hdc, TRANSPARENT); 
			BeginPath(hdc); 
		}

		DrawTextA( hdc, sizewcsSoFarins, wcslen(sizewcsSoFarins), &r, 0 );

		if( needBorder )
		{
			CloseFigure(hdc);
			EndPath(hdc); 
		}
/*
BeginPath(hdc); 
TextOut(hdc, r.left, r.top, sizewcsSoFarins, wcslen(sizewcsSoFarins) ); 
EndPath(hdc); 
 
GetRgnBox(PathToRegion(hdc), &r );
		DrawText( hdc, sizewcsSoFarins, wcslen(sizewcsSoFarins), &r, 0 );
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
	if( !wcslen(fontmatchus) )
		return;
/*
	if( !wcslen(sizewcsNew) )return;

	nSizeThisLine+=haGSDraw( sizewcsNew );
*/

	if( !wcslen(sizewcsSoFar) )return;

	nSizeThisLine=haGSDraw( sizewcsSoFar );


//		m_width = (int)(m_style.fontScaleX/100*m_width + 4) >> 3;

//	nSizeThisLine=(int)(800/100*nSizeThisLine + 4) >> 3;


	FILE *f;
	f=0;
	_wfopen_s( &f, L"sizetable.txt", L"at" );
	fwprintf( f, L"|%s| : %d\n", sizewcsSoFar, nSizeThisLine );
	fclose(f);

//	getch();
}


long haGetSizThisOne()
{
	if( !wcslen(fontmatchus) )
		return 0;
	if( !wcslen(g_thiswcs) )
		return 0;
	wchar_t tmp[4096];
	wcscpy_s( tmp, 4096, g_thiswcs );
	if( tmp[wcslen(tmp)-1]==' ' )
		tmp[wcslen(tmp)-1]=0;  //vob sub doesnt use ' ' at line end

	if( tmp[wcslen(tmp)-2]==-127 && tmp[wcslen(tmp)-1]==64 )
		tmp[wcslen(tmp)-2]=0;  //vob sub doesnt use ' ' at line end;  \81\40 is a kanji wide ' '

	nSizeThisOne=haGSDraw( tmp );//-nSizeThisLine;
	FILE *f;
	f=0;
	_wfopen_s( &f, L"sizetable.txt", L"at" );
	fwprintf( f, L"|%s| -> |%s| : %d\n", g_thiswcs, tmp, nSizeThisOne );
	fclose(f);
	return nSizeThisOne;
}

long haGetYSizThisOne()
{
	if( !wcslen(fontmatchus) )
		return 0;
	if( !wcslen(g_thiswcs) )
		return 0;
	wchar_t tmp[4096];
	wcscpy_s( tmp, 4096, g_thiswcs );
	if( tmp[wcslen(tmp)-1]==' ' )
		tmp[wcslen(tmp)-1]=0;  //vob sub doesnt use ' ' at line end

	if( tmp[wcslen(tmp)-2]==-127 && tmp[wcslen(tmp)-1]==64 )
		tmp[wcslen(tmp)-2]=0;  //vob sub doesnt use ' ' at line end;  \81\40 is a kanji wide ' '

	haGSDraw( tmp );//-nSizeThisLine;
	FILE *f;
	f=0;
	_wfopen_s( &f, L"sizetabley.txt", L"at" );
	fwprintf( f, L"|%s| -> |%s| : %d\n", g_thiswcs, tmp, haGSDraw_sy );
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
		if( !wcslen(fontmatchus) )
			return 0;
		if( !wcslen(g_thiswcs) )
			return 0;
		wchar_t tmp[4096];
		wcscpy_s( tmp, 4096, g_thiswcs );
		if( tmp[wcslen(tmp)-1]==' ' )
			tmp[wcslen(tmp)-1]=0;  //vob sub doesnt use ' ' at line end

		if( tmp[wcslen(tmp)-2]==-127 && tmp[wcslen(tmp)-1]==64 )
			tmp[wcslen(tmp)-2]=0;  //vob sub doesnt use ' ' at line end;  \81\40 is a kanji wide ' '

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





wchar_t lTextIndex[256][256]={0};

extern "C" void TextindexStore( double ind )
{
	if( ind<0 || ind>255 )return;
	wcscpy_s( lTextIndex[ (int)( ind+0.5f ) ], 256, g_thiswcs );
}

extern "C" void TextindexGet( double ind )
{
	if( ind<0 || ind>255 )return;
	fwprintf( foutt, L"%s", lTextIndex[ (int)( ind+0.5f ) ] );
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


#define gid(a)  (wcscpy_s( name.name, sizeof(name.name), a )?get_identifier( name ):0)
#define sid(a,b)  (wcscpy_s( name.name, sizeof(name.name), a )?set_identifier( name,b ):0)


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

		if( !wcslen(fontmatchus) )
			return;
		if( !wcslen(g_thiswcs) )
			return;
		wchar_t tmp[4096];
		wcscpy_s( tmp, 4096, g_thiswcs );
		if( tmp[wcslen(tmp)-1]==' ' )
			tmp[wcslen(tmp)-1]=0;  //vob sub doesnt use ' ' at line end

		if( tmp[wcslen(tmp)-2]==-127 && tmp[wcslen(tmp)-1]==64 )
			tmp[wcslen(tmp)-2]=0;  //vob sub doesnt use ' ' at line end;  \81\40 is a kanji wide ' '

		HDC hdc;
		hdc = GetDC( 0 );
		haGSDraw( tmp,hdc, 1 );
		wcsokePath(hdc);
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

			fwprintf( foutt, L"\nDialogue: 1," );
			print_time_of( gid( L"tborderpartstart" ) );
			fwprintf( foutt, L"," );
			print_time_of( gid( L"tborderpartend" ) );
			fwprintf( foutt, L"," );
			print_identifier( L"style" );
			fwprintf( foutt, L"_border,,0000,0000,0000,," );

			fwprintf( foutt, L"{\\fad(" );
			print_tval_of( gid( L"tborderpartfadein" ) );
			fwprintf( foutt, L"," );
			print_tval_of( gid( L"tborderpartfadeout" ) );
			fwprintf( foutt, L")}" );

			int xPos=(int)gid(L"borderpartposx");
			int yPos=(int)gid(L"borderpartposy");

			int xpr=(int)( borderLSorted[ i ].p.x - gid(L"nsizthisone")*0.5 );
			int ypr=(int)( borderLSorted[ i ].p.y - gid(L"nysizthisone")*0.5 );

			int xpr2=xpr;
			int ypr2=ypr;

			xpr*=(int)gid(L"borderpartxsc");
			ypr*=(int)gid(L"borderpartysc");

			xpr+=(int)gid(L"borderpartxof");
			ypr+=(int)gid(L"borderpartyof");

			fwprintf( foutt, L"{\\an5\\move(" );
			print_pos_of( xPos+xpr );
			fwprintf( foutt, L"," );
			print_pos_of( yPos+ypr );
			fwprintf( foutt, L"," );
			print_pos_of( xPos+xpr2 );
			fwprintf( foutt, L"," );
			print_pos_of( yPos+ypr2 );
			fwprintf( foutt, L"," );
			print_tval_of( gid( L"tborderpartmovestart" ) );
			fwprintf( foutt, L"," );
			print_tval_of( gid( L"tborderpartmoveend" ) );
			fwprintf( foutt, L")}" );

			fwprintf( foutt, L"{\\p2}m -1 -1 l 2 -1 2 2 -1 2 c {\\p0}" );
		}
	}
}




bool localfx_bHasPass_fnc( int num )
{
	if( num<2 )return 1;
	else return 0;
}

void localfx_CallPass_fnc( wchar_t *fnam, scan_file_fncp sffp, scan_wcs_fncp ssfp, calc_parse_fncp cpfp )
{
	calc_type name;

	if( !wcscmp(fnam,L"p0h.txt") )
	{
		fontmatchuse(L"auto" );
		if( !stylelock_identifier( L"engsub" ) )return;
		fwprintf( foutt, L"\nDialogue: 1," );
		print_time_of( gid( L"wtstart" ) );
		fwprintf( foutt, L"," );
		print_time_of( gid( L"wtend" ) );
		fwprintf( foutt, L"," );
		print_identifier( L"style" );
		fwprintf( foutt, L",OP,0000,0000,0000,," );
		fwprintf( foutt, L"{\\fad(200,200)}" );
		fwprintf( foutt, L"{\\be1}" );
	}
	if( !wcscmp(fnam,L"p0.txt") )
	{
		if( !stylelock_identifier( L"engsub" ) )return;
		print_identifier( L"text" );
	}


	if( !wcscmp(fnam,L"p1h.txt") )
	{
		if( !stylelock_identifier( L"japro" ) )return;
		bCharwise=1;
		fontmatchuse(L"auto" );
	}


	if( !wcscmp(fnam,L"p1.txt") )
	{
		if( !stylelock_identifier( L"japro" ) )return;
		double curx=gid(L"nsiz")-gid(L"nsizall")*0.5+gid(L"nsizthisone")*0.5+320;
		double cury=45;

		sid( L"curx", curx );
		sid( L"cury", cury );

		fwprintf( foutt, L"\nDialogue: 200," );
		print_time_of( gid( L"wtstart" )+(gid( L"nsiz" )-gid( L"nsizall" ))*0.01 );
		fwprintf( foutt, L"," );
		print_time_of( gid( L"tstart" ) );
		fwprintf( foutt, L",OP,0000,0000,0000,," );
		fwprintf( foutt, L"{\\fad(100,0)}" );
		fwprintf( foutt, L"{\\be1}" );
		fwprintf( foutt, L"{\\an2\\pos(" );
		print_pos_of( curx );
		fwprintf( foutt, L"," );
		print_pos_of( cury );
		fwprintf( foutt, L")}" );
		print_identifier( L"text" );

		double curtime=( ( gid(L"tend") - gid(L"tstart") ) * ( ( gid(L"rand")*0.2 ) + 0.8 ) ) + gid(L"tstart");

		fwprintf( foutt, L"\nDialogue: 200," );
		print_time_of( gid( L"tstart" ) );
		fwprintf( foutt, L"," );
		print_time_of( curtime );
		fwprintf( foutt, L",OP,0000,0000,0000,," );
		fwprintf( foutt, L"{\\be1}" );
		fwprintf( foutt, L"{\\an2\\pos(" );
		print_pos_of( curx );
		fwprintf( foutt, L"," );
		print_pos_of( cury );
		fwprintf( foutt, L")}" );

		fwprintf( foutt, L"{\\3c&H" );
		print_identifier( L"stylecolor2" );
		fwprintf( foutt, L"&)\\t(\\3c&H" );
		print_identifier( L"stylecolor3" );
		fwprintf( foutt, L"&)}" );

		print_identifier( L"text" );

		loop_file( L"p1char.txt", 6 );

	}


	if( !wcscmp(fnam,L"p1char.txt") )
	{		
		double curx=gid(L"curx");
		double cury=gid(L"cury");
		double thisdur=gid(L"rand")*0.3;
		double nextx=curx+(((gid(L"rand")*10)-5)*thisdur*8);
		double nexty=cury+(thisdur*60);
		double fadeS=gid(L"loopvar")/6.0;
		if( fadeS<0 )fadeS=0;if(fadeS>1)fadeS=1;
		double fadeE=(gid(L"loopvar")+1)/6.0;
		if( fadeE<0 )fadeE=0;if(fadeE>1)fadeE=1;

		fwprintf( foutt, L"\nDialogue: " );
		print_pos_of( 100-gid(L"loopvar") );
		fwprintf( foutt, L"," );
		print_time_of( gid( L"curtime" ) );
		fwprintf( foutt, L"," );
		print_time_of( gid( L"curtime" )+thisdur );
		fwprintf( foutt, L",OP,0000,0000,0000,," );
		fwprintf( foutt, L"{\\fad(100,0)}" );
		fwprintf( foutt, L"{\\be1}" );
		fwprintf( foutt, L"{\\frx180}" );

		fwprintf( foutt, L"{\\an2\\move(" );
		print_pos_of( curx );
		fwprintf( foutt, L"," );
		print_pos_of( cury );
		fwprintf( foutt, L"," );
		print_pos_of( nextx );
		fwprintf( foutt, L"," );
		print_pos_of( nexty );
		fwprintf( foutt, L")}" );

		fwprintf( foutt, L"{\\fade(" );
		print_pos_of( fadeS*255 );
		fwprintf( foutt, L"," );
		print_pos_of( fadeS*255 );
		fwprintf( foutt, L"," );
		print_pos_of( fadeE*255 );
		fwprintf( foutt, L",0,0,0," );
		print_tval_of( thisdur );
		fwprintf( foutt, L")}" );

		print_identifier( L"text" );

		double nct=gid(L"curtime")+thisdur;
		sid(L"curtime",nct);
		sid(L"curx",nextx);
		sid(L"cury",nexty);


	}
}

