#include <stdlib.h>
#include <string.h>
#include "tableDeLabels.h"
#include "elementCollection.h"

TDL_TableDeLabels TDL_tableDeLabels() {
  return (TDL_TableDeLabels)LC_listeChainee();
}

void TDL_ajouterLabel(TDL_TableDeLabels *pt, LAB_Label *pl) {
  LC_ajouter((LC_ListeChainee*)pt, (void*)pl, LAB_copierLabel);
}


LAB_Label* TDL_obtenirLabel(TDL_TableDeLabels t, char* identifiant) {
  LC_ListeChainee temp = (LC_ListeChainee)t;
  unsigned int trouve = 0;
  LAB_Label *pl;
  while (!trouve && ! LC_estVide(temp)) {
    pl = (LAB_Label*)LC_obtenirElement(temp);
    if (strcmp(identifiant,LAB_obtenirIdentifiant(*pl)) == 0)
      trouve = 1;
    else
      temp = LC_obtenirListeSuivante(temp);
  }
  if (trouve)
    return pl;
  else
    return NULL;
}

void TDL_liberer(TDL_TableDeLabels *pt) {
  LC_supprimer((LC_ListeChainee*)pt, LAB_desallocationLabel);
}
