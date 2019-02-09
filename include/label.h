/**
 * \file label.h
 * \brief implantation du TAD Label
 * \author N. Delestre
 * \version 1.0
 * \date 2016
 */

#ifndef __LABEL__
#define __LABEL__
#include "listeChainee.h"

typedef struct {
  char* identifiant;
  LC_ListeChainee liste;
} LAB_Label;

LAB_Label * LAB_label(char* id, LC_ListeChainee l);
char * LAB_obtenirIdentifiant(LAB_Label label);
LC_ListeChainee LAB_obtenirListe(LAB_Label label);
void LAB_fixerValeur(LAB_Label *pLabel, LC_ListeChainee);
void LAB_liberer(LAB_Label *pLabel);
void* LAB_copierLabel(void *pLabel);
void LAB_desallocationLabel(void *pLabel);
int LAB_comparaisonLabel(void *pLabel1,void *pLabel2);
#endif
