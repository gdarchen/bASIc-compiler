#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "memoire.h"
#include "elementCollection.h"
#include "valeur.h"
#include "variable.h"

MEM_Memoire MEM_memoire() {
  return (MEM_Memoire)LC_listeChainee();
}

void MEM_ajouterVariable(MEM_Memoire *m, VAR_Variable *v) {
  LC_ajouter((LC_ListeChainee*)m, (void*)v, VAR_copierVariable);
}

VAR_Variable * MEM_obtenirVariable(MEM_Memoire m, char* identifiant) {
  LC_ListeChainee temp = (LC_ListeChainee)m;
  unsigned int trouve = 0;
  VAR_Variable *v;
  while (!trouve && ! LC_estVide(temp)) {
    v = (VAR_Variable*)LC_obtenirElement(temp);
    if (strcmp(identifiant,VAR_obtenirIdentifiant(*v)) == 0)
      trouve = 1;
    else
      temp = LC_obtenirListeSuivante(temp);
  }
  if (trouve)
    return v;
  else
    return NULL;
}


void MEM_afficher(MEM_Memoire m){
  LC_ListeChainee temp = (LC_ListeChainee)m;
  VAR_Variable *v;
  VAL_Valeur va;
  while (!LC_estVide(temp)) {
    v = (VAR_Variable*)LC_obtenirElement(temp);
    printf("%s ",VAR_obtenirIdentifiant(*v));
    va = VAR_obtenirValeur(*v);
    switch (VAL_obtenirType(va)) {
    case ENTIER : printf("%ld ",VAL_obtenirValeurEntiere(va));break;
    case REEL :  printf("%f ",VAL_obtenirValeurReelle(va));break;
    case BOOLEEN : printf("%d ",VAL_obtenirValeurBooleenne(va));break;
    }
    temp = LC_obtenirListeSuivante(temp);
  }
  printf("\n");
}

void MEM_liberer(MEM_Memoire *m) {
  LC_supprimer((LC_ListeChainee*)m, VAR_desallocationVariable);
}
