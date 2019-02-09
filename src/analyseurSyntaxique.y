%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction.h"
#include "memoire.h"
#include "variable.h"
#include "expression.h"
#include "erreur.h"
#include "constantes.h"

extern int yylex (void);
int yyerror(INSTR_Instruction*, char *label, int*, char *msg);
%}

%union {VAL_Valeur valeur; EXP_Expression expression; INSTR_Instruction instruction; char* id;}

//Definition des lexemes
%token	<id>		ID
%token	<valeur>	TERMINAL_CONSTANTE
%token			PAR_G PAR_D MARQUEUR_LABEL
%token			TERMINAL_AFFEC TERMINAL_ECRIRE TERMINAL_FIN TERMINAL_LIRE TERMINAL_RIEN  
%token 			COND_SI COND_ALORS
%token 			JUMP_ALLERA
%token 			BOOL_NON BOOL_ET BOOL_OU BOOL_EGAL BOOL_DIFFERENT BOOL_PLUS_PETIT BOOL_PLUS_PETIT_OU_EGAL BOOL_PLUS_GRAND BOOL_PLUS_GRAND_OU_EGAL
%token			OP_ADD OP_SOUS OP_DIV OP_MUL
// Definition l'ordre des priorites ainsi que l'associativite
%left BOOL_EGAL BOOL_DIFFERENT BOOL_PLUS_PETIT BOOL_PLUS_PETIT_OU_EGAL BOOL_PLUS_GRAND BOOL_PLUS_GRAND_OU_EGAL
%left BOOL_ET BOOL_OU
%left BOOL_NON
%left OP_ADD OP_SOUS
%left OP_MUL OP_DIV
// Designation du champ de YYSTYPE utilise pour les non terminaux
%type	<instruction>	instr
%type	<expression>	expr
// les parametres de yyparse
%parse-param {INSTR_Instruction* pInstruction}
%parse-param {char* label}
%parse-param {int* pErreur}

%%
ligne:		instr TERMINAL_FIN 			{*pInstruction = $1; label[0]='\0';}
	|	ID MARQUEUR_LABEL instr TERMINAL_FIN	{*pInstruction = $3; strcpy(label,$1);}
		;

instr: 		ID TERMINAL_AFFEC expr 		{$$ = INSTR_creerAffectation($1,$3);}
        | 	TERMINAL_ECRIRE expr 		{$$ = INSTR_creerEcrire($2);}
	|	TERMINAL_LIRE ID 		{$$ = INSTR_creerLire($2);}
	|	TERMINAL_RIEN 			{$$ = INSTR_creerRien();}
	|	JUMP_ALLERA ID 			{$$ = INSTR_creerAllerA($2);}
	|	COND_SI expr COND_ALORS instr 	{$$ = INSTR_creerSiAlors($2,$4);}
		;

expr:		ID	      		  		{$$ = EXP_creerAPartirDUnIdentifiantDeVariable($1);}
	|	TERMINAL_CONSTANTE			{$$ = EXP_creerAPartirDUneConstante($1);}
        |	PAR_G expr PAR_D			{$$ = $2;}
        |	OP_SOUS expr	        		{$$ = EXP_creerAPartirDUneOperationUnaire(MOINS,$2);}
        |	expr OP_ADD expr			{$$ = EXP_creerAPartirDUneOperationBinaire(ADDITION,$1,$3);}
	|	expr OP_SOUS expr       		{$$ = EXP_creerAPartirDUneOperationBinaire(SOUSTRACTION,$1,$3);}
	|	expr OP_MUL expr			{$$ = EXP_creerAPartirDUneOperationBinaire(MULTIPLICATION,$1,$3);}
	|	expr OP_DIV expr			{$$ = EXP_creerAPartirDUneOperationBinaire(DIVISION,$1,$3);}
	|	BOOL_NON expr				{$$ = EXP_creerAPartirDUneOperationUnaire(NON,$2);}
	|	expr BOOL_ET expr 			{$$ = EXP_creerAPartirDUneOperationBinaire(ET,$1,$3);}
	| 	expr BOOL_OU expr			{$$ = EXP_creerAPartirDUneOperationBinaire(OU,$1,$3);}
	| 	expr BOOL_EGAL expr 			{$$ = EXP_creerAPartirDUneOperationBinaire(EGAL,$1,$3);}
	|	expr BOOL_DIFFERENT expr		{$$ = EXP_creerAPartirDUneOperationBinaire(DIFFERENT,$1,$3);}
	|	expr BOOL_PLUS_PETIT expr		{$$ = EXP_creerAPartirDUneOperationBinaire(PLUS_PETIT,$1,$3);}
	|	expr BOOL_PLUS_PETIT_OU_EGAL expr	{$$ = EXP_creerAPartirDUneOperationBinaire(PLUS_PETIT_OU_EGAL,$1,$3);}
	|	expr BOOL_PLUS_GRAND expr		{$$ = EXP_creerAPartirDUneOperationBinaire(PLUS_GRAND,$1,$3);}
	|	expr BOOL_PLUS_GRAND_OU_EGAL expr	{$$ = EXP_creerAPartirDUneOperationBinaire(PLUS_GRAND_OU_EGAL,$1,$3);}	
		;
%%

extern char * yytext;

int yyerror(INSTR_Instruction* pInstruction, char *label, int* pErreur, char *msg) {
  *pErreur = 1;
  return 1;
}
