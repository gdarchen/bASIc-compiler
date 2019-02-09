#include "label.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

LAB_Label * LAB_label(char* id, LC_ListeChainee l) {
  LAB_Label *res;
  res = (LAB_Label*)malloc(sizeof(LAB_Label));
  res->identifiant = (char*)malloc(strlen(id)+1);
  strcpy(res->identifiant, id);
  res->identifiant[strlen(id)] = '\0';
  res->liste = l;
  return res;
}

char* LAB_obtenirIdentifiant(LAB_Label l) {
  return l.identifiant;
}

LC_ListeChainee LAB_obtenirListe(LAB_Label l) {
  return l.liste;
}

void LAB_fixerValeur(LAB_Label *pLabel, LC_ListeChainee l) {
  pLabel->liste = l; 
}

void LAB_liberer(LAB_Label *pLabel) {
  free(pLabel->identifiant);
  free(pLabel);
}

void* LAB_copierLabel(void* pL) {
  LAB_Label *pLr = (LAB_Label*)pL;
  LAB_Label *copie = LAB_label(LAB_obtenirIdentifiant(*pLr),LAB_obtenirListe(*pLr));
  return (void*)copie;
}

void LAB_desallocationLabel(void *pLabel) {
  LAB_liberer((LAB_Label*) pLabel);
}

int LAB_comparaisonLabel(void *pLabel1,void *pLabel2) {
  return strcmp(LAB_obtenirIdentifiant(*(LAB_Label*)pLabel1),
		LAB_obtenirIdentifiant(*(LAB_Label*)pLabel2));
}



