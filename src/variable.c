#include "variable.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

VAR_Variable * VAR_variable(char* id, VAL_Valeur v) {
  VAR_Variable *res;
  res = (VAR_Variable*)malloc(sizeof(VAR_Variable));
  res->identifiant = (char*)malloc(strlen(id)+1);
  strcpy(res->identifiant, id);
  res->identifiant[strlen(id)] = '\0';
  res->valeur = v;
  return res;
}

char* VAR_obtenirIdentifiant(VAR_Variable v) {
  return v.identifiant;
}

VAL_Valeur VAR_obtenirValeur(VAR_Variable v) {
  return v.valeur;
}

void VAR_fixerValeur(VAR_Variable *v, VAL_Valeur va) {
  v->valeur = va; 
}

void VAR_liberer(VAR_Variable *v) {
  free(v->identifiant);
  free(v);
  v=NULL;
}

void* VAR_copierVariable(void* v) {
  VAR_Variable *vr = (VAR_Variable*)v;
  VAR_Variable *copie = VAR_variable(VAR_obtenirIdentifiant(*vr),VAR_obtenirValeur(*vr));
  return (void*)copie;
}

void VAR_desallocationVariable(void* v) {
  VAR_liberer((VAR_Variable*)v);
}

int VAR_comparaisonVariable(void* v1,void* v2) {
  return strcmp(VAR_obtenirIdentifiant(*(VAR_Variable*)v1),
		VAR_obtenirIdentifiant(*(VAR_Variable*)v2));
}



