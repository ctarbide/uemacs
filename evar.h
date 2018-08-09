/*	EVAR.H
 *
 *	Environment and user variable definitions
 *
 *	written 1986 by Daniel Lawrence
 *	modified by Petri Kutvonen
 */
#ifndef EVAR_H_
#define EVAR_H_

/* Max #chars in a var name. */
#define	NVSIZE	10

/* Structure to hold user variables and their definitions. */
struct user_variable {
	char u_name[NVSIZE + 1]; /* name of user variable */
	char *u_value;		 /* value (string) */
};

/* List of recognized environment variables. */

static char *envars[] = {
	"fillcol",		/* current fill column */
	"pagelen",		/* number of lines used by editor */
	"curcol",		/* current column pos of cursor */
	"curline",		/* current line in file */
	"ram",			/* ram in use by malloc */
	"flicker",		/* flicker supression */
	"curwidth",		/* current screen width */
	"cbufname",		/* current buffer name */
	"cfname",		/* current file name */
	"sres",			/* current screen resolution */
	"debug",		/* macro debugging */
	"fdebug",		/* file debugging */
	"status",		/* returns the status of the last command */
	"palette",		/* current palette string */
	"asave",		/* # of chars between auto-saves */
	"acount",		/* # of chars until next auto-save */
	"lastkey",		/* last keyboard char struck */
	"curchar",		/* current character under the cursor */
	"discmd",		/* display commands on command line */
	"version",		/* current version number */
	"progname",		/* returns current prog name - "MicroEMACS" */
	"seed",			/* current random number seed */
	"disinp",		/* display command line input characters */
	"wline",		/* # of lines in current window */
	"cwline",		/* current screen line in window */
	"target",		/* target for line moves */
	"search",		/* search pattern */
	"replace",		/* replacement pattern */
	"match",		/* last matched magic pattern */
	"kill",			/* kill buffer (read only) */
	"cmode",		/* mode of current buffer */
	"gmode",		/* global modes */
	"tpause",		/* length to pause for paren matching */
	"pending",		/* type ahead pending flag */
	"lwidth",		/* width of current line */
	"line",			/* text of current line */
	"gflags",		/* global internal emacs flags */
	"rval",			/* child process return value */
	"tab",			/* tab 4 or 8 */
	"overlap",
	"jump",
#if SCROLLCODE
	"scroll",		/* scroll enabled */
#endif
};

/* And its preprocesor definitions. */

#define	EVFILLCOL	0
#define	EVPAGELEN	1
#define	EVCURCOL	2
#define	EVCURLINE	3
#define	EVRAM		4
#define	EVFLICKER	5
#define	EVCURWIDTH	6
#define	EVCBUFNAME	7
#define	EVCFNAME	8
#define	EVSRES		9
#define	EVDEBUG		10
#define EVFDEBUG	11
#define	EVSTATUS	12
#define	EVPALETTE	13
#define	EVASAVE		14
#define	EVACOUNT	15
#define	EVLASTKEY	16
#define	EVCURCHAR	17
#define	EVDISCMD	18
#define	EVVERSION	19
#define	EVPROGNAME	20
#define	EVSEED		21
#define	EVDISINP	22
#define	EVWLINE		23
#define EVCWLINE	24
#define	EVTARGET	25
#define	EVSEARCH	26
#define	EVREPLACE	27
#define	EVMATCH		28
#define	EVKILL		29
#define	EVCMODE		30
#define	EVGMODE		31
#define	EVTPAUSE	32
#define	EVPENDING	33
#define	EVLWIDTH	34
#define	EVLINE		35
#define	EVGFLAGS	36
#define	EVRVAL		37
#define EVTAB		38
#define EVOVERLAP	39
#define EVSCROLLCOUNT	40
#define EVSCROLL	41

enum function_type {
	NILNAMIC = 0,
	MONAMIC,
	DYNAMIC,
	TRINAMIC,
};

/* List of recognized user functions. */
struct user_function {
	char *f_name;
	enum function_type f_type;
};

static struct user_function funcs[] = {
	{ "add", DYNAMIC },	/* add two numbers together */
	{ "sub", DYNAMIC },	/* subtraction */
	{ "tim", DYNAMIC },	/* multiplication */
	{ "div", DYNAMIC },	/* division */
	{ "mod", DYNAMIC },	/* mod */
	{ "neg", MONAMIC },	/* negate */
	{ "cat", DYNAMIC },	/* concatinate string */
	{ "lef", DYNAMIC },	/* left string(string, len) */
	{ "rig", DYNAMIC },	/* right string(string, pos) */
	{ "mid", TRINAMIC },	/* mid string(string, pos, len) */
	{ "not", MONAMIC },	/* logical not */
	{ "equ", DYNAMIC },	/* logical equality check */
	{ "les", DYNAMIC },	/* logical less than */
	{ "gre", DYNAMIC },	/* logical greater than */
	{ "seq", DYNAMIC },	/* string logical equality check */
	{ "sle", DYNAMIC },	/* string logical less than */
	{ "sgr", DYNAMIC },	/* string logical greater than */
	{ "ind", MONAMIC },	/* evaluate indirect value */
	{ "and", DYNAMIC },	/* logical and */
	{ "or", DYNAMIC },	/* logical or */
	{ "len", MONAMIC },	/* string length */
	{ "upp", MONAMIC },	/* uppercase string */
	{ "low", MONAMIC },	/* lower case string */
	{ "tru", MONAMIC },	/* Truth of the universe logical test */
	{ "asc", MONAMIC },	/* char to integer conversion */
	{ "chr", MONAMIC },	/* integer to char conversion */
	{ "gtk", NILNAMIC },	/* get 1 charater */
	{ "rnd", MONAMIC },	/* get a random number */
	{ "abs", MONAMIC },	/* absolute value of a number */
	{ "sin", DYNAMIC },	/* find the index of one string in another */
	{ "env", MONAMIC },	/* retrieve a system environment var */
	{ "bin", MONAMIC },	/* loopup what function name is bound to a key */
	{ "exi", MONAMIC },	/* check if a file exists */
	{ "fin", MONAMIC },	/* look for a file on the path... */
	{ "ban", DYNAMIC },	/* bitwise and   9-10-87  jwm */
	{ "bor", DYNAMIC },	/* bitwise or    9-10-87  jwm */
	{ "bxo", DYNAMIC },	/* bitwise xor   9-10-87  jwm */
	{ "bno", MONAMIC },	/* bitwise not */
	{ "xla", TRINAMIC },	/* XLATE character string translation */
};

/* And its preprocesor definitions. */

#define	UFADD		0
#define	UFSUB		1
#define	UFTIMES		2
#define	UFDIV		3
#define	UFMOD		4
#define	UFNEG		5
#define	UFCAT		6
#define	UFLEFT		7
#define	UFRIGHT		8
#define	UFMID		9
#define	UFNOT		10
#define	UFEQUAL		11
#define	UFLESS		12
#define	UFGREATER	13
#define	UFSEQUAL	14
#define	UFSLESS		15
#define	UFSGREAT	16
#define	UFIND		17
#define	UFAND		18
#define	UFOR		19
#define	UFLENGTH	20
#define	UFUPPER		21
#define	UFLOWER		22
#define	UFTRUTH		23
#define	UFASCII		24
#define	UFCHR		25
#define	UFGTKEY		26
#define	UFRND		27
#define	UFABS		28
#define	UFSINDEX	29
#define	UFENV		30
#define	UFBIND		31
#define	UFEXIST		32
#define	UFFIND		33
#define UFBAND		34
#define UFBOR		35
#define UFBXOR		36
#define	UFBNOT		37
#define	UFXLATE		38

#endif  /* EVAR_H_ */
