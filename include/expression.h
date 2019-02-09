/**
 * \file expression.h
 * \brief Implantation du TAD expression 
 * \author N. Delestre
 * \version 1.0
 * \date 09/07/2015
 *
 */

/* Partie privee */
#ifndef __EXPRESSION__
#define __EXPRESSION__

#include "valeur.h"
#include "memoire.h"
#include "erreur.h"

/**
 * \type EXP_Type 
 * \brief Permet de savoir si une expression  est un nombre, une variable ou une opération
 */
typedef enum EXP_Type {CONSTANTE, IDENTIFIANT, OPERATION} EXP_Type;

/**
 * \type EXP_CardinaliteOperation 
 * \brief Dans le cas ou une expression  est une opération, EXP_CardinaliteOperation permet de savoir si c'est une opération uniare ou binaire
 */
typedef enum EXP_CardinaliteOperation {UNAIRE,BINAIRE} EXP_CardinaliteOperation;

/**
 * \type EXP_OperateurUnaire 
 * \brief Dans le cas ou une expression  est une opération composée d'un opérateur unaire, EXP_OperateurUnaire parmet de savoir si c'est l'oparteur moins
 */
typedef enum EXP_OperateurUnaire {MOINS, NON} EXP_OperateurUnaire;

/**
 * \type EXP_OperateurBinaire 
 * \brief Dans le cas ou une expression  est une opération composée d'un opérateur binaire, EXP_OperateurBinaire parmet de savoir si c'est l'un des opérateurs arithmétique ou de comparaison
 */
typedef enum EXP_OperateurBinaire {ADDITION, SOUSTRACTION, MULTIPLICATION, DIVISION, EGAL, DIFFERENT, PLUS_PETIT_OU_EGAL, PLUS_PETIT, PLUS_GRAND_OU_EGAL, PLUS_GRAND, ET, OU} EXP_OperateurBinaire; 

/**
   \type EXP_Expression
   \brief Représente une expression arithmétique ou booléenne
 */
typedef struct EXP_Expression* EXP_Expression;

typedef struct EXP_OperationUnaire{
  EXP_OperateurUnaire operateur;
  EXP_Expression operande;
} EXP_OperationUnaire;

typedef struct EXP_OperationBinaire{
  EXP_OperateurBinaire operateur;
  EXP_Expression operandeGauche;
  EXP_Expression operandeDroite;
} EXP_OperationBinaire;

typedef struct EXP_Operation {
  EXP_CardinaliteOperation cardinalite;
  EXP_OperationUnaire operationUnaire;
  EXP_OperationBinaire operationBinaire;
} EXP_Operation;

struct EXP_Expression {
  EXP_Type type;
  VAL_Valeur constante;
  char* identifiant;
  EXP_Operation operation;
};

/* Partie publique*/

/**
 * \fn EXP_Expression EXP_creerAPartirDUneConstante(VAL_Valeur ct)
 * \brief Création d'une expression à partir d'une constante
 * \param ct VAL_Valeur
 * \return EXP_Expression
 */
EXP_Expression EXP_creerAPartirDUneConstante(VAL_Valeur ct);
EXP_Expression EXP_creerAPartirDUnIdentifiantDeVariable(char* id);
EXP_Expression EXP_creerAPartirDUneOperationUnaire(EXP_OperateurUnaire operateur, 
							     EXP_Expression operande);
EXP_Expression EXP_creerAPartirDUneOperationBinaire(EXP_OperateurBinaire operateur, 
							      EXP_Expression operandeG, 
							      EXP_Expression operandeD);
EXP_Expression EXP_dupliquer(EXP_Expression exp); 

int EXP_estUneConstante(EXP_Expression exp);
int EXP_estUnIdentifiant(EXP_Expression exp);
int EXP_estUneOperationUnaire(EXP_Expression exp);
int EXP_estUneOperationBinaire(EXP_Expression exp);

/* Les fonctions suivantes peuvent genenerer des erreurs  */
#define ERRNO_OK 0
#define ERRNO_PAS_UN_CONSTANTE 1
#define ERRNO_PAS_UN_IDENTIFIANT 2
#define ERRNO_PAS_UNE_OPERATION_UNAIRE 3
#define ERRNO_PAS_UNE_OPERATION_BINAIRE 4
VAL_Valeur EXP_obtenirConstante(EXP_Expression exp);
char* EXP_obtenirIdentifiant(EXP_Expression exp);
void EXP_obtenirOperationUnaire(EXP_Expression exp, 
			       EXP_OperateurUnaire* operateur, 
			       EXP_Expression* operande);
void EXP_obtenirOperationBinaire(EXP_Expression exp, 
				EXP_OperateurBinaire* operateur, 
				EXP_Expression* operandeG, 
				EXP_Expression* operandeD);
void EXP_evaluerExpression(EXP_Expression expression,
			   MEM_Memoire memoire,
			   VAL_Valeur *pValeur,
			   ERR_Erreur *pErreur);
char* EXP_enChaine(EXP_Expression exp);
void EXP_detruire(EXP_Expression* exp);
#endif


