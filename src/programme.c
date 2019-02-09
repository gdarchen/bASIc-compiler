#include <stdlib.h>
#include <stdio.h>
#include "programme.h"

PRG_Programme PRG_programme() {
  PRG_Programme resultat;
  resultat.lesInstructions  = LC_listeChainee();
  resultat.positionInstructionCourante = NULL;
  resultat.positionDerniereInstruction = resultat.lesInstructions;
  resultat.tableDesLabels = TDL_tableDeLabels();
  return resultat;
}

void PRG_ajouterInstructionALaFin(LC_ListeChainee *pL, INSTR_Instruction instr, LC_ListeChainee *pPositionDerniereInstruction) {
  LC_ListeChainee tmp;
  if (LC_estVide(*pL)) {
    LC_ajouter(pL,(void*)instr,INSTR_copierInstruction);
    *pPositionDerniereInstruction = *pL;
  } else {
    tmp = LC_listeChainee();
    LC_ajouter(&tmp,(void*)instr,INSTR_copierInstruction);
    LC_fixerListeSuivante(pPositionDerniereInstruction, tmp);
    *pPositionDerniereInstruction = tmp;
  }
}

void PRG_ajouterInstruction(PRG_Programme *pPrg, INSTR_Instruction instr) {
  PRG_ajouterInstructionALaFin(&(pPrg->lesInstructions), instr, &(pPrg->positionDerniereInstruction));
}

void PRG_ajouterInstructionLabelise(PRG_Programme *pPrg, INSTR_Instruction instr, char *idLabel) {
  LAB_Label* pLabel;
  PRG_ajouterInstruction(pPrg, instr);
  pLabel = LAB_label(idLabel,pPrg->positionDerniereInstruction);
  TDL_ajouterLabel(&(pPrg->tableDesLabels),pLabel);
  LAB_liberer(pLabel);
}

void PRG_allerALInstructionSuivante(PRG_Programme *pPrg) {
  pPrg->positionInstructionCourante = LC_obtenirListeSuivante((LC_ListeChainee)pPrg->positionInstructionCourante);
}

void PRG_allerAUnLabel(PRG_Programme *pPrg, char *idLabel, ERR_Erreur *pErreur) {
  LAB_Label *label = TDL_obtenirLabel(pPrg->tableDesLabels, idLabel);
  if (label != NULL)
    pPrg->positionInstructionCourante = LAB_obtenirListe(*label);
  else
    *pErreur = ERR_erreur(LABEL_INCONNU, "Label inconnu");
}


void PRG_executerInstructionCourante(PRG_Programme *pPrg, MEM_Memoire *pM, ERR_Erreur *pE) {
  INSTR_Instruction instr;
  instr = (INSTR_Instruction)LC_obtenirElement(pPrg->positionInstructionCourante);
  INSTR_executer(instr,pPrg,pM,pE);
  /*MEM_afficher(*pM);*/
}

void PRG_executer(PRG_Programme prg) {
  ERR_Erreur e=ERR_pasDerreur();
  MEM_Memoire m = MEM_memoire();
  prg.positionInstructionCourante = prg.lesInstructions;
  while (!LC_estVide((LC_ListeChainee)prg.positionInstructionCourante) && !ERR_uneErreurAEteProvoque(e)) {
    PRG_executerInstructionCourante(&prg, &m, &e);
    if (ERR_uneErreurAEteProvoque(e))
      printf("%s\n",ERR_explication(e));
  }
  MEM_liberer(&m);
  ERR_liberer(&e);
}

void PRG_liberer(PRG_Programme *pPrg) {
  LC_supprimer((LC_ListeChainee*)pPrg,INSTR_desallocationInstruction);
}
