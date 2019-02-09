/**
 * \file valeur.h
 * \brief implantation du TAD Valeur
 * \author N. Delestre
 * \version 1.0
 * \date 2016
 */
#ifndef __VALEUR__
#define __VALEUR__


/**
 * \enum VAL_Type
 * \brief type d'une valeur (VAL_Valeur)
 */
typedef enum {ENTIER,REEL,BOOLEEN} VAL_Type;

/**
 * \type VAL_Valeur
 * \brief représentation d'une valeur qui peut être un entier, un réel ou un booléen
 */
typedef struct {
  VAL_Type type;
  union {
    long int valeurEntiere;
    double valeurReelle;
    unsigned short valeurBooleenne;
  } valeur;
} VAL_Valeur;

/**
 * \fn VAL_Valeur VAL_valeurEntiere(long int a)
 * \brief Création d'une valeur à partir d'un long int
 * \param a long int
 * \return VAL_Valeur
 */
VAL_Valeur VAL_valeurEntiere(long int a);
/**
 * \fn VAL_Valeur VAL_valeurReelle(double x)
 * \brief Création d'une valeur à partir d'un double
 * \param x double
 * \return VAL_Valeur
 */
VAL_Valeur VAL_valeurReelle(double x);
/**
 * \fn VAL_Valeur VAL_valeurBooleenne(unsigned short b)
 * \brief Création d'une valeur à partir d'un unsigned short qui représente un booléen
 * \param b unsigned short
 * \return VAL_Valeur
 */
VAL_Valeur VAL_valeurBooleenne(unsigned short b);
/**
 * \fn VAL_Type VAL_obtenirType(VAL_Valeur v)
 * \brief Obtention du type d'une valeur (entier, réelle ou booléen)
 * \param v VAL_Valeur
 * \return VAL_Type
 */
VAL_Type VAL_obtenirType(VAL_Valeur v);
/**
 * \fn long int VAL_obtenirValeurEntiere(VAL_Valeur v)
 * \brief Obtention de l'entier contenu dans une valeur
 * \warning Une assertion vérifie que VAL_obtenirType(v) vaut ENTIER
 * \param v VAL_Valeur
 * \return long int
 */
long int VAL_obtenirValeurEntiere(VAL_Valeur v);
/**
 * \fn double VAL_obtenirValeurReelle(VAL_Valeur v)
 * \brief Obtention du réel contenu dans une valeur
 * \warning Une assertion vérifie que VAL_obtenirType(v) vaut REEL
 * \param v VAL_Valeur
 * \return double
 */
double VAL_obtenirValeurReelle(VAL_Valeur v);
/**
 * \fn unsigned short VAL_obtenirValeurBooleenne(VAL_Valeur v)
 * \brief Obtention du booléen contenu dans une valeur
 * \warning Une assertion vérifie que VAL_obtenirType(v) vaut BOOLEEN
 * \param v VAL_Valeur
 * \return unsigned short
 */
unsigned short VAL_obtenirValeurBooleenne(VAL_Valeur v);

#endif


