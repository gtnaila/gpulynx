
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "./cod.y"

#include "config.h"
#ifdef SEGMENTED_POINTERS
int cod_segmented_pointers = 1;
#else
int cod_segmented_pointers = 0;
#endif
#ifdef KPLUGINS_INTEGRATION
int cod_kplugins_integration = 1;
#else
int cod_kplugins_integration = 0;
#endif
#ifndef LINUX_KERNEL_MODULE
#include "stdio.h"
#endif
#ifdef LINUX_KERNEL_MODULE
#ifndef MODULE
#define MODULE
#endif
#ifndef __KERNEL__
#define __KERNEL__
#endif
#include <linux/kernel.h>
#include <linux/module.h>
#endif
#ifndef LINUX_KERNEL_MODULE
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#endif
#include "fm.h"
#include "cod.h"
#include "cod_internal.h"
#include "assert.h"
#ifndef LINUX_KERNEL_MODULE
#include <ctype.h>
#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif
#include <string.h>
#else
#include <linux/ctype.h>
#include <linux/string.h>
#include <linux/mm.h>
#endif
#include "structs.h"
#ifdef HAVE_DILL_H
#include "dill.h"
#else
enum {
    DILL_C,    /* char */
    DILL_UC,   /* unsigned char */
    DILL_S,    /* short */
    DILL_US,   /* unsigned short */
    DILL_I,    /* int */
    DILL_U,    /* unsigned */
    DILL_L,    /* long */
    DILL_UL,   /* unsigned long */
    DILL_P,    /* pointer */
    DILL_F,    /* floating */
    DILL_D,    /* double */
    DILL_V,    /* void */
    DILL_B,    /* block structure */
    DILL_EC,
    DILL_ERR   /* no type */
};
#endif
#if defined(_MSC_VER)
#define strdup _strdup
#endif
#ifndef LINUX_KERNEL_MODULE
#ifdef STDC_HEADERS
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#else
#include "kecl.h"
#define malloc (void *)DAllocMM
#define free(a) DFreeMM((addrs_t)a)
#define realloc(a,b) DReallocMM((addrs_t)a,b)
#define fprintf(fmt, args...) printk(args);
#define printf printk
char *strdup(const char *s)
{
	char *p;

	p = (char *)kmalloc(strlen(s)+1, GFP_KERNEL);
	if (p != NULL)
		strcpy(p,s);
	return p;
}
#endif
#define yyparse cod_yyparse
#define yylex cod_yylex
#define yyrestart cod_yyrestart
#define yywrap cod_yywrap
#define yyerror cod_yyerror
#define yy_create_buffer cod_yy_create_buffer
#define yy_delete_buffer cod_yy_delete_buffer
#define yy_flush_buffer cod_yy_flush_buffer
#define yy_init_buffer cod_yy_init_buffer
#define yy_load_buffer_state cod_yy_load_buffer_state
#define yy_scan_buffer cod_yy_scan_buffer
#define yy_scan_bytes cod_yy_scan_bytes
#define yy_scan_string cod_yy_scan_string
#define yy_switch_to_buffer cod_yy_switch_to_buffer
#define yychar cod_yychar
#define yyin cod_yyin
#define yyleng cod_yyleng
#define yylval cod_yylval
#define yynerrs cod_yynerrs
#define yyout cod_yyout
#define yytext cod_yytext
#define yyset_out cod_yyset_out
#define yyset_lineno cod_yyset_lineno
#define yyset_in cod_yyset_in
#define yyset_debug cod_yyset_debug
#define yyrealloc cod_yyrealloc
#define yyalloc cod_yyalloc
#define yyfree cod_yyfree
#define yypush_buffer_state cod_yypush_buffer_state
#define yypop_buffer_state cod_yypop_buffer_state
#define yylex_destroy cod_yylex_destroy
#define yyget_out cod_yyget_out
#define yyget_lineno cod_yyget_lineno
#define yyget_in cod_yyget_in
#define yyget_debug cod_yyget_debug
#define yyget_text cod_yyget_text
#define yyget_leng cod_yyget_leng

static char *create_string_from_yytext();
extern int yylex();
extern int yyparse();
static sm_ref yyparse_value;
static int yyerror_count = 1;
extern void yyerror(char *str);
static int parsing_type = 0;
static int parsing_param_spec = 0;
static cod_parse_context yycontext;
static sm_ref cod_build_parsed_type_node(cod_parse_context c, char *name, sm_list l);
static sm_list
cod_dup_list(sm_list list)
{
    sm_list ret_list, new_list = NULL;
    sm_list *last_p = &ret_list;
    while (list != NULL) {
	*last_p = new_list = malloc(sizeof(struct list_struct));
	last_p = &(new_list->next);
	new_list->node = malloc(sizeof(*(list->node)));
	memcpy(new_list->node, list->node, sizeof(*(list->node)));
	list = list->next;
    }
    *last_p = NULL;
    return ret_list;
}


/* Line 189 of yacc.c  */
#line 232 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ARROW = 258,
     LPAREN = 259,
     RPAREN = 260,
     LCURLY = 261,
     RCURLY = 262,
     COLON = 263,
     LBRACKET = 264,
     RBRACKET = 265,
     DOT = 266,
     STAR = 267,
     AT = 268,
     SLASH = 269,
     MODULUS = 270,
     PLUS = 271,
     MINUS = 272,
     LEQ = 273,
     LT = 274,
     GEQ = 275,
     GT = 276,
     EQ = 277,
     NEQ = 278,
     LEFT_SHIFT = 279,
     RIGHT_SHIFT = 280,
     ASSIGN = 281,
     LOG_OR = 282,
     LOG_AND = 283,
     ARITH_OR = 284,
     ARITH_AND = 285,
     ARITH_XOR = 286,
     INC_OP = 287,
     DEC_OP = 288,
     BANG = 289,
     SEMI = 290,
     IF = 291,
     ELSE = 292,
     FOR = 293,
     WHILE = 294,
     CHAR = 295,
     SHORT = 296,
     INT = 297,
     LONG = 298,
     UNSIGNED = 299,
     SIGNED = 300,
     FLOAT = 301,
     DOUBLE = 302,
     VOID = 303,
     STRING = 304,
     STATIC = 305,
     STRUCT = 306,
     UNION = 307,
     CONST = 308,
     SIZEOF = 309,
     TYPEDEF = 310,
     RETURN_TOKEN = 311,
     PRINT = 312,
     COMMA = 313,
     DOTDOTDOT = 314,
     integer_constant = 315,
     string_constant = 316,
     floating_constant = 317,
     identifier_ref = 318,
     type_id = 319
   };
#endif
/* Tokens.  */
#define ARROW 258
#define LPAREN 259
#define RPAREN 260
#define LCURLY 261
#define RCURLY 262
#define COLON 263
#define LBRACKET 264
#define RBRACKET 265
#define DOT 266
#define STAR 267
#define AT 268
#define SLASH 269
#define MODULUS 270
#define PLUS 271
#define MINUS 272
#define LEQ 273
#define LT 274
#define GEQ 275
#define GT 276
#define EQ 277
#define NEQ 278
#define LEFT_SHIFT 279
#define RIGHT_SHIFT 280
#define ASSIGN 281
#define LOG_OR 282
#define LOG_AND 283
#define ARITH_OR 284
#define ARITH_AND 285
#define ARITH_XOR 286
#define INC_OP 287
#define DEC_OP 288
#define BANG 289
#define SEMI 290
#define IF 291
#define ELSE 292
#define FOR 293
#define WHILE 294
#define CHAR 295
#define SHORT 296
#define INT 297
#define LONG 298
#define UNSIGNED 299
#define SIGNED 300
#define FLOAT 301
#define DOUBLE 302
#define VOID 303
#define STRING 304
#define STATIC 305
#define STRUCT 306
#define UNION 307
#define CONST 308
#define SIZEOF 309
#define TYPEDEF 310
#define RETURN_TOKEN 311
#define PRINT 312
#define COMMA 313
#define DOTDOTDOT 314
#define integer_constant 315
#define string_constant 316
#define floating_constant 317
#define identifier_ref 318
#define type_id 319




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 159 "./cod.y"

    lx_info info;
    sm_ref reference;
    sm_list list;
    char *string;



/* Line 214 of yacc.c  */
#line 405 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 417 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   671

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNRULES -- Number of states.  */
#define YYNSTATES  242

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    15,    17,    22,
      26,    31,    35,    39,    42,    45,    47,    51,    53,    56,
      59,    62,    65,    68,    71,    74,    77,    82,    84,    89,
      91,    95,    99,   103,   105,   109,   113,   115,   119,   123,
     125,   129,   133,   137,   141,   143,   147,   151,   153,   157,
     159,   163,   165,   169,   171,   175,   177,   181,   183,   185,
     189,   191,   193,   194,   195,   201,   204,   206,   209,   211,
     214,   216,   219,   221,   225,   227,   229,   231,   233,   235,
     237,   239,   241,   243,   245,   247,   249,   251,   253,   259,
     264,   267,   269,   271,   273,   276,   280,   282,   286,   288,
     291,   293,   296,   298,   300,   302,   305,   307,   311,   316,
     320,   325,   329,   331,   334,   337,   341,   343,   346,   349,
     353,   355,   358,   360,   364,   366,   370,   373,   375,   378,
     380,   382,   383,   386,   388,   390,   392,   394,   396,   398,
     401,   405,   410,   411,   414,   418,   421,   427,   435,   445,
     451,   452,   454,   456,   458
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      66,     0,    -1,   115,    -1,   114,    -1,    63,    -1,   121,
      -1,     4,    84,     5,    -1,    67,    -1,    68,     9,    84,
      10,    -1,    68,    11,    63,    -1,    68,     4,    69,     5,
      -1,    68,     4,     5,    -1,    68,     3,    63,    -1,    68,
      32,    -1,    68,    33,    -1,    83,    -1,    69,    58,    83,
      -1,    68,    -1,    32,    70,    -1,    33,    70,    -1,    12,
      71,    -1,    34,    71,    -1,    30,    71,    -1,    16,    71,
      -1,    17,    71,    -1,    54,    70,    -1,    54,     4,   108,
       5,    -1,    70,    -1,     4,   108,     5,    71,    -1,    71,
      -1,    72,    12,    71,    -1,    72,    14,    71,    -1,    72,
      15,    71,    -1,    72,    -1,    73,    16,    72,    -1,    73,
      17,    72,    -1,    73,    -1,    74,    24,    73,    -1,    74,
      25,    73,    -1,    74,    -1,    75,    19,    74,    -1,    75,
      21,    74,    -1,    75,    18,    74,    -1,    75,    20,    74,
      -1,    75,    -1,    76,    22,    75,    -1,    76,    23,    75,
      -1,    76,    -1,    77,    30,    76,    -1,    77,    -1,    78,
      31,    77,    -1,    78,    -1,    79,    29,    78,    -1,    79,
      -1,    80,    28,    79,    -1,    80,    -1,    81,    27,    80,
      -1,    81,    -1,    82,    -1,    70,    26,    83,    -1,    83,
      -1,    82,    -1,    -1,    -1,    89,    87,    90,    88,    35,
      -1,     1,    35,    -1,    91,    -1,    91,    89,    -1,    92,
      -1,    92,    89,    -1,   100,    -1,   100,    89,    -1,   101,
      -1,   101,    26,   110,    -1,    55,    -1,    50,    -1,    40,
      -1,    41,    -1,    42,    -1,    43,    -1,    46,    -1,    47,
      -1,    48,    -1,    45,    -1,    44,    -1,    49,    -1,    64,
      -1,    93,    -1,    94,    63,     6,    95,     7,    -1,    94,
       6,    95,     7,    -1,    94,    63,    -1,    51,    -1,    52,
      -1,    96,    -1,    95,    96,    -1,    99,    97,    35,    -1,
      98,    -1,    97,    58,    98,    -1,   101,    -1,    92,    99,
      -1,    92,    -1,   100,    99,    -1,   100,    -1,    53,    -1,
     102,    -1,   103,   102,    -1,    63,    -1,     4,   101,     5,
      -1,    63,     4,   105,     5,    -1,    63,     4,     5,    -1,
     102,     9,    85,    10,    -1,   102,     9,    10,    -1,    12,
      -1,    12,   104,    -1,    12,   103,    -1,    12,   104,   103,
      -1,    13,    -1,    13,   104,    -1,    13,   103,    -1,    13,
     104,   103,    -1,   100,    -1,   104,   100,    -1,   106,    -1,
     106,    58,    59,    -1,   107,    -1,   106,    58,   107,    -1,
      89,   101,    -1,    99,    -1,    99,   109,    -1,   103,    -1,
      83,    -1,    -1,   111,   112,    -1,   113,    -1,   114,    -1,
     117,    -1,   118,    -1,   119,    -1,   116,    -1,     1,    35,
      -1,    63,     8,   112,    -1,     6,   115,   111,     7,    -1,
      -1,   115,    86,    -1,    56,   120,    35,    -1,    84,    35,
      -1,    36,     4,    84,     5,   112,    -1,    36,     4,    84,
       5,   112,    37,   112,    -1,    38,     4,   120,    35,   120,
      35,   120,     5,   112,    -1,    39,     4,    84,     5,   112,
      -1,    -1,    84,    -1,    60,    -1,    62,    -1,    61,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   285,   285,   289,   295,   301,   303,   309,   311,   318,
     325,   332,   338,   341,   348,   358,   364,   378,   379,   386,
     393,   400,   407,   414,   421,   428,   435,   450,   451,   460,
     462,   471,   480,   491,   493,   502,   513,   515,   524,   535,
     537,   546,   555,   564,   575,   577,   586,   597,   599,   610,
     612,   623,   625,   636,   638,   649,   651,   663,   668,   671,
     682,   687,   692,   699,   691,   771,   777,   782,   788,   793,
     799,   804,   812,   814,   822,   827,   835,   840,   845,   850,
     855,   860,   865,   870,   875,   880,   885,   890,   896,   899,
     902,   908,   909,   915,   916,   927,   978,   983,   995,   998,
    1004,  1009,  1015,  1023,  1031,  1033,  1047,  1056,  1059,  1068,
    1077,  1084,  1094,  1102,  1110,  1118,  1132,  1143,  1154,  1165,
    1185,  1190,  1203,  1204,  1219,  1225,  1241,  1280,  1281,  1292,
    1296,  1300,  1301,  1324,  1325,  1326,  1327,  1328,  1329,  1330,
    1336,  1343,  1351,  1353,  1376,  1384,  1392,  1401,  1413,  1423,
    1436,  1438,  1441,  1448,  1455
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ARROW", "LPAREN", "RPAREN", "LCURLY",
  "RCURLY", "COLON", "LBRACKET", "RBRACKET", "DOT", "STAR", "AT", "SLASH",
  "MODULUS", "PLUS", "MINUS", "LEQ", "LT", "GEQ", "GT", "EQ", "NEQ",
  "LEFT_SHIFT", "RIGHT_SHIFT", "ASSIGN", "LOG_OR", "LOG_AND", "ARITH_OR",
  "ARITH_AND", "ARITH_XOR", "INC_OP", "DEC_OP", "BANG", "SEMI", "IF",
  "ELSE", "FOR", "WHILE", "CHAR", "SHORT", "INT", "LONG", "UNSIGNED",
  "SIGNED", "FLOAT", "DOUBLE", "VOID", "STRING", "STATIC", "STRUCT",
  "UNION", "CONST", "SIZEOF", "TYPEDEF", "RETURN_TOKEN", "PRINT", "COMMA",
  "DOTDOTDOT", "integer_constant", "string_constant", "floating_constant",
  "identifier_ref", "type_id", "$accept", "start", "primary_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "expression",
  "constant_expression", "declaration", "$@1", "@2",
  "declaration_specifiers", "init_declarator", "storage_class_specifier",
  "type_specifier", "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator",
  "specifier_qualifier_list", "type_qualifier", "declarator",
  "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "type_name", "abstract_declarator", "initializer", "statement_list",
  "statement", "labeled_statement", "compound_statement",
  "declaration_list", "jump_statement", "expression_statement",
  "selection_statement", "iteration_statement", "expression_opt",
  "constant", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    66,    67,    67,    67,    68,    68,    68,
      68,    68,    68,    68,    68,    69,    69,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    71,    71,    72,
      72,    72,    72,    73,    73,    73,    74,    74,    74,    75,
      75,    75,    75,    75,    76,    76,    76,    77,    77,    78,
      78,    79,    79,    80,    80,    81,    81,    82,    83,    83,
      84,    85,    87,    88,    86,    86,    89,    89,    89,    89,
      89,    89,    90,    90,    91,    91,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    93,    93,
      93,    94,    94,    95,    95,    96,    97,    97,    98,    99,
      99,    99,    99,   100,   101,   101,   102,   102,   102,   102,
     102,   102,   103,   103,   103,   103,   103,   103,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   108,   108,   109,
     110,   111,   111,   112,   112,   112,   112,   112,   112,   112,
     113,   114,   115,   115,   116,   117,   118,   118,   119,   119,
     120,   120,   121,   121,   121
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     3,     1,     4,     3,
       4,     3,     3,     2,     2,     1,     3,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     4,     1,     4,     1,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     3,
       1,     1,     0,     0,     5,     2,     1,     2,     1,     2,
       1,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     4,
       2,     1,     1,     1,     2,     3,     1,     3,     1,     2,
       1,     2,     1,     1,     1,     2,     1,     3,     4,     3,
       4,     3,     1,     2,     2,     3,     1,     2,     2,     3,
       1,     2,     1,     3,     1,     3,     2,     1,     2,     1,
       1,     0,     2,     1,     1,     1,     1,     1,     1,     2,
       3,     4,     0,     2,     3,     2,     5,     7,     9,     5,
       0,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     142,   142,     0,     3,     0,     0,     1,     0,    76,    77,
      78,    79,    84,    83,    80,    81,    82,    85,    75,    91,
      92,   103,    74,    86,   143,    62,    66,    68,    87,     0,
      70,     0,    65,     0,    67,    69,     0,    90,    71,     0,
       0,   141,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,   152,   154,   153,     4,     7,    17,
      27,    29,    33,    36,    39,    44,    47,    49,    51,    53,
      55,    57,    58,    60,     0,   132,   133,   134,   138,   135,
     136,   137,     5,     0,   112,   116,   106,    63,    72,   104,
       0,   100,     0,    93,     0,   102,     0,   139,     4,     0,
     127,     0,    27,    20,    23,    24,    22,     0,    18,    19,
      21,     0,   150,     0,     0,    25,   151,     0,     0,     0,
       0,     0,     0,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,     0,   120,   114,   113,   118,
     117,     0,     0,     0,     0,   105,    99,    89,    94,     0,
      96,    98,   101,     0,     6,   129,   128,     0,     0,     0,
       0,     0,   144,   140,    12,    11,     0,    15,     0,     9,
      59,    30,    31,    32,    34,    35,    37,    38,    42,    40,
      43,    41,    45,    46,    48,    50,    52,    54,    56,   107,
     121,   115,   119,   109,     0,     0,   122,   124,    64,   130,
      73,   111,    61,     0,    95,     0,    88,    28,     0,   150,
       0,    26,    10,     0,     8,   126,   108,     0,   110,    97,
     146,     0,   149,    16,   123,   125,     0,   150,   147,     0,
       0,   148
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    58,    59,   176,   102,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     213,    24,    33,   152,    25,    87,    26,    91,    28,    29,
      92,    93,   159,   160,    94,    95,   161,    89,    90,   148,
     205,   206,   207,   101,   166,   210,    31,    75,    76,    77,
       4,    78,    79,    80,    81,   117,    82
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -106
static const yytype_int16 yypact[] =
{
      23,  -106,    31,  -106,   112,   227,  -106,     0,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,   582,   582,  -106,     9,
     582,   291,  -106,    36,  -106,  -106,   607,    27,  -106,     3,
     352,  -106,   440,   440,   440,   440,   475,   475,   440,    53,
      71,    75,   494,   440,  -106,  -106,  -106,    47,  -106,   203,
      56,  -106,    51,    28,    37,    33,    55,    11,    67,    78,
      81,    57,  -106,  -106,    84,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,    36,    34,    34,   117,  -106,    97,   118,
      13,   607,   518,  -106,    36,   607,   607,  -106,  -106,   123,
      76,   125,  -106,  -106,  -106,  -106,  -106,   440,  -106,  -106,
    -106,   440,   440,   440,   352,  -106,  -106,    96,   327,    70,
     405,   440,    79,  -106,  -106,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,  -106,   129,  -106,  -106,    34,  -106,
      34,   140,   103,   440,   415,   118,  -106,  -106,  -106,    -8,
    -106,  -106,  -106,   532,  -106,  -106,  -106,   440,   134,   106,
     143,   145,  -106,  -106,  -106,  -106,    15,  -106,   141,  -106,
    -106,  -106,  -106,  -106,    51,    51,    28,    28,    37,    37,
      37,    37,    33,    33,    55,    11,    67,    78,    81,  -106,
    -106,  -106,  -106,  -106,    36,   161,   110,  -106,  -106,  -106,
    -106,  -106,  -106,   159,  -106,    36,  -106,  -106,   327,   440,
     327,  -106,  -106,   440,  -106,  -106,  -106,   557,  -106,  -106,
     133,   136,  -106,  -106,  -106,  -106,   327,   440,  -106,   167,
     327,  -106
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -106,  -106,  -106,  -106,  -106,   -10,   -32,   -24,   -15,   -65,
     -12,    35,    38,    32,    52,    54,  -106,    21,   -86,   -21,
    -106,  -106,  -106,  -106,   -22,  -106,  -106,    -2,  -106,  -106,
      83,   -78,  -106,   -19,   -31,    -4,   -27,   109,   -26,   115,
    -106,  -106,   -25,    87,  -106,  -106,  -106,  -100,  -106,   211,
     202,  -106,  -106,  -106,  -106,  -105,  -106
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -132
static const yytype_int16 yytable[] =
{
      30,    30,    27,    27,    34,    35,    88,   169,    38,   100,
     103,   104,   105,   106,   158,    36,   110,    83,   173,    99,
     222,    60,    30,    30,    27,    27,    30,   214,    27,     1,
      60,     6,   116,    96,   177,    32,   108,   109,    97,   180,
      83,   139,   115,    60,   129,   130,    84,    85,    84,    85,
     215,   133,   134,   135,   136,   118,   145,   111,   147,   149,
     156,   131,   132,   126,   162,   127,   128,   209,   188,   189,
     190,   191,    37,   223,   165,   112,    86,   137,   138,   113,
     146,   146,   125,   100,   143,   158,    99,    21,    84,    85,
     168,   116,   170,    99,   181,   182,   183,    60,   140,    86,
     178,    60,    60,    60,    60,   184,   185,   141,    60,   142,
      60,    60,    -2,     7,   231,    60,   186,   187,   230,   144,
     232,   151,   201,   153,   202,   192,   193,   154,   164,   204,
     167,   172,   239,   174,   199,   217,   238,   233,   208,   218,
     241,   219,   179,    60,   200,   203,   200,    30,   220,    27,
     221,   224,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,   226,    22,   227,   228,
     236,   237,   240,   196,   194,   212,    23,   225,   195,   163,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,   197,    22,   229,   198,   116,   155,
     150,   171,   235,     5,    23,   204,   119,   120,    60,    60,
      60,     3,   121,    60,   122,     0,   116,     0,     0,     0,
       0,     0,     0,    30,     0,    27,    60,    60,     7,     0,
      60,  -131,     0,  -131,  -131,   123,   124,     0,     0,  -131,
       0,     0,     0,  -131,  -131,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -131,     0,  -131,
    -131,  -131,     0,  -131,     0,  -131,  -131,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,  -131,    22,  -131,     0,     0,     0,  -131,  -131,  -131,
    -131,    23,    39,     0,     0,    40,     0,     1,    41,     0,
       0,     0,     0,    42,     0,     0,     0,    43,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,    46,    47,    48,     0,    49,    39,    50,
      51,    40,     0,     1,     0,     0,     0,     0,     0,    42,
       0,     0,     0,    43,    44,    52,     0,    53,     0,     0,
       0,    54,    55,    56,    57,     0,    40,    45,     0,    46,
      47,    48,     0,    49,    42,    50,    51,     0,    43,    44,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    52,    45,    53,    46,    47,    48,    54,    55,    56,
      57,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,    19,    20,    21,    52,     0,     0,    40,
     175,     0,    54,    55,    56,    98,    23,    42,     0,    40,
       0,    43,    44,     0,     0,   211,     0,    42,     0,     0,
       0,    43,    44,     0,     0,    45,     0,    46,    47,    48,
       0,     0,     0,     0,    40,    45,     0,    46,    47,    48,
       0,     0,    42,     0,     0,     0,    43,    44,     0,    52,
       0,     0,     0,     0,     0,    54,    55,    56,    98,    52,
      45,     0,    46,    47,    48,    54,    55,    56,    98,   107,
       0,     0,     0,     0,     0,     0,     0,    42,     0,     0,
       0,    43,    44,     0,    52,     0,     0,     0,   114,     0,
      54,    55,    56,    98,     0,    45,    42,    46,    47,    48,
      43,    44,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,   157,    46,    47,    48,    52,
       0,     0,     0,     0,     0,    54,    55,    56,    98,   216,
       0,     0,     0,     0,     0,     0,     0,     0,    52,     0,
       0,     0,     0,     0,    54,    55,    56,    98,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,    19,
      20,    21,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    23,    19,    20,    21,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     0,    22,     0,     0,     0,   234,     0,     0,     0,
       0,    23,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     0,    22,     0,     0,
       0,     0,     0,     0,     0,     0,    23,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     0,    19,    20,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23
};

static const yytype_int16 yycheck[] =
{
       4,     5,     4,     5,    26,    27,    33,   112,    30,    40,
      42,    43,    44,    45,    92,     6,    48,     4,   118,    40,
       5,    31,    26,    27,    26,    27,    30,    35,    30,     6,
      40,     0,    53,     6,   120,    35,    46,    47,    35,   125,
       4,    30,    52,    53,    16,    17,    12,    13,    12,    13,
      58,    18,    19,    20,    21,     8,    83,     4,    84,    85,
      91,    24,    25,    12,    95,    14,    15,   153,   133,   134,
     135,   136,    63,    58,   100,     4,    63,    22,    23,     4,
      84,    85,    26,   114,    27,   163,   107,    53,    12,    13,
     111,   112,   113,   114,   126,   127,   128,   107,    31,    63,
     121,   111,   112,   113,   114,   129,   130,    29,   118,    28,
     120,   121,     0,     1,   219,   125,   131,   132,   218,    35,
     220,     4,   148,    26,   150,   137,   138,     9,     5,   151,
       5,    35,   237,    63,     5,   167,   236,   223,    35,     5,
     240,    35,    63,   153,   148,     5,   150,   151,     5,   151,
       5,    10,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,     5,    55,    58,    10,
      37,    35,     5,   141,   139,   154,    64,   204,   140,    96,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,   142,    55,   215,   143,   219,    90,
      85,   114,   227,     1,    64,   227,     3,     4,   218,   219,
     220,     0,     9,   223,    11,    -1,   237,    -1,    -1,    -1,
      -1,    -1,    -1,   227,    -1,   227,   236,   237,     1,    -1,
     240,     4,    -1,     6,     7,    32,    33,    -1,    -1,    12,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    34,    -1,    36,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    60,    61,    62,
      63,    64,     1,    -1,    -1,     4,    -1,     6,     7,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    34,    -1,    36,     1,    38,
      39,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    16,    17,    54,    -1,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    -1,     4,    30,    -1,    32,
      33,    34,    -1,    36,    12,    38,    39,    -1,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    30,    56,    32,    33,    34,    60,    61,    62,
      63,    -1,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    -1,    51,    52,    53,    54,    -1,    -1,     4,
       5,    -1,    60,    61,    62,    63,    64,    12,    -1,     4,
      -1,    16,    17,    -1,    -1,    10,    -1,    12,    -1,    -1,
      -1,    16,    17,    -1,    -1,    30,    -1,    32,    33,    34,
      -1,    -1,    -1,    -1,     4,    30,    -1,    32,    33,    34,
      -1,    -1,    12,    -1,    -1,    -1,    16,    17,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    54,
      30,    -1,    32,    33,    34,    60,    61,    62,    63,     4,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    16,    17,    -1,    54,    -1,    -1,    -1,     4,    -1,
      60,    61,    62,    63,    -1,    30,    12,    32,    33,    34,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,     7,    32,    33,    34,    54,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,     7,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    64,    51,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    -1,    55,    -1,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    64,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    51,    52,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    66,   114,   115,   115,     0,     1,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    55,    64,    86,    89,    91,    92,    93,    94,
     100,   111,    35,    87,    89,    89,     6,    63,    89,     1,
       4,     7,    12,    16,    17,    30,    32,    33,    34,    36,
      38,    39,    54,    56,    60,    61,    62,    63,    67,    68,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,   112,   113,   114,   116,   117,
     118,   119,   121,     4,    12,    13,    63,    90,   101,   102,
     103,    92,    95,    96,    99,   100,     6,    35,    63,    84,
      99,   108,    70,    71,    71,    71,    71,     4,    70,    70,
      71,     4,     4,     4,     4,    70,    84,   120,     8,     3,
       4,     9,    11,    32,    33,    26,    12,    14,    15,    16,
      17,    24,    25,    18,    19,    20,    21,    22,    23,    30,
      31,    29,    28,    27,    35,   101,   100,   103,   104,   103,
     104,     4,    88,    26,     9,   102,    99,     7,    96,    97,
      98,   101,    99,    95,     5,   103,   109,     5,    84,   120,
      84,   108,    35,   112,    63,     5,    69,    83,    84,    63,
      83,    71,    71,    71,    72,    72,    73,    73,    74,    74,
      74,    74,    75,    75,    76,    77,    78,    79,    80,     5,
     100,   103,   103,     5,    89,   105,   106,   107,    35,    83,
     110,    10,    82,    85,    35,    58,     7,    71,     5,    35,
       5,     5,     5,    58,    10,   101,     5,    58,    10,    98,
     112,   120,   112,    83,    59,   107,    37,    35,   112,   120,
       5,   112
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 285 "./cod.y"
    {
	    yyparse_value = (sm_ref)(yyvsp[(1) - (1)].list);
	}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 289 "./cod.y"
    {
	    yyparse_value = (yyvsp[(1) - (1)].reference);
	}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 295 "./cod.y"
    {
	    (yyval.reference) = cod_new_identifier();
	    (yyval.reference)->node.identifier.id = (yyvsp[(1) - (1)].info).string;
	    (yyval.reference)->node.identifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 304 "./cod.y"
    { (yyval.reference) = (yyvsp[(2) - (3)].reference); }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 311 "./cod.y"
    {
	    (yyval.reference) = cod_new_element_ref();
	    (yyval.reference)->node.element_ref.lx_srcpos = (yyvsp[(2) - (4)].info).lx_srcpos;
	    (yyval.reference)->node.element_ref.expression = (yyvsp[(3) - (4)].reference);
	    (yyval.reference)->node.element_ref.array_ref = (yyvsp[(1) - (4)].reference);
	}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 318 "./cod.y"
    {
	    (yyval.reference) = cod_new_field_ref();
	    (yyval.reference)->node.field_ref.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.field_ref.lx_field = (yyvsp[(3) - (3)].info).string;
	    (yyval.reference)->node.field_ref.struct_ref = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 325 "./cod.y"
    {
	    (yyval.reference) = cod_new_subroutine_call();
	    (yyval.reference)->node.subroutine_call.lx_srcpos = (yyvsp[(2) - (4)].info).lx_srcpos;
	    (yyval.reference)->node.subroutine_call.arguments = (yyvsp[(3) - (4)].list);
	    (yyval.reference)->node.subroutine_call.sm_func_ref = (yyvsp[(1) - (4)].reference);
	}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 332 "./cod.y"
    {
	    (yyval.reference) = cod_new_subroutine_call();
	    (yyval.reference)->node.subroutine_call.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.subroutine_call.arguments = NULL;
	    (yyval.reference)->node.subroutine_call.sm_func_ref = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 338 "./cod.y"
    {
           assert(0);
	}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 341 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (2)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_inc;
	    (yyval.reference)->node.operator.right = NULL;
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (2)].reference);
	}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 348 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (2)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_dec;
	    (yyval.reference)->node.operator.right = NULL;
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (2)].reference);
	}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 358 "./cod.y"
    {
		(yyval.list) = malloc(sizeof(struct list_struct));
		(yyval.list)->node = (yyvsp[(1) - (1)].reference);
		(yyval.list)->next = NULL;
	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 364 "./cod.y"
    {
	    sm_list tmp = (yyvsp[(1) - (3)].list);
	    while (tmp->next != NULL) {
		tmp = tmp->next;
	    }
	    tmp->next = malloc(sizeof(struct list_struct));
	    tmp->next->node = (yyvsp[(3) - (3)].reference);
	    tmp->next->next = NULL;
	    (yyval.list) = (yyvsp[(1) - (3)].list);
	}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 379 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_inc;
	    (yyval.reference)->node.operator.right = (yyvsp[(2) - (2)].reference);
	    (yyval.reference)->node.operator.left = NULL;
	}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 386 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_dec;
	    (yyval.reference)->node.operator.right = (yyvsp[(2) - (2)].reference);
	    (yyval.reference)->node.operator.left = NULL;
	}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 393 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_deref;
	    (yyval.reference)->node.operator.right = (yyvsp[(2) - (2)].reference);
	    (yyval.reference)->node.operator.left = NULL;
	}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 400 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_log_neg;
	    (yyval.reference)->node.operator.right = (yyvsp[(2) - (2)].reference);
	    (yyval.reference)->node.operator.left = NULL;
	}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 407 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_address;
	    (yyval.reference)->node.operator.right = (yyvsp[(2) - (2)].reference);
	    (yyval.reference)->node.operator.left = NULL;
	}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 414 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_plus;
	    (yyval.reference)->node.operator.right = (yyvsp[(2) - (2)].reference);
	    (yyval.reference)->node.operator.left = NULL;
	}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 421 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_minus;
	    (yyval.reference)->node.operator.right = (yyvsp[(2) - (2)].reference);
	    (yyval.reference)->node.operator.left = NULL;
	}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 428 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_sizeof;
	    (yyval.reference)->node.operator.right = (yyvsp[(2) - (2)].reference);
	    (yyval.reference)->node.operator.left = NULL;
	}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 435 "./cod.y"
    {
	    /* dummy up a cast to hold the sm_list of the type */
	    sm_ref cast = cod_new_cast();
	    cast->node.cast.lx_srcpos = (yyvsp[(1) - (4)].info).lx_srcpos;
	    cast->node.cast.type_spec = (yyvsp[(3) - (4)].list);
	    cast->node.cast.expression = NULL;

	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(1) - (4)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_sizeof;
	    (yyval.reference)->node.operator.right = cast;
	    (yyval.reference)->node.operator.left = NULL;
	}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 451 "./cod.y"
    {
	    (yyval.reference) = cod_new_cast();
	    (yyval.reference)->node.cast.lx_srcpos = (yyvsp[(1) - (4)].info).lx_srcpos;
	    (yyval.reference)->node.cast.type_spec = (yyvsp[(2) - (4)].list);
	    (yyval.reference)->node.cast.expression = (yyvsp[(4) - (4)].reference);
	}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 463 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_mult;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 472 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_div;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 481 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_modulus;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 494 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.op = op_plus;
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 503 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_minus;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 516 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_left_shift;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 525 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_right_shift;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 538 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_lt;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 547 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_gt;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 556 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_leq;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 565 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_geq;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 578 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_eq;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 587 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_neq;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 600 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_arith_and;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 613 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_arith_xor;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 626 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_arith_or;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 639 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_log_and;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 652 "./cod.y"
    {
	    (yyval.reference) = cod_new_operator();
	    (yyval.reference)->node.operator.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.operator.op = op_log_or;
	    (yyval.reference)->node.operator.right = (yyvsp[(3) - (3)].reference);
	    (yyval.reference)->node.operator.left = (yyvsp[(1) - (3)].reference);
	}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 669 "./cod.y"
    { (yyval.reference) = (yyvsp[(1) - (1)].reference);}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 672 "./cod.y"
    {
	    (yyval.reference) = cod_new_assignment_expression();
	    (yyval.reference)->node.assignment_expression.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
	    (yyval.reference)->node.assignment_expression.left = (yyvsp[(1) - (3)].reference);
	    (yyval.reference)->node.assignment_expression.right = (yyvsp[(3) - (3)].reference);
	}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 683 "./cod.y"
    {(yyval.reference) = (yyvsp[(1) - (1)].reference);}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 692 "./cod.y"
    { 
		 if (parsing_type) {
		     yyparse_value = (sm_ref) (yyvsp[(1) - (1)].list);
		     YYACCEPT;
		 }
	     }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 699 "./cod.y"
    {  /* stop here if we're just doing a proc decl */
		if (parsing_param_spec) {
		    (yyval.reference) = (yyvsp[(3) - (3)].reference);
		    if ((yyval.reference)->node_type == cod_declaration) {
			if  ((yyval.reference)->node.declaration.type_spec == NULL) {
			    (yyval.reference)->node.declaration.type_spec = (yyvsp[(1) - (3)].list);
			} else {
			    /* 
			     * the pointer type list (with the declarator)
			     * goes at the end 
			     */
			    sm_list tmp = (yyvsp[(1) - (3)].list);
			    while (tmp->next != NULL) {
				tmp = tmp->next;
			    }
			    tmp->next = (yyval.reference)->node.declaration.type_spec;
			    (yyval.reference)->node.declaration.type_spec = (yyvsp[(1) - (3)].list);
			}
		    } else {
		        printf("unexpected node in init_declarator\n");
			cod_print((yyval.reference));
		    }
		    yyparse_value = (yyvsp[(3) - (3)].reference);
		    YYACCEPT;
		}
	    }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 726 "./cod.y"
    {
		sm_list type_spec = (yyvsp[(1) - (5)].list);
		(yyval.reference) = (yyvsp[(3) - (5)].reference);
		if ((yyval.reference)->node_type == cod_declaration) {
		    if  ((yyval.reference)->node.declaration.type_spec == NULL) {
			(yyval.reference)->node.declaration.type_spec = (yyvsp[(1) - (5)].list);
		    } else {
			/* 
			 * the pointer type list (with the declarator)
			 * goes at the end 
			 */
			sm_list tmp = (yyvsp[(1) - (5)].list);
			while (tmp->next != NULL) {
			    tmp = tmp->next;
			}
			tmp->next = (yyval.reference)->node.declaration.type_spec;
			(yyval.reference)->node.declaration.type_spec = (yyvsp[(1) - (5)].list);
		    }
		} else if ((yyval.reference)->node_type == cod_array_type_decl) {
		    if  ((yyval.reference)->node.array_type_decl.type_spec == NULL) {
			(yyval.reference)->node.array_type_decl.type_spec = (yyvsp[(1) - (5)].list);
		    } else {
			/* 
			 * the pointer type list (with the declarator)
			 * goes at the end 
			 */
			sm_list tmp = (yyvsp[(1) - (5)].list);
			while (tmp->next != NULL) {
			    tmp = tmp->next;
			}
			tmp->next = (yyval.reference)->node.array_type_decl.type_spec;
			(yyval.reference)->node.array_type_decl.type_spec = (yyvsp[(1) - (5)].list);
		    }
		} else {
		    printf("Unknown decl entry\n");
		    cod_print((yyval.reference));
		}
		while (type_spec != NULL) {
		    if (type_spec->node->node.type_specifier.token == TYPEDEF) {
			cod_add_defined_type((yyval.reference)->node.declaration.id, yycontext);
		    }
		    type_spec = type_spec->next;
		}

	    }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 771 "./cod.y"
    {
	    (yyval.reference) = NULL;
	}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 777 "./cod.y"
    {
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = (yyvsp[(1) - (1)].reference);
	    (yyval.list)->next = NULL;
	}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 782 "./cod.y"
    {
	    sm_list tmp = malloc(sizeof(struct list_struct));
	    tmp->node = (yyvsp[(1) - (2)].reference);
	    tmp->next = (yyvsp[(2) - (2)].list);
	    (yyval.list) = tmp;
	}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 788 "./cod.y"
    {
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = (yyvsp[(1) - (1)].reference);
	    (yyval.list)->next = NULL;
	}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 793 "./cod.y"
    {
	    sm_list tmp = malloc(sizeof(struct list_struct));
	    tmp->node = (yyvsp[(1) - (2)].reference);
	    tmp->next = (yyvsp[(2) - (2)].list);
	    (yyval.list) = tmp;
	}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 799 "./cod.y"
    {
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = (yyvsp[(1) - (1)].reference);
	    (yyval.list)->next = NULL;
	}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 804 "./cod.y"
    {
	    sm_list tmp = malloc(sizeof(struct list_struct));
	    tmp->node = (yyvsp[(1) - (2)].reference);
	    tmp->next = (yyvsp[(2) - (2)].list);
	    (yyval.list) = tmp;
	}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 815 "./cod.y"
    {
		assert((yyvsp[(1) - (3)].reference)->node_type == cod_declaration);
		(yyvsp[(1) - (3)].reference)->node.declaration.init_value = (yyvsp[(3) - (3)].reference);
	    }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 822 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = TYPEDEF;
	}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 827 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = STATIC;
	}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 835 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = CHAR;
	}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 840 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = SHORT;
	}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 845 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = INT;
	}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 850 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = LONG;
	}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 855 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = FLOAT;
	}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 860 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = DOUBLE;
	}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 865 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = VOID;
	}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 870 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = SIGNED;
	}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 875 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = UNSIGNED;
	}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 880 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = STRING;
	}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 885 "./cod.y"
    {
	    (yyval.reference) = cod_new_identifier();
	    (yyval.reference)->node.identifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.identifier.id = (yyvsp[(1) - (1)].info).string;
	}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 890 "./cod.y"
    {
	    (yyval.reference) = (yyvsp[(1) - (1)].reference);
	}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 896 "./cod.y"
    {
	    (yyval.reference) = cod_build_parsed_type_node(yycontext, (yyvsp[(2) - (5)].info).string, (yyvsp[(4) - (5)].list));
	}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 899 "./cod.y"
    {
	    (yyval.reference) = cod_build_parsed_type_node(yycontext, "anon", (yyvsp[(3) - (4)].list));
	}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 902 "./cod.y"
    {
	    (yyval.reference) = cod_build_parsed_type_node(yycontext, (yyvsp[(2) - (2)].info).string, NULL);
	}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 909 "./cod.y"
    {
            yyerror("UNIONs not supported!");
	}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 916 "./cod.y"
    {
	    sm_list tmp = (yyvsp[(1) - (2)].list);
	    while (tmp->next != NULL) {
		tmp = tmp->next;
	    }
	    tmp->next =(yyvsp[(2) - (2)].list);
	    (yyval.list) = (yyvsp[(1) - (2)].list);
	}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 927 "./cod.y"
    {
	    sm_list type_spec = (yyvsp[(1) - (3)].list);
	    sm_list decl_list = (yyvsp[(2) - (3)].list);
 	    (yyval.list) = (yyvsp[(2) - (3)].list);
/******** GSE This isn't right.  Reusing potentially modified type spec */
	    while (decl_list != NULL) {
		sm_ref decl = decl_list->node;
		if (decl->node_type == cod_declaration) {
		    if  (decl->node.declaration.type_spec == NULL) {
			decl->node.declaration.type_spec = type_spec;
		    } else {
			/* 
			 * the pointer type list (with the declarator)
			 * goes at the end 
			 */
			sm_list tmp = (yyvsp[(1) - (3)].list);
			while (tmp->next != NULL) {
			    tmp = tmp->next;
			}
			tmp->next = decl->node.declaration.type_spec;
			decl->node.declaration.type_spec = type_spec;
		    }
		} else if (decl->node_type == cod_array_type_decl) {
		    if  (decl->node.array_type_decl.type_spec == NULL) {
			decl->node.array_type_decl.type_spec = type_spec;
		    } else {
			/* 
			 * the pointer type list (with the declarator)
			 * goes at the end 
			 */
			sm_list tmp = type_spec;
			while (tmp->next != NULL) {
			    tmp = tmp->next;
			}
			tmp->next = decl->node.array_type_decl.type_spec;
			decl->node.array_type_decl.type_spec = type_spec;
		    }
		} else {
		    printf("Unknown decl entry\n");
		    cod_print(decl);
		}
		decl_list = decl_list->next;
		if (decl_list != NULL) {
		    type_spec = cod_dup_list(type_spec);
		}
	    }
	}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 978 "./cod.y"
    {
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = (yyvsp[(1) - (1)].reference);
	    (yyval.list)->next = NULL;
	}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 983 "./cod.y"
    {
	    sm_list tmp = (yyvsp[(1) - (3)].list);
	    while (tmp->next != NULL) {
		tmp = tmp->next;
	    }
	    tmp->next = malloc(sizeof(struct list_struct));
	    tmp->next->node = (yyvsp[(3) - (3)].reference);
	    tmp->next->next = NULL;
	    (yyval.list) = (yyvsp[(1) - (3)].list);
	}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 998 "./cod.y"
    {
	    sm_list tmp = malloc(sizeof(struct list_struct));
	    tmp->node = (yyvsp[(1) - (2)].reference);
	    tmp->next = (yyvsp[(2) - (2)].list);
	    (yyval.list) = tmp;
	}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1004 "./cod.y"
    {
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = (yyvsp[(1) - (1)].reference);
	    (yyval.list)->next = NULL;
	}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1009 "./cod.y"
    {
	    sm_list tmp = malloc(sizeof(struct list_struct));
	    tmp->node = (yyvsp[(1) - (2)].reference);
	    tmp->next = (yyvsp[(2) - (2)].list);
	    (yyval.list) = tmp;
	}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1015 "./cod.y"
    {
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = (yyvsp[(1) - (1)].reference);
	    (yyval.list)->next = NULL;
	}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1023 "./cod.y"
    {
	    (yyval.reference) = cod_new_type_specifier();
	    (yyval.reference)->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    (yyval.reference)->node.type_specifier.token = CONST;
	}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1033 "./cod.y"
    {
	    (yyval.reference) = (yyvsp[(2) - (2)].reference);
	    if ((yyval.reference)->node_type == cod_declaration) {
		(yyval.reference)->node.declaration.type_spec = (yyvsp[(1) - (2)].list);
	    } else if ((yyval.reference)->node_type == cod_array_type_decl) {
		(yyval.reference)->node.array_type_decl.type_spec = (yyvsp[(1) - (2)].list);
	    } else {
		printf("Unknown direct_declarator entry\n");
		cod_print((yyval.reference));
	    }
	}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1047 "./cod.y"
    {
		(yyval.reference) = cod_new_declaration();
		(yyval.reference)->node.declaration.param_num = -1;
		(yyval.reference)->node.declaration.id = (yyvsp[(1) - (1)].info).string;
		(yyval.reference)->node.declaration.init_value = NULL;
		(yyval.reference)->node.declaration.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
		(yyval.reference)->node.declaration.is_subroutine = 0;
		(yyval.reference)->node.declaration.params = NULL;
	    }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1056 "./cod.y"
    {
	    (yyval.reference) = (yyvsp[(2) - (3)].reference);
	}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1059 "./cod.y"
    {
		(yyval.reference) = cod_new_declaration();
		(yyval.reference)->node.declaration.param_num = -1;
		(yyval.reference)->node.declaration.id = (yyvsp[(1) - (4)].info).string;
		(yyval.reference)->node.declaration.init_value = NULL;
		(yyval.reference)->node.declaration.lx_srcpos = (yyvsp[(1) - (4)].info).lx_srcpos;
		(yyval.reference)->node.declaration.is_subroutine = 1;
		(yyval.reference)->node.declaration.params = (yyvsp[(3) - (4)].list);
	}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1068 "./cod.y"
    {
		(yyval.reference) = cod_new_declaration();
		(yyval.reference)->node.declaration.param_num = -1;
		(yyval.reference)->node.declaration.id = (yyvsp[(1) - (3)].info).string;
		(yyval.reference)->node.declaration.init_value = NULL;
		(yyval.reference)->node.declaration.lx_srcpos = (yyvsp[(1) - (3)].info).lx_srcpos;
		(yyval.reference)->node.declaration.is_subroutine = 1;
		(yyval.reference)->node.declaration.params = NULL;
	}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1077 "./cod.y"
    {
		(yyval.reference) = cod_new_array_type_decl();
		(yyval.reference)->node.array_type_decl.lx_srcpos = (yyvsp[(2) - (4)].info).lx_srcpos;
		(yyval.reference)->node.array_type_decl.size_expr = (yyvsp[(3) - (4)].reference);
		(yyval.reference)->node.array_type_decl.element_ref = (yyvsp[(1) - (4)].reference);
		(yyval.reference)->node.array_type_decl.sm_dynamic_size = NULL;
	}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1084 "./cod.y"
    {
		(yyval.reference) = cod_new_array_type_decl();
		(yyval.reference)->node.array_type_decl.lx_srcpos = (yyvsp[(2) - (3)].info).lx_srcpos;
		(yyval.reference)->node.array_type_decl.size_expr = NULL;
		(yyval.reference)->node.array_type_decl.element_ref = (yyvsp[(1) - (3)].reference);
		(yyval.reference)->node.array_type_decl.sm_dynamic_size = NULL;
	}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1094 "./cod.y"
    {
	    sm_ref star = cod_new_type_specifier();
	    star->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    star->node.type_specifier.token = STAR;
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = star;
	    (yyval.list)->next = NULL;
	}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1102 "./cod.y"
    {
	    sm_ref star = cod_new_type_specifier();
	    star->node.type_specifier.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    star->node.type_specifier.token = STAR;
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = star;
	    (yyval.list)->next = (yyvsp[(2) - (2)].list);
	}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1110 "./cod.y"
    {
	    sm_ref star = cod_new_type_specifier();
	    star->node.type_specifier.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    star->node.type_specifier.token = STAR;
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = star;
	    (yyval.list)->next = (yyvsp[(2) - (2)].list);
	}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1118 "./cod.y"
    {
	    sm_list tmp = (yyvsp[(2) - (3)].list);
	    sm_ref star = cod_new_type_specifier();
	    star->node.type_specifier.lx_srcpos = (yyvsp[(1) - (3)].info).lx_srcpos;
	    star->node.type_specifier.token = STAR;

	    while (tmp->next != NULL) {
		tmp = tmp->next;
	    }
	    tmp->next = (yyvsp[(3) - (3)].list);
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = star;
	    (yyval.list)->next = (yyvsp[(2) - (3)].list);
	}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1132 "./cod.y"
    {
	    sm_ref star = cod_new_type_specifier();
	    if(!cod_segmented_pointers) { 
                yyerror("Segmented pointers disabled!");
	    }
	    star->node.type_specifier.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	    star->node.type_specifier.token = AT;
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = star;
	    (yyval.list)->next = NULL;
	}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1143 "./cod.y"
    {
	    sm_ref star = cod_new_type_specifier();
	    if(!cod_segmented_pointers) {
                yyerror("Segmented pointers disabled!");
	    }
	    star->node.type_specifier.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    star->node.type_specifier.token = AT;
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = star;
	    (yyval.list)->next = (yyvsp[(2) - (2)].list);
	}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1154 "./cod.y"
    {
	    sm_ref star = cod_new_type_specifier();
	    if(!cod_segmented_pointers) {
                yyerror("Segmented pointers disabled!");
	    }
	    star->node.type_specifier.lx_srcpos = (yyvsp[(1) - (2)].info).lx_srcpos;
	    star->node.type_specifier.token = AT;
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = star;
	    (yyval.list)->next = (yyvsp[(2) - (2)].list);
	}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1165 "./cod.y"
    {
	    sm_list tmp = (yyvsp[(2) - (3)].list);
	    sm_ref star = cod_new_type_specifier();
	    if(!cod_segmented_pointers) {
                yyerror("Segmented pointers disabled!");
	    }
	    star->node.type_specifier.lx_srcpos = (yyvsp[(1) - (3)].info).lx_srcpos;
	    star->node.type_specifier.token = AT;

	    while (tmp->next != NULL) {
		tmp = tmp->next;
	    }
	    tmp->next = (yyvsp[(3) - (3)].list);
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = star;
	    (yyval.list)->next = (yyvsp[(2) - (3)].list);
	}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1185 "./cod.y"
    {
	    (yyval.list) = malloc(sizeof(struct list_struct));
	    (yyval.list)->node = (yyvsp[(1) - (1)].reference);
	    (yyval.list)->next = NULL;
	}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1190 "./cod.y"
    {
	    sm_list tmp = (yyvsp[(1) - (2)].list);
	    while (tmp->next != NULL) {
		tmp = tmp->next;
	    }
	    tmp->next = malloc(sizeof(struct list_struct));
	    tmp->next->node = (yyvsp[(2) - (2)].reference);
	    tmp->next->next = NULL;
	    (yyval.list) = (yyvsp[(1) - (2)].list);
	}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1204 "./cod.y"
    {
	    sm_list tmp = (yyvsp[(1) - (3)].list);
	    sm_ref id = cod_new_declaration();
	    while (tmp->next != NULL) {
		tmp = tmp->next;
	    }
	    tmp->next = malloc(sizeof(struct list_struct));
	    tmp->next->node = id;
	    tmp->next->next = NULL;
	    id->node.declaration.id = strdup("...");
	    (yyval.list) = (yyvsp[(1) - (3)].list);
	}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1219 "./cod.y"
    {
		(yyval.list) = malloc(sizeof(struct list_struct));
		(yyval.list)->node = (yyvsp[(1) - (1)].reference);
		(yyval.list)->next = NULL;
	}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1225 "./cod.y"
    {
	    sm_list tmp = (yyvsp[(1) - (3)].list);
	    while (tmp->next != NULL) {
		tmp = tmp->next;
	    }
	    tmp->next = malloc(sizeof(struct list_struct));
	    tmp->next->node = (yyvsp[(3) - (3)].reference);
	    tmp->next->next = NULL;
	    (yyval.list) = (yyvsp[(1) - (3)].list);
	}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1241 "./cod.y"
    {
		(yyval.reference) = (yyvsp[(2) - (2)].reference);
		if ((yyval.reference)->node_type == cod_declaration) {
		    (yyval.reference)->node.declaration.static_var = 0;
		    if  ((yyval.reference)->node.declaration.type_spec == NULL) {
		        (yyval.reference)->node.declaration.type_spec = (yyvsp[(1) - (2)].list);
		    } else {
		        /* 
			 * the pointer type list (with the declarator)
			 * goes at the end 
			 */
		      sm_list tmp = (yyvsp[(1) - (2)].list);
		      while (tmp->next != NULL) {
			  tmp = tmp->next;
		      }
		      tmp->next = (yyval.reference)->node.declaration.type_spec;
		      (yyval.reference)->node.declaration.type_spec = (yyvsp[(1) - (2)].list);
		    }
		} else if ((yyval.reference)->node_type == cod_array_type_decl) {
		    if  ((yyval.reference)->node.array_type_decl.type_spec == NULL) {
		        (yyval.reference)->node.array_type_decl.type_spec = (yyvsp[(1) - (2)].list);
		    } else {
		        /* 
			 * the pointer type list (with the declarator)
			 * goes at the end 
			 */
		      sm_list tmp = (yyvsp[(1) - (2)].list);
		      while (tmp->next != NULL) {
			  tmp = tmp->next;
		      }
		      tmp->next = (yyval.reference)->node.array_type_decl.type_spec;
		      (yyval.reference)->node.array_type_decl.type_spec = (yyvsp[(1) - (2)].list);
		    }
		} else {
		    printf("unexpected node in parameter_declaration");
		}
	}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1281 "./cod.y"
    {
	    sm_list tmp = (yyvsp[(1) - (2)].list);
	    while (tmp->next != NULL) {
		tmp = tmp->next;
	    }
	    tmp->next = (yyvsp[(2) - (2)].list);
	    (yyval.list) = (yyvsp[(1) - (2)].list);
	}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1296 "./cod.y"
    { (yyval.reference) = (yyvsp[(1) - (1)].reference);}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1300 "./cod.y"
    {(yyval.list) = NULL;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1301 "./cod.y"
    {
	    if ((yyvsp[(2) - (2)].reference) == NULL) {
		(yyval.list) = (yyvsp[(1) - (2)].list);
	    } else {
		if ((yyvsp[(1) - (2)].list) == NULL) {
		    (yyval.list) = malloc(sizeof(struct list_struct));
		    (yyval.list)->node = (yyvsp[(2) - (2)].reference);
		    (yyval.list)->next = NULL;
		} else {
		    sm_list tmp = (yyvsp[(1) - (2)].list);
		    while (tmp->next != NULL) {
			tmp = tmp->next;
		    }
		    tmp->next = malloc(sizeof(struct list_struct));
		    tmp->next->node = (yyvsp[(2) - (2)].reference);
		    tmp->next->next = NULL;
		    (yyval.list) = (yyvsp[(1) - (2)].list);
		}
	    }
	}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1330 "./cod.y"
    {
	      (yyval.reference) = NULL;
	  }
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1336 "./cod.y"
    {
	    (yyval.reference) = cod_new_label_statement();
	    (yyval.reference)->node.label_statement.name =  (yyvsp[(1) - (3)].info).string;
	    (yyval.reference)->node.label_statement.statement = (yyvsp[(3) - (3)].reference);
	}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1343 "./cod.y"
    {
	    (yyval.reference) = cod_new_compound_statement();
	    (yyval.reference)->node.compound_statement.decls = (yyvsp[(2) - (4)].list);
	    (yyval.reference)->node.compound_statement.statements = (yyvsp[(3) - (4)].list);
	    cod_remove_defined_types((yyvsp[(2) - (4)].list), yycontext);
	}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1351 "./cod.y"
    { (yyval.list) = NULL; }
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1353 "./cod.y"
    {
	    if ((yyvsp[(2) - (2)].reference) == NULL) {
		(yyval.list) = (yyvsp[(1) - (2)].list);
	    } else {
		if ((yyvsp[(1) - (2)].list) == NULL) {
		    (yyval.list) = malloc(sizeof(struct list_struct));
		    (yyval.list)->node = (yyvsp[(2) - (2)].reference);
		    (yyval.list)->next = NULL;
		} else {
		    sm_list tmp = (yyvsp[(1) - (2)].list);
		    while (tmp->next != NULL) {
			tmp = tmp->next;
		    }
		    tmp->next = malloc(sizeof(struct list_struct));
		    tmp->next->node = (yyvsp[(2) - (2)].reference);
		    tmp->next->next = NULL;
		    (yyval.list) = (yyvsp[(1) - (2)].list);
		}
	    }
	}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1376 "./cod.y"
    {
	    (yyval.reference) = cod_new_return_statement();
	    (yyval.reference)->node.return_statement.expression = (yyvsp[(2) - (3)].reference);
	    (yyval.reference)->node.return_statement.lx_srcpos = (yyvsp[(1) - (3)].info).lx_srcpos;
	}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1384 "./cod.y"
    { 
	    (yyval.reference) = cod_new_expression_statement();
	    (yyval.reference)->node.expression_statement.expression = (yyvsp[(1) - (2)].reference);
	}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1393 "./cod.y"
    { 
	    (yyval.reference) = cod_new_selection_statement();
	    (yyval.reference)->node.selection_statement.lx_srcpos = (yyvsp[(1) - (5)].info).lx_srcpos;
	    (yyval.reference)->node.selection_statement.conditional = (yyvsp[(3) - (5)].reference);
	    (yyval.reference)->node.selection_statement.then_part = (yyvsp[(5) - (5)].reference);
	    (yyval.reference)->node.selection_statement.else_part = NULL;
	}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1402 "./cod.y"
    { 
	    (yyval.reference) = cod_new_selection_statement();
	    (yyval.reference)->node.selection_statement.lx_srcpos = (yyvsp[(1) - (7)].info).lx_srcpos;
	    (yyval.reference)->node.selection_statement.conditional = (yyvsp[(3) - (7)].reference);
	    (yyval.reference)->node.selection_statement.then_part = (yyvsp[(5) - (7)].reference);
	    (yyval.reference)->node.selection_statement.else_part = (yyvsp[(7) - (7)].reference);
	}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1414 "./cod.y"
    { 
	    (yyval.reference) = cod_new_iteration_statement();
	    (yyval.reference)->node.selection_statement.lx_srcpos = (yyvsp[(1) - (9)].info).lx_srcpos;
	    (yyval.reference)->node.iteration_statement.init_expr = (yyvsp[(3) - (9)].reference);
	    (yyval.reference)->node.iteration_statement.test_expr = (yyvsp[(5) - (9)].reference);
	    (yyval.reference)->node.iteration_statement.iter_expr = (yyvsp[(7) - (9)].reference);
	    (yyval.reference)->node.iteration_statement.statement = (yyvsp[(9) - (9)].reference);
	}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1424 "./cod.y"
    { 
	    (yyval.reference) = cod_new_iteration_statement();
	    (yyval.reference)->node.selection_statement.lx_srcpos = (yyvsp[(1) - (5)].info).lx_srcpos;
	    (yyval.reference)->node.iteration_statement.init_expr = NULL;
	    (yyval.reference)->node.iteration_statement.test_expr = (yyvsp[(3) - (5)].reference);
	    (yyval.reference)->node.iteration_statement.iter_expr = NULL;
	    (yyval.reference)->node.iteration_statement.statement = (yyvsp[(5) - (5)].reference);
	}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1436 "./cod.y"
    { (yyval.reference) = NULL; }
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1441 "./cod.y"
    {
	    (yyval.reference) = cod_new_constant();
	    (yyval.reference)->node.constant.token = integer_constant;
	    (yyval.reference)->node.constant.const_val = (yyvsp[(1) - (1)].info).string;
	    (yyval.reference)->node.constant.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1448 "./cod.y"
    {
	    (yyval.reference) = cod_new_constant();
	    (yyval.reference)->node.constant.token = floating_constant;
	    (yyval.reference)->node.constant.const_val = (yyvsp[(1) - (1)].info).string;
	    (yyval.reference)->node.constant.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1455 "./cod.y"
    {
	    (yyval.reference) = cod_new_constant();
	    (yyval.reference)->node.constant.token = string_constant;
	    (yyval.reference)->node.constant.const_val = (yyvsp[(1) - (1)].info).string;
	    (yyval.reference)->node.constant.lx_srcpos = (yyvsp[(1) - (1)].info).lx_srcpos;
	}
    break;



/* Line 1455 of yacc.c  */
#line 3602 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1463 "./cod.y"

#include "lex.yy.c"

typedef struct scope *scope_ptr;

struct parse_struct {
    sm_list decls;
    sm_list standard_decls;
    scope_ptr scope;
    int defined_type_count;
    char **defined_types;
    err_out_func_t error_func;
    void *client_data;
    sm_list return_type_list;
    int return_cg_type;
    int has_exec_context;
};

static int
semanticize_compound_statement(cod_parse_context context, sm_ref compound, 
			       scope_ptr containing_scope);
static int semanticize_decls_list(cod_parse_context context, sm_list decls, 
				  scope_ptr scope);
static int semanticize_array_type_node(cod_parse_context context,
				       sm_ref array, scope_ptr scope);
static int semanticize_reference_type_node(cod_parse_context context,
					   sm_ref decl, scope_ptr scope);
static void add_decl(char *id, sm_ref node, scope_ptr scope);
static sm_ref find_complex_type(sm_ref node, scope_ptr scope);
static const char *cod_code_string;
static int is_string(sm_ref expr);


int
cod_semanticize_added_decls(cod_parse_context context)
{
    return semanticize_decls_list(context, context->decls, context->scope);
}

extern void
cod_swap_decls_to_standard(cod_parse_context context)
{
    context->standard_decls = context->decls;
    context->decls = NULL;
}

int
cod_parse_for_context(code, context)
char *code;
cod_parse_context context;
{
    sm_list decls;
    int ret;
#if defined(YYDEBUG) && (YYDEBUG != 0)
    extern int yydebug;
    yydebug = 1;
#endif
    if (code != NULL) {
	setup_for_string_parse(code, context->defined_type_count, context->defined_types);
	cod_code_string = code;
    }
    yyerror_count = 0;
    yycontext = context;
    yyparse();
    terminate_string_parse();

    if ((yyparse_value == NULL) || (yyerror_count != 0)) {
	return 0;
    }

    decls = (sm_list) yyparse_value;
    if (context->decls) {
	sm_list last = context->decls;
	while (last->next != NULL)
	    last = last->next;
	last->next = decls;
    } else {
	context->decls = decls;
    }
    ret = semanticize_decls_list(context, decls, context->scope);
    if (ret == 0) {
	cod_rfree_list(decls, NULL);
	context->decls = NULL;
    }
    return ret;
}

cod_code
cod_code_gen(code, context)
char *code;
cod_parse_context context;
{
    sm_ref tmp, tmp2;
    cod_code ret_code;
    unsigned int offset;
    void *func;

    if (code != NULL) {
	setup_for_string_parse(code, context->defined_type_count, context->defined_types);
	cod_code_string = code;
    }

    yyerror_count = 0;
    yycontext = context;
    yyparse();
    terminate_string_parse();

    if ((yyparse_value == NULL) || (yyerror_count != 0)) {
	return 0;
    }
    tmp = cod_new_compound_statement();
    tmp->node.compound_statement.decls = context->decls;
    tmp->node.compound_statement.statements =
	malloc(sizeof(struct list_struct));
    tmp->node.compound_statement.statements->next = NULL;
    tmp->node.compound_statement.statements->node = yyparse_value;
    tmp2 = cod_new_compound_statement();
    tmp2->node.compound_statement.decls = context->standard_decls;
    tmp2->node.compound_statement.statements =
	malloc(sizeof(struct list_struct));
    tmp2->node.compound_statement.statements->next = NULL;
    tmp2->node.compound_statement.statements->node = tmp;
    if (!semanticize_compound_statement(context, tmp, context->scope)) {
	tmp->node.compound_statement.decls = NULL;
	tmp2->node.compound_statement.decls = NULL;
	cod_rfree(tmp2);
	return NULL;
    }
    ret_code = malloc(sizeof(struct _cod_code_struct));
    memset(ret_code, 0, sizeof(struct _cod_code_struct));
    ret_code->code_memory_block = NULL;
    ret_code->data = NULL;
    ret_code->has_exec_ctx = context->has_exec_context;
    ret_code->static_block_address_register = -1;
    func = cod_cg_net(tmp, context->return_cg_type, &offset, ret_code);
    tmp->node.compound_statement.decls = NULL;
    tmp2->node.compound_statement.decls = NULL;
    cod_rfree(tmp2);
    ret_code->func = (void(*)())(long)func;
    return ret_code;
}

void 
cod_dump(cod_code code)
{
    printf("ECL CODE structure %p - \n", code);
    printf("  function pointer %p, code memory block %p, data %p, static size %d\n",
	   code->func, code->code_memory_block,
	   code->data, code->static_size_required);
#ifdef HAVE_DILL_H
    dill_dump((dill_stream) code->drisc_context);
#endif
}
    

int
cod_code_verify(code, context)
char *code;
cod_parse_context context;
{
    sm_ref tmp;

    if (code != NULL) {
	setup_for_string_parse(code, context->defined_type_count, context->defined_types);
	cod_code_string = code;
    }

    yyerror_count = 0;
    yycontext = context;
    yyparse();
    terminate_string_parse();

    if ((yyparse_value == NULL) || (yyerror_count != 0)) {
	return 0;
    }

    tmp = cod_new_compound_statement();
    tmp->node.compound_statement.decls = context->decls;
    tmp->node.compound_statement.statements =
	malloc(sizeof(struct list_struct));
    tmp->node.compound_statement.statements->next = NULL;
    tmp->node.compound_statement.statements->node = yyparse_value;
    if (semanticize_compound_statement(context, tmp, context->scope) == 0) {
	tmp->node.compound_statement.decls = NULL;
	cod_rfree(tmp);
	return 0;
    }
    tmp->node.compound_statement.decls = NULL;
    cod_rfree(tmp);
    return 1;
}

extern void 
cod_code_free(code)
cod_code code;
{
    if (code->code_memory_block) free(code->code_memory_block);
    if (code->data) free(code->data);
#if defined(HAVE_DILL_H)
    if (code->drisc_context) {
	dill_free_stream((dill_stream) code->drisc_context);
    }
#endif
    free(code);
}

static char *
copy_line(const char *line_begin)
{
    const char *line_end;
    if ((line_end = strchr(line_begin, 10)) == NULL) {
	/* no CR */
	return strdup(line_begin);
    } else {
	char *tmp = malloc(line_end - line_begin + 1);
	strncpy(tmp, line_begin, line_end - line_begin);
	tmp[line_end - line_begin] = 0;
	return tmp;
    }
}

static void
default_error_out(void *client_data, char *string)
{
    fprintf(stderr, "%s", string);
}

static void
print_context(cod_parse_context context, int line, int character)
{
    const char *tmp = cod_code_string;
    const char *line_begin = cod_code_string;
    char *line_copy = NULL;
    int i, line_len, offset = 0;

    while (line > 1) {
	switch(*tmp) {
	case 10:
	    line_begin = tmp + 1;
	    line--;
	    break;
	case 0:
	    line = 1;   /* end of src */
	    break;
	}
	tmp++;
    }
    if (character > 40) {
	offset = character - 40;
    }
    line_copy = copy_line(line_begin + offset);
    line_len = strlen(line_copy);
    if (line_len > 60) {
	line_copy[60] = 0;
    }
    context->error_func(context->client_data, line_copy);
    context->error_func(context->client_data, "\n");
    free(line_copy);
    for(i=offset + 1; i< character; i++) {
	if (line_begin[i-1] == '\t') {
	    context->error_func(context->client_data, "\t");
	} else {
	    context->error_func(context->client_data, " ");
	}
    }
    context->error_func(context->client_data, "^\n");
}

void yyerror(str)
char *str;
{
    char tmp_str[100];
    yycontext->error_func(yycontext->client_data, "## Error ");
    yycontext->error_func(yycontext->client_data, str);
    yycontext->error_func(yycontext->client_data, "\n");
    yycontext->error_func(yycontext->client_data, "## While parsing near ");
    yycontext->error_func(yycontext->client_data, yytext);
    sprintf(tmp_str, ", offset = %d, line = %d ####\n",lex_offset,line_count);
    yycontext->error_func(yycontext->client_data, tmp_str);
    print_context(yycontext, line_count, lex_offset);
    yyerror_count++;
}

#ifdef STDC_HEADERS
static void
cod_src_error(cod_parse_context context, sm_ref expr, char *format, ...)
#else
static void
cod_src_error(context, expr, format, va_alist)
cod_parse_context context;
sm_ref expr;
char *format;
va_dcl
#endif
{

    va_list ap;
    char *tmp = malloc(10240); /* arbitrarily large */
    srcpos lx_srcpos = {0,0};
#ifdef STDC_HEADERS
    va_start(ap, format);
#else
    va_start(ap);
#endif
    if (expr) lx_srcpos = cod_get_srcpos(expr);
    context->error_func(context->client_data, "## Ecode Error:  ");
    vsprintf(tmp, format, ap);
    context->error_func(context->client_data, tmp);
    sprintf(tmp, " at line %d, char %d\n", lx_srcpos.line, lx_srcpos.character);
    context->error_func(context->client_data, tmp);
    free(tmp);
    print_context(context, lx_srcpos.line, lx_srcpos.character);
}

extern void
cod_print_dimen_p(dimen_p d)
{
    int i;
    for (i=0; i < d->dimen_count; i++) {
	if (d->dimens[i].static_size != -1) {
	    printf("[%d]", d->dimens[i].static_size);
	} else {
	    sm_ref field = d->dimens[i].control_field;
	    printf("[%s]", field->node.field.name);
	}
    }
    printf("\n");
}

extern void
cod_print_operator_t(operator_t o)
{
    switch (o) {
    case  op_modulus:
	printf("MODULUS");
	break;
    case  op_plus:
	printf("PLUS");
	break;
    case  op_minus:
	printf("MINUS");
	break;
    case  op_leq:
	printf("LEQ");
	break;
    case  op_lt:
	printf("LESS THAN");
	break;
    case  op_geq:
	printf("GEQ");
	break;
    case  op_gt:
	printf("GREATER THAN");
	break;
    case  op_eq:
	printf("EQUAL");
	break;
    case  op_neq:
	printf("NOT EQUAL");
	break;
    case  op_log_or:
	printf("LOGICAL OR");
	break;
    case  op_log_and:
	printf("LOGICAL AND");
	break;
    case op_log_neg:
	printf("LOGICAL NEGATION");
	break;
    case op_arith_and:
	printf("ARITH AND");
	break;
    case op_arith_or:
	printf("ARITH OR");
	break;
    case op_arith_xor:
	printf("ARITH XOR");
	break;
    case op_left_shift:
	printf("LEFT SHIFT");
	break;
    case op_right_shift:
	printf("RIGHT SHIFT");
	break;
    case  op_mult:
	printf("MULTIPLY");
	break;
    case  op_div:
	printf("DIVISION");
	break;
    case  op_deref:
	printf("DEREFERENCE");
	break;
    case  op_inc:
	printf("INCREMENT");
	break;
    case  op_dec:
	printf("DECREMENT");
	break;
    case  op_address:
	printf("ADDRESS");
	break;
    case op_sizeof:
	printf("SIZEOF");
	break;
    }
}

extern void
cod_print_srcpos(srcpos pos)
{
    printf("line %d, char %d", pos.line, pos.character);
}

extern void
cod_print_enc_info(enc_info enc)
{
    if (enc == NULL) {
	printf("Not encoded");
    } else {
	switch(enc->byte_order) {
	case 1:
	    printf("Bigendian");
	    break;
	case 2:
	    printf("Littleendian");
	    break;
	}
    }
}

extern void
free_enc_info(enc_info enc)
{
    free(enc);
}

typedef struct st_entry {
    char *id;
    sm_ref node;
    struct st_entry *next;
} *st_entry;

struct scope {
    cod_extern_list externs;
    struct st_entry *entry_list;
    struct scope *containing_scope;
};


extern cod_parse_context
cod_copy_context(context)
cod_parse_context context;
{
    int i;
    cod_parse_context new_context = new_cod_parse_context();
    new_context->has_exec_context = context->has_exec_context;
    new_context->decls = cod_copy_list(context->decls);
    new_context->scope->externs = context->scope->externs;
    new_context->error_func = context->error_func;
    new_context->client_data = context->client_data;
    semanticize_decls_list(new_context, new_context->decls, 
			   new_context->scope);
    new_context->defined_types = malloc(sizeof(char*) *
					context->defined_type_count);
    for (i=0; i< context->defined_type_count; i++) {
	new_context->defined_types[i] = context->defined_types[i];
    }
    return new_context;
}

static void *
resolve_extern(char *id, scope_ptr scope)
{
    if (scope == NULL) return NULL;
    if (scope->externs != NULL) {
	cod_extern_list externs = scope->externs;
	while(externs->extern_name != NULL) {
	    if (strcmp(id, externs->extern_name) == 0) {
		return externs->extern_value;
	    }
	    externs++;
	}
    }
    return resolve_extern(id, scope->containing_scope);
}

static scope_ptr
push_scope(scope_ptr containing_scope)
{
    scope_ptr new_scope = malloc(sizeof(*new_scope));
    new_scope->externs = NULL;
    new_scope->entry_list = NULL;
    new_scope->containing_scope = containing_scope;
    return new_scope;
}

static void
pop_scope(scope_ptr scope)
{
    st_entry list = scope->entry_list;
    while (list != NULL) {
	st_entry tmp = list->next;
	free(list);
	list = tmp;
    }
    free(scope);
}

extern void
dump_scope(scope_ptr scope)
{
    printf("Containing_scope is %p\n", scope->containing_scope);
    printf("Extern list:");
    if (scope->externs != NULL) {
	int i = 0;
	while (scope->externs[i].extern_name != NULL) {
	    printf("\t\"%s\" -> 0x%p\n", scope->externs[i].extern_name,
		   scope->externs[i].extern_value);
	    i++;
	}
    }
    printf("Symbol list:");
    if (scope->entry_list != NULL) {
	st_entry e = scope->entry_list;
	while (e != NULL) {
	    printf("\t\"%s\" -> 0x%p\n", e->id, e->node);
	    cod_print(e->node);
	    e = e->next;
	}
    }
}	
static void
add_decl(char *id, sm_ref node, scope_ptr scope)
{
    st_entry entry = malloc(sizeof(*entry));
    entry->node = node;
    entry->id = id;
    entry->next = scope->entry_list;
    scope->entry_list = entry;
}

extern void
cod_add_decl_to_scope(char *id, sm_ref node, cod_parse_context context)
{
    add_decl(id, node, context->scope);
}

static sm_ref
resolve_local(char *id, scope_ptr scope)
{
    st_entry list = scope->entry_list;
    while(list != NULL) {
	if (strcmp(list->id, id) == 0) {
	    return list->node;
	}
	list = list->next;
    }
    return NULL;
}

static sm_ref
resolve(char *id, scope_ptr scope)
{
    sm_ref tmp;
    if (scope == NULL) return NULL;
    tmp = resolve_local(id, scope);
    if (tmp != NULL) {
	return tmp;
    }
    return resolve(id, scope->containing_scope);
}

static char*
gen_anon()
{
    static int anon_count = 0;
    char *ret = malloc(strlen("Anonymous-xxxxxxxxxxxxxxxxx"));
    sprintf(ret, "Anonymous-%d", anon_count++);
    return ret;
}

static int
determine_unary_type(cod_parse_context context, sm_ref expr, sm_ref right)
{
    int right_type = cod_sm_get_type(right);
    operator_t op = expr->node.operator.op;
    switch(right_type) {
    case DILL_C: case DILL_UC: case DILL_S: case DILL_US:
	right_type = DILL_I;   /* integer promotion */
    }
    if (op == op_minus) {
	switch(right_type) {
	case DILL_U:
	    return DILL_I;
	case DILL_UL:
	    return DILL_L;
	}
    }
    return right_type;
}

static int 
determine_op_type(cod_parse_context context, sm_ref expr, 
		  sm_ref left, sm_ref right)
{
    int unsigned_used = 0;
    int left_type  = cod_sm_get_type(left);
    int right_type = cod_sm_get_type(right);
    operator_t op = expr->node.operator.op;

    if (left_type == DILL_P) {
	if (is_string(expr->node.operator.left) &&
	    is_string(expr->node.operator.right) &&
	    (op == op_eq)) {
	    return DILL_I;
	}

	if(get_complex_type(context, left)->node_type == cod_struct_type_decl) {
	    cod_src_error(context, expr, 
			  "Illegal arithmetic. Left side is a structure.");
	    return DILL_ERR;
	}

	switch(right_type) {
	case DILL_P:
	case DILL_C:
	case DILL_UC:
	case DILL_S:
	case DILL_US:
	case DILL_I:
	case DILL_U:
	case DILL_L:
	case DILL_UL:
	    return DILL_P;
	    
	default:
	    cod_src_error(context, expr, 
			  "Illegal pointer arithmetic. Right side is of incompatible type.");
	    return DILL_ERR;
	}
    }
    if (right_type == DILL_P) {

	if(get_complex_type(context, right)->node_type == cod_struct_type_decl) {
	    cod_src_error(context, expr, 
			  "Illegal arithmetic. Right side is a structure.");
	    return DILL_ERR;
	}

	switch(left_type) {
	case DILL_P:
	case DILL_C:
	case DILL_UC:
	case DILL_S:
	case DILL_US:
	case DILL_I:
	case DILL_U:
	case DILL_L:
	case DILL_UL:
	    return DILL_P;
	    
	default:
	    cod_src_error(context, expr, 
			  "Illegal pointer arithmetic. Left side is of incompatible type.");
	    return DILL_ERR;
	}	
	
    }
    if (left_type == DILL_B) {
	cod_src_error(context, expr, 
		      "Illegal arithmetic.  Left side is a structured type");
	return DILL_ERR;
    }
    if (right_type == DILL_B) {
	cod_src_error(context, expr, 
		      "Illegal arithmetic.  Right side is a structured type");
	return DILL_ERR;
    }
    if ((left_type == DILL_D) || (right_type == DILL_D)) {
	if ((op == op_modulus) || (op == op_log_or) || (op == op_log_and)) {
	    cod_src_error(context, expr, "Operands must be integral.");
	    return DILL_ERR;
	} else {
	    return DILL_D;
	}
    }
    if ((left_type == DILL_F) || (right_type == DILL_F)) {
	if ((op == op_modulus) || (op == op_log_or) || (op == op_log_and)) {
	    cod_src_error(context, expr, "Operands must be integral.");
	    return DILL_ERR;

	} else {
	    return DILL_F;
	}
    }
    switch(left_type) {
    case DILL_C: case DILL_UC: case DILL_S: case DILL_US:
	left_type = DILL_I;   /* integer promotion */
    }
    switch(right_type) {
    case DILL_C: case DILL_UC: case DILL_S: case DILL_US:
	right_type = DILL_I;   /* integer promotion */
    }
    switch(left_type) {
    case DILL_UC: case DILL_US: case DILL_U: case DILL_UL:
	unsigned_used++;
    }
    switch(right_type) {
    case DILL_UC: case DILL_US: case DILL_U: case DILL_UL:
	unsigned_used++;
    }
    if ((op == op_left_shift) || (op == op_right_shift)) return left_type;
    if ((left_type == DILL_UL) || (right_type == DILL_UL)) return DILL_UL;
    if ((left_type == DILL_L) || (right_type == DILL_L)) {
	/* GSE -bug  This test should be for *generated* target, not host */
	if (sizeof(long) > sizeof(unsigned int)) {
	    /* Long can represent all values of unsigned int */
	    return DILL_L;
	} else {
	    return unsigned_used? DILL_UL : DILL_L;
	}
    }
    if ((left_type == DILL_U) || (right_type == DILL_U)) return DILL_U;
    return unsigned_used? DILL_U: DILL_I;
}

static sm_ref reduce_type_list(cod_parse_context context, sm_list type_list, 
			       int *cg_type, scope_ptr scope, int *is_typedef);
static int 
assignment_types_match(cod_parse_context context, sm_ref left, sm_ref right);

static int
is_n_dimen_array(int dimen, sm_ref expr)
{
    if ((dimen == 0) && (expr == NULL)) return 1;
    if ((dimen > 0) && (expr == NULL)) return 0;
    if (dimen == 0) {
	if (expr->node_type == cod_array_type_decl) {
	    return 0;
	} else {
	    return 1;
	}
    }
    if (expr->node_type == cod_field_ref) {
	return is_n_dimen_array(dimen, expr->node.field_ref.sm_field_ref);
    }
    if (expr->node_type == cod_element_ref) {
	return is_n_dimen_array(dimen + 1, expr);
    }
    if (expr->node_type != cod_field) return 0;
    if (expr->node_type == cod_field) {
	return is_n_dimen_array(dimen, expr->node.field.sm_complex_type);
    }
    /* ought to recurse or handle above */
    assert(0);
    return 0;
}

static int 
is_string(sm_ref expr)
{
    if (expr->node_type == cod_field) {
	return (strcmp(expr->node.field.string_type, "string") == 0);
    } else if (expr->node_type == cod_field_ref) {
	return is_string(expr->node.field_ref.sm_field_ref);
    } else if (expr->node_type == cod_identifier) {
	return is_string(expr->node.identifier.sm_declaration);
    } else if (expr->node_type == cod_declaration) {
	if (expr->node.declaration.cg_type != DILL_P) return 0;
	if (expr->node.declaration.sm_complex_type != NULL) return 0;
	/* only strings have pointers without complex types */
	return 1;
    } else if (expr->node_type == cod_constant) {
	return (expr->node.constant.token == string_constant);
    }
    return 0;
}

extern int 
cod_expr_is_string(sm_ref expr)
{
    return is_string(expr);
}

extern int 
is_control_value(sm_ref expr, sm_ref strct)
{
    sm_list fields;
    if (expr->node_type == cod_field_ref) {
	return is_control_value(expr->node.field_ref.sm_field_ref,
				expr->node.field_ref.struct_ref);
    }
    if (expr->node_type != cod_field) return 0;
    assert(strct != NULL);
    strct = get_complex_type(0, strct);	
    if (strct->node_type == cod_reference_type_decl) {
	strct = strct->node.reference_type_decl.sm_complex_referenced_type;
    }
    if (strct->node_type == cod_declaration) {
	strct = strct->node.declaration.sm_complex_type;
    }
    assert(strct->node_type == cod_struct_type_decl);
    fields =  strct->node.struct_type_decl.fields;
    while(fields != NULL) {
	sm_ref ctype = fields->node->node.field.sm_complex_type;
	if ((ctype != NULL) && (ctype->node_type == cod_reference_type_decl))
	    ctype = ctype->node.reference_type_decl.sm_complex_referenced_type;
	while (ctype != NULL) {
	    if (ctype->node_type == cod_array_type_decl) {
		if (ctype->node.array_type_decl.sm_dynamic_size == expr) {
		    return 1;
		}
		ctype = ctype->node.array_type_decl.sm_complex_element_type;
	    } else {
		ctype = NULL;
	    }
	}
	fields = fields->next;
    }
    return 0;
}


static char*
type_list_to_string(cod_parse_context context, sm_list type_list, int *size)
{
    sm_list orig_list = type_list;
    int short_appeared = 0;
    int long_appeared = 0;
    int int_appeared = 0;
    int double_appeared = 0;
    int float_appeared = 0;
    int char_appeared = 0;
    int signed_appeared = 0;
    int unsigned_appeared = 0;
    int void_appeared = 0;
    int string_appeared = 0;
    int spec_count = 0;
    int prefix_end = 0;
    int type_found = 0;
    int cg_type;

    cg_type = DILL_ERR;
    while ((type_list != NULL) && (prefix_end == 0)) {
	int typ = type_list->node->node.type_specifier.token;
	if ((type_list->node->node_type != cod_type_specifier) ||
	    (typ == STAR) || (typ == AT)) {
	    prefix_end = 1;
	} else {
	    spec_count++;
	    switch (typ) {
	    case INT:
		int_appeared++;
		break;
	    case LONG:
		long_appeared++;
		break;
	    case SHORT:
		short_appeared++;
		break;
	    case DOUBLE:
		double_appeared++;
		break;
	    case STRING:
		string_appeared++;
		break;
	    case VOID:
		void_appeared++;
		break;
	    case FLOAT:
		float_appeared++;
		break;
	    case CHAR:
		char_appeared++;
		break;
	    case SIGNED:
		signed_appeared++;
		break;
	    case UNSIGNED:
		unsigned_appeared++;
		break;
	    case TYPEDEF:
		break;
	    default:
		printf("Unknown type\n");
	    }
	    type_list = type_list->next;
	}
    }
    if (spec_count == 0) {
	if (type_list == NULL) cg_type = DILL_I;   /* default to int */
	goto finalize;
    }
    if (void_appeared && (spec_count > 1)) {
	cod_src_error(context, orig_list->node, 
		      "Void type may not appear with other specifiers");
	cg_type = DILL_ERR;
	return NULL;
    }
    if (string_appeared && (spec_count > 1)) {
	cod_src_error(context, orig_list->node, 
		      "String type may not appear with other specifiers");
	cg_type = DILL_ERR;
	return NULL;
    }
    if (void_appeared) {
	cg_type = DILL_V;
	goto finalize;
    }
    if (string_appeared) {
	cg_type = DILL_P;
	goto finalize;
    }
    if (short_appeared + long_appeared > 1) {
	cod_src_error(context, orig_list->node, 
		      "Only one of long or short permitted");
	cg_type = DILL_ERR;
	return NULL;
    }
    if (short_appeared && (double_appeared + float_appeared)) {
	cod_src_error(context, orig_list->node, 
		      "Short may not be specified with double or float");
	cg_type = DILL_ERR;
	return NULL;
    }
    if (double_appeared + float_appeared) {
	if (double_appeared + float_appeared + short_appeared + signed_appeared + unsigned_appeared + char_appeared + int_appeared > 1) {
	    cod_src_error(context, orig_list->node, "Bad type spec");
	    cg_type = DILL_ERR;
	    return NULL;
	} else {
	    /* not handling LONG plus one of these */
	    if (double_appeared) {
		cg_type = DILL_D;
		goto finalize;
	    } else {
		cg_type = DILL_F;
		goto finalize;
	    }
	}
    }

    /* neither float or double appeared */
    if (short_appeared + char_appeared + long_appeared >= 2) {
	cod_src_error(context, orig_list->node, 
		      "Only one integer size spec may be specified");
	cg_type = DILL_ERR;
	return NULL;
    }
    if (unsigned_appeared + signed_appeared > 1) {
	cod_src_error(context, orig_list->node, "Bad type spec");
	cg_type = DILL_ERR;
	return NULL;
    }
    if (unsigned_appeared) {
	if (char_appeared) {
	    cg_type = DILL_UC;
	    goto finalize;
	} else if (short_appeared) {
	    cg_type = DILL_US;
	    goto finalize;
	} else if (long_appeared) {
	    cg_type = DILL_UL;
	    goto finalize;
	} else {
	    cg_type = DILL_U;
	    goto finalize;
	}
    } else {
	if (char_appeared) {
	    cg_type = DILL_C;
	    goto finalize;
	} else if (short_appeared) {
	    cg_type = DILL_S;
	    goto finalize;
	} else if (long_appeared) {
	    cg_type = DILL_L;
	    goto finalize;
	} else {
	    cg_type = DILL_I;
	    goto finalize;
	}
    }
 finalize:
    if (cg_type != DILL_ERR) {
	type_found++;
    }
    switch(cg_type) {
    case DILL_I: 
	*size = sizeof(int);
	return strdup("integer");
    case DILL_L:
	*size = sizeof(long);
	return strdup("integer");
    case DILL_S:
	*size = sizeof(short);
	return strdup("integer");
    case DILL_U: 
	*size = sizeof(int);
	return strdup("unsigned");
    case DILL_UL:
	*size = sizeof(long);
	return strdup("unsigned");
    case DILL_US:
	*size = sizeof(short);
	return strdup("unsigned");
    case DILL_F:
	*size = sizeof(float);
	return strdup("float");
    case DILL_D:
	*size = sizeof(double);
	return strdup("float");
    }
    return NULL;
}

static sm_ref
cod_build_parsed_type_node(cod_parse_context c, char *name, sm_list l)
{
    sm_ref decl = cod_new_struct_type_decl();
    sm_list *end_ptr = &decl->node.struct_type_decl.fields;

    sm_list tmp = l;
    sm_list last_type = NULL;
    int field_count = 0;
    decl->node.struct_type_decl.id = strdup(name);
    
     while(tmp != NULL) {
	sm_ref node = tmp->node;
	sm_list typ = NULL;
	sm_list new_elem;
	new_elem = malloc(sizeof(*new_elem));
	new_elem->next = NULL;
	new_elem->node = cod_new_field();
	if (node->node_type == cod_declaration) {
	    typ = node->node.declaration.type_spec;
	    new_elem->node->node.field.name = node->node.declaration.id;
	    new_elem->node->node.field.string_type  = 
		type_list_to_string(c, typ, &new_elem->node->node.field.cg_size);
	} else if (node->node_type == cod_array_type_decl) {
	    sm_ref base_decl = node->node.array_type_decl.element_ref;
	    sm_ref size = node->node.array_type_decl.size_expr;
	    char *base_string_type = NULL;
	    char *size_str = NULL, *final_type;
	    typ = node->node.array_type_decl.type_spec;
	    if (base_decl->node_type != cod_declaration) {
		printf("Array base type must be a simple type\n");
		return NULL;
	    }
	    new_elem->node->node.field.name = base_decl->node.declaration.id;
	    base_string_type  = 
		type_list_to_string(c, typ, &new_elem->node->node.field.cg_size);
	    if (size->node_type == cod_constant) {
		if (size->node.constant.token != integer_constant) {
		    printf("Array size constant is non-integer\n");
		    return NULL;
		} else {
		    size_str = size->node.constant.const_val;
		}
	    } else if (size->node_type == cod_identifier) {
		size_str = size->node.identifier.id;
	    } else {
		printf("Unexpected value for array size\n");
		return NULL;
	    }
	    final_type = malloc(strlen(base_string_type) + 
				      strlen(size_str) + 3);
	    sprintf(final_type, "%s[%s]", base_string_type, size_str);
	    new_elem->node->node.field.string_type = final_type;
	    free(base_string_type);
		
	}
	new_elem->node->node.field.cg_offset = -1;
	new_elem->node->node.field.cg_type = DILL_ERR;
	new_elem->node->node.field.type_spec = typ;
	free(node);
	field_count++;
	last_type = tmp;
	tmp = tmp->next;
	free(last_type);
	*end_ptr = new_elem;
	end_ptr = &new_elem->next;
    }
    return decl;
}

static int 
is_array(sm_ref expr)
{
    sm_ref typ;
    if (expr->node_type == cod_field_ref) {
	return is_array(expr->node.field_ref.sm_field_ref);
    }
    if (expr->node_type == cod_identifier) {
	return is_array(expr->node.identifier.sm_declaration);
    }
    if (expr->node_type == cod_declaration) {
	sm_ref ctype = expr->node.declaration.sm_complex_type;
	if ((ctype != NULL) && (ctype->node_type == cod_array_type_decl)) {
	    return 1;
	}
    }
    typ = get_complex_type(NULL, expr);
    if (typ == NULL) return 0;

    if (typ->node_type == cod_array_type_decl) {
	return 1;
    }

    if (typ->node_type == cod_reference_type_decl) {
	sm_ref ctype = 
	    typ->node.reference_type_decl.sm_complex_referenced_type;
	if (ctype == NULL) return 0;
	if (ctype->node_type == cod_array_type_decl) {
	    return 1;
	}
    }
    return 0;
}
    
static sm_ref
get_containing_structure(sm_ref expr)
{
    switch(expr->node_type) {
    case cod_element_ref:
	return get_containing_structure(expr->node.element_ref.array_ref);
    case cod_field_ref:
	return expr->node.field_ref.struct_ref;
    default:
	return NULL;
    }
}

    
static void
add_field_list(int *format_count_p, FMStructDescList *format_list_p, sm_ref typ)
{
    sm_list fields =  typ->node.struct_type_decl.fields;
    FMFieldList field_list = malloc(sizeof(field_list[0]) * 2);
    int field_count = 0;
    int my_format_num = (*format_count_p)++;
    *format_list_p = realloc(*format_list_p, sizeof(*format_list_p[0]) * (*format_count_p + 1));
    while(fields != NULL) {
	field_list = realloc(field_list, (sizeof(field_list[0]) * (field_count +2)));
	field_list[field_count].field_name = strdup(fields->node->node.field.name);
	field_list[field_count].field_type = strdup(fields->node->node.field.string_type);
	field_list[field_count].field_size = fields->node->node.field.cg_size;
	field_list[field_count].field_offset = fields->node->node.field.cg_offset;
	if ((fields->node->node.field.sm_complex_type != NULL) &&
	    (fields->node->node.field.sm_complex_type->node_type == cod_struct_type_decl)) {
	    add_field_list(format_count_p, format_list_p,
			   fields->node->node.field.sm_complex_type);
	}
	field_count++;
	fields = fields->next;
    }
    field_list[field_count].field_name = field_list[field_count].field_type = NULL;
    field_list[field_count].field_size = field_list[field_count].field_offset = 0;
    (*format_list_p)[my_format_num].format_name = strdup(typ->node.struct_type_decl.id);
    (*format_list_p)[my_format_num].field_list = field_list;
    (*format_list_p)[my_format_num].struct_size = typ->node.struct_type_decl.cg_size;
    (*format_list_p)[my_format_num].opt_info = NULL;
}

static FMStructDescList
build_format_list(cod_parse_context context, sm_ref expr)
{
    sm_ref typ = get_complex_type(context, expr);
    FMStructDescList formats = malloc(sizeof(formats[0]) * 2);
    int format_count = 0;
    if (typ == NULL) {
	cod_src_error(context, expr->node.field_ref.struct_ref, 
		      "Reference must be structured type", 
		      expr->node.field_ref.lx_field);
	return 0;
    }
    if (typ->node_type == cod_reference_type_decl) {
	typ = typ->node.reference_type_decl.sm_complex_referenced_type;
    }
    if (typ->node_type == cod_declaration) {
	typ = typ->node.declaration.sm_complex_type;
    }
    add_field_list(&format_count, &formats, typ);
    formats[format_count].format_name = NULL;
    formats[format_count].field_list = NULL;
    return formats;
}

static int semanticize_expr(cod_parse_context context, sm_ref expr, 
			    scope_ptr scope) 
{
    switch(expr->node_type) {
    case cod_identifier: {
	sm_ref tmp = resolve(expr->node.identifier.id, scope);
	if (tmp != NULL) {
            if (tmp->node_type == cod_constant) {
                srcpos old_srcpos = expr->node.identifier.lx_srcpos;
                /* morph idenfitfier into constant */
                expr->node_type = cod_constant;
                expr->node.constant.token = tmp->node.constant.token;
                expr->node.constant.const_val = strdup(tmp->node.constant.const_val);
                expr->node.constant.lx_srcpos = old_srcpos;
                return semanticize_expr(context, expr, scope);
            } else {
                expr->node.identifier.sm_declaration = tmp;
                return 1;
            }
	} else {
	    cod_src_error(context, expr,
			  "Undefined Symbol \"%s\"", 
			  expr->node.identifier.id);
	    return 0;
	}
    }
    case cod_cast: {
	int cg_type;
	sm_ref typ;
	if (expr->node.cast.expression &&
	    !semanticize_expr(context, expr->node.cast.expression, scope)) {
	    return 0;
	}

	typ = reduce_type_list(context, expr->node.cast.type_spec, &cg_type, 
			       scope, NULL);
	if ((cg_type == DILL_ERR) && (typ == NULL)) {
	    cod_src_error(context, expr, "Illegal cast");
	    return 0;
	}
	expr->node.cast.cg_type = cg_type;
	expr->node.cast.sm_complex_type = typ;
	return 1;
    }
    case cod_operator: {
	int ret = 1;
	if (expr->node.operator.left != NULL) {
	    if (!semanticize_expr(context, expr->node.operator.left, scope)) {
		ret = 0;
	    }
	}
	if (expr->node.operator.right != NULL) {
	    if (!semanticize_expr(context, expr->node.operator.right, scope)) {
		ret = 0;
	    }
	}
	if (ret == 0) return 0;
	if ((expr->node.operator.left != NULL) && 
	    (expr->node.operator.right != NULL)) {
	    expr->node.operator.operation_type = 
		determine_op_type(context, expr, 
				  expr->node.operator.left,
				  expr->node.operator.right);
	    if (expr->node.operator.operation_type == DILL_ERR) {
		return 0;
	    }
	} else if (expr->node.operator.right != NULL) {
	    expr->node.operator.operation_type = 
		determine_unary_type(context, expr, expr->node.operator.right);
	} else if (expr->node.operator.left != NULL) {
	    expr->node.operator.operation_type = 
		determine_unary_type(context, expr, expr->node.operator.left);
	}
	switch (expr->node.operator.op) {
	case op_leq: case op_lt: case op_geq: case op_gt: case op_neq: 
	case op_eq:  case op_log_neg: case op_log_or: case op_log_and:
	case op_sizeof:
	    expr->node.operator.result_type = DILL_I;
	    break;
	case op_address:
	    expr->node.operator.result_type = DILL_P;
	    if (expr->node.operator.right->node_type == cod_identifier) {
		sm_ref decl = expr->node.operator.right->node.identifier.sm_declaration;
		if (decl->node_type == cod_declaration) {
		    if (decl->node.declaration.param_num != -1) {
			cod_src_error(context, expr, "Cannot take address of a parameter");
			return 0;
		    }
		    decl->node.declaration.addr_taken = 1;
		}
	    } else {
		/* Can only take the address of something we can name... */
		cod_src_error(context, expr, "Invalid operand to address operator");
		return 0;
	    }
	    break;
	case op_deref: {
	    sm_ref typ = get_complex_type(context, expr->node.operator.right);
	    if (!typ || (typ->node_type != cod_reference_type_decl)) {
		cod_src_error(context, expr, "Cannot dereference a non-reference type");
		return 0;
	    } else {
		expr->node.operator.result_type =
		    typ->node.reference_type_decl.cg_referenced_type;
	    }
	    break;
	}
	default:
	    /* Operator applied to pointer types? Check compatibility... */
	    if(expr->node.operator.operation_type == DILL_P) {
		
		switch(expr->node.operator.op) {
		case op_inc:
		case op_dec:
		    break;
		    
		case op_plus:
		{
		    sm_ref left  = expr->node.operator.left;
		    sm_ref right = expr->node.operator.right;
		    
		    sm_ref lcplx = NULL;
		    sm_ref rcplx = NULL;

		    if(!left) {
			cod_src_error(context, expr,
				      "Invalid operand to unary plus\n");
			return 0;
		    }
		    
		    /* Extract complex types, if any */
		    lcplx = get_complex_type(context, left);
		    rcplx = get_complex_type(context, right);
		 
		    /* Pointers do not add with complex types */
		    if(lcplx && rcplx) {
			cod_src_error(context, expr,
				      "Invalid operands to binary plus");
			return 0;
		    }

		    /*
		     * We're ok if we reach this, since that implies we have subtraction 
		     * between a pointer and an integral type. The suitability of the
		     * integral type has been checked in determine_op_type() already.
		     */
		}
		break;

		case op_minus:
		{
		    sm_ref left  = expr->node.operator.left;
		    sm_ref right = expr->node.operator.right;
		    
		    sm_ref lcplx = NULL;
		    sm_ref rcplx = NULL;

		    if(!left) {
			cod_src_error(context, expr,
				      "Invalid operand to unary minus\n");
			return 0;
		    }

		    /* Extract complex types, if any */
		    lcplx = get_complex_type(context, left);
		    rcplx = get_complex_type(context, right);

		    
		    /* If both are complex types... */
		    if(lcplx && rcplx) {

			/* If both are pointers... */
			if(lcplx->node_type == cod_reference_type_decl &&
			   rcplx->node_type == cod_reference_type_decl) {
			    /* Check if the argument pointers are compatible */
			    if(!are_compatible_ptrs(lcplx, rcplx)) {
				cod_src_error(context, expr,
					      "Incompatible pointer arguments to binary minus");
				return 0;
			    } else {
				/*
				 * Binary minus between two compatible pointers is allowed,
				 * but it produces an integral type, so we fix that here.
				 */
				expr->node.operator.result_type=DILL_L;
				
				/*
				 * NOTE how we return success directly from here and do not
				 * break from the switch through the line below setting the
				 * result_type from the operation_type... In this case this
				 * would cause problems. We want operation_type to stay DILL_P
				 * but the final result_type to be a DILL_L.
				 */
				return 1;
			    }
			} else {
			    /*
			     * Pointers and other complex types do not subtract.
			     * Arithmetic canno be done on non-pointer complex types.
			     */
			    cod_src_error(context, expr,
					  "Incompatible arguments to binary minus");
			    return 0;
			}
		    }

		    /*
		     * We're ok if we reach this, since that implies we have subtraction 
		     * between a pointer and an integral type. The suitability of the
		     * integral type has been checked in determine_op_type() already.
		     */
		}
		break;
		
		default:
		    cod_src_error(context, expr,
				  "Operator cannot be applied to pointer types!\n");
		    return 0;
		}
	    }
	    /*
	     * NOTE: If anything here changes, one (potentially) has to
	     * update the code above which deals with binary minus
	     * between two compatible pointers, changes the result to
	     * an integral type, and returns directly without going
	     * through this code (as all other cases do).
	     */
	    expr->node.operator.result_type=expr->node.operator.operation_type;
	}
	return ret;
    }
    case cod_constant:
	return 1;
    case cod_assignment_expression: {
	int ret = 1;
	if (!semanticize_expr(context, expr->node.assignment_expression.left, scope)) {
	    ret = 0;
	} else {
	    expr->node.assignment_expression.cg_type = 
		cod_sm_get_type(expr->node.assignment_expression.left);
	}
	if ((expr->node.assignment_expression.cg_type == DILL_P) ||
	    (expr->node.assignment_expression.cg_type == DILL_ERR)) {
	    sm_ref typ = 
		get_complex_type(context, 
				 expr->node.assignment_expression.left);
	    if (typ == NULL) {
		if (!is_string(expr->node.assignment_expression.left)) {
		    cod_src_error(context, expr->node.assignment_expression.left, "Invalid assignment, left side must be simple, non-pointer type");
		    ret = 0;
		}
	    } else {
		if (typ->node_type != cod_reference_type_decl) {
		    cod_src_error(context, expr->node.assignment_expression.left, "Invalid assignment, left side must be simple, non-pointer type");
		    ret = 0;
		}
	    }
	}
	if (!semanticize_expr(context, expr->node.assignment_expression.right, scope)){
	    ret = 0;
	} else {
	    int right_type = 
		cod_sm_get_type(expr->node.assignment_expression.right);
	    if ((right_type == DILL_P) && 
		(is_string(expr->node.assignment_expression.right))) {
		if (expr->node.assignment_expression.cg_type != DILL_P) {
		    cod_src_error(context, expr, "assignment mixes string and non-string types");
		    ret = 0;
		}
	    } else if ((right_type == DILL_B) || (right_type == DILL_ERR)) {
		cod_src_error(context, expr->node.assignment_expression.right, "Invalid assignment, right side must be simple type");
		ret = 0;
	    }
	}
	if (ret == 1) {
	    ret = assignment_types_match(context,
					 expr->node.assignment_expression.left,
					 expr->node.assignment_expression.right);
	}
	return ret;
    }
    case cod_field_ref: {
	sm_ref typ;
	sm_list fields;
	if (!semanticize_expr(context, expr->node.field_ref.struct_ref, scope)) {
	    return 0;
	}
	typ = get_complex_type(context, expr->node.field_ref.struct_ref);
	if (typ == NULL) {
	    cod_src_error(context, expr->node.field_ref.struct_ref, 
			  "Reference must be structured type", 
			  expr->node.field_ref.lx_field);
	    return 0;
	}
	if (typ->node_type == cod_reference_type_decl) {
	    typ = typ->node.reference_type_decl.sm_complex_referenced_type;
	}
	if (typ->node_type == cod_declaration) {
	    typ = typ->node.declaration.sm_complex_type;
	}
	fields =  typ->node.struct_type_decl.fields;
	while(fields != NULL) {
	    if (strcmp(expr->node.field_ref.lx_field,
		       fields->node->node.field.name) == 0) {
		break;
	    }
	    fields = fields->next;
	}
	if (fields == NULL) {
	    cod_src_error(context, expr, 
			  "Unknown field reference, \"%s\".",
			  expr->node.field_ref.lx_field);
	    return 0;
	}
	expr->node.field_ref.sm_field_ref = fields->node;
	return 1;
    }
    case cod_element_ref: {
	if (semanticize_expr(context, expr->node.element_ref.array_ref, scope)) {
	    int cg_type;
	    sm_ref arr;
	    if (!is_array(expr->node.element_ref.array_ref)) {
		cod_src_error(context, expr, "Indexed element must be array");
		return 0;
	    }
	    arr = get_complex_type(NULL, expr->node.element_ref.array_ref);
	    if (arr->node_type == cod_reference_type_decl) {
		arr = arr->node.reference_type_decl.sm_complex_referenced_type;
	    }
	    expr->node.element_ref.sm_complex_element_type = 
		arr->node.array_type_decl.sm_complex_element_type;
	    expr->node.element_ref.cg_element_type = 
		arr->node.array_type_decl.cg_element_type;
	    expr->node.element_ref.sm_containing_structure_ref =
		get_containing_structure(expr->node.element_ref.array_ref);
	    if (!semanticize_expr(context, expr->node.element_ref.expression, scope)) {
		return 0;
	    }
	    
	    cg_type = cod_sm_get_type(expr->node.element_ref.expression);
	    switch(cg_type) {
	    case DILL_C:
	    case DILL_UC:
	    case DILL_S:
	    case DILL_US:
	    case DILL_I: 
	    case DILL_U: 
	    case DILL_L:
	    case DILL_UL:
		return 1;
		break;
	    }
	    cod_src_error(context, expr, 
			  "Index for element reference must be integer type");
	    return 0;
	}
	return 0;
    }
    case cod_subroutine_call: {
	sm_ref func_ref = expr->node.subroutine_call.sm_func_ref;
	sm_ref tmp = resolve(func_ref->node.identifier.id, scope);
	sm_list args = expr->node.subroutine_call.arguments;
	sm_list formals;
	int ret = 1;
	if (tmp != NULL) {
	    if ((tmp->node_type != cod_declaration) ||
		!tmp->node.declaration.is_subroutine) {
		cod_src_error(context, expr, 
			      "Identifier is not subroutine \"%s\".", 
			func_ref->node.identifier.id);
		return 0;
	    }
	    free(func_ref->node.identifier.id);
	    free(func_ref);
	    expr->node.subroutine_call.sm_func_ref = func_ref = tmp;
	    formals = func_ref->node.declaration.params;
	} else {
	    cod_src_error(context, func_ref, "Undefined Subroutine \"%s\".", 
			  func_ref->node.identifier.id);

	    return 0;
	}
	while (args != NULL) {
	    sm_ref arg = args->node;
	    sm_ref formal = NULL;
	    if (formals != NULL) {
		formal = formals->node;
	    }
	    if (formal && (formal->node.declaration.sm_complex_type != NULL)) {
		sm_ref ct = formal->node.declaration.sm_complex_type;
		if ((ct->node_type == cod_reference_type_decl) &&
		    (ct->node.reference_type_decl.name != NULL)) {
		    if (strcmp(ct->node.reference_type_decl.name, "cod_exec_context") == 0) {
                        if (context->has_exec_context == 0) {
                            cod_src_error(context, arg, "Calling subroutine has no cod_exec_context");
                            return 0;
                        }
                        /* swallow next formal, we'll fill that in ourselves */
                        formals = formals->next;
                        continue;
                    } else if (strcmp(ct->node.reference_type_decl.name, "cod_closure_context") == 0) {
                        sm_list tmp_args = malloc(sizeof(struct list_struct));
                        char tmp[30];
                        tmp_args->next = args->next;
			tmp_args->node = args->node;
			args->next = tmp_args;
                        sprintf(tmp, "%d", func_ref->node.declaration.closure_id);

                        args->node = cod_new_constant();
                        args->node->node.constant.token = integer_constant;
                        args->node->node.constant.const_val = strdup(tmp);
                    }
                }
	    }
	    if (!semanticize_expr(context, arg, scope) ) {
		args = args->next;
		continue;
	    }
	    if (formal == NULL) {
		cod_src_error(context, arg, "Too many arguments to subroutine");
		ret = 0;
		return ret;
	    }
	    if (strcmp(formal->node.declaration.id, "...") != 0) {
		/* we've got a real formal to check against */
		/* do some checking... */
		int mismatch = 0;
		switch (cod_sm_get_type(arg)) {
		case DILL_D: case DILL_F:
		    if ((formal->node.declaration.cg_type != DILL_D) &&
			(formal->node.declaration.cg_type != DILL_F)) {
			mismatch++;
		    }
		    break;
		case DILL_I: case DILL_U:
		case DILL_L: case DILL_UL:
		    if ((formal->node.declaration.cg_type == DILL_D) ||
			(formal->node.declaration.cg_type == DILL_F) ||
			(formal->node.declaration.cg_type == DILL_P)) {
			sm_ref ct = formal->node.declaration.sm_complex_type;
			if (!ct || 
			    (ct->node_type != cod_reference_type_decl) ||
			    (strcmp(ct->node.reference_type_decl.name, "cod_type_spec") != 0)) {
			    mismatch++;
			}
		    }
		    break;
		case DILL_P:
		    if ((formal->node.declaration.cg_type != DILL_P) &&
			(formal->node.declaration.sm_complex_type->node_type !=
			 cod_reference_type_decl)) {
			mismatch++;
		    }
		    break;
		}

		if (mismatch) {
		    cod_src_error(context, arg, 
				  "Type mismatch, parameter \"%s\".",
			    formal->node.declaration.id);
		    ret = 0;
		}
	    }
	    if ((formals != NULL) &&
		(strcmp(formal->node.declaration.id, "...") != 0)) {
		formals = formals->next;
		formal = NULL;
		if (formals != NULL) formal = formals->node;
	    }
	    /* look ahead to next formal and insert an arg if it's cod_type_spec */
	    if (formal &&
		formal->node.declaration.sm_complex_type != NULL) {
		sm_ref ct = formal->node.declaration.sm_complex_type;
		if ((ct->node_type == cod_reference_type_decl) &&
		    (strcmp(ct->node.reference_type_decl.name, "cod_type_spec")
		     == 0)) {
		    /* swallow next formal, we'll fill that in ourselves */
		    sm_list tmp_args = malloc(sizeof(struct list_struct));
		    FMStructDescList list = build_format_list(context,  arg);
		    char tmp[30];
		    sprintf(&tmp[0], "0x%p", list);
		    tmp_args->node = cod_new_constant();
		    tmp_args->node->node.constant.token = integer_constant;
		    tmp_args->node->node.constant.const_val = strdup(tmp);
		    tmp_args->next = args->next;
		    args->next = tmp_args;
		}
	    }
	    args = args->next;
	    if ((args == NULL) && (formals != NULL)) {
		if (strcmp(formal->node.declaration.id, "...") != 0) {
		    cod_src_error(context, arg, "Too few arguments to function");
		    ret = 0;
		}
	    }
	}
	return ret;
    }
    default:
	fprintf(stderr, "Unknown case in semanticize_expression\n");
	cod_print(expr);
    }
    return 0;
}

extern int
cod_sm_get_type(sm_ref node)
{
    switch(node->node_type) {
    case cod_identifier:
	if (node->node.identifier.sm_declaration != NULL) {
	    return cod_sm_get_type(node->node.identifier.sm_declaration);
	}
	return node->node.identifier.cg_type;
    case cod_operator:
	return node->node.operator.result_type;
    case cod_cast:
	return node->node.cast.cg_type;
    case cod_assignment_expression:
	return node->node.assignment_expression.cg_type;
    case cod_declaration:
	return node->node.declaration.cg_type;
    case cod_constant:
	/* need to handle bigger constants */
	if (node->node.constant.token == string_constant) {
	    return DILL_P;
	} else if (node->node.constant.token == floating_constant) {
	    return DILL_F;
	} else {
	    return DILL_I;
	}
    case cod_field_ref:
	return cod_sm_get_type(node->node.field_ref.sm_field_ref);
    case cod_element_ref:
	return node->node.element_ref.cg_element_type;
    case cod_field:
	if (is_array(node)) {
	    return DILL_P;
	} else {
	    return node->node.field.cg_type;
	}
    case cod_subroutine_call:
	return cod_sm_get_type(node->node.subroutine_call.sm_func_ref);
    default:
	fprintf(stderr, "Unknown case in cod_sm_get_type()\n");
	cod_print(node);
    }
    return DILL_ERR;
}

extern int
are_compatible_ptrs(sm_ref left, sm_ref right) {
    sm_ref lTyp, rTyp;

    /* Sanity check */
    if(left->node_type != cod_reference_type_decl ||
       right->node_type != cod_reference_type_decl) return 0;
    
    lTyp = left->node.reference_type_decl.sm_complex_referenced_type;
    rTyp = right->node.reference_type_decl.sm_complex_referenced_type;

    if(lTyp && rTyp) {
	/* Two complex referenced types */
	if(lTyp->node_type == cod_reference_type_decl &&
	   rTyp->node_type == cod_reference_type_decl) {
	    /* Recurse if both are pointers */
	    return are_compatible_ptrs(lTyp, rTyp);
	}
	return (lTyp == rTyp)?1:0;
    }

    if(!lTyp && !rTyp) {
	/* Two integral referenced types */
	return (left->node.reference_type_decl.cg_referenced_type ==
		right->node.reference_type_decl.cg_referenced_type)?1:0;
    }

    /* Mix of a pointer to a complex type and a pointer to an integral type */
    return 0;
}

extern sm_ref
get_complex_type(cod_parse_context context, sm_ref node)
{
    switch(node->node_type) {
    case cod_subroutine_call:
	return NULL;
    case cod_identifier:
	return get_complex_type(context, 
				node->node.identifier.sm_declaration);
    case cod_element_ref:
	return node->node.element_ref.sm_complex_element_type;
    case cod_field:
	return node->node.field.sm_complex_type;
    case cod_declaration:
	return node->node.declaration.sm_complex_type;
    case cod_field_ref:{
	sm_ref typ;
	sm_list fields;
	typ = get_complex_type(context, node->node.field_ref.struct_ref);
	if (typ->node_type == cod_reference_type_decl) {
	    typ = typ->node.reference_type_decl.sm_complex_referenced_type;
	}
	if (typ->node_type == cod_declaration) {
	    typ = typ->node.declaration.sm_complex_type;
	}
	fields =  typ->node.struct_type_decl.fields;
	while ((fields != NULL) && 
	       (strcmp(node->node.field_ref.lx_field,
		       fields->node->node.field.name) != 0)) {
	    fields = fields->next;
	}
	if (fields == NULL) {
	    cod_src_error(context, node, "Unknown field reference \"%s\".",
		    node->node.field_ref.lx_field);
	    return NULL;
	}
	return fields->node->node.field.sm_complex_type;
    }
    case cod_constant:
	return NULL;
    case cod_operator:
	switch (node->node.operator.op) {
	case op_deref: {
	    sm_ref right = get_complex_type(NULL, node->node.operator.right);
	    if ((right != NULL) && 
		(right->node_type == cod_reference_type_decl)) {
		return right->node.reference_type_decl.sm_complex_referenced_type;
	    }
	    return NULL;
	}
	case op_plus: case op_minus: case op_inc: case op_dec: {
	    sm_ref right = NULL;
	    sm_ref left  = NULL;
	    if (node->node.operator.right)
		right = get_complex_type(NULL, node->node.operator.right);
	    if (node->node.operator.left)
		left = get_complex_type(NULL, node->node.operator.left);
	    if (right && (left == NULL)) return right;
	    if (left && (right == NULL)) return left;
	    if ((left == NULL) && (right == NULL)) return NULL;
	    /*
	     * GANEV: op_minus can be applied to two pointers,
	     * i.e. two complex types => both left _and_ right can be
	     * non-NULL, hence this code. This shouldn't happen in
	     * other cases... (I think).
	     */
	    if(node->node.operator.op == op_minus && right && left) {
		if(left->node_type == cod_reference_type_decl &&
		   right->node_type == cod_reference_type_decl) {
		    /* Ok, so it's op_minus between two pointers, then check compatibility */
		    if(are_compatible_ptrs(left, right)) {
			return left;
		    } else {
			cod_src_error(context, node, 
				      "Incompatible pointer args to binary minus");
			return NULL;
		    }
		}
	    }
	    fprintf(stderr, "Unknown case in get_complex_type() int ops\n");
	    cod_print(node);
	    return NULL;
	}
	default:
	    return NULL;
	}

    case cod_cast:
	/* GANEV: can we have casts to complex types? */
	return NULL;
	break;

    default:
	fprintf(stderr, "Unknown case in get_complex_type()\n");
	cod_print(node);
    }
    return NULL;
}

static sm_ref
reduce_type_list(cod_parse_context context, sm_list type_list, int *cg_type,
			    scope_ptr scope, int*is_typedef) 
{
    sm_list orig_list = type_list;
    int short_appeared = 0;
    int long_appeared = 0;
    int int_appeared = 0;
    int double_appeared = 0;
    int float_appeared = 0;
    int char_appeared = 0;
    int signed_appeared = 0;
    int unsigned_appeared = 0;
    int void_appeared = 0;
    int string_appeared = 0;
    int spec_count = 0;
    int prefix_end = 0;
    int type_found = 0;
    sm_ref complex_return_type = NULL;;

    *cg_type = DILL_ERR;
    while ((type_list != NULL) && (prefix_end == 0)) {
	int typ = type_list->node->node.type_specifier.token;
	if ((type_list->node->node_type != cod_type_specifier) ||
	    (typ == STAR) || (typ == AT)) {
	    prefix_end = 1;
	} else {
	    spec_count++;
	    switch (typ) {
	    case INT:
		int_appeared++;
		break;
	    case LONG:
		long_appeared++;
		break;
	    case SHORT:
		short_appeared++;
		break;
	    case DOUBLE:
		double_appeared++;
		break;
	    case STRING:
		string_appeared++;
		break;
	    case VOID:
		void_appeared++;
		break;
	    case FLOAT:
		float_appeared++;
		break;
	    case CHAR:
		char_appeared++;
		break;
	    case SIGNED:
		signed_appeared++;
		break;
	    case UNSIGNED:
		unsigned_appeared++;
		break;
	    case TYPEDEF:
		if (is_typedef) (*is_typedef)++;
		break;
	    default:
		printf("Unknown type\n");
	    }
	    type_list = type_list->next;
	}
    }
    if (spec_count == 0) {
	if (type_list == NULL) *cg_type = DILL_I;   /* default to int */
	goto finalize;
    }
    if (void_appeared && (spec_count > 1)) {
	cod_src_error(context, orig_list->node, 
		      "Void type may not appear with other specifiers");
	*cg_type = DILL_ERR;
	return NULL;
    }
    if (string_appeared && (spec_count > 1)) {
	cod_src_error(context, orig_list->node, 
		      "String type may not appear with other specifiers");
	*cg_type = DILL_ERR;
	return NULL;
    }
    if (void_appeared) {
	*cg_type = DILL_V;
	goto finalize;
    }
    if (string_appeared) {
	*cg_type = DILL_P;
	goto finalize;
    }
    if (short_appeared + long_appeared > 1) {
	cod_src_error(context, orig_list->node, 
		      "Only one of long or short permitted");
	*cg_type = DILL_ERR;
	return NULL;
    }
    if (short_appeared && (double_appeared + float_appeared)) {
	cod_src_error(context, orig_list->node, 
		      "Short may not be specified with double or float");
	*cg_type = DILL_ERR;
	return NULL;
    }
    if (double_appeared + float_appeared) {
	if (double_appeared + float_appeared + short_appeared + signed_appeared + unsigned_appeared + char_appeared + int_appeared > 1) {
	    cod_src_error(context, orig_list->node, "Bad type spec");
	    *cg_type = DILL_ERR;
	    return NULL;
	} else {
	    /* not handling LONG plus one of these */
	    if (double_appeared) {
		*cg_type = DILL_D;
		goto finalize;
	    } else {
		*cg_type = DILL_F;
		goto finalize;
	    }
	}
    }

    /* neither float or double appeared */
    if (short_appeared + char_appeared + long_appeared >= 2) {
	cod_src_error(context, orig_list->node, 
		      "Only one integer size spec may be specified");
	*cg_type = DILL_ERR;
	return NULL;
    }
    if (unsigned_appeared + signed_appeared > 1) {
	cod_src_error(context, orig_list->node, "Bad type spec");
	*cg_type = DILL_ERR;
	return NULL;
    }
    if (unsigned_appeared) {
	if (char_appeared) {
	    *cg_type = DILL_UC;
	    goto finalize;
	} else if (short_appeared) {
	    *cg_type = DILL_US;
	    goto finalize;
	} else if (long_appeared) {
	    *cg_type = DILL_UL;
	    goto finalize;
	} else {
	    *cg_type = DILL_U;
	    goto finalize;
	}
    } else {
	if (char_appeared) {
	    *cg_type = DILL_C;
	    goto finalize;
	} else if (short_appeared) {
	    *cg_type = DILL_S;
	    goto finalize;
	} else if (long_appeared) {
	    *cg_type = DILL_L;
	    goto finalize;
	} else {
	    *cg_type = DILL_I;
	    goto finalize;
	}
    }
 finalize:
    if (type_list == NULL) {
	/* no error and no more to process */
	return NULL;  
    }
    if (*cg_type != DILL_ERR) {
	type_found++;
    }
    while (type_list != NULL) {
	sm_ref node = type_list->node;
	switch (node->node_type) {
	case cod_identifier: 
	{
	    if (type_found != 0) {
		cod_src_error(context, node, 
			      "Type identifier cannot follow prior identifiers");
		*cg_type = DILL_ERR;
		return NULL;
	    }
	    complex_return_type = find_complex_type(node, scope);
	    if ((complex_return_type != NULL)&&
		(complex_return_type->node_type == cod_declaration)) {
		complex_return_type = complex_return_type->node.declaration.sm_complex_type;
	    }
	    if ((complex_return_type != NULL)&&
		(complex_return_type->node_type == cod_reference_type_decl)) {
		*cg_type = DILL_P;
	    }
	    if ((complex_return_type != NULL)&&
		(complex_return_type->node_type == cod_struct_type_decl)) {
		*cg_type = DILL_B;
	    }
	    if ((complex_return_type == NULL) && node->node.identifier.id &&
		((strcmp(node->node.identifier.id, "cod_type_spec") == 0) ||
                 (strcmp(node->node.identifier.id, "cod_closure_context") == 0) ||
		 (strcmp(node->node.identifier.id, "cod_exec_context") == 0))) {
		/* special ECL type information for prior arg */
		sm_ref typ = cod_new_reference_type_decl();
		typ->node.reference_type_decl.name = node->node.identifier.id;
		if (strcmp(node->node.identifier.id, "cod_type_spec") == 0) {
		    *cg_type = DILL_P;
                } else if (strcmp(node->node.identifier.id, "cod_closure_context") == 0) {
                    *cg_type = DILL_I;
		} else {
		    context->has_exec_context = 1;
		    *cg_type = DILL_EC;
		}
		typ->node.reference_type_decl.cg_referenced_type = *cg_type;
		typ->node.reference_type_decl.sm_complex_referenced_type =
		    complex_return_type;
		typ->node.reference_type_decl.kernel_ref = 0;
		complex_return_type = typ;
	    }
	    assert(complex_return_type != NULL);
	    type_found++;
	}
	break;
	case cod_type_specifier:
	    switch (node->node.type_specifier.token) {
	    case STAR:
	      {
		  if (node->node.type_specifier.created_type_decl == NULL) {
		      /* GSE create anon-type */
		      sm_ref typ = cod_new_reference_type_decl();
		      typ->node.reference_type_decl.name = gen_anon();
		      typ->node.reference_type_decl.cg_referenced_type = *cg_type;
		      *cg_type = DILL_P;
		      typ->node.reference_type_decl.sm_complex_referenced_type =
			  complex_return_type;
		      typ->node.reference_type_decl.kernel_ref = 0;
		      complex_return_type = typ;
		      node->node.type_specifier.created_type_decl = typ;
		  } else {
		      complex_return_type = node->node.type_specifier.created_type_decl;
		      *cg_type = DILL_P;
		  }
	      }
	      break;
	    case AT:
	      {
		  /* GSE create anon-type */
		  sm_ref typ = cod_new_reference_type_decl();
		  typ->node.reference_type_decl.name = gen_anon();
		  typ->node.reference_type_decl.cg_referenced_type = *cg_type;
		  *cg_type = DILL_P;
		  typ->node.reference_type_decl.sm_complex_referenced_type =
		      complex_return_type;
		  typ->node.reference_type_decl.kernel_ref = 1;
		  complex_return_type = typ;
	      }
	      break;
	    default:
		if (type_found != 0) {
		    cod_src_error(context, node, 
				  "Only '*', '@', and CONST can follow valid type");
		    *cg_type = DILL_ERR;
		    return NULL;
		}
	    }
	    break;
	case cod_struct_type_decl: {
	    complex_return_type = node;
	    break;
	}
	default:
	    printf("Unexpected node in reduce_type_list\n");
	    return NULL;
	}
	type_list = type_list->next;
    }
    return complex_return_type;
}

static int 
assignment_types_match(cod_parse_context context, sm_ref left, sm_ref right)
{
    sm_ref left_smt, right_smt;
    int left_cgt, right_cgt;
    left_smt = get_complex_type(context, left);
    right_smt = get_complex_type(context, right);
    left_cgt = cod_sm_get_type(left);
    right_cgt = cod_sm_get_type(right);
    if ((left_smt == NULL) && (right_smt == NULL)) {
	/* just check cgts */
	/* don't mix DILL_P, DILL_B and anything else */
	switch (left_cgt) {
	case DILL_P: 
	    switch (right_cgt) {
	    case DILL_P:
	    case DILL_L:
	    case DILL_UL:
		return 1;
		break;
	    default:
		cod_src_error(context, left, "Trying to assign a pointer variable with a non-pointer value.");
		return 0;
	    }
	default:
	    switch (right_cgt) {
	    case DILL_P:
		cod_src_error(context, left, "Trying to assign pointer to an incompatible variable.");
		return 0;
	    default:
		return 1;
		break;
	    }
	}
    }
    if ((left_smt != NULL) && 
	(left_smt->node_type != cod_reference_type_decl)) {
	cod_src_error(context, left, "Only pointer complex types allowed as LHS in assignment");
	return 0;
    }
    if ((right_smt != NULL) && 
	(right_smt->node_type != cod_reference_type_decl)) {
	cod_src_error(context, right, "Only pointer complex types allowed as RHS in assignment");
	return 0;
    }
    if (left_smt && (right_smt == NULL)) {

	switch(right_cgt) {
	case DILL_P:
	case DILL_L:
	case DILL_UL:
	    return 1;

	default:
	    cod_src_error(context, right, "Right hand side must be pointer type");
	    return 0;
	}
    }
    if (right_smt && (left_smt == NULL)) {
	switch(left_cgt) {
	case DILL_C:
	case DILL_UC:
	case DILL_S:
	case DILL_US:
	case DILL_I:
	case DILL_U:
	case DILL_L:
	case DILL_UL:
	case DILL_P:
	    /* GANEV: should we have a warning here? */
	    return 1;

	default:
	    cod_src_error(context, right, "Pointer converted without explicit cast");
	    return 0;
	}
    }
    return 1;	
}

static int semanticize_struct_type_node(cod_parse_context context, sm_ref decl, 
					scope_ptr scope);

static int semanticize_decl(cod_parse_context context, sm_ref decl, 
			    scope_ptr scope)
{
    switch(decl->node_type) {
    case cod_declaration: 
	if (resolve_local(decl->node.declaration.id, scope) != NULL) {
	    if (resolve_local(decl->node.declaration.id, scope) != decl) {
		cod_src_error(context, decl, "Duplicate Symbol \"%s\"", 
			      decl->node.declaration.id);
		return 0;
	    } else {
		/* been here, done that */
		return 1;
	    }
	} else {
	    add_decl(decl->node.declaration.id, decl, scope);
	}
	if (scope->containing_scope == NULL) {
	    /* must be external variable */
	    void *extern_value = 
		resolve_extern(decl->node.declaration.id, scope);
	    if (extern_value == NULL) {
		cod_src_error(context, decl, 
			      "External symbol lacking address \"%s\"", 
			decl->node.declaration.id);
		return  0;
	    }
	    decl->node.declaration.cg_address = extern_value;
	    decl->node.declaration.is_extern = 1;
	}
	if (decl->node.declaration.type_spec != NULL) {
	    sm_list l = decl->node.declaration.type_spec;
	    if ((l->node->node_type == cod_type_specifier) && 
		(l->node->node.type_specifier.token == STATIC)) {
		decl->node.declaration.type_spec = l->next;
		decl->node.declaration.static_var = 1;
		free(l);
	    }
	}
	if (decl->node.declaration.static_var) {
	    if (decl->node.declaration.init_value != NULL) {
		sm_ref const_val = decl->node.declaration.init_value;
		if (const_val->node_type != cod_constant) {
		    cod_src_error(context, const_val, 
				  "Only simple constants allowed as static initializers.  Variable \"%s\"",
			decl->node.declaration.id);
		    return 0;
		}
	    }
	}
	if ((decl->node.declaration.sm_complex_type != NULL) &&
	    (decl->node.declaration.param_num != -1)) {
	    /* complex type + param, must be pass by reference */
	    sm_ref type = decl->node.declaration.sm_complex_type;
	    decl->node.declaration.cg_type = DILL_P;
	    if (type->node_type == cod_array_type_decl) {
		int ret = semanticize_array_type_node(context, type, 
						      scope);
		if (ret == 0) return ret;
	    }
	}
	/* some array decls have sm_complex_type set already */
	if (decl->node.declaration.sm_complex_type == NULL) {
	    sm_ref typ = NULL;
	    int cg_type = DILL_I;
	    if (decl->node.declaration.type_spec != NULL) {
		int type_def = 0;
		typ = reduce_type_list(context, decl->node.declaration.type_spec,
				       &cg_type, scope, &type_def);
		if (type_def) {
		    decl->node.declaration.is_typedef = 1;
		}
		if (type_def != 0) {
		    semanticize_decl(context, typ, scope);
		}
	    } else {
		sm_ref arr = decl->node.declaration.sm_complex_type;
		if ((arr != NULL) && 
		    (arr->node_type == cod_array_type_decl)) {
		    typ = reduce_type_list(context, 
					    arr->node.array_type_decl.type_spec, 
					    &cg_type, scope, NULL);
		}
	    }
	    if ((typ == NULL) && (cg_type == DILL_ERR)) return 0;
	    decl->node.declaration.cg_type = cg_type;
	    decl->node.declaration.sm_complex_type = typ;
	}
	if (decl->node.declaration.init_value != NULL) {
	    int ret;
	    ret = semanticize_expr(context, decl->node.declaration.init_value, 
				   scope);
	    if (ret == 0) return ret;
	    ret = assignment_types_match(context, decl, 
					 decl->node.declaration.init_value);
	    return ret;
	}
	if (decl->node.declaration.is_subroutine) {
	    int ret;
	    scope_ptr sub_scope = push_scope(scope);
	    ret = semanticize_decls_list(context,
					 decl->node.declaration.params, 
					 sub_scope);
	    pop_scope(sub_scope);
	    return ret;
	}
	return 1;
	break;
    case cod_struct_type_decl:
	return semanticize_struct_type_node(context, decl, scope);
	break;
    case cod_array_type_decl:
	if (decl->node.array_type_decl.type_spec != NULL) {
	    sm_list l = decl->node.array_type_decl.type_spec;
	    if ((l->node->node_type == cod_type_specifier) && 
		(l->node->node.type_specifier.token == STATIC)) {
		decl->node.array_type_decl.type_spec = l->next;
		decl->node.array_type_decl.element_ref->node.declaration.static_var = 1;
		free(l);
	    }
	}
	return semanticize_array_type_node(context, decl, scope);
	break;
    case cod_reference_type_decl:
	return semanticize_reference_type_node(context, decl, scope);
	break;
    case cod_constant:
        return 1;
        break;
    default:
	printf("Unhandled case in semanticize decls_list\n");
	cod_print(decl);
    }
    return 0;
}

static int
semanticize_decls_list(cod_parse_context context, sm_list decls, 
		       scope_ptr scope)
{
    int ret = 1;
    while (decls != NULL) {
	if (!semanticize_decl(context, decls->node, scope)) {
	    ret = 0;
	}
	decls = decls->next;
    }
    return ret;
}

static int semanticize_statement(cod_parse_context context, sm_ref stmt, 
				 scope_ptr scope);

static int
semanticize_selection_statement(cod_parse_context context, sm_ref selection,
				scope_ptr scope)
{
    int ret = 1;
    if (!semanticize_expr(context, 
			  selection->node.selection_statement.conditional,
			  scope)) {
	ret = 0;
    }
    if (!semanticize_statement(context,
			       selection->node.selection_statement.then_part,
			       scope)) {
	ret = 0;
    }
    if (selection->node.selection_statement.else_part) {
	if (!semanticize_statement(context,
				   selection->node.selection_statement.else_part,
				   scope)) {
	    ret = 0;
	}
    }
    return ret;
}

static int
semanticize_iteration_statement(cod_parse_context context, sm_ref iteration,
				scope_ptr scope)
{
    int ret = 1;
    if (iteration->node.iteration_statement.init_expr != NULL) {
	if (!semanticize_expr(context, 
			      iteration->node.iteration_statement.init_expr,
			      scope)) {
	    ret = 0;
	}
    }

    if (iteration->node.iteration_statement.test_expr != NULL) {
	if (!semanticize_expr(context, 
			      iteration->node.iteration_statement.test_expr,
			      scope)) {
	    ret = 0;
	}
    }

    if (iteration->node.iteration_statement.iter_expr != NULL) {
	if (!semanticize_expr(context, 
			      iteration->node.iteration_statement.iter_expr,
			      scope)) {
	    ret = 0;
	}
    }

    if (iteration->node.iteration_statement.statement != NULL) {
	if (!semanticize_statement(context,
				   iteration->node.iteration_statement.statement,
				   scope)) {
	    ret = 0;
	}
    }
    return ret;
}

static int 
semanticize_statement(cod_parse_context context, sm_ref stmt, 
		      scope_ptr scope)
{
    switch (stmt->node_type) {
    case cod_selection_statement:
	return semanticize_selection_statement(context, stmt, scope);
    case cod_iteration_statement:
	return semanticize_iteration_statement(context, stmt, scope);
    case cod_expression_statement: {
	return semanticize_expr(context, 
				stmt->node.expression_statement.expression,
				scope);
    }	
    case cod_compound_statement:
	return semanticize_compound_statement(context, stmt, scope);
    case cod_return_statement:{
	stmt->node.return_statement.cg_func_type = context->return_cg_type;
	return semanticize_expr(context, 
				stmt->node.return_statement.expression,
				scope);
    }	
    case cod_label_statement:{
	return semanticize_statement(context, stmt->node.label_statement.statement, scope);
    }
    default:
	printf("unhandled case in semanticize statement\n");
	return 1;
    }
}

static int
semanticize_statements(cod_parse_context context, sm_list stmts, 
		       scope_ptr scope)
{
    int ret = 1;
    while (stmts != NULL) {
	if (!semanticize_statement(context, stmts->node, scope)) {
	    ret = 0;
	}
	stmts = stmts->next;
    }
    return ret;
}

extern int
semanticize_compound_statement(cod_parse_context context, sm_ref compound, 
			       scope_ptr containing_scope)
{
    int ret = 1;
    scope_ptr current_scope = push_scope(containing_scope);
    ret &= semanticize_decls_list(context,
				  compound->node.compound_statement.decls,
				  current_scope);
    ret &= semanticize_statements(context,
				  compound->node.compound_statement.statements,
				  current_scope);
    pop_scope(current_scope);
    return ret;
}

extern sm_ref
cod_build_type_node(const char *name, FMFieldList field_list)
{
    sm_ref decl = cod_new_struct_type_decl();
    sm_list *end_ptr = &decl->node.struct_type_decl.fields;

    decl->node.struct_type_decl.id = strdup(name);
    while ((field_list != NULL) && (field_list->field_name != NULL)) {
	sm_list new_elem;
	new_elem = malloc(sizeof(*new_elem));
	new_elem->next = NULL;
	new_elem->node = cod_new_field();
	new_elem->node->node.field.name = strdup(field_list->field_name);
	new_elem->node->node.field.string_type = strdup(field_list->field_type);
	new_elem->node->node.field.cg_size = field_list->field_size;
	new_elem->node->node.field.cg_offset = field_list->field_offset;
	new_elem->node->node.field.cg_type = DILL_ERR;
	*end_ptr = new_elem;
	end_ptr = &new_elem->next;
	field_list++;
    }
    return decl;
}


void
cod_add_defined_type(id, context)
char *id;
cod_parse_context context;
{
    int count = context->defined_type_count;
    if (count == 0) {
	context->defined_types = malloc(sizeof(char*));
    } else {
	context->defined_types = realloc(context->defined_types,
					 (count+1)*sizeof(char*));
    }
    context->defined_types[count] = id;
    context->defined_type_count++;
    reset_types_table(context->defined_type_count, context->defined_types);
}

extern void
cod_add_struct_type(const char *name, FMFieldList field_list, 
		    cod_parse_context context)
{
    sm_ref node = cod_build_type_node(name, field_list);
    cod_add_decl_to_parse_context(name, node, context);
    cod_add_decl_to_scope((char*)name, node, context);
}

static int
str_to_data_type(str, size)
char *str;
int size;
{
    char *tmp = malloc(strlen(str) + 1);
    char *free_str = tmp;
    strcpy(tmp, str);
    str = tmp;			/* make a copy of str parameter */

    while (isspace((int)*str) || (*str == '*') || (*str == '(')) {	/* skip preceeding space */
	str++;
    }
    tmp = str + strlen(str) - 1;
    while (isspace((int)*tmp) || (*tmp == ')')) {  /* test trailing space */
	*tmp = 0;
	tmp--;
    }
    tmp = str;
    while (*tmp) {		/* map to lower case */
	*tmp = tolower(*tmp);
	tmp++;
    }
    if ((strcmp(str, "integer") == 0) || (strcmp(str, "enumeration") == 0)) {
	free(free_str);
	if (size == sizeof(long)) {
	    return DILL_L;
	} else if (size == sizeof(int)) {
	    return DILL_I;
	} else if (size == sizeof(short)) {
	    return DILL_S;
	} else if (size == sizeof(char)) {
	    return DILL_C;
	} else {
	    return DILL_L;
	}
    } else if (strcmp(str, "unsigned integer") == 0) {
	free(free_str);
	if (size == sizeof(long)) {
	    return DILL_UL;
	} else if (size == sizeof(int)) {
	    return DILL_U;
	} else if (size == sizeof(short)) {
	    return DILL_US;
	} else if (size == sizeof(char)) {
	    return DILL_UC;
	} else {
	    return DILL_UL;
	}
    } else if ((strcmp(str, "float") == 0) || (strcmp(str, "double") == 0)) {
	free(free_str);
	if (size == sizeof(double)) {
	    return DILL_D;
	} else if (size == sizeof(float)) {
	    return DILL_F;
	} else {
	    fprintf(stderr, "unsupported float size %d\n", size);
	    return DILL_D;
	}
    } else if (strcmp(str, "char") == 0) {
	free(free_str);
	assert(size == 1);
	return DILL_C;
    } else if (strcmp(str, "string") == 0) {
	free(free_str);
	return DILL_P;
    } else {
	free(free_str);
	return DILL_ERR;
    }
}

static int
array_str_to_data_type(str, size)
char *str;
int size;
{
    int ret_type;
    char field_type[1024];
    char *left_paren;
    if ((left_paren = strchr(str, '[')) == NULL) {
	ret_type = str_to_data_type(str, size);
    } else {
	char *tmp = str;
	int i = 0;
	for( ; tmp < left_paren; tmp++) {
	    field_type[i++] = *tmp;
	}
	field_type[i] = 0;
	ret_type = str_to_data_type(field_type, size);
    }
    return ret_type;
}

static int
ECLget_array_size_dimen(str, fields, dimen, control_field)
const char *str;
FMFieldList fields;
int dimen;
int *control_field;
{
    char *left_paren, *end;
    long static_size;

    *control_field = -1;
    if ((left_paren = strchr(str, '[')) == NULL) {
	return 0;
    }	
    while (dimen != 0) {
	left_paren = strchr(left_paren + 1, '[');
	if (left_paren == NULL) return 0;
	dimen--;
    }
    static_size = strtol(left_paren + 1, &end, 0);
    if (left_paren + 1 == end) {
	/* dynamic element */
	char field_name[1024];
	int count = 0;
	int i = 0;
	while (((left_paren+1)[count] != ']') &&
	       ((left_paren+1)[count] != 0)) {
	    field_name[count] = (left_paren+1)[count];
	    count++;
	}
	field_name[count] = 0;
	while (fields[i].field_name != NULL) {
	    if (strcmp(field_name, fields[i].field_name) == 0) {
		*control_field = i;
		return -1;
	    }
	    i++;
	}
	fprintf(stderr, "Array dimension \"%s\" in type spec \"%s\" not recognized.\n",
		field_name, str);
	fprintf(stderr, "Dimension must be a field name (for dynamic arrays) or a positive integer.\n");
	fprintf(stderr, "To use a #define'd value for the dimension, use the FMArrayDecl() macro.\n");
	return -1;
    }
    if (*end != ']') {
	fprintf(stderr, "Malformed array dimension, unexpected character '%c' in type spec \"%s\"\n",
		*end, str);
	fprintf(stderr, "Dimension must be a field name (for dynamic arrays) or a positive integer.\n");
	fprintf(stderr, "To use a #define'd value for the dimension, use the FMArrayDecl() macro.\n");
	return -1;
    }
    if (static_size <= 0) {
	fprintf(stderr, "Non-positive array dimension %ld in type spec \"%s\"\n",
		static_size, str);
	fprintf(stderr, "Dimension must be a field name (for dynamic arrays) or a positive integer.\n");
	fprintf(stderr, "To use a #define'd value for the dimension, use the FMArrayDecl() macro.\n");
	return -1;
    }
    return static_size;
}

static sm_ref
build_subtype_nodes(context, decl, f, desc, err, scope)
cod_parse_context context;
sm_ref decl;
field* f;
FMTypeDesc *desc;
int *err;
scope_ptr scope;
{
    sm_ref ret = NULL;
    sm_ref subtype = NULL;
    if (desc->next != NULL) {
	subtype = build_subtype_nodes(context, decl, f, desc->next, err, scope);
	if (*err != 0) {
	    return NULL;
	}
    }
    switch (desc->type) {
    case FMType_array: {
	sm_list fields = decl->node.struct_type_decl.fields;
	sm_ref cf;
	int i;
	ret = cod_new_array_type_decl();
	ret->node.array_type_decl.cg_static_size = desc->static_size;
	if (desc->static_size == 0) {
	    ret->node.array_type_decl.cg_static_size = -1;
	}
	ret->node.array_type_decl.cg_element_type = DILL_B;
	ret->node.array_type_decl.sm_complex_element_type = subtype;
	if (subtype == NULL) {
	    ret->node.array_type_decl.cg_element_type = 
		array_str_to_data_type(f->string_type, f->cg_size);
	    ret->node.array_type_decl.cg_element_size = f->cg_size;
	} else {
	    if (subtype->node_type == cod_array_type_decl) {
		int sub_size = subtype->node.array_type_decl.cg_static_size;
		if (sub_size == -1) {
		    /* element of *this* array has varying elements */
		    ret->node.array_type_decl.cg_element_size = -1;
		} else {
		    ret->node.array_type_decl.cg_element_size = 
			sub_size * subtype->node.array_type_decl.cg_element_size;;
		}
	    } else {
		ret->node.array_type_decl.cg_element_size = f->cg_size;
	    }
	}
	    
	if (ret->node.array_type_decl.cg_static_size != -1) {
	    ret->node.array_type_decl.sm_dynamic_size = NULL;
	} else {
	    for (i=0; i < desc->control_field_index; i++) {
		fields = fields->next;
	    }
	    cf = fields->node;
	    switch (str_to_data_type(cf->node.field.string_type, 
				     (int)sizeof(int))) {
	    case DILL_C: case DILL_UC: case DILL_S: case DILL_US: 
	    case DILL_I: case DILL_U: case DILL_L: case DILL_UL:
		break;
	    default:
		cod_src_error(context, NULL, 
			      "Variable length control field \"%s\"not of integer type.", cf->node.field.string_type);
		*err = 1;
		return NULL;
		break;
	    }
	    ret->node.array_type_decl.sm_dynamic_size = cf;
	}
	break;
    }
    case FMType_pointer:
	ret = cod_new_reference_type_decl();
	ret->node.reference_type_decl.name = gen_anon();
	ret->node.reference_type_decl.cg_referenced_type = DILL_ERR;
	ret->node.reference_type_decl.sm_complex_referenced_type = subtype;
	ret->node.reference_type_decl.cg_referenced_size = -1;
	break;
    case FMType_subformat: {
	char *tmp_str = FMbase_type(f->string_type);
	ret = resolve(tmp_str, scope);
	if (ret == NULL) {
	    *err = 1;
	}
	break;
    }
    case FMType_simple:
    case FMType_string:
	ret = NULL;
	break;
    }
    return ret;

}

static void
build_type_nodes(context, decl, f, fields, cg_size, cg_type, desc, err, scope)
cod_parse_context context;
sm_ref decl;
field* f;
sm_list fields;
int cg_size;
int cg_type;
FMTypeDesc* desc;
int *err;
scope_ptr scope;
{
    sm_ref complex_type = build_subtype_nodes(context, decl, f, desc, err, scope);
    f->sm_complex_type = complex_type;
}

static int
semanticize_array_element_node(context, array, super_type, base_type_spec, 
			       scope)
cod_parse_context context;
sm_ref array;
sm_ref super_type;
sm_list base_type_spec;
scope_ptr scope;
{
    if (array->node.array_type_decl.size_expr != NULL) {
	if (semanticize_expr(context,
			     array->node.array_type_decl.size_expr, scope) == 0) {
	    return 0;
	}
    } else {
	sm_ref element_ref = array->node.array_type_decl.element_ref;
	/* allow NULL array type sizes */
	if (element_ref->node_type != cod_declaration) {
	    cod_src_error(context, element_ref, 
			  "Null sizes only allowed in parameter contexts");
	    return 0;
	}
	    
    }
    if (array->node.array_type_decl.element_ref->node_type 
	== cod_declaration) {
	/* we're the last in line */
	sm_ref typ = NULL;
	int cg_type = DILL_ERR;
	int ret;
	sm_ref decl = array->node.array_type_decl.element_ref;
	decl->node.declaration.sm_complex_type = super_type;
	decl->node.declaration.cg_type = DILL_B;
	ret = semanticize_decl(context, decl, scope);
	if (ret == 0) return 0;

	if (decl->node.declaration.type_spec != NULL) {
	    typ = reduce_type_list(context, decl->node.declaration.type_spec,
				   &cg_type, scope, NULL);
	} else {
	    sm_ref arr = decl->node.declaration.sm_complex_type;
	    if ((arr != NULL) && 
		(arr->node_type == cod_array_type_decl)) {
		typ = reduce_type_list(context, 
					arr->node.array_type_decl.type_spec, 
					&cg_type, scope, NULL);
	    }
	}
	if ((typ == NULL) && (cg_type == DILL_ERR)) return 0;
	array->node.array_type_decl.cg_element_type = cg_type;
	array->node.array_type_decl.sm_complex_element_type = typ;
    } else {
	assert(array->node.array_type_decl.element_ref->node_type == cod_array_type_decl);
	array->node.array_type_decl.sm_complex_element_type = array->node.array_type_decl.element_ref;
	return semanticize_array_element_node(context, 
					      array->node.array_type_decl.element_ref,
					      array,  
					      base_type_spec, scope);
    }
    return 1;
}	

static int
semanticize_array_type_node(context, array, scope)
cod_parse_context context;
sm_ref array;
scope_ptr scope;
{
    return semanticize_array_element_node(context, array, array,  
					  array->node.array_type_decl.type_spec,
					  scope);
}

#define Max(i,j) ((i<j) ? j : i)

extern FMTypeDesc*
gen_FMTypeDesc(FMFieldList fl, int field, const char *typ);

static int
semanticize_struct_type_node(cod_parse_context context, sm_ref decl, 
		      scope_ptr scope)
{
    FMFieldList fl = malloc(sizeof(fl[0]));
    int field_num = 0;
    int ret = 1;
    int struct_size = 0;
    sm_list fields = decl->node.struct_type_decl.fields;
    add_decl(decl->node.struct_type_decl.id, decl, scope);
    while(fields != NULL) {
	field *f = &fields->node->node.field;
	fl[field_num].field_name = f->name;
	fl[field_num].field_type = f->string_type;
	fl = realloc(fl, sizeof(fl[0]) * (field_num + 2));
	field_num++;
	fields = fields->next;
    }
    fl[field_num].field_name = NULL;
    fl[field_num].field_type = NULL;
    field_num = 0;
    fields = decl->node.struct_type_decl.fields;
    while(fields != NULL) {
	field *f = &fields->node->node.field;
	int err = 0;
	int field_size = f->cg_size;

	if (f->string_type != NULL) {
	    /* FFS-compatible field type */
	    FMTypeDesc* desc = gen_FMTypeDesc(fl, field_num, f->string_type);
	    if (desc == NULL) {
		cod_src_error(context, decl, 
			      "Field \"%s\" has unknown type \"%s\".",
			      f->name, f->string_type);
		ret = 0;
	    }
	    build_type_nodes(context, decl, f, fields, f->cg_size, f->cg_type,
			     desc, &err, scope);
	    
	    f->cg_type = str_to_data_type(f->string_type, f->cg_size);
	    field_size = f->cg_size;
	    if (f->sm_complex_type) {
		if (f->sm_complex_type->node_type == cod_reference_type_decl) {
		    field_size = sizeof(char*);
		} else if (f->sm_complex_type->node_type == cod_array_type_decl) {
		    sm_ref arr = f->sm_complex_type;
		    while (arr && (arr->node_type == cod_array_type_decl)) {
			if (arr->node.array_type_decl.cg_static_size != -1) {
			    field_size *= arr->node.array_type_decl.cg_static_size;
			}
			arr = arr->node.array_type_decl.sm_complex_element_type;
		    }
		}
	    }
	} else {
	    /* not able to get a FFS-compatible form */
	    int type_def = 0;
	    int cg_type;
	    sm_ref typ;
	    typ = reduce_type_list(context, f->type_spec, &cg_type, scope, 
				   &type_def);
	    f->sm_complex_type = typ;
	    f->cg_type = cg_type;
	    field_size = -1;
	}
	if (err == 1) ret = 0;
	struct_size = Max(struct_size,
			  (f->cg_offset + field_size));
	fields = fields->next;
	field_num++;
    }
    decl->node.struct_type_decl.cg_size = struct_size;
    return ret;
}

static int
semanticize_reference_type_node(cod_parse_context context, sm_ref decl, 
				scope_ptr scope)
{
    int ret = 1;
    int struct_size = 0;
    if (decl->node.reference_type_decl.name != NULL) {
	add_decl(decl->node.reference_type_decl.name, decl, scope);
    }
    decl->node.struct_type_decl.cg_size = struct_size;
    return ret;
}

extern sm_ref
cod_build_param_node(const char *id, sm_ref typ, int param_num)
{
    sm_ref node = cod_new_declaration();
    sm_ref ident;
    node->node.declaration.param_num = param_num;
    node->node.declaration.id = strdup(id);
    node->node.declaration.sm_complex_type = typ;
    if (typ != NULL) {
	ident = cod_new_identifier();
	node->node.declaration.type_spec = malloc(sizeof(struct list_struct));
	node->node.declaration.type_spec->next = NULL;
	node->node.declaration.type_spec->node = ident;
	ident->node.identifier.id = strdup(typ->node.struct_type_decl.id);
    }
    return node;
}

static
sm_ref cod_build_type_node_FMformat(FMFormat format, cod_parse_context context)
{
    sm_ref decl = cod_new_struct_type_decl();
    sm_list *end_ptr = &decl->node.struct_type_decl.fields;
    FMfloat_format data_float;
    FMinteger_format data_int;
    int column_major;
    int pointer_size;
    FMFieldList field_list = format->field_list;
    get_IOformat_characteristics(format, &data_float, &data_int, &column_major, &pointer_size);

    decl->node.struct_type_decl.id = strdup(name_of_FMformat(format));
    decl->node.struct_type_decl.encode_info = malloc(sizeof(struct enc_struct));
    decl->node.struct_type_decl.encode_info->byte_order = data_int;
    decl->node.struct_type_decl.encode_info->float_order = data_float;
    decl->node.struct_type_decl.encode_info->pointer_size = pointer_size;
    while ((field_list != NULL) && (field_list->field_name != NULL)) {
	sm_list new_elem;
	char *colon = strchr(field_list->field_type, ':');
	char *bracket = strchr(field_list->field_type, '[');

	if (colon != NULL) {
	    *colon = 0;
	    if (bracket != NULL) strcpy(colon, bracket);
	}
	new_elem = malloc(sizeof(*new_elem));
	new_elem->next = NULL;
	new_elem->node = cod_new_field();
	new_elem->node->node.field.name = strdup(field_list->field_name);
	new_elem->node->node.field.string_type = strdup(field_list->field_type);
	new_elem->node->node.field.cg_size = field_list->field_size;
	new_elem->node->node.field.cg_offset = field_list->field_offset;
	new_elem->node->node.field.cg_type = DILL_ERR;
	*end_ptr = new_elem;
	end_ptr = &new_elem->next;
	field_list++;
    }
    return decl;
}

extern void
cod_add_encoded_param(const char *id, char *data, int param_num, 
		      FMContext c, cod_parse_context context)
{
    int i = 0;
    FMFormat format = FMformat_from_ID(c, data);
    FMFormat *formats = format->subformats;
    sm_ref top_type = NULL, param_node;
    while (formats[i] != NULL) {
	sm_ref node = cod_build_type_node_FMformat(formats[i], context);
	cod_add_decl_to_parse_context(name_of_FMformat(formats[i]), node, context); 
	cod_add_decl_to_scope(name_of_FMformat(formats[i]), node, context); 
	top_type = node;
	i++;
    }
    
    param_node = cod_build_param_node(id, NULL, param_num);
    param_node->node.declaration.sm_complex_type = top_type;
    cod_add_decl_to_parse_context(id, param_node, context);
}

extern void
cod_add_param(const char *id, const char *typ, int param_num, 
	      cod_parse_context context)
{
    sm_list type_list;
    sm_ref node;
    setup_for_string_parse(typ, context->defined_type_count, context->defined_types);
    cod_code_string = typ;
    parsing_type = 1;
    yyerror_count = 0;
    yycontext = context;
    yyparse();
    parsing_type = 0;
    terminate_string_parse();

    if ((yyparse_value == NULL) || (yyerror_count != 0)) {
	return;
    }
    type_list = (sm_list) yyparse_value;

    node = cod_build_param_node(id, NULL, param_num);
    node->node.declaration.type_spec = type_list;
    cod_add_decl_to_parse_context(id, node, context);
}

extern void
cod_subroutine_declaration(const char *decl, cod_parse_context context)
{
    sm_list type_list, params;
    sm_ref complex_type, declaration;
    int cg_type, param_num;

    setup_for_string_parse(decl, context->defined_type_count, 
			   context->defined_types);
    cod_code_string = decl;
    parsing_param_spec = 1;
    yyerror_count = 0;
    yycontext = context;
    yyparse();
    parsing_param_spec = 0;
    terminate_string_parse();

    if ((yyparse_value == NULL) || (yyerror_count != 0)) {
	return;
    }
    declaration = yyparse_value;
    type_list = declaration->node.declaration.type_spec;

    /* handle return type */
    complex_type = reduce_type_list(context, type_list, &cg_type, context->scope, NULL);
    context->return_type_list = type_list;
    if (complex_type != NULL) {
	cg_type = DILL_P;
    }
    context->return_cg_type = cg_type;


    /* handle params */
    params = declaration->node.declaration.params;
    param_num = 0;
    while (params != NULL) {
	sm_ref param = NULL;
	switch (params->node->node_type) {
	case cod_declaration:
	    param = params->node;
	    break;
	case cod_array_type_decl:
	    param = params->node->node.array_type_decl.element_ref;
	    param->node.declaration.sm_complex_type = params->node;
	    break;
	default:
	    printf("unhandled case in cod_subroutine_declaration\n");
	}
	param->node.declaration.param_num = param_num;
	cod_add_decl_to_parse_context(param->node.declaration.id,
				      params->node, context);
	param_num++;
	params = params->next;
    }
}

extern void
cod_set_return_type(char *typ, cod_parse_context context)
{
    sm_list type_list;
    int cg_type;
    sm_ref complex_type;
    setup_for_string_parse(typ, context->defined_type_count, context->defined_types);
    cod_code_string = typ;
    parsing_type = 1;
    yyerror_count = 0;
    yycontext = context;
    yyparse();
    parsing_type = 0;
    terminate_string_parse();

    if ((yyparse_value == NULL) || (yyerror_count != 0)) {
	return;
    }
    type_list = (sm_list) yyparse_value;

    complex_type = reduce_type_list(context, type_list, &cg_type, context->scope, NULL);
    context->return_type_list = type_list;
    if (complex_type != NULL) {
	cg_type = DILL_P;
    }
    context->return_cg_type = cg_type;
}

static sm_ref
find_complex_type(sm_ref node, scope_ptr scope)
{
    assert(node->node_type == cod_identifier);
    return resolve(node->node.identifier.id, scope);
}

extern cod_parse_context
new_cod_parse_context()
{
    cod_parse_context context = malloc(sizeof(struct parse_struct));
    context->decls = NULL;
    context->defined_type_count = 0;
    context->defined_types = NULL;
    context->error_func = default_error_out;
    context->client_data = NULL;
    context->return_type_list = NULL;
    context->return_cg_type = DILL_I;
    context->scope = push_scope(NULL);
    context->has_exec_context = 0;
    cod_add_standard_elements(context);
    return context;
}

extern void
cod_free_parse_context(cod_parse_context parse_context)
{
    pop_scope(parse_context->scope);
    if (parse_context->defined_types) {
	free(parse_context->defined_types);
    }
    if (parse_context->decls) {
	cod_rfree_list(parse_context->decls, NULL);
    }
    if (parse_context->standard_decls) {
	cod_rfree_list(parse_context->standard_decls, NULL);
    }
    free(parse_context);
}

extern void
cod_assoc_externs(cod_parse_context context, cod_extern_list externs)
{
    context->scope->externs = externs;
}

extern void
cod_add_decl_to_parse_context(const char *name, sm_ref item, cod_parse_context context)
{
    sm_list *last_ptr = &context->decls;
    sm_list list = context->decls;
    while (list != NULL) {
	last_ptr = &list->next;
	list = list->next;
    }
    *last_ptr = malloc(sizeof(*list));
    (*last_ptr)->next = NULL;
    (*last_ptr)->node = item;
    if (item->node_type == cod_struct_type_decl) {
	cod_add_defined_type((char *)name, context);
    }
}

extern void 
cod_remove_defined_types(sm_list decls_list, cod_parse_context context)
{
    sm_list l = decls_list;
    while (l != NULL) {
	if (l->node->node_type == cod_declaration) {
	    int i = 0;
	    while ((i < context->defined_type_count) && 
	           (l->node->node.declaration.id != context->defined_types[i])) {
		i++;
	    }
	    if (i < context->defined_type_count) {
		while (i < (context->defined_type_count-1)) {
		    context->defined_types[i] = context->defined_types[i+1];
		    i++;
		}
		context->defined_type_count--;
	    }
	}
	l = l->next;
    }
}

extern void
cod_add_int_constant_to_parse_context(const char *name, int value, cod_parse_context context)
{
    sm_ref constant;
    char str_value[64];
    sprintf(str_value, "%d", value);
    constant = cod_new_constant();
    constant->node.constant.token = integer_constant;
    constant->node.constant.const_val = strdup(str_value);
    cod_add_decl_to_scope((char*) name, constant, context);
    cod_add_decl_to_parse_context(name, constant, context);
}

extern void
cod_set_closure(char *name, int closure_context, cod_parse_context context)
{
    sm_ref decl;
    decl = resolve(name, context->scope);
    assert(decl->node_type == cod_declaration);
    assert(decl->node.declaration.is_subroutine);
    decl->node.declaration.closure_id = closure_context;
}

static void
space_to_underscore(char *str){
    while(*str != '\0'){
	if(isspace(*str))
	    *str = '_';
	    str++;
    }
}

static void
purify_name(FMStructDescList list){
    int i,j;
    for(i=0; list[i].format_name; i++){
	FMFieldList fl = list[i].field_list;
	space_to_underscore((char*)list[i].format_name);
	for(j=0; fl[j].field_name; j++){
	    space_to_underscore((char*)fl[j].field_name);
	    space_to_underscore((char*)fl[j].field_type);
	}
    }
}

static void
uniqueify_names(FMStructDescList list, char *prefix)
{
    int i = 0;
    int prefix_len = strlen(prefix);
    while (list[i].format_name != NULL) {
	int j = 0;
	FMFieldList fl = list[i].field_list;
	char *new_name =
	    malloc(strlen(list[i].format_name) + prefix_len + 1);
	strcpy(new_name, prefix);
	strcpy(new_name + prefix_len, list[i].format_name);
	free(list[i].format_name);
	list[i].format_name = new_name;
	while (fl[j].field_name != 0) {
	    int field_type_len = strlen(fl[j].field_type);
	    char *bracket = strchr(fl[j].field_type, '[');
	    int k;
	    if (bracket != NULL) {
		field_type_len = (long) bracket - (long) fl[j].field_type;
	    }
	    for (k = 0; k < i; k++) {
		char *new_type;
		if (strncmp
		    (fl[j].field_type, list[k].format_name + prefix_len,
		     field_type_len) != 0) {
		    /* don't match in N chars */
		    continue;
		}
		if ((list[k].format_name + prefix_len)[field_type_len] !=
		    0) {
		    /* list name is longer */
		    continue;
		}
		new_type =
		    malloc(strlen(fl[j].field_type) + prefix_len + 1);
		strcpy(new_type, prefix);
		strcpy(new_type + prefix_len, fl[j].field_type);
		free((void *) fl[j].field_type);
		fl[j].field_type = new_type;
		break;
	    }
	    j++;
	}
	i++;
    }
    purify_name(list);
}

/* Returns the ecode function which will do message format conversion */
extern cod_code
gen_rollback_code(FMStructDescList format1, FMStructDescList format2, char *xform_code)
{
    /* setup ECL generation */
    /* 
     *  NOTE:  We have to make the type names (structure names)
     *  in format1 and format2 to be unique. 
     *  Because of the nature of the problem, they are likely to be 
     *  identical and this may cause namespace collisions in ECL.
     */
    cod_code code;
    cod_parse_context parse_context = new_cod_parse_context();

    int i = 0;
    uniqueify_names(format1, "f0_");
    while (format1[i].format_name != NULL) {
	cod_add_struct_type(format1[i].format_name,
			    format1[i].field_list, parse_context);
	i++;
    }
    cod_add_param("new", format1[i - 1].format_name, 0, parse_context);

    i = 0;
    uniqueify_names(format2, "f1_");
    while (format2[i].format_name != NULL) {
	cod_add_struct_type(format2[i].format_name,
			    format2[i].field_list, parse_context);
	i++;
    }
    cod_add_param("old", format2[i - 1].format_name, 1, parse_context);

    code = cod_code_gen(xform_code, parse_context);
    cod_free_parse_context(parse_context);

    /* 
     * the "code" structure is the only output from this block,
     * all else is free'd.
     */
    return code;
}

