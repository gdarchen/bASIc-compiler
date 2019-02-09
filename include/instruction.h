/**
 * \file instruction.h
 * \brief implantation du TAD Instruction
 * \author N. Delestre
 * \version 1.0
 * \date 2016
 */

#ifndef __INSTRUCTION__
#define __INSTRUCTION__
#include "expression.h"
#include "memoire.h"
#include "erreur.h"

typedef enum {AFFECTATION,SIALORS,ALLER_A,LIRE,ECRIRE,RIEN} INSTR_Type;

typedef struct {
  char* identifiant;
  EXP_Expression expression;
} INSTR_Affectation;

typedef struct {
  EXP_Expression expression;
  struct INSTR_Instruction *instruction;
} INSTR_SiAlors;

/**
   \type INSTR_Instruction
   \brief Représente une instruction du langage (affectation, lire, écrire, sialors, aller à et rien)
 */
typedef struct INSTR_Instruction {
  INSTR_Type type;
  union {
    INSTR_Affectation affectation;
    INSTR_SiAlors siAlors;
    char* allerA;
    char* idLire;
    EXP_Expression expEcrire;
  } instruction;
} * INSTR_Instruction;

#include "programme.h"

/**
   \fn INSTR_creerAffectation(char* id, EXP_Expression exp)
   \brief Création d'une instruction qui est une affectation
   \param id char* l'identifiant de la variable
   \param exp EXP_Expression la valeur qui va être affectée
   \return INSTR_Instruction
*/
INSTR_Instruction INSTR_creerAffectation(char* id, EXP_Expression exp);

/**
   \fn INSTR_Instruction INSTR_creerEcrire(EXP_Expression exp)
   \brief Créer une instruction qui est un écrire
   \param exp EXP_Expression l'expression à afficher
   \return INSTR_Instruction
*/
INSTR_Instruction INSTR_creerEcrire(EXP_Expression exp);

/**
   \fn INSTR_Instruction INSTR_creerSiAlors(EXP_Expression exp, INSTR_Instruction instr)
   \brief Création d'une instruction qui est un si alors
   \param exp EXP_Expression la condition
   \param instr INSTR_Instruction l'instruction à exécuter si la condition est VRAI
   \return INSTR_Instruction
*/
INSTR_Instruction INSTR_creerSiAlors(EXP_Expression exp, INSTR_Instruction instr);

/**
   \fn INSTR_Instruction INSTR_creerAllerA(char *idLabel)
   \brief Créer une instruction qui est un aller à
   \param idLabel char*
   \return INSTR_Instruction
*/
INSTR_Instruction INSTR_creerAllerA(char *idLabel);

/**
   \fn INSTR_Instruction INSTR_creerLire(char *id)
   \brief Création d'une instruction qui est un lire
   \param id char*
   \return INSTR_Instruction
*/
INSTR_Instruction INSTR_creerLire(char *id);

/**
   \fn INSTR_Instruction INSTR_creerRien()
   \brief Créer une instruction "vide"
   \param id char*
   \return INSTR_Instruction
*/
INSTR_Instruction INSTR_creerRien();

/**
   \fn void INSTR_executer(INSTR_Instruction instruction, PRG_Programme *pPrg, MEM_Memoire *pMemoire,ERR_Erreur *pErreur)
   \brief Exécution d'une instruction dans le cadre d'un environnement (programme + mémoire)
   \param instruction INSTR_Instruction à exéuter
   \param pPrg PRG_Programme* le programme ou s'exécute l'instruction (son pointeur d'instruction peut changer à l'issu de l'instruction)
   \param pMemoire MEM_Memoire* la mémoire qui peut être modifiée
   \param pErreur ERR_Erreur* l'erreur qui peut survenir
*/
void INSTR_executer(INSTR_Instruction instruction, PRG_Programme *pPrg, MEM_Memoire *pMemoire,ERR_Erreur *pErreur);

/**
 * \fn void* void* INSTR_copierInstruction(void* instr)
 * \brief Fonction permettant de copier une instruction dans une SDD
 * \param v void*
 * \return void*
 */
void* INSTR_copierInstruction(void* instr);

/**
 * \fn void INSTR_desallocationInstruction(void* instr)
 * \brief Fonction de libération d'une instruction stockze dans une SDD
 * \param v void*
 */
void INSTR_desallocationInstruction(void* instr);

/**
 * \fn int INSTR_comparaisonInstruction(void* instr1,void* instr2)
 * \brief Fonction permettant de comparerdeux instructions stockées dans des SDD 
 * \param v1 void*
 * \param v2 void*
 * \return int
 */
int INSTR_comparaisonInstruction(void* instr1,void* instr2);
#endif
