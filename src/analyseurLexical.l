%{
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "instruction.h"
#include "valeur.h"
#include "expression.h"
#include "constantes.h"
char* dupliquerChaine(char *);

#define YY_NO_INPUT
%}
%option nounput

ENT			[0-9]+
NBRE_ENTIER 		{ENT}
EXP			[eE][+-]{ENT}
VIRG			\.{ENT}
NBRE_REEL		{ENT}|{ENT}{VIRG}|{ENT}{EXP}|{ENT}{VIRG}{EXP}
ECRIRE  		[eE][cC][rR][iI][rR][eE]
LIRE    		[lL][iI][rR][eE]
RIEN    		[rR][iI][eE][nN]
SI			[sS][iI]
ALORS 			[aA][lL][oO][rR][sS]
ALLERA 			[aA][lL][lL][eE][rR][aA]
NON			[nN][oO][nN]
ET			[eE][tT]
OU	 		[oO][uU]
IDENT			[_a-zA-Z][_0-9a-zA-Z]*

%%
[ \t]		;
{NBRE_ENTIER}   {yylval.valeur = VAL_valeurEntiere(atoi(yytext)); return TERMINAL_CONSTANTE;}
{NBRE_REEL}    	{yylval.valeur = VAL_valeurReelle(atof(yytext)); return TERMINAL_CONSTANTE;}
{ECRIRE}        return TERMINAL_ECRIRE;
{LIRE}          return TERMINAL_LIRE;
{RIEN}		return TERMINAL_RIEN;
{SI}		return COND_SI;
{ALORS}         return COND_ALORS;
{ALLERA}	return JUMP_ALLERA;
{NON}		return BOOL_NON;
{ET}		return BOOL_ET;
{OU} 		return BOOL_OU;
{IDENT}		{yylval.id = dupliquerChaine(yytext);return ID;}
[=][=]		return BOOL_EGAL;
[!][=]		return BOOL_DIFFERENT;
[<]		return BOOL_PLUS_PETIT;
[<][=]	 	return BOOL_PLUS_PETIT_OU_EGAL;
[>]		return BOOL_PLUS_GRAND;
[>][=]	 	return BOOL_PLUS_GRAND_OU_EGAL;
[+] 	        return OP_ADD;
[-] 	        return OP_SOUS;
[*] 	        return OP_MUL;
[/] 	        return OP_DIV;
[(] 	        return PAR_G;
[)] 	        return PAR_D;
[=] 	        return TERMINAL_AFFEC;
[\n]            return TERMINAL_FIN;
[:]             return MARQUEUR_LABEL;
%%

char* dupliquerChaine(char *chaine) {
  char* nouvelleChaine = malloc(strlen(chaine)+1);
  strcpy(nouvelleChaine, chaine);
  return nouvelleChaine;
}

int yywrap(void){
  return 1;
}
