/**
 * \file elementCollection.h
 * \brief Définitions des types de fonctions qui permettent de:
 *  - copier un élément dans une collection
 *  - supprimer un élément d'une collection
 *  - comparer deux éléments
 * \author N. Delestre
 * \version 2.0
 * \date 23/10/2012
 *
 */


#ifndef __ELEMENT_COLLECTION__
#define __ELEMENT_COLLECTION__

typedef void* (*EC_FonctionCopierDansCollection) (void*);
typedef void (*EC_FonctionLibererDeCollection) (void*);
typedef int (*EC_FonctionComparaison) (void*,void*);
#endif
