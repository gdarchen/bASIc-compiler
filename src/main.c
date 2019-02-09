#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "programme.h"
#include "constantes.h"
#include "regex.h"
 
extern struct yy_buffer_state * yy_scan_string(char*);

void normaliserLigneDeCode(char *ch) {
  unsigned int longueurLigne;
  longueurLigne = strlen(ch);
  if (ch[longueurLigne-1] != '\n') {
    ch[longueurLigne] = '\n';
    ch[longueurLigne+1] = '\0';
  }  
}

int estUneLigneDeCodeVide(char *ch) {
  const char* exp = "^[[:space:]]*$";
  regex_t expressionRationnel;
  int erreur;
  int match;
  erreur = regcomp(&expressionRationnel, exp, REG_NOSUB | REG_EXTENDED);
  if (!erreur) {
    match = regexec(&expressionRationnel, ch, 0, NULL, 0);
    regfree(&expressionRationnel);
    return !match;
  } else {
    return 1;
  }
}

PRG_Programme lireProgramme(FILE *fichier) {
  PRG_Programme prg;
  INSTR_Instruction instr;
  char label[100];
  int erreurSyntaxe = 0;
  char ligne[100];
  prg = PRG_programme();
  while (!feof(fichier) && !erreurSyntaxe) {
    strcpy(ligne,"");
    fgets(ligne,100,fichier);
    if (!estUneLigneDeCodeVide(ligne)) {
      normaliserLigneDeCode(ligne);
      yy_scan_string(ligne);
      yyparse(&instr,label,&erreurSyntaxe);
      if (strcmp(label,"")==0)
	PRG_ajouterInstruction(&prg,instr);
      else
	PRG_ajouterInstructionLabelise(&prg,instr,label);
      INSTR_desallocationInstruction(instr);
    }
  }
  if (erreurSyntaxe) {
    printf("Erreur de syntaxe\n%s\n",ligne);
    exit(EXIT_FAILURE);
  }
  return prg;
}

int main(int argv, char **argc){
  FILE *fichier;
  PRG_Programme prg;
  fichier = fopen(argc[1],"r");
  if (fichier != NULL) {
    prg=lireProgramme(fichier);
    PRG_executer(prg);
    fclose(fichier);
    return EXIT_SUCCESS;  
  } else
    return EXIT_FAILURE;
}
