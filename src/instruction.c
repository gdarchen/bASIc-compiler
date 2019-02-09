#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "instruction.h"
#include "variable.h"

#define LONGUEUR_MAX_LIRE 100

void* INSTR_copierInstruction(void* pInstr);

INSTR_Instruction INSTR_creerAffectation(char *id, EXP_Expression exp) {
  INSTR_Instruction resultat = (INSTR_Instruction)malloc(sizeof(struct INSTR_Instruction));
  resultat->type=AFFECTATION;
  resultat->instruction.affectation.identifiant=id;
  resultat->instruction.affectation.expression=exp;
  return resultat;
}

INSTR_Instruction INSTR_creerEcrire(EXP_Expression exp) {
  INSTR_Instruction resultat = (INSTR_Instruction)malloc(sizeof(struct INSTR_Instruction));
  resultat->type=ECRIRE;
  resultat->instruction.expEcrire=exp;
  return resultat;
}

INSTR_Instruction INSTR_creerLire(char *id) {
  INSTR_Instruction resultat = (INSTR_Instruction)malloc(sizeof(struct INSTR_Instruction));
  resultat->type=LIRE;
  resultat->instruction.idLire=id;
  return resultat;
}

INSTR_Instruction INSTR_creerSiAlors(EXP_Expression exp, INSTR_Instruction instr) {
  INSTR_Instruction resultat = (INSTR_Instruction)malloc(sizeof(struct INSTR_Instruction));
  resultat->type=SIALORS;
  resultat->instruction.siAlors.expression=exp;
  resultat->instruction.siAlors.instruction=instr;
  return resultat;
}

INSTR_Instruction INSTR_creerAllerA(char *idLabel) {
  INSTR_Instruction resultat  = (INSTR_Instruction)malloc(sizeof(struct INSTR_Instruction));
  resultat->type = ALLER_A;
  resultat->instruction.allerA = (char*)malloc(strlen(idLabel)+1);
  strcpy(resultat->instruction.allerA,idLabel);
  return resultat;
}

INSTR_Instruction INSTR_creerRien() {
  INSTR_Instruction resultat  = (INSTR_Instruction)malloc(sizeof(struct INSTR_Instruction));
  resultat->type = RIEN;
  return resultat;
}

void INSTR_executerAffectation(INSTR_Affectation affectation, PRG_Programme *pPrg, MEM_Memoire *pMemoire,ERR_Erreur *pErreur) {
  VAR_Variable *variable;
  VAL_Valeur valeur;
  variable=MEM_obtenirVariable(*pMemoire,affectation.identifiant);
  EXP_evaluerExpression(affectation.expression,*pMemoire,&valeur,pErreur);
  if (!ERR_uneErreurAEteProvoque(*pErreur)) {
    if (variable == NULL) {
      variable=VAR_variable(affectation.identifiant,valeur);
      MEM_ajouterVariable(pMemoire,variable);
      VAR_liberer(variable);
    } else {
      VAR_fixerValeur(variable,valeur);
    }
    PRG_allerALInstructionSuivante(pPrg);
  }
}

void INSTR_executerEcrire(EXP_Expression exp, PRG_Programme *pPrg, MEM_Memoire *pMemoire,ERR_Erreur *pErreur) {
  VAL_Valeur valeur;
  EXP_evaluerExpression(exp,*pMemoire,&valeur,pErreur);
  if (!ERR_uneErreurAEteProvoque(*pErreur)) {
    switch (VAL_obtenirType(valeur)) {
      case ENTIER :
	printf("%ld\n",VAL_obtenirValeurEntiere(valeur));
	break;
      case REEL :
	printf("%f\n",VAL_obtenirValeurReelle(valeur));
	break;
      case BOOLEEN :
	if (VAL_obtenirValeurBooleenne(valeur))
	  printf("VRAI\n");
	else
	  printf("FAUX\n");
	break;
    }
    PRG_allerALInstructionSuivante(pPrg);
  }
}

void INSTR_executerLire(char *id, PRG_Programme *pPrg, MEM_Memoire *pMemoire,ERR_Erreur *pErreur) {
  char temp[LONGUEUR_MAX_LIRE];
  long int valEntiere;
  double valReel;
  char *positionErreur;
  VAR_Variable *variable = NULL;
  VAL_Valeur valeur;
  scanf("%s",temp);
  valEntiere = strtol(temp,&positionErreur,10);
  if (strcmp(positionErreur,"")==0) {
    valeur = VAL_valeurEntiere(valEntiere);
    variable = VAR_variable(id,valeur);
  } else {
    valReel = strtod(temp,&positionErreur);
    if (strcmp(positionErreur,"")==0) {
      valeur = VAL_valeurEntiere(valReel);
      variable = VAR_variable(id,valeur);
    }
  }
  if (variable != NULL) {
    MEM_ajouterVariable(pMemoire,variable);  
    PRG_allerALInstructionSuivante(pPrg);
  } else {
    *pErreur = ERR_erreur(TYPE_INCOMPATIBLE, "type de donnee inconnu");
  }
}

void INSTR_executerSiAlors(EXP_Expression exp, PRG_Programme *pPrg, INSTR_Instruction instr, MEM_Memoire *pMemoire,ERR_Erreur *pErreur) {
  VAL_Valeur valeur;
  EXP_evaluerExpression(exp,*pMemoire,&valeur,pErreur);
  if (!ERR_uneErreurAEteProvoque(*pErreur)) {
    switch (VAL_obtenirType(valeur)) {
      case BOOLEEN :
	if (VAL_obtenirValeurBooleenne(valeur))
	  INSTR_executer(instr,pPrg,pMemoire,pErreur);
	else
	  PRG_allerALInstructionSuivante(pPrg);
	break;
    default :
      *pErreur = ERR_erreur(TYPE_INCOMPATIBLE, "l'expression de la condition du si doit etre un booleen");
    }
  }
}

void INSTR_executer(INSTR_Instruction inst, PRG_Programme *pPrg, MEM_Memoire *pMemoire,ERR_Erreur *pErreur) {
  switch (inst->type) {
  case AFFECTATION :
    INSTR_executerAffectation(inst->instruction.affectation,pPrg,pMemoire,pErreur);
    break;
  case ECRIRE :
    INSTR_executerEcrire(inst->instruction.expEcrire,pPrg,pMemoire,pErreur);  
    break;
  case SIALORS :
    INSTR_executerSiAlors(inst->instruction.siAlors.expression,
			 pPrg,
			 inst->instruction.siAlors.instruction,
			 pMemoire,
			 pErreur);
    break;
  case ALLER_A :
    PRG_allerAUnLabel(pPrg, inst->instruction.allerA, pErreur);    
    break;
  case LIRE :
    INSTR_executerLire(inst->instruction.idLire,pPrg,pMemoire,pErreur);
    break;
  case RIEN :
    PRG_allerALInstructionSuivante(pPrg);
  default:
    break;
  }
}
/*
void* INSTR_copierInstruction(void* instr) {
  INSTR_Instruction instruction = (INSTR_Instruction)instr;
  INSTR_Instruction copie = (INSTR_Instruction)malloc(sizeof(struct INSTR_Instruction));
  memcpy(copie,instruction,sizeof(struct INSTR_Instruction));
  switch (instruction->type) {
  case AFFECTATION :
    copie->instruction.affectation.identifiant = strdup(instruction->instruction.affectation.identifiant);
    copie->instruction.affectation.expression = EXP_dupliquer(instruction->instruction.affectation.expression);
    break;
  case SIALORS :
    copie->instruction.siAlors.expression = EXP_dupliquer(instruction->instruction.siAlors.expression);
    copie->instruction.siAlors.instruction = (INSTR_Instruction)INSTR_copierInstruction((void*)instruction->instruction.siAlors.instruction);
    break;
  case ALLER_A :
    copie->instruction.allerA = strdup(instruction->instruction.allerA);
    break;
  case LIRE :
    copie->instruction.idLire = strdup(instruction->instruction.idLire);
    break;
  case ECRIRE :
    copie->instruction.expEcrire = EXP_dupliquer(instruction->instruction.expEcrire);
    break;
  default:
    break;
  }
  return (void*)copie;
}
*/
void* INSTR_copierInstruction(void* instr) {
  INSTR_Instruction instruction = (INSTR_Instruction)instr;
  INSTR_Instruction copie;
  switch (instruction->type) {
  case AFFECTATION :
    copie = INSTR_creerAffectation(strdup(instruction->instruction.affectation.identifiant),
				   EXP_dupliquer(instruction->instruction.affectation.expression));
    break;
  case SIALORS :
    copie = INSTR_creerSiAlors(EXP_dupliquer(instruction->instruction.siAlors.expression),
			       (INSTR_Instruction)INSTR_copierInstruction((void*)instruction->instruction.siAlors.instruction));
    break;
  case ALLER_A :
    copie = INSTR_creerAllerA(strdup(instruction->instruction.allerA));
    break;
  case LIRE :
    copie = INSTR_creerLire(strdup(instruction->instruction.idLire));
    break;
  case ECRIRE :
    copie = INSTR_creerEcrire(EXP_dupliquer(instruction->instruction.expEcrire));
    break;
  default:
    break;
  }
  return (void*)copie;
}



void INSTR_desallocationInstruction(void* instr) {
  INSTR_Instruction instruction = (INSTR_Instruction)instr;
  switch (instruction->type) {
  case AFFECTATION :
    free(instruction->instruction.affectation.identifiant);
    EXP_detruire(&(instruction->instruction.affectation.expression));
    break;
  case SIALORS :
    EXP_detruire(&(instruction->instruction.siAlors.expression));
    INSTR_desallocationInstruction(instruction->instruction.siAlors.instruction);
    break;
  case ALLER_A :
    free(instruction->instruction.allerA);
    break;
  case LIRE :
    free(instruction->instruction.idLire);
    break;
  case ECRIRE :
    EXP_detruire(&(instruction->instruction.expEcrire));
    break;
  default:
    break;
  }
  free(instr);
}

int INSTR_comparaisonInstruction(void* pInstr1,void* pInstr2) {
  return 0;
}
  

