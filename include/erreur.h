/**
 * \file erreur.h
 * \brief Implantation de la gestion des erreurs
 * \author N. Delestre
 * \version 1.0
 * \date 09/07/2015
 *
 */

/* Partie privee */
#ifndef __ERREUR__
#define __ERREUR__

typedef enum {PAS_D_ERREUR, DIVISION_PAR_ZERO, TYPE_INCOMPATIBLE, VARIABLE_NON_INITIATLISEE, LABEL_INCONNU} ERR_Type;

typedef struct {
  ERR_Type erreur;
  char* explication;
} ERR_Erreur;

ERR_Erreur ERR_pasDerreur();
ERR_Erreur ERR_erreur(ERR_Type terreur, char* explication);
int ERR_uneErreurAEteProvoque(ERR_Erreur err);
char *ERR_explication(ERR_Erreur err);
void ERR_liberer(ERR_Erreur *erreur);
#endif
