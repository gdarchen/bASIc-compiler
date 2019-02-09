/**
 * \file programme.h
 * \brief implantation du TAD Programme
 * \author N. Delestre
 * \version 1.0
 * \date 2016
 */

#ifndef __PROGRAMME__
#define __PROGRAMME__
#include "listeChainee.h"
#include "tableDeLabels.h"
#include "erreur.h"

/**
 * \type PRG_Programme
 * \brief Réprésentation d'un programme comme une suite d'instructions
 */
typedef struct {
  LC_ListeChainee lesInstructions;
  LC_ListeChainee positionInstructionCourante;
  LC_ListeChainee positionDerniereInstruction;
  TDL_TableDeLabels tableDesLabels;
} PRG_Programme;

#include "instruction.h"

/**
 * \fn void PRG_Programme PRG_programme()
 * \brief Créer un programme vide
 */
PRG_Programme PRG_programme();

/**
 * \fn void PRG_ajouterInstruction(PRG_Programme *pPrg, INSTR_Instruction instr)
 * \brief Ajouter une instruction à la fin d'un programme
 * \param pPrg PRG_Programme *
 * \param instr INSTR_Instruction
 */
void PRG_ajouterInstruction(PRG_Programme *pPrg, INSTR_Instruction instr);

/**
 * \fn void PRG_ajouterInstructionLabelise(PRG_Programme *pPrg, INSTR_Instruction instr, char *label)
 * \brief Ajouter une instruction à la fin d'un programme. Cette instruction est labelisée (on pourra y revenir grâce à l'istruction allerà)
 * \param pPrg PRG_Programme *
 * \param instr INSTR_Instruction
 * \param label char*
 */
void PRG_ajouterInstructionLabelise(PRG_Programme *pPrg, INSTR_Instruction instr, char *label);

/**
 * \fn void PRG_allerALInstructionSuivante(PRG_Programme *pPrg)
 * \brief Déplacer le "pointeur" d'instruction sur l'instruction suivante
 * \param pPrg PRG_Programme *
 */
void PRG_allerALInstructionSuivante(PRG_Programme *pPrg);

/**
 * \fn void PRG_allerAUnLabel(PRG_Programme *pPrg, char *idLabel, ERR_Erreur *pErreur)
 * \brief Déplacer le "pointeur" d'instruction sur l'instruction identifiée par un label. Une erreur peut survenir si le label n'existe pas.
 * \param pPrg PRG_Programme *
 * \param idLabel char*
 * \param pErreur ERR_Erreur*
 */
void PRG_allerAUnLabel(PRG_Programme *pPrg, char *idLabel, ERR_Erreur *pErreur);

/**
 * \fn void PRG_executer(PRG_Programme prg)
 * \brief Exécuter un programme, c'est-à-dire parcourir les instructions et les évaluer une à une
 * \param pPrg PRG_Programme
 */
void PRG_executer(PRG_Programme prg);

/**
 * \fn void PRG_liberer(PRG_Programme *pPrg)
 * \brief Libérer toutes les zones mémoires allouées par un programme
 * \param pPrg PRG_Programme *
 */
void PRG_liberer(PRG_Programme *pPrg);

#endif
