
/*
opt.c  version 3.17  ... modified for Cygwin windows compatibility
                         (varargs.h replaced by stdarg.h)

OPT is a subroutine library which facilitates the convenient 
input of parameters to a C or C++ program. Parameters are parsed 
from a command line, with further facilities for reading options 
from files, from environment strings, or from an interactive 
environment. The aim of the opt package is to permit programs to 
be both user- and programmer- friendly. The package attempts to 
on the one hand provide a direct and relatively full-featured 
input interface to the ultimate user of the program, and at the 
same time impose a minimal amount of work on the programmer to 
"attach" the package to his or her software. A texinfo file is 
part of the distribution; or you can view the html documentation at:
http://nis-www.lanl.gov/~jt/Software/opt/opt_toc.html

Download the lastest version of the source code from:
http://nis-www.lanl.gov/~jt/Software/

opt is available to the public under the GNU General Public License:
http://www.gnu.org/copyleft/gpl.html

This SOFTWARE has been authored by an employee of the University of
California, operator of the Los Alamos National Laboratory under
Contract No. W-7405-ENG-36 with the U.S. Department of Energy. The
U.S. Government has rights to use, reproduce, and distribute this
SOFTWARE. The public may copy, distribute, prepare derivative works
and publicly display this SOFTWARE without charge, provided that this
Notice and any statement of authorship are reproduced on all
copies. Neither the Government nor the University makes any warranty,
express or implied, or assumes any liability or responsibility for the
use of this SOFTWARE. If SOFTWARE is modified to produce derivative
works, such modified SOFTWARE should be clearly marked, so as not to
confuse it with the version available from LANL.

*/

#define SINGLEFILE 1

#ifndef DISABLE_VARARGS
#define DISABLE_VARARGS 0
#endif
#ifndef DISABLE_LONGJUMP
#define DISABLE_LONGJUMP 0
#endif
#ifndef DISABLE_SIGNAL
#define DISABLE_SIGNAL 0
#endif

#include <stdio.h>
#ifdef convex
#include <strings.h>
#else
#include <string.h>
#endif
#ifdef __TURBOC__
#include <stdlib.h>
#include <alloc.h>
#endif
#include <ctype.h>

#if !DISABLE_LONGJUMP
#include <setjmp.h>
#endif

#if !DISABLE_SIGNAL
#include <signal.h>
#endif

#if !DISABLE_VARARG
#ifdef __TURBOC__
#include <stdarg.h>
#else
#include <stdarg.h>
#endif
#endif

static char gstr[160];	/* generally useful global string */
/* opt.h */
/*
	User Include File for options package
*/

#ifndef _OPT_H
#define	_OPT_H 	/* Signal that this header file has been included */

/* 
 * These are delimiter characters 
 */
#define DELIM		'-'		/* option delimiter character */
#define	ALTDELIM	'/'		/* alternate delimiter character */
#define	OPTFROMFILE	'@'		/* denotes options are in a file */
#define	OPTTOFILE	'%'		/* says to put options in a file */
#define	DOCUMENT	'-'		/* write document to file */
#define	INTERACT	'$'		/* Flags interactive menu */
#define	HELPCH		'?'		/* Help character */
/*
 * These are not available on command line 
 * But may be invoked from a file
 */
#define IGNOREEOL       ';'		/* Ignore until the end of line */
#define	RUN             '='		/* Says to just run to completion */
#define	QUITCH		    '.'		/* Quit character */
/*
 * These are not available on command line or from a file
 * But may be invoked from the menu
 */
#define	BANG		    '!'		/* Shell escape character */
#define	ADDITIONAL_OPTS	'+'		/* Additional options */


typedef enum    {
                INT,            UNSINT,          LONG,           CHAR,
                INTLEVEL,       
                FLOAT,          DOUBLE,
                FLAG,           NEGFLAG,        ABSFLAG,        ABSNEGFLAG,
                VSTRING,        CSTRING,        UNDELIMV,       UNDELIMC
                }
                opt_TYPE;


typedef	int	(*PFI)();

#define	OPT_EXT	".opt"	/* standard options file extension */

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#ifndef	ARGCHECK
#ifdef __TURBOC__ 
#define	ARGCHECK
#endif /* __TURBOC__ */
#ifdef __cplusplus 
#define	ARGCHECK
#endif /* __cplusplus */
#endif /* ARGCHECK */


#ifdef	ARGCHECK
	extern  int     opt_register(char *,opt_TYPE,char,char *);
	extern	void	opt_usage_set(char *);
	extern	void	opt_title_set(char *);
	extern	void	opt_verify_set(PFI);
	extern	void	opt_doc_set(PFI);
	extern	void	opt_quit_set(PFI);
	extern	void	opt_run_set(PFI);
	extern	void	opt_help_setf(PFI);
	extern	void	opt_help_set(char,char *);
	extern	void	opt_ufilter_set(PFI);
	extern	void	opt_dfilter_set(PFI);
    extern	void	opt_env_set(char *);
    extern	void	opt_default_set(char *);
#if DISABLE_VARARGS
	extern	void	opt_errmess(char *);
	extern	void	opt_message(char *);
	extern	void	opt_warning(char *);
	extern	void	opt_fatal(char *);
#else
	extern	void	opt_errmess();
	extern	void	opt_message();
	extern	void	opt_warning();
	extern	void	opt_fatal();
#endif /* DISABLE_VARARGS */
	extern	void	opt_abort_run(void);
	extern	int	    opt_begin_run(PFI);
	extern	int		getopts(int,char **);
#else
	extern  int     opt_register();
	extern	void	opt_usage_set();
	extern	void	opt_title_set();
	extern	void	opt_verify_set();
	extern	void	opt_doc_set();
	extern	void	opt_quit_set();
	extern	void	opt_run_set();
	extern	void	opt_help_setf();
	extern	void	opt_help_set();
	extern	void	opt_help_set();
	extern	void	opt_ufilter_set();
	extern	void	opt_dfilter_set();
    extern	void	opt_env_set();
    extern	void	opt_default_set();

	extern	void	opt_errmess();
	extern	void	opt_message();
	extern	void	opt_warning();
	extern	void	opt_fatal();

	extern	void	opt_abort_run();
	extern	int	    opt_begin_run();
	extern	int		getopts();

#endif /* ARGCHECK */


/*********************************
 * Macro's for registering options
 */

#define	optregister(val,typ,c,str) opt_register((char *)&val,typ,c,str)
#define optrunset(r) {int r(); opt_run_set( r );}

#endif /* _OPT_H */
/* ag.h */


#ifndef _AG_H
#define _AG_H

#ifndef	TRUE
#define	TRUE	1
#define	FALSE	0
#endif

/*************************************
 * ARGVECTOR structure
 * Basically, an (argc,argv) construct
 * with indices to which character of 
 * which word is the current position
 */

typedef struct
        {
                char    **v;            /* argument vector */
                int     c;              /* argument count  */
                int     iw;             /* current word    */
                int     ic;             /* current character */
        }
        ARGVECTOR;

/* 
 * Function prototypes 
 */


#ifdef	ARGCHECK

extern  ARGVECTOR *ag_new(int,char **,ARGVECTOR *);
extern	int	    ag_enstring(char *,ARGVECTOR *,int);
extern  void    ag_reset(ARGVECTOR *);
extern  int     ag_w_number(ARGVECTOR *);
extern  void    ag_w_advance(ARGVECTOR *);
extern  int     ag_eow(ARGVECTOR *);
extern  int     ag_end(ARGVECTOR *);
extern  char    ag_c(ARGVECTOR *);
extern  char    ag_c_next(ARGVECTOR *);
extern  char    ag_cnn_next(ARGVECTOR *);
extern  char    ag_c_advance(ARGVECTOR *);
extern  char    ag_backspace(ARGVECTOR *);
extern  char    *ag_s(ARGVECTOR *);
extern  char    *ag_s_next(ARGVECTOR *);
extern  char    *ag_s_advance(ARGVECTOR *);
extern	char	*argnext(ARGVECTOR *);
extern	double	argnextnum(ARGVECTOR *);
#else

extern  ARGVECTOR *ag_new();
extern	int	    ag_enstring();
extern  void    ag_reset();
extern  int     ag_w_number();
extern  void    ag_w_advance();
extern  int     ag_eow();
extern  int     ag_end();
extern  char    ag_c();
extern  char    ag_c_next();
extern  char    ag_cnn_next();
extern  char    ag_c_advance();
extern  char    ag_backspace();
extern  char    *ag_s();
extern  char    *ag_s_next();
extern  char    *ag_s_advance();
extern	char	*argnext();
extern	double	argnextnum();

#endif /* ARGCHECK */
#endif /* _AG_H */
/* opt_p.h */
/*
 *	Private header file for OPT package.
 */

#ifndef _OPT_P_H
#define _OPT_P_H

#define OPT_MAXSTRLEN 80

#ifndef	TRUE
#define	TRUE	1
#define	FALSE	0
#endif
#ifndef	OKAY
#define	OKAY		0
#define	NOT_OKAY	(-1)
#endif
#ifndef DEBUG
#define DEBUG 0
#endif

typedef enum { False=FALSE, True=TRUE } flag;

/******************
 * Global variables
 */
extern	int		nregopts;		/* Number of registered options */
extern	flag	menuflag;		/* Is menu ON? */
extern	flag	fileflag;		/* Are options being read from a file? */


/*********************
 * Function Prototypes
 */

#ifndef	  ARGCHECK
#ifdef    __TURBOC__
#define	  ARGCHECK
#endif /* __TURBOC__ */
#endif /* ARGCHECK   */

#ifdef	ARGCHECK

extern  int     opt_register(char *,opt_TYPE,char,char *);
extern  int     opt_number(char);
extern  int		opt_fprint(FILE *,int);
extern  int		opt_tofile(FILE *);
extern	char	*optstrval(int);
extern	char	*optstrtyp(int);
extern  int     opt_undelim(ARGVECTOR *);
extern  int     opt_delim(ARGVECTOR *);
extern	void	opt_get_help(char);

#else

extern  int     opt_register();
extern  int     opt_number();
extern  int		opt_fprint();
extern  int		opt_tofile();
extern	char	*optstrval();
extern	char	*optstrtyp();
extern  int     opt_undelim();
extern  int     opt_delim();
extern	void	opt_get_help();

#endif

		/* --------------- */
		/* Process Options */
		/* --------------- */

extern	char	*opt_program_name;
extern	PFI	dfilter_fcn,
		 	ufilter_fcn, 
		  	verify_fcn,
			doc_fcn, 
			quit_fcn, 
			help_fcn,
			run_fcn;

#ifdef	ARGCHECK

extern	void	opt_wr_title(void);
extern  void    opt_process(int,char **);
extern  int     opt_fromfname(char *);
extern	int		opt_tofname(char *);
extern  int     opt_getline(char *,FILE *);
extern	char	*opt_mstring(int);
extern  int     opt_number(char);
extern  char    *short_progname(char *);
extern  int     opt_undelim(ARGVECTOR *);
extern  int     opt_delim(ARGVECTOR *);

extern	void	opt_menu(void);

extern	void	usage(char *);
extern	void	opt_help();
extern	void	opt_quit();
extern	void	opt_doc();
extern	void	opt_usage(FILE *);

#else

extern	void	opt_wr_title();
extern  void    opt_process();
extern  int     	opt_fromfname();
extern  int     		opt_getline();
extern	int		opt_tofname();
extern  int     	opt_delim();
extern  int     		opt_number();
extern  int     	opt_undelim();
extern	void		opt_menu();
extern	char		*opt_mstring();

extern	void	opt_doc();
extern	void	opt_help();
extern	void	opt_quit();

extern	void	usage();
extern	void	opt_usage();
extern  char    *short_progname();
extern  int     ignore_after_char();

#endif /* ARGCHECK */



#endif /* _OPT_P_H */
/* ag.c */

#ifndef	SINGLEFILE
#include <stdio.h>
#ifdef convex
#include <strings.h>
#else
#include <string.h>
#endif
#include "ag.h"
#endif

/* primitive routines for manipulation argument vectors */

/*
        make-new-argvector              ag_new()
        reset-argvector                 ag_reset()
        flag-end-of-word                ag_eow()
        what-is-character               ag_c()
        what-is-string                  ag_s()

        read-character                  ag_c()
        read-next-character             ag_c_next()
        read-next-non-null-character    ag_cnn_next()
        read-character-advance          ag_c_advance()
        read-string                     ag_s()
        read-next-string                ag_s_next()
        read-string-advance             ag_s_advance()
        word-number                     ag_w_number()
        word-advance                    ag_w_advance()
        backspace                       ag_backspace()

		clear							ag_clear()

		get-next-argument				argnext()
		get-next-argument-value			argnextnum()
*/

ARGVECTOR *
ag_new(argc,argv,ag)
int     argc;
char    **argv;
ARGVECTOR       *ag;
{
        ag->v = argv;
        ag->c = argc;
        ag->iw = 0;
        ag->ic = 0;
        return(ag);
}
ag_fprint(fp,ag)
FILE            *fp;
ARGVECTOR       *ag;
{
        int     i;
        for(i=0; i<ag->c; ++i)
                fprintf(fp,"[%s]",ag->v[i]);
        fprintf(fp,"\n");
}
void
ag_reset(ag)
ARGVECTOR       *ag;
{
        ag->iw = 0;
        ag->ic = 0;
}
int
ag_w_number(ag)
ARGVECTOR       *ag;
{
        return( ag->iw );
}
void
ag_w_advance(ag)
ARGVECTOR       *ag;
{
        ++(ag->iw);             /* advance to next word */
        ag->ic=0;               /* beginning of next word */
}
/*      ag_eow: end of word
                        flag whether current position is at end of word
*/
int
ag_eow(ag)
ARGVECTOR       *ag;
{
        if( ag->iw >= ag->c )
                return(TRUE);
        if( ag->ic >= strlen(ag->v[ag->iw]) )
                return(TRUE);
        return(FALSE);
}
/*      ag_end: end of command line
                flag whether current position is at end of command line 
*/
int
ag_end(ag)
ARGVECTOR       *ag;
{
        if( ag->iw >= ag->c )
                return(TRUE);
        if( ag_eow(ag) && ag->iw == (ag->c)-1 )
                return(TRUE);
        return(FALSE);
}
/*      ag_c:   return current character
                do not advance
*/
char
ag_c(ag)
ARGVECTOR       *ag;
{
        return(ag->v[ag->iw][ag->ic]);
}
char
ag_c_next(ag)
ARGVECTOR       *ag;
{
        return(ag->v[ag->iw][ag->ic+1]);
}
char
ag_cnn_next(ag)
ARGVECTOR       *ag;
{
        if( ag_c_next(ag) == '\0' )
        {
                if(ag->iw+1 >= ag->c)
                        return('\0');
                else    return(ag->v[ag->iw+1][0]);
        }
        else    return( ag_c_next(ag) );
}
/*      ag_c_advance:   read current character, and advance to next
                        return '\0' if end of word
                        do not advance to next word
*/
char
ag_c_advance(ag)
ARGVECTOR       *ag;
{
        char    c;              /* current character */

        if( ag_eow(ag) )
                return(c='\0'); /* return NULL to signal that current*/
                                /* character is past end of word     */
        c = ag->v[ag->iw][ag->ic];
        ++(ag->ic);             /* advance to next character */
        return(c);
}
char
ag_backspace(ag)
ARGVECTOR       *ag;
{
        if( --(ag->ic) < 0 )            /* if back past beginning of word */
        {       ag->ic=0;
                if(--(ag->iw) < 0)      /* goto beginning of previous word */
                        ag_reset(ag);           /* if no previous, reset */
                else
                {       while( !ag_eow(ag) )    /* goto end of prevous word */
                                ag_c_advance(ag);
                        ag_backspace(ag);       /* back to just before end */
                }
        }
        return(ag->v[ag->iw][ag->ic]);
}
/*      ag_s:   returns current string
                returns "" if current position is at end of word
                returns NULL if past end of argument vector
*/
char    *
ag_s(ag)
ARGVECTOR       *ag;
{
        if( ag->iw < ag->c )
                return( ag->v[ag->iw]+ag->ic );
        else    return( NULL );
}
char    *
ag_s_next(ag)
ARGVECTOR       *ag;
{
        if( ag->v[ag->iw][ag->ic+1] == '\0' )
        {
                if(ag->iw+1 >= ag->c)
                        return(NULL);
                else    return(ag->v[ag->iw+1]);
        }
        else    return( ag->v[ag->iw]+ag->ic+1 );
}
/*      ag_s_advance:   read current string and advance to next
                        returns NULL if current string is at end
                        does not check advanced string
*/
char    *
ag_s_advance(ag)
ARGVECTOR       *ag;
{
        char    *s;             /* current string */

        if( ag_eow(ag) )        /* if end of word, go to next word */
                ag_w_advance(ag);
        if( ag_eow(ag) )        /* if still at end of word,  */
                s = NULL;       /* signify by returning NULL */
        else    s = ag->v[ag->iw] + ag->ic;

        ag_w_advance(ag);       /* advance to next word */

        return(s);
}
int
ag_clear(ag)
ARGVECTOR *ag;
{
	while( !ag_end(ag) )
		argnext(ag);
	return 1;
}


	/* ------------------------ */
	/* return the next argument */
	/* ------------------------ */
char *
argnext(ag)
ARGVECTOR *ag;
{
    static char nullchar='\0';
    char *s;

    s = ag_s_advance(ag);
    if( s==NULL )	
    	s = &nullchar;
    return(s);
}
	/* ------------------------------------------- */
	/* return the numerical value of next argument */
	/* ------------------------------------------- */
double	
argnextnum(ag)
ARGVECTOR *ag;
{
    extern double atof();
    return( atof(argnext(ag)) );
}




/* opt_reg.c */

/************************ register options ********************************
 *
 *    options are stored in an array,
 *    each element of which is a structure
 *
 *    The members of the structure contain information about
 *        1) the variable which is altered
 *        2) the type of variable
 *        3) a character by which the variable is invoked
 *        4) a brief description of the variable's role in the program
 *        5) a longer help message
 *            
 *    The structure elements are not assigned directly, but are
 *    "registered" with a call to the function opt_register().
 *        
 *    In this file are the routines which access the structure of
 *    registered options.
 *
 *          I) Register options and help strings
 *         II) Get number corresponding to name of option
 *        III) Print options out
 *             a) to a file which can be used as an input command line
 *             b) to the screen as part of a usage message
 *             c) to the screen as part of an interactive menu
 *         IV) Process single delimited and undelimited options
 */

#ifndef	SINGLEFILE
#include <stdio.h>
#ifdef convex
#include <strings.h>
#else
#include <string.h>
#endif
#ifdef __TURBOC__
#include <alloc.h>
#endif
#include "ag.h"
#include "opt_p.h"
static char gstr[160]; /* global string for general use */
#endif



        /* -------------------------- */
        /* List of Registered Options */
        /* -------------------------- */

#define MAXOPTS 62      /* one for each upper and lower case letter */

typedef struct
        {
        char            *value;         /* pointer to value of option */
        opt_TYPE        type;           /* will be cast according to type */
        char            name;           /* name by which option is invoked */
        char            *brief;         /* a brief description */
		char			*help;			/* longer help message */
        }
        EACH_OPT;

static	EACH_OPT	optlist[MAXOPTS];       /* array of options */
int                 nregopts=0;             /* number of registered opts */

    /* ---------- */
    /* OPT macros */
    /* ---------- */

#define	OPT_isflagtype(o) \
	((o)==FLAG || (o)==NEGFLAG || (o)==ABSFLAG || (o)==ABSNEGFLAG)
#define	OPT_isundelimtype(o) ((o)==UNDELIMV || (o)==UNDELIMC)


	/* ----------------------------------------------- */
	/* OPTVALUE: a macro to get the value of an option */
	/* ----------------------------------------------- */

#define	OPTVALUE(typ,i)		((typ)(*((typ *)(optlist[i].value))))

#define SETOPTVALUE(typ,i,val)  { typ *xptr;                        \
                                  xptr = (typ *)(optlist[i].value); \
                                  *xptr = val;                      \
							    }
        /* ------------------------------- */
        /* Routine to register each option */
        /* ------------------------------- */

int
opt_register(val,otype,name,brief)
char            *val;
opt_TYPE        otype;
char            name;
char            *brief;
{
    if( nregopts >= MAXOPTS )
        opt_fatal("opt_register: too many options");
	
    if( name != '\0' && opt_number(name) != -1 )
    {
		char gstr[80];
		sprintf(gstr,"opt_register: Duplicate option name \'%c\'",name),
		opt_warning(gstr);
    }
	
	/* Programmer may specify that an option is to be an
	 * undelimted option by setting the name to '\0'
	 */
    if(name=='\0')
    {
		if(otype==VSTRING) 
			otype=UNDELIMV;
		if(otype==CSTRING)
			otype=UNDELIMC;
    }

	/* Having checked for various warnings, now register the options */

    optlist[nregopts].value         = val;
    optlist[nregopts].type          = otype;
    optlist[nregopts].name          = name;
    optlist[nregopts].brief         = brief;
    optlist[nregopts].help          = NULL;
	
	/* UN-delimited strings are set to NULL when registered */
	/* This enables them to be invoked on the command line  */
	
    if(otype==UNDELIMC)
		*(optlist[nregopts].value)='\0';
    if(otype==UNDELIMV)
		SETOPTVALUE(char *,nregopts,NULL)

	++nregopts;
	
    return(nregopts);
}
void
opt_help_set(c,help)
char c, *help;
{
	int n;
	n = opt_number(c);
	if (n>=0 && n<nregopts)
		optlist[n].help = help;
	else
		sprintf(gstr,"opt_help_set: Unregistered option name \'%c\'",c),
		opt_warning(gstr);
}
void
opt_get_help(c)
char c;
{
	int n;
	n = opt_number(c);
	if (n>=0 && n<nregopts && optlist[n].help != NULL)
		sprintf(gstr,"%c: %s\n",c,optlist[n].help),
		opt_message(gstr);
	else
		sprintf(gstr,"Help unavailable for \'%c\'\n",c),
		opt_message(gstr);
}
	
	

        /* --------------------------------------- */
        /* Get number corresponding to option name */
        /* --------------------------------------- */

/* opt_number returns the number of a named option.
 * if c=='\0', signifying an undelimited option,
 * then the number of the FIRST undelimited option is returned
 */
int
opt_number(c)
char    c;
{
        int     i=0;                    /* see which registered option */
        for(i=0; i<nregopts; ++i)       
        {
                if( c == optlist[i].name )
                        return(i);
        }
        return(-1);                     /* to signify not an option */
}

	/* -------------------------------------------- */
	/* Print value of registered option to a string */
	/* -------------------------------------------- */

/* optstrval:
 * returns the value of the ith registered option as a string
 * Thus if x = 12.6, this returns the string "12.6"
 * The return value is a pointer to a static string which is
 * overwritten with each call
 * FLAG values are returned as "+" or "-"
 * INTLEVEL values are returned as "- -xxxx..." depending on value
 */
char *
optstrval(i)
int i;
{
    int     maybe;
    static char stval_buf[80];
    
    switch( optlist[i].type )
    {
    case INT:
        sprintf(stval_buf,"%d", OPTVALUE(int,i) );
		break;
    case UNSINT:
        sprintf(stval_buf,"%u", OPTVALUE(unsigned int,i) );
		break;
    case LONG:
        sprintf(stval_buf,"%ld", OPTVALUE(long,i) );
		break;
    case FLOAT:
        sprintf(stval_buf,"%g", OPTVALUE(float,i) );
		break;
    case DOUBLE:
        sprintf(stval_buf,"%lg", OPTVALUE(double,i) );
		break;
    case CHAR:
        sprintf(stval_buf,"%c", OPTVALUE(char,i));
		break;
    case INTLEVEL:
    {
		int j;
		char buff[80];
		strcpy(stval_buf,"-"); 		/* Begin with level==OFF */
		for(j=0; j< OPTVALUE(int,i); ++j)
		{
			sprintf(buff,(j==0?" -%c":"%c"),optlist[i].name);
			strcat(stval_buf,buff);
		}
    }
		break;
    case FLAG:
    case ABSFLAG:
		maybe = OPTVALUE(int,i);
		sprintf(stval_buf,"%c", (maybe==TRUE ? '+' : '-') );
		break;
    case NEGFLAG:
    case ABSNEGFLAG:
		maybe = OPTVALUE(int,i);
		sprintf(stval_buf,"%c", (maybe==TRUE ? '-' : '+') );
		break;
    case CSTRING:    
    case UNDELIMC:
		sprintf(stval_buf,"\"%s\"",optlist[i].value);
		break;
    case VSTRING:
    case UNDELIMV:
		if( optlist[i].value == NULL )	/* this should never happen */
			sprintf(stval_buf,"\"\"");
		else 
			if( OPTVALUE(char *,i) == NULL )
				sprintf(stval_buf,"\"\"");
			else
				sprintf(stval_buf,"\"%s\"",OPTVALUE(char *,i));
		break;
    default:
		opt_fatal("optstrval: Undefined o-type");
		break;
    }
    /* ---- Return value is static buffer ---- */
    return(stval_buf);
}/*optstrval*/


/* optstrtyp:
 * returns the type of the ith registered option as a string
 * Thus if x = 12.6 is a float , this returns the string "<real>"
 * The return value is a pointer to a static string which is
 * overwritten with each call
 */
char *
optstrtyp(i)
int i;
{
	static char	sttyp_buf[80];

	switch( optlist[i].type )
	{
	case INT:
	case UNSINT:
	case LONG:
		strcpy(sttyp_buf,"<integer>");
		break;
	case FLOAT:
	case DOUBLE:
	    strcpy(sttyp_buf,"<real>");
	    break;
	case CHAR:
	    strcpy(sttyp_buf,"<character>");
	    break;
	case INTLEVEL:
	case FLAG:
	case NEGFLAG:
	case ABSFLAG:
	case ABSNEGFLAG:
	    strcpy(sttyp_buf,"<flag>");
	    break;
	case VSTRING:
	case CSTRING:
	case UNDELIMV:
	case UNDELIMC:
	    strcpy(sttyp_buf,"<string>");
	    break;
	default:
	    opt_fatal("usage: undefined o-type");
	}
	return(sttyp_buf);
}

		/* ------------------------------ */
		/* Put registered options to file */
		/* ------------------------------ */

int
opt_tofile(fp)
FILE    *fp;
{
    int	i;
    char *format;
    char *fnumstr="-%c %-38s %c%s\n";	/* numbers and strings  */
    char *fflgchr="-%c%-38s  %c%s\n";	/* flags and characters */
    void opt_fileheader();
    
    opt_fileheader(fp);
    for(i=0; i<nregopts; ++i)
    {
	if( OPT_isundelimtype( optlist[i].type ) )
	    continue;
	if( OPT_isflagtype( optlist[i].type )
		|| optlist[i].type == INTLEVEL
		|| optlist[i].type == CHAR )
		format = fflgchr;
	else
		format = fnumstr;
	fprintf(fp,format,optlist[i].name,
		optstrval(i),IGNOREEOL,optlist[i].brief);
    }
}
void
opt_fileheader(fp)
FILE	*fp;
{
    extern char *opt_program_name;
    int	i,n;
    char buf[80];

    sprintf(buf,"Options file created by: [%.30s]",opt_program_name);
    n = strlen(buf);

    fputc(IGNOREEOL,fp);
    fprintf(fp,"%s",buf);
    fputc(IGNOREEOL,fp); fputc('\n',fp);

    fputc(IGNOREEOL,fp);
    for(i=0;i<n;++i) fprintf(fp,"-");
	fputc(IGNOREEOL,fp); fputc('\n',fp);
}
		/* ----------------------------------------- */
		/* write options out to the interactive menu */
		/* ----------------------------------------- */

char *
opt_mstring(i)
int	i;
{
    static char mstring[180];
    char	flgstr[10];
    char	*s;
    char	*optstrval();
    char	*format = "%c %-40s %s";

    if( OPT_isundelimtype( optlist[i].type ) )
		return(NULL);

    s = optstrval(i);
    if( optlist[i].type == INTLEVEL )
	{
		int f;
		f = OPTVALUE(int,i);
		if(f==0)
			strcpy(flgstr,"OFF");
		else if (f==1)
			strcpy(flgstr,"ON");
		else
			sprintf(flgstr,"ON:%d",f);
		s=flgstr;
	}
    else
	if( optlist[i].type == CHAR )
	{
		switch (s[0])
		{
		case '\0':	sprintf(flgstr,"\'\\0\'"); break;
		case '\n':	sprintf(flgstr,"\'\\n\'"); break;
		case '\t':	sprintf(flgstr,"\'\\t\'"); break;
		case ' ':	sprintf(flgstr,"\'  \'");  break;
		default:	sprintf(flgstr,"%c",s[0]); break;
		}
		s = flgstr;
	}
	else
	if( OPT_isflagtype( optlist[i].type ) )
	{
		if( *s == '+' )
			strcpy(flgstr,"TRUE");
		if( *s == '-' )
			strcpy(flgstr,"FALSE");
		s=flgstr;
	}
	
    sprintf(mstring,format,optlist[i].name,optlist[i].brief,s);
    return(mstring);
}
int
opt_fprint(fp,i)
FILE	*fp;
int		i;
{
	char	*optstrval();
	fprintf(fp,"-%c%-17s %c%s\n",optlist[i].name,
			optstrval(i),IGNOREEOL,optlist[i].brief);
		return(i);
}
	/* ----------------------------------------------------- */
	/* write a usage statement describing registered options */
	/* ----------------------------------------------------- */

void
opt_usage()
{
	char	buf[100];
    char	*dformat = " -%c %-12s\t%s\n";
    char	*uformat =  "    %-12s\t%s\n";
	
    int     i;
    for(i=0; i<nregopts; ++i)
    {
		if( OPT_isundelimtype( optlist[i].type ) )
		{
			sprintf(buf,uformat,
					optstrtyp(i),optlist[i].brief);
			opt_message(buf);
		}
		else
		{
			sprintf(buf,dformat,optlist[i].name,
					optstrtyp(i),optlist[i].brief);
			opt_message(buf);
		}
    }
}

	/* ----------------------- */
	/* Get and process options */
	/* ----------------------- */

	/*
	 * The routines below make use of the ARGVECTOR structure
	 * defined in "ag.h" to process the command line options
	 */
		
	/* -------------------------------------- */
	/* get and process an UN-delimited option */
	/* -------------------------------------- */

int
opt_undelim(ag)
ARGVECTOR       *ag;
{
	int     i;
	char    *s;
	
	if(1)
	{
		/* This is the hook that the programmer can install
		 * to filter undelimited strings from the command line
		 */
		extern	PFI	ufilter_fcn;
		if( ufilter_fcn != NULL )
			if( (*ufilter_fcn)(ag_s(ag),ag) != 0 )     
				return(1);
	}
	
	if(DEBUG)
	{
		opt_message("opt_udelim: ");
		ag_fprint(ag);
	}
	
	/* Find the first un-initialized undelimited option */
	/* and set that to the argument string */
	/* Note that once an undelimited option has been initialized */
	/* it cannot be reset to a new value unless it is somehow */
	/* set back to NULL or blank */
	
	s = ag_s_advance(ag);
	for(i=0; i<nregopts; ++i)
	{
		if( optlist[i].type==UNDELIMC && *(optlist[i].value)=='\0' )
		{
			strcpy( optlist[i].value, s );
			return(1);
		}
		if( optlist[i].type==UNDELIMV && OPTVALUE(char *,i)==NULL )
		{
			SETOPTVALUE(char *,i,(char *)malloc(strlen(s)+1));
			strcpy( OPTVALUE(char *,i), s );/* ?? */
			return(1);
		}
		
	}
	return(0);
}

		/* ---------------------------------- */
		/* get and process a delimited option */
		/* ---------------------------------- */

opt_delim(ag)
ARGVECTOR       *ag;
{
    int     	i;
    opt_TYPE	o;
    char    	c;
    char    	*s;
    int     	yes,no,maybe,toggle;    /* flag values */
    
    /**************************************************
     * first, check to see if the programmer wants to
     * interrupt this delimited option: if so, it will
     * be done by the routine (*dfilter_fcn)(), which
     * the programmer has provided and a 
     * nonzero value will be returned.
     ***************************************************/
	if(1)
	{
		extern	PFI	dfilter_fcn;
		if( dfilter_fcn != NULL )
			if( (*dfilter_fcn)(ag_s(ag),ag) != 0 )     
				return(1);
	}
	
	c = ag_c_advance(ag);   /* first character gives name of option */
	i = opt_number(c);      /* this is number of option w/ name 'c' */
	
	if(i<0)	/* if invalid option name */
	{
		char s[80];
		sprintf(s,"%c not a registered option name\n",c);
		opt_warning(s);
		return(0);
	}

    /* ------------- */
    /* act on option */
    /* ------------- */
    switch( o=optlist[i].type )
    {
    case INT:
		SETOPTVALUE(int,i, argnextnum(ag));
		break;
    case UNSINT:
		SETOPTVALUE(unsigned int,i, argnextnum(ag));
		break;
    case LONG:
		SETOPTVALUE(long,i, argnextnum(ag));
		break;
    case FLOAT:
		SETOPTVALUE(float,i, argnextnum(ag));
		break;
    case DOUBLE:
		SETOPTVALUE(double,i, argnextnum(ag));
		break;
    case CHAR:
		SETOPTVALUE(char,i, ag_c_advance(ag));
		break;

    case FLAG:
    case NEGFLAG:
    case ABSFLAG:
    case ABSNEGFLAG:
		/* define terms:
		 * yes: value of flag when  ON
		 * no:  value of flag when OFF
		 * maybe:  present value of flag
		 * toggle: negative of maybe
		 */
		maybe  = OPTVALUE(int,i);
		toggle = (maybe==TRUE ? FALSE : TRUE);
		if( o==FLAG || o==ABSFLAG )     yes=TRUE;
		else                            yes=FALSE;
		no = (yes==TRUE ? FALSE : TRUE);
		c = ag_c(ag);           /* character following 'c' */
		switch(c)
		{
		case '+':
			*((int *)(optlist[i].value)) = yes;
			ag_c_advance(ag);       /* eat the '+' */
			break;
		case '-':
			*((int *)(optlist[i].value)) = no;
			ag_c_advance(ag);       /* eat the '-' */
			break;
		default:
			if( o==ABSFLAG || o==ABSNEGFLAG )
				*((int *)(optlist[i].value)) = maybe;
			else    /* otherwise toggle value */
				*((int *)(optlist[i].value)) = toggle;
			break;
		}
		break;

    case INTLEVEL:
		SETOPTVALUE(int,i,OPTVALUE(int,i) + 1);  /* default is to increment */
		c = ag_c(ag);
		switch(c)
		{
		case '+':
			/* we've already incremented */
			ag_c_advance(ag);
			break;
		case '-':
			SETOPTVALUE(int,i,0);
			ag_c_advance(ag);
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			SETOPTVALUE(int,i,c-'0');
			ag_c_advance(ag);
		default:
			break;
		}
		break;

    case VSTRING:
		s = argnext(ag);
		if( OPTVALUE(char *,i) != NULL )
			free( OPTVALUE(char *,i));       /* if prev. malloc'd */
		*((char **)(optlist[i].value)) = (char *)malloc( strlen(s)+1 );
		strcpy( OPTVALUE(char *,i) , s );
		break;
    case CSTRING:
		strncpy( optlist[i].value , argnext(ag), OPT_MAXSTRLEN );
		break;

    case UNDELIMC:
    case UNDELIMV:
		opt_fatal("opt_delim: can't process UNDELIM type");
		break;

    default:
		opt_fatal("opt_delim: don't know this type");
		break;
    }
    return(1);
}
/* opt_proc.c */
/*
 *	process options in the OPT package
 */

#ifndef	SINGLEFILE
#include <stdio.h>
#include <ctype.h>
#ifdef convex
#include <strings.h>
#else
#include <string.h>
#endif
#ifdef __TURBOC__
#include <alloc.h>
#include <stdarg.h>
#endif
#include "ag.h"
#include "opt_p.h"
static  char	gstr[160];	/* general purpose global string */
#endif /* SINGLEFILE */



/******************
 * Global variables 
 */

char	*opt_program_name;
flag	fileflag = False;

char	*optfile_name; 
char	*opt_envstring=NULL;
char	*opt_defstring=NULL;
PFI	dfilter_fcn=NULL,
 	ufilter_fcn=NULL, 
  	verify_fcn=NULL,		/* NOTE: this has been disabled ! */
	doc_fcn=NULL, 
	quit_fcn=NULL,
	help_fcn=NULL,
	run_fcn=NULL;

/****************************
 * Static Function prototypes 
 */

static int line2argv();
static int l2a();
static flag break_word();


static  char	*Title = NULL;
static	char	*Usage = NULL;

/***************************
 * set title, usage, etc.  *
 ***************************/
void
opt_title_set(s)
char	*s;
{
    if(Title != NULL)
		free(Title);
    Title = (char *)calloc(strlen(s)+1,sizeof(char));
    if(Title == NULL)
		sprintf(gstr,"opt_title_set: cannot allocate for %s",s), 
		opt_fatal(gstr);
    strcpy(Title,s);
}
void
opt_wr_title()
{
    sprintf(gstr,"%s\n",
			(Title==NULL ? opt_program_name : Title));
	opt_message(gstr);
}
void
opt_usage_set(s)
char	*s;
{
    if(Usage != NULL)
		free(Usage);
    Usage = (char *)calloc(strlen(s)+1,sizeof(char));
    if(Usage == NULL)
		sprintf(gstr,"opt_usage_set: cannot allocate for %s",s), 
		opt_fatal(gstr);
    strcpy(Usage,s);
}
void
opt_dfilter_set(fcn)
PFI	fcn;
{
    extern	PFI	dfilter_fcn;
    dfilter_fcn = fcn;
}
void
opt_ufilter_set(fcn)
PFI	fcn;
{
    extern	PFI	ufilter_fcn;
    ufilter_fcn = fcn;
}
void
opt_verify_set(fcn)
PFI	fcn;
{
    extern	PFI	verify_fcn;
	opt_warning("The verify facility has been disabled!!");
    verify_fcn = fcn;
}
void
opt_quit_set(fcn)
PFI	fcn;
{
    extern	PFI	quit_fcn;
    quit_fcn = fcn;
}
void
opt_doc_set(fcn)
PFI	fcn;
{
    extern	PFI	doc_fcn;
    doc_fcn = fcn;
}
void
opt_help_setf(fcn)
PFI	fcn;
{
    extern	PFI	help_fcn;
    help_fcn = fcn;
}
void
opt_run_set(fcn)
PFI	fcn;
{
    extern	PFI	run_fcn;
    run_fcn = fcn;
}
void
opt_env_set(s)
char	*s;
{
    extern	char	*opt_envstring;
    opt_envstring = s;
}
void
opt_default_set(s)
char	*s;
{
    extern	char	*opt_defstring;
    opt_defstring = s;
}


/* ------------------------------------------------------------------ */

	/* ------- */
	/* getopts */
	/* ------- */

/*
 * this is the routine that is called from main(argc,argv).
 * returns value of argc.
 */
int
getopts(argc,argv)
int	argc;
char	*argv[];
{
    int	nargc;
    char	**nargv;
    
    char	*short_progname();
    char	*append_string();
    
	/*
	 * Before processing, set the global variables
	 * opt_program_name : name of routine that is running
	 * optfile_name     : default name of options file
	 */
    opt_program_name = short_progname(argv[0]);
    optfile_name = append_string(opt_program_name,OPT_EXT);

	/* Begin options processing */
	/* ------------------------ */

    /* First process default string */
    opt_lineprocess(opt_defstring);

    /* Second, check environment variable */
    if(opt_envstring != NULL)
    {
	char	*s;
	char	*getenv();
	
	s = getenv(opt_envstring);
	opt_lineprocess(s);
    }

    /* Finally, parse the command line */
    opt_process(argc-1,argv+1);

    return(argc);
}
char	*
append_string(s,t)
char	*s,*t;
{
    /* input two strings "s" and "t":
     * concatenates them to get string "st"
     * which it allocates space for and returns
     */
    char *st;
    st = (char *)malloc( strlen(s)+strlen(t)+1 );
    strcpy(st,s);
    strcat(st,t);
    return(st);
}
char *
short_progname(pname)
char *pname;
{
    char	*p;
    int	len;

    /*
     * inelegant routine
     * returns the shortened name of the program named [pname].
     * It (recursively) strips off leading directory or drive number
     * and trailing ".EXE" in the case of MS-DOS executable
     */

    p = pname;
    while( *p != '/' && *p!='\\' && *p!=':' && *p!='\0' )
    	++p;
    if( *p=='\0')
    {	/* remove .EXE if it exists */
    	len = strlen(pname);
    	if( len > 4 )
	{
    	    if( ( 0==strcmp(pname+len-4,".EXE") ||
    	    	  0==strcmp(pname+len-4,".exe") ) )
    	    		pname[len-4]='\0';
	}
    	return( pname );
    }
    else
    	return( short_progname(++p) );
}
/* ----------------------------------------------------------------- */

	/* ------- */
	/* process */
	/* ------- */

/****************************************************************
 * opt_process(): 
 *	INPUT:
 *		argc, argv;
 *
 *	this is the central receiving facility for the options package.
 *	opt_process takes an argument list given by (argc,argv) and
 *	and processes it,
 *	Although the input may come from either of
 *		system command line
 *		options file
 *		interactive command line
 *	the behavior is slightly different if the global menuflag is set
 */

void
opt_process(argc,argv)
int	argc;
char	*argv[];
{
    char		c;
    char		*s;
    int		iword;
    ARGVECTOR	agvect,*ag;
    
    /*
     * convert the argument vector (argc,argv) into
     * an ARGVECTOR structure, to ease manipulations
     */
    
    if( argc==0 )
		return;
    
    ag = &agvect;
    ag_new(argc,argv,ag);

    if(DEBUG)
    {
		ag_fprint(stderr,ag);
    }

    /* Loop through the options in the argument vector */
    
    while( !ag_end(ag) )
    {	
		if( ag_eow(ag)	)		/* if necessary...      */
			ag_w_advance(ag);	/* advance to next word */
		
		if(DEBUG)
			if( ag->ic != 0 )		/* this should never happen */
				opt_warning("opt_process: not on first character");
		
		c=ag_c_advance(ag);		/* first character of word */
		
		/* ------ */
		/* switch */
		/* ------ */
		
		switch( c )
		{
		case DELIM:
		case ALTDELIM:
			/* if unadorned "-" */
			if( ag_eow(ag) )
			{
				if (!menuflag && !fileflag)
				{
					usage("");				/* usage message */
					opt_abort_run();
				}
				ag_clear(ag);
			}
			/* if "--something" */
			else
			if( ag_c(ag) == c )
			{
				if (!menuflag && !fileflag)
				{
					usage(argnext(ag));
					opt_abort_run();
				}
			}
			/* if "-something" */
			else
			{
				iword = ag_w_number(ag);
				while( iword==ag_w_number(ag) && !ag_eow(ag) )
					opt_delim(ag);
			}
			break;

		case OPTFROMFILE:
			if(1)
			{
				flag tmp_fileflag;
				tmp_fileflag = fileflag;
				fileflag = True;
				opt_fromfname(argnext(ag));
				fileflag = tmp_fileflag;
			}
			break;

		case OPTTOFILE:
			opt_tofname(argnext(ag));
			break;

		case HELPCH:
			if( !fileflag)
				opt_help(argnext(ag));
			break;

		case INTERACT:
			if ( !menuflag )		/* If not called already */
				opt_menu();				/* Call the menu */	
			else						/* otherwise */
			{
				menuflag=False;			/* turn off menu */
				ag_clear(ag);
			}
			break;
		case IGNOREEOL:
			ag_clear(ag);
			break;
		case RUN:
			if( run_fcn != NULL )
				opt_begin_run(run_fcn);
			else
			{
				/* if run_fcn is not set, and 'RUN' is called
				 * from the menu, then exit the menu, so that
				 * the routine is run, and then program will exit
				 */
				if ( menuflag )
				{
					menuflag=False;			/* turn off menu */
					ag_clear(ag);
				}
				else
				{
					/* RUN called from a file or the command line:
					 * There is no reason to be doing this.
					 */
					opt_warning("No Run Function has been registered");
				}
				break;
				
			case QUITCH:
				opt_quit();
				break;
				
			case BANG:
				if (!menuflag)
					opt_warning("Shell can only be invoked from the menu");
				else
				{
					sprintf(gstr,"Shell to system invalid unless \'%c\'",BANG);
					strcat(gstr," is the first character in the line\n");
					opt_warning(gstr);
				}
#if 0
				/* bang...shell to system */
				if(1)
				{
					char s[160];
					strcpy(s,argnext(ag));
					system(s);
					break;
				}
#endif

			case ' ':		/* blanks and empty characters, ignore */
			case '\t':
			case '\0':
				break;
				
			default:
				/* in the default case, option may be undelimited */
				/* ---------------------------------------------- */
				ag_backspace(ag);
				if(DEBUG)
				{
					sprintf(gstr,
							"opt_process: in default section [%s]\n",ag_s(ag));
					opt_warning(gstr);
				}
				if(1)
				{
					char s[80];
					strcpy(s,ag_s(ag));
					
					if( opt_undelim(ag) == 0)
					{
						sprintf(gstr,
								"%c (in %s) is invalid delimeter\n",
								c,s);
						opt_warning(gstr);
					}
				}
				break;
			}
		}
	}
}/*opt_process*/

/* opt_lineprocess()
 * process a string, by converting it first into an argument vector
 * then calling opt_process
 * return the number of processed arguments
 */

int
opt_lineprocess(line)
char *line;
{
    int nargc;
    char **nargv;

    if( line==NULL || *line=='\0') return(0);
 
    line2argv(&nargc,&nargv,line);
    opt_process(nargc,nargv);
    return(nargc);
}
/*	line2argv(): converts a one-line string into an argument vector */

static int
line2argv(pargc,pargv,line)
int	*pargc;
char	***pargv;
char	*line;
{
    char	*lincp;
    if(line==NULL)
    {	
	*pargc = 0;
	**pargv = NULL;
	return(0);
    }
	/*
	 * First thing to do is copy the line into
	 * a buffer ("lincp") so that input line will
 	 * not be corrupted -- also so that input line
 	 * doesn't have to be double null terminated
 	 */
    lincp = (char *)calloc(strlen(line)+2,sizeof(char));
    strcpy(lincp,line);
	/*
	 * Next step is to double null terminate 
	 * the copied line
	 */
    lincp[strlen(line)+1]='\0';
    	/* count words in line */
    *pargc = l2a(lincp,NULL);
    	/* allocate array for arg vector */
    *pargv = (char **)malloc(((*pargc)+1)*sizeof(char *));
    	/* fill arg vector with words in line */
    l2a(lincp,*pargv);
	/*
	 * Note that lincp cannot be freed since
	 * that space is used by pargv
	 */
    return(*pargc);
}

#define	QUOTE	'\"'
#define	BKSLASH	'\\'

/* l2a */
/*	l2a() is slave routine to line2argv()           */
/*	if argv==NULL then count the words in the line	*/
/*	if argv!=NULL then put those words into argv[]  */
/* 	WARNINGS:
 *	l2a assumes that input line is double-null terminated!!
 *	the line buffer is pointed to by argv[]'s so do not
 *	free the input line buffer
 */
	/* quoted material counts as a single word */
	/* so that -s"string with spaces"-g is parsed */
	/* into 
		-s
	        string with spaces
		-g
	*/
	/* Comment: should be able to escape with backslash */

static int
l2a(line,argv)
char	*line;
char	**argv;
{
    flag inquote=False;	/* flag: inside quotation */
    int	 iarg;
    
    for(iarg=0; *line != '\0'; ++iarg)
    {
		if(!inquote)
		{
			while( isspace(*line) )
				++line;	/* skip leading blank spaces */
			if( *line == QUOTE )
			{
				inquote=True;
				++line;	/* skip past leading quote */
			}
		}
		if(argv!=NULL)			/* point to */
			argv[iarg] = line;	/* first character of line */
		
		while( !break_word(inquote,line) )
			++line;
		
		if( *line==QUOTE )		/* toggle quote */
		{	
			inquote = (inquote==True ? False : True );
			if(argv==NULL)	++line;	/* skip past quote */
		}
		
		if(argv!=NULL)
		{
			*line='\0';	/* Null terminate string */
			++line;		/* and go to next character */
		}
		else 
			while( isspace(*line) )
				++line;		/* skip trailing blanks */
		
    }
    return(iarg);
}
static flag
break_word(inquote,line)
flag	inquote;
char	*line;
{
    if( *line == '\0' || *line==QUOTE )
		return(True);
    if( !inquote && isspace(*line) )
		return(True);
    
    return(False);
}


	/* --------------------------- */
	/* write out a usage statement */
	/* --------------------------- */

/* usage("") gives minimal usage message 
   usage("-") gives fuller usage message
   usage("--") gives output document
 */

static void short_usage();
static void long_usage();
static void doc_usage();

void
usage(s)
char	*s;
{
	if (s==NULL || *s=='\0')
	{
		short_usage();
		sprintf(gstr,"For a list of options, type:\n"), opt_message(gstr);
		sprintf(gstr,"\t%s %c%c\n",opt_program_name,DELIM,DELIM);
		doc_usage();
		return;
	}
	
    else
	if (*s == DELIM )
	{
		++s;
		if (*s=='\0')
		{
			short_usage();
			doc_usage();
			long_usage();
			return;
		}
		if (*s==DELIM)
		{
			opt_doc();
			return;
		}
		
	}
}
static void
short_usage()
{
    if(Title != NULL)
		sprintf(gstr,"%s\n",Title), opt_message(gstr);
    if(Usage != NULL)
		sprintf(gstr,"[%s] %s\n",opt_program_name,Usage), opt_message(gstr);
    sprintf(gstr,"To invoke the menu, type:\n\t%s %c\n",
			opt_program_name,INTERACT), 
	opt_message(gstr);
}	
static void
long_usage()
{
	sprintf(gstr,"The options are:\n"), opt_message(gstr);
	opt_usage();

}
static void
doc_usage()
{
		if(doc_fcn != NULL)
		{
			sprintf(gstr,"For fuller documentation, type:\n\t"), 
			opt_message(gstr);
			sprintf(gstr,"%s %c%c%c\n",opt_program_name,
					DELIM,DELIM,DELIM), 
			opt_message(gstr);
		}

}

	/* --------------------------------- */
	/* put current options in named file */
	/* --------------------------------- */

int
opt_tofname(fname)
char	*fname;
{
    FILE	*fp;
    
    if( *fname != OPTTOFILE )
    {
	free((char *)optfile_name);
	optfile_name = append_string(fname,"");
    }
    if( access(optfile_name,0)==0 )
    {
	sprintf(gstr,"Options file [%s] has been overwritten\n",
		optfile_name), opt_message(gstr);
	backup_file(optfile_name);
    }
    fp = fopen(optfile_name,"w");

    if(fp==NULL)
    {
	sprintf(gstr,"cant open file %s\n",fname), opt_message(gstr);
	return(0);
    }
    opt_tofile(fp);
    fclose(fp);
    return(1);
}
#ifdef __TURBOC__
backup_file(fname)
char *fname;
{}
#else
backup_file(fname)
char *fname;
{
    char fname_backup[80];
    sprintf(fname_backup,"%s%s",fname,"~");
    sprintf(gstr,"%s %s %s","cp",fname,fname_backup);
    system(gstr);
    sprintf(gstr,"File [%s] is backup file\n",fname_backup);
    opt_message(gstr);
}
#endif
	/* ----------------------------------------- */
	/* get and process options from a named file */
	/* ----------------------------------------- */

#define	MAXOPLINE	256
int
opt_fromfname(fname)
char	*fname;
{
    FILE	*fp;
    char	line[MAXOPLINE+2];	/* leave room for termination */

    if( *fname != OPTFROMFILE )		/* if not default file */
    {
	if( access(fname,0)!=0 )	/* if file doesn't exist */
	{
	    sprintf(gstr,"File [%s] does not exist\n",fname);
	    opt_message(gstr);
	    return(0);
	}
	else
	{
	    free((char *)optfile_name);
	    optfile_name = append_string(fname,"");
	}
    }
    fp = fopen(optfile_name,"r");
    
    if(fp==NULL)
    {
	sprintf(gstr,"Cannot open options file [%s]\n",optfile_name);
	opt_warning(gstr);
	return(0);
    }
    
    while( opt_getline(line,fp) > 0 )
    	opt_lineprocess(line);
    
    fclose(fp);
    return(1);
}
int
opt_getline(line,fp)
char	*line;
FILE	*fp;
{
    int	c;
    int	count=0;
	
    while( (c=getc(fp)) != '\n' && c!=EOF )
    {
		*line = (char)c;
		++line;
		if( ++count > MAXOPLINE-3 )
		{
			opt_warning("Options line too long");
			break;
        }
    }
    *line++ = '\0';		/* double terminate line !! */
    *line++ = '\0';
    
    return(count);
}/*opt_getline*/

/* ------------------- */
/* basic help function */
/* ------------------- */

void
opt_help(s)
char	*s;
{
    if(s==NULL || *s=='\0')
    {
	sprintf(gstr,"\t%c %-20s\n",DELIM,"Options delimiter"), 
	opt_message(gstr); 
	sprintf(gstr,"\t%c %-20s\n",HELPCH,"Help"), 
	opt_message(gstr);
	sprintf(gstr,"\t%c %-20s\n",RUN,"Run program and return to menu"), 
	opt_message(gstr);
	sprintf(gstr,"\t%c %-20s\n",BANG,"Shell to Operating System"), 
	opt_message(gstr); 
	if (menuflag)
		sprintf(gstr,"\t%c %-20s\n",INTERACT,"Exit menu"), 
		opt_message(gstr); 
	else
		sprintf(gstr,"\t%c %-20s\n",INTERACT,"Invoke menu"), 
		opt_message(gstr); 
	sprintf(gstr,"\t%c %-20s\n",ADDITIONAL_OPTS,"Additional options"), 
	opt_message(gstr);
	sprintf(gstr,"\t%c<filename> %-20s\n",OPTFROMFILE,
		"Get options from file",optfile_name), 
	opt_message(gstr);
	sprintf(gstr,"\t%c%c %-2s [%s]\n",OPTFROMFILE,OPTFROMFILE,
		"Get options from file",optfile_name), 
	opt_message(gstr);
	sprintf(gstr,"\t%c<filename> %-20s\n",OPTTOFILE,
		"Put options in file"), 
	opt_message(gstr);
	sprintf(gstr,"\t%c%c %-2s [%s]\n",OPTTOFILE,OPTTOFILE,
		"Put options in file",optfile_name), 
	opt_message(gstr);
	sprintf(gstr,"\t%c %-20s\n",QUITCH,"Quit"), 
	opt_message(gstr);
    }
	else
	{
		/* first check if help is available for single character delimiter */
		if( s[1]=='\0' && opt_number(s[0]) >=0 )
			opt_get_help(s[0]); 
		else
		{
			if( help_fcn==NULL )
				sprintf(gstr,"Help unavailable for: [%s]\n",s), 
				opt_message(gstr);
			else
				(*help_fcn)(s);
		}
	}
}
/* ------ */
/* quit() */ 
/* ------ */
void
opt_quit()
{
    if( quit_fcn == NULL )
		opt_abort_run();
    else
	{
		(*quit_fcn)();
		opt_abort_run();
	}
}
/* ---------- */
/* document() */
/* ---------- */
void
opt_doc()
{
    if( doc_fcn == NULL )
	return;
    else
	(*doc_fcn)();
}
/* opt_menu.c */


#ifndef	SINGLEFILE
#include <stdio.h>
#include <ctype.h>
#ifdef convex
#include <strings.h>
#else
#include <string.h>
#endif
#ifdef __TURBOC__
#include <alloc.h>
#endif
#include "opt_p.h"
#endif /* SINGLEFILE */

/* --------------------- menu flag ------------------- */

flag menuflag=False;

static char mgstring[160];	/* global menu string */

#define menu_wr_string(str)       opt_message(str)
#define menu_getresponse(respond) opt_getline(respond,stdin)

static void write_the_menu();
static int auto_prefix_delim();


/* ----------------------------------------------------	*/
/*  opt_menu:	Get options from an interactive menu	*/
/* ----------------------------------------------------	*/

#define	MAXRESPONDLINE	280
#ifndef	MAXOPTSINMENU
#define	MAXOPTSINMENU	20
#endif

void
opt_menu()
{
    char respond[MAXRESPONDLINE+2];
    static int maxoptsinmenu=MAXOPTSINMENU;
	flag fullmenu;
    int	iop,iopfrom,iopto;

    menuflag=True;	/* turn on MENUFLAG in case it is not set already */
    
    iopfrom = 0;
    iopto = ( nregopts < maxoptsinmenu ? nregopts : maxoptsinmenu );
    
	respond[0]='\0';

	opt_wr_title();
	write_the_menu(iopfrom,iopto);

    while( menuflag )
    {
	    menu_wr_string("-> ");
		menu_getresponse(respond);
		
		switch(*respond)
		{
		case ADDITIONAL_OPTS:
			if( respond[1] != '\0' && respond[1] != ' ' )
			{
				maxoptsinmenu = atoi(respond+1);
				if(maxoptsinmenu < 1)
					maxoptsinmenu = nregopts;
				sprintf(mgstring,"Scroll %d options\n",maxoptsinmenu);
				menu_wr_string(mgstring);
				iopfrom = 0;
				iopto = 
					( nregopts < maxoptsinmenu ? nregopts : maxoptsinmenu );
			}
			else
			{
				iopfrom += maxoptsinmenu;
				if( iopfrom > nregopts)
					iopfrom = 0;
				iopto = iopfrom + maxoptsinmenu;
				if( iopto > nregopts )
					iopto = nregopts;
			}
			write_the_menu(iopfrom,iopto);
			break;
		case INTERACT:
			menuflag=False;
			break;
	    case BANG:
			system( respond+1 );
			break;
		case '\0':
			write_the_menu(iopfrom,iopto);
			break;
		case QUITCH:
			/* only quit if the QUITCH is followed by whitespace */
			if ( respond[1]=='\0' || respond[1]==' ' )
				opt_abort_run(0);
			break;
		case DELIM:
		case ALTDELIM:
			opt_lineprocess(respond);
			break;
		default:
			auto_prefix_delim(respond);
			opt_lineprocess(respond);
			break;
		}
	}
}/* opt_menu */


/**********
 * write_the_menu:
 *	write the menu including options from iopfrom to iopto.
 */
static void
write_the_menu(iopfrom,iopto)
int iopfrom,iopto;
{
	int iop;
	flag fullmenu;

	fullmenu = ((iopfrom==0 && iopto==nregopts) ? True : False );

	if( !fullmenu )
	{
		sprintf(mgstring,"menu: %d->%d [%d]\n",iopfrom,iopto,nregopts);
		menu_wr_string(mgstring);
	}

	for(iop=iopfrom; iop<iopto; ++iop)
	{
		char *s;
		s = opt_mstring(iop);
		if (s!=NULL)
		{
			strcpy( mgstring, s );
			menu_wr_string(mgstring);
			menu_wr_string("\n");
		}
	}
	if (!fullmenu)
	{
		sprintf(mgstring,"%c Additional options\n",ADDITIONAL_OPTS);
		menu_wr_string(mgstring);
	}
	sprintf(mgstring,"(Type %c for Help)\n",HELPCH);
	menu_wr_string(mgstring);
}

/*	auto_prefix_delim:	
 *		this is a fru-fru piece of code that automatically
 *		sticks a DELIM character onto the front of a string
 *		in cases where it imagines that that is what the user
 *		really meant.  Thus
 *		-> m4
 *		gives the same effect as
 *		-> -m4
 *		But be warned that this only applies in limited cases.
 *		Eg.,
 *		-> m4 b3
 *		is not the same as
 *		-> -m4 -b3
 *
 *		a '-' will be prepended in the case that 
 *		the first character is a registered name
 */
static int
auto_prefix_delim(r)
char *r;
{
    if( opt_number( *r ) != -1 )
    {
		int len;
		len = strlen(r)+1;	/* +1 since double terminated */
		while(len>=0)
		{
			r[len+1]=r[len];
			--len;
		}
		r[0]=DELIM;
		return(1);
    }
    else
		return(0);
}/* auto_prefix_delim */


/**************************
 *  some useful utilities *
 **************************/
/*
 *  1) Variable argument lists: for error messages
 *     opt_errmess(), gives message and then aborts run
 *  2) Long Jump: for aborting run() without losing the entire job
 *     opt_begin_run()
 *     opt_abort_run()
 *  3) Signal: trapping ^C so that it aborts run()
 *     
 */
/*  Can be disabled by setting constants
 *                        DISABLE_VARARG, 
 *                        DISABLE_LONGJUMP, 
 *                        DISABLE_SIGNAL
 */
#ifndef SINGLEFILE
#include <stdio.h>
#include "opt_p.h"
#endif

static void   set_signal(/* void */);
static void unset_signal(/* void */);
static void catch_signal(/* void */);


void
opt_message(s)
char *s;
{
	if (s != NULL)
		fputs(s,stderr);
}
void
opt_warning(s)
char *s;
{
	fputs(opt_program_name,stderr);
	fputs(":: ",stderr);
    fputs("OPT Warning: ",stderr);
    fputs(s,stderr);
	fputs("\n",stderr);
}
void
opt_fatal(s)
char *s;
{
	fputs(opt_program_name,stderr);
	fputs(":: ",stderr);
    fputs("OPT Fatal error: ",stderr);
    fputs(s,stderr);
    exit(1);
}

/**********
 * VARARG *
 **********/

#if DISABLE_VARARG

void
opt_errmess(s)
char *s;
{
	fputs(opt_program_name,stderr);
	fputs(":: ",stderr);
    fputs(s,stderr);
    opt_abort_run();
}

#else /* if not DISABLE_VARARGS */

#ifdef __TURBOC__
/* Turbo-C implements variable argument lists differently than SUN */

#ifndef SINGLEFILE
#include <stdarg.h>
#endif

void
opt_errmess(char *format, ...)
{
    va_list argptr;
    
    va_start(argptr,format);
    vfprintf(stderr,format,argptr);
    va_end(argptr);
    opt_abort_run();
}
#else /* if not __TURBOC__ but default instead */
#ifndef SINGLEFILE
#include <stdarg.h>
#endif
#endif /* if __TURBOC__ */
#endif /* end VARARGS */

/************
 * LONGJUMP *
 ************/

#if DISABLE_LONGJUMP

int
opt_begin_run(run)
int	(*run)();
{    return( (*run)() );
}
void
opt_abort_run()
{    exit(1);
}

#else /* if not DISABLE_LONGJUMP */

#ifndef SINGLEFILE
#include <setjmp.h>
#endif

static jmp_buf	opt_jumpstart;
static int		opt_jump_set=FALSE;

void
opt_abort_run()
{
    if(opt_jump_set)
		longjmp(opt_jumpstart,1);
    else
		exit(1);
}
int
opt_begin_run(run)
int	(*run)();
{
    int value;

    opt_jump_set=TRUE;
	set_signal();

    value = setjmp(opt_jumpstart);
    if(value!=0)
		opt_message("Run aborted...try again\n");
    else
		value = (*run)();
	
	unset_signal();
	opt_jump_set=FALSE;

    return value;
}
#endif /* end LONGJUMP */

/**********
 * SIGNAL *
 **********/

#if DISABLE_SIGNAL

static void
set_signal()
{}
static void
unset_signal()
{}
#else

#ifndef SINGLEFILE
#include <signal.h>
#endif

static	void (*old_catcher)();

static void
set_signal()
{
    old_catcher = signal(SIGINT,catch_signal);
}
static void
unset_signal()
{
	signal(SIGINT,old_catcher);
}
#ifdef __TURBOC__
   static void catch_signal(sig)
   int sig;
#else
#ifdef convex
   static void catch_signal(sig,code,scp)
   int sig, code; 
   struct sigcontext *scp;
#else /* default */
   static void catch_signal(sig,code,scp,addr)
   int sig, code;
   struct sigcontext *scp;
   char *addr;
#endif
#endif
{
    opt_message("\nOPT Interrupted:\n");
    longjmp(opt_jumpstart,1);
    perror("Did not long-jump");
    exit(0);
}
#endif /* end SIGNAL */
