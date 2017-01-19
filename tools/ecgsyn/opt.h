/*
opt.h  version 3.17  -	User Include File for options package.

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
