
/**
 * \file tableDeLabels.h
 * \brief implantation du TAD Table de labels
 * \author N. Delestre
 * \version 1.0
 * \date 2016
 */
#ifndef __TABLE_DE_LABELS__
#define __TABLE_DE_LABELS__
#include "label.h"
#include "listeChainee.h"

/**
 * \type TDL_TableDeLabels
 * \brief Représentation d'une liste de labels
 */
typedef LC_ListeChainee TDL_TableDeLabels;

/**
 * \fn TDL_TableDeLabels TDL_tableDeLabels()
 * \brief Créer d'une table de labels vide
 */
TDL_TableDeLabels TDL_tableDeLabels();

/**
 * \fn void TDL_ajouterLabel(TDL_TableDeLabels *pt, LAB_Label *pl)
 * \brief Ajouter d'un label (le label est dupliqué)
 * \param pt TDL_TableDeLabels *
 * \param pl LAB_Label *
 */
void TDL_ajouterLabel(TDL_TableDeLabels *pt, LAB_Label *pl);

/**
 * \fn LAB_Label* TDL_obtenirLabel(TDL_TableDeLabels t, char* identifiant)
 * \brief Obtenir un label à partir de son identifiant
 * \param t TDL_TableDeLabels 
 * \param identifiant char*
 * \return LAB_Label*
 */
LAB_Label* TDL_obtenirLabel(TDL_TableDeLabels t, char* identifiant);

/**
 * \fn TDL_liberer(TDL_TableDeLabels *pt)
 * \brief Libérer tous les espaces mémoires alloués par une table de labels
 * \param pt TDL_TableDeLabels *
 */
void TDL_liberer(TDL_TableDeLabels *pt);

#endif
