
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 159 "./cod.y"

    lx_info info;
    sm_ref reference;
    sm_list list;
    char *string;



/* Line 1676 of yacc.c  */
#line 189 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


