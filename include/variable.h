
/**
 * \file variable.h
 * \brief implantation du TAD Variable
 * \author N. Delestre
 * \version 1.0
 * \date 2016
 */

#ifndef __VARIABLE__
#define __VARIABLE__
#include "valeur.h"

/**
 * \type VAR_Variable
 * \brief représentation d'une variable (association d'un identifiant et d'une valeur)
 */
typedef struct {
  char* identifiant;
  VAL_Valeur valeur;
} VAR_Variable;

/**
 * \fn VAR_Variable * VAR_variable(char* id, VAL_Valeur v)
 * \brief Création (allocation dynamique) d'une avriable à partir d'un identifiant et d'une valeur
 * \param id char * l'identifiant (une zone mémoire sera allouée)
 * \param v VAL_Valeur la valeur
 * \return VAR_Variable
 */
VAR_Variable * VAR_variable(char* id, VAL_Valeur v);

/**
 * \fn char * VAR_obtenirIdentifiant(VAR_Variable v)
 * \brief Obtention de l'identifiant d'une variable
 * \warning Ce n'est pas une copie de l'identifiant
 * \param v VAR_Variable
 * \return char*
 */
char * VAR_obtenirIdentifiant(VAR_Variable v);

/**
 * \fn VAL_Valeur VAR_obtenirValeur(VAR_Variable v)
 * \brief Obtention de la valeur d'une variable
 * \param v VAR_Variable
 * \return VAL_Valeur
 */
VAL_Valeur VAR_obtenirValeur(VAR_Variable v);

/**
 * \fn void VAR_fixerValeur(VAR_Variable *v, VAL_Valeur va)
 * \brief Modification de la valeur d'une variable
 * \param v VAR_Variable*
 * \param va VAL_Valeur la nouvelle valeur
 */
void VAR_fixerValeur(VAR_Variable *v, VAL_Valeur va);

/**
 * \fn void VAR_liberer(VAR_Variable *v)
 * \brief Libération de l'espace mémoire allouée lors de la création de la variable
 * \param v VAR_Variable*
 */
void VAR_liberer(VAR_Variable *v);

/**
 * \fn void* VAR_copierVariable(void* v)
 * \brief Fonction permettant de copier une variable dans une SDD
 * \param v void*
 * \return void*
 */
void* VAR_copierVariable(void* v);

/**
 * \fn void VAR_desallocationVariable(void* v)
 * \brief Fonction de libération d'une variable stockée dans une SDD
 * \param v void*
 */
void VAR_desallocationVariable(void* v);

/**
 * \fn int VAR_comparaisonVariable(void* v1,void* v2)
 * \brief Fonction permettant de comparer (du point de vue de leurs identifiants) deux variables stockées dans des SDD 
 * \param v1 void*
 * \param v2 void*
 * \return int
 */
int VAR_comparaisonVariable(void* v1,void* v2);
#endif


