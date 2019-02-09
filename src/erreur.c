#include "erreur.h"
#include <stdlib.h>
#include <string.h>

ERR_Erreur ERR_pasDerreur() {
  ERR_Erreur resultat;
  resultat.erreur = PAS_D_ERREUR;
  resultat.explication = NULL;
  return resultat;
}

ERR_Erreur ERR_erreur(ERR_Type terreur, char* explication){
  ERR_Erreur resultat;
  resultat.erreur = terreur;
  resultat.explication = (char*)malloc(strlen(explication)+1);
  strcpy(resultat.explication,explication);
  return resultat;
}

int ERR_uneErreurAEteProvoque(ERR_Erreur err) {
  return (err.erreur != PAS_D_ERREUR);
}

char *ERR_explication(ERR_Erreur err) {
  return err.explication;
}

void ERR_liberer(ERR_Erreur *erreur) {
  if (erreur->explication != NULL) {
    free(erreur->explication);
    erreur->erreur = PAS_D_ERREUR;
  }
}
