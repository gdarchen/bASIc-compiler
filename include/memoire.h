/**
 * \file memoire.h
 * \brief implantation du TAD Mémoire
 * \author N. Delestre
 * \version 1.0
 * \date 2016
 */

#ifndef __MEMOIRE__
#define __MEMOIRE__
#include "variable.h"
#include "listeChainee.h"

/**
   \type MEM_Memoire
   \brief Une mémoire est un ensemble de variable
 */
typedef LC_ListeChainee MEM_Memoire;

/**
   \fn MEM_Memoire MEM_memoire()
   \brief Création d'une mémoire vide
   \return MEM_Memoire
 */
MEM_Memoire MEM_memoire();

/**
   \fn void MEM_ajouterVariable(MEM_Memoire *m, VAR_Variable *v)
   \brief Ajout d'une variable
   \param m MEM_Memoire*
   \param v VAR_Variable*
 */
void MEM_ajouterVariable(MEM_Memoire *m, VAR_Variable *v);

/**
   \fn MEM_obtenirVariable(MEM_Memoire m, char* identifiant)
   \brief Obtention d'une variable à partir de son identifiant
   \param m MEM_Memoire
   \param identifiant char*
   \return v VAR_Variable*
 */
VAR_Variable * MEM_obtenirVariable(MEM_Memoire m, char* identifiant);
void MEM_afficher(MEM_Memoire m);

/**
   \fn void MEM_liberer(MEM_Memoire *m)
   \brief Liberation de la mémoire allouée par une mémoire
   \param m MEM_Memoire*
 */
void MEM_liberer(MEM_Memoire *m);

#endif
