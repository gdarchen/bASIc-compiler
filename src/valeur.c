#include "valeur.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

VAL_Valeur VAL_valeurEntiere(long int a) {
  VAL_Valeur v;
  v.type = ENTIER;
  v.valeur.valeurEntiere = a;
  return v;
}
VAL_Valeur VAL_valeurReelle(double x) {
  VAL_Valeur v;
  v.type = REEL;
  v.valeur.valeurReelle = x;
  return v;
}

VAL_Valeur VAL_valeurBooleenne(unsigned short b) {
  VAL_Valeur v;
  v.type = BOOLEEN;
  v.valeur.valeurBooleenne = b;
  return v; 
}

VAL_Type VAL_obtenirType(VAL_Valeur v) {
  return v.type;
}

long int VAL_obtenirValeurEntiere(VAL_Valeur v) {
  assert(VAL_obtenirType(v)==ENTIER);

  return v.valeur.valeurEntiere;
}

double VAL_obtenirValeurReelle(VAL_Valeur v) {
  assert(VAL_obtenirType(v)==REEL);

  return v.valeur.valeurReelle; 
}

unsigned short VAL_obtenirValeurBooleenne(VAL_Valeur v) {
  assert(VAL_obtenirType(v)==BOOLEEN);

  return v.valeur.valeurBooleenne;
}



