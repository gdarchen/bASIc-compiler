/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_INCLUDE_CONSTANTES_H_INCLUDED
# define YY_YY_INCLUDE_CONSTANTES_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    TERMINAL_CONSTANTE = 259,
    PAR_G = 260,
    PAR_D = 261,
    MARQUEUR_LABEL = 262,
    TERMINAL_AFFEC = 263,
    TERMINAL_ECRIRE = 264,
    TERMINAL_FIN = 265,
    TERMINAL_LIRE = 266,
    TERMINAL_RIEN = 267,
    COND_SI = 268,
    COND_ALORS = 269,
    JUMP_ALLERA = 270,
    BOOL_NON = 271,
    BOOL_ET = 272,
    BOOL_OU = 273,
    BOOL_EGAL = 274,
    BOOL_DIFFERENT = 275,
    BOOL_PLUS_PETIT = 276,
    BOOL_PLUS_PETIT_OU_EGAL = 277,
    BOOL_PLUS_GRAND = 278,
    BOOL_PLUS_GRAND_OU_EGAL = 279,
    OP_ADD = 280,
    OP_SOUS = 281,
    OP_DIV = 282,
    OP_MUL = 283
  };
#endif
/* Tokens.  */
#define ID 258
#define TERMINAL_CONSTANTE 259
#define PAR_G 260
#define PAR_D 261
#define MARQUEUR_LABEL 262
#define TERMINAL_AFFEC 263
#define TERMINAL_ECRIRE 264
#define TERMINAL_FIN 265
#define TERMINAL_LIRE 266
#define TERMINAL_RIEN 267
#define COND_SI 268
#define COND_ALORS 269
#define JUMP_ALLERA 270
#define BOOL_NON 271
#define BOOL_ET 272
#define BOOL_OU 273
#define BOOL_EGAL 274
#define BOOL_DIFFERENT 275
#define BOOL_PLUS_PETIT 276
#define BOOL_PLUS_PETIT_OU_EGAL 277
#define BOOL_PLUS_GRAND 278
#define BOOL_PLUS_GRAND_OU_EGAL 279
#define OP_ADD 280
#define OP_SOUS 281
#define OP_DIV 282
#define OP_MUL 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 16 "src/analyseurSyntaxique.y" /* yacc.c:1909  */
VAL_Valeur valeur; EXP_Expression expression; INSTR_Instruction instruction; char* id;

#line 113 "include/constantes.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (INSTR_Instruction* pInstruction, char* label, int* pErreur);

#endif /* !YY_YY_INCLUDE_CONSTANTES_H_INCLUDED  */
