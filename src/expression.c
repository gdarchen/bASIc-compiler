#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include"expression.h"

EXP_Expression EXP_creer() {
  return (EXP_Expression)malloc(sizeof(struct EXP_Expression));
}

EXP_Expression EXP_creerAPartirDUneConstante(VAL_Valeur ct) {
  EXP_Expression resultat=EXP_creer();
  resultat->type=CONSTANTE;
  resultat->constante=ct;
  return resultat;
}

EXP_Expression EXP_creerAPartirDUnIdentifiantDeVariable(char* id) {
  EXP_Expression resultat=EXP_creer();
  resultat->type=IDENTIFIANT;
  resultat->identifiant=malloc(strlen(id)+1);
  resultat->identifiant[0]='\0';
  strcpy(resultat->identifiant,id);
  return resultat;
}

EXP_Expression EXP_creerAPartirDUneOperationUnaire(EXP_OperateurUnaire operateur, 
						   EXP_Expression operande) {
  EXP_Expression resultat=EXP_creer();
  resultat->type=OPERATION;
  resultat->operation.cardinalite=UNAIRE;
  resultat->operation.operationUnaire.operateur=operateur;
  resultat->operation.operationUnaire.operande=operande;
  return resultat;
}

EXP_Expression EXP_creerAPartirDUneOperationBinaire(EXP_OperateurBinaire operateur, 
						    EXP_Expression operandeG, 
						    EXP_Expression operandeD) {
  EXP_Expression resultat=EXP_creer();
  resultat->type=OPERATION;
  resultat->operation.cardinalite=BINAIRE;
  resultat->operation.operationBinaire.operateur=operateur;
  resultat->operation.operationBinaire.operandeGauche=operandeG;
  resultat->operation.operationBinaire.operandeDroite=operandeD;
  return resultat;
}

EXP_Expression EXP_dupliquerIdentifiant(EXP_Expression exp) {
    char* id;
    char* newid;
    id=EXP_obtenirIdentifiant(exp);
    newid=(char*)malloc(1+strlen(id));
    strcpy(newid,id);
    return EXP_creerAPartirDUnIdentifiantDeVariable(newid);
}

EXP_Expression EXP_dupliquerOperationUnaire(EXP_Expression exp) {
  EXP_OperateurUnaire operateur;
  EXP_Expression operande;
  EXP_obtenirOperationUnaire(exp,&operateur,&operande);
  return EXP_creerAPartirDUneOperationUnaire(operateur,EXP_dupliquer(operande));
}

EXP_Expression EXP_dupliquerOperationBinaire(EXP_Expression exp) {
  EXP_OperateurBinaire operateur;
  EXP_Expression operandeG;
  EXP_Expression operandeD;
  EXP_obtenirOperationBinaire(exp,&operateur,&operandeG,&operandeD);
  return EXP_creerAPartirDUneOperationBinaire(operateur,EXP_dupliquer(operandeG),EXP_dupliquer(operandeD));
}

EXP_Expression EXP_dupliquer(EXP_Expression exp) {
  if (EXP_estUneConstante(exp))
    return EXP_creerAPartirDUneConstante(EXP_obtenirConstante(exp));
  else
    if (EXP_estUnIdentifiant(exp)) 
      return EXP_dupliquerIdentifiant(exp);
    else 
      if (EXP_estUneOperationUnaire(exp)) 
	return EXP_dupliquerOperationUnaire(exp);
      else
	return EXP_dupliquerOperationBinaire(exp);	
}

int EXP_estUneConstante(EXP_Expression exp) {
  return exp->type==CONSTANTE;
}
int EXP_estUnIdentifiant(EXP_Expression exp) {
  return exp->type==IDENTIFIANT;
}

int EXP_estUneOperationUnaire(EXP_Expression exp) {
  return (exp->type==OPERATION) && (exp->operation.cardinalite==UNAIRE);
}

int EXP_estUneOperationBinaire(EXP_Expression exp) {
  return (exp->type==OPERATION) && (exp->operation.cardinalite==BINAIRE);
}

/* Les fonctions suivantes peuvent genenerer des erreurs (voir errno) */
VAL_Valeur EXP_obtenirConstante(EXP_Expression exp) {
  VAL_Valeur resultat = VAL_valeurEntiere(0);
  errno=ERRNO_OK;
  if (!EXP_estUneConstante(exp)) {
    errno=ERRNO_PAS_UN_CONSTANTE;
  } else {
    resultat=exp->constante;
  }
  return resultat;
}

char* EXP_obtenirIdentifiant(EXP_Expression exp) {
  char* resultat;
  errno=ERRNO_OK;
  if (!EXP_estUnIdentifiant(exp)) {
    errno=ERRNO_PAS_UN_IDENTIFIANT;
  } else {
    resultat=exp->identifiant;
  }
  return resultat;
}

void EXP_obtenirOperationUnaire(EXP_Expression exp, 
				EXP_OperateurUnaire* operateur, 
				EXP_Expression* operande) {
  errno=ERRNO_OK;
  if (!EXP_estUneOperationUnaire(exp)) {
    errno=ERRNO_PAS_UNE_OPERATION_UNAIRE;
  } else {
    *operateur=exp->operation.operationUnaire.operateur;
    *operande=exp->operation.operationUnaire.operande;
  }
}

void EXP_obtenirOperationBinaire(EXP_Expression exp, 
				 EXP_OperateurBinaire* operateur, 
				 EXP_Expression* operandeG, 
				 EXP_Expression* operandeD) {
  errno=ERRNO_OK;
  if (!EXP_estUneOperationBinaire(exp)) {
    errno=ERRNO_PAS_UNE_OPERATION_BINAIRE;
  } else {
    *operateur=exp->operation.operationBinaire.operateur;
    *operandeG=exp->operation.operationBinaire.operandeGauche;
    *operandeD=exp->operation.operationBinaire.operandeDroite;
  }
}

char* EXP_operationUnaireEnChaine(EXP_Expression exp) {
  EXP_OperateurUnaire operateur;
  EXP_Expression operande;
  char *temp,*resultat;
  EXP_obtenirOperationUnaire(exp,&operateur,&operande);
  temp = EXP_enChaine(operande);
  switch (operateur) {
  case MOINS :
    resultat = (char*)malloc(strlen(temp)+1+1);
    resultat[0]='\0';
    strcpy(resultat,"-");
    break;
  case NON :
    resultat = (char*)malloc(strlen(temp)+1+4);
    resultat[0]='\0';
    strcpy(resultat,"non ");
    break;    
  }
  strcat(resultat,temp);
  free(temp);
    
  return resultat;
}

char* EXP_operationBinaireEnChaine(EXP_Expression exp) {
  EXP_OperateurBinaire operateur;
  EXP_Expression operandeG,operandeD;
  char *tempG,*tempD,*resultat;
  unsigned int longueurChaine;
  
  EXP_obtenirOperationBinaire(exp,&operateur,&operandeG,&operandeD);
  tempG = EXP_enChaine(operandeG);
  tempD = EXP_enChaine(operandeD);

  longueurChaine=strlen(tempG)+strlen(tempD)+1+4; /* 4 pour les parenthÃ¨ses*/
  switch (operateur) {
  case PLUS_PETIT_OU_EGAL : longueurChaine=longueurChaine+2;break;
  case PLUS_GRAND_OU_EGAL : longueurChaine=longueurChaine+2;break;
  case ET : longueurChaine=longueurChaine+2;break;
  case OU : longueurChaine=longueurChaine+2;break;
  default : longueurChaine=longueurChaine+1;break;
  }
  
  resultat = (char*)malloc(longueurChaine);
  resultat[0]='\0';
  strcpy(resultat,"(");
  strcat(resultat,tempG);
  strcat(resultat,")");
  switch (operateur) {
  case ADDITION : strcat(resultat,"+");break;
  case SOUSTRACTION : strcat(resultat,"-");break;
  case MULTIPLICATION : strcat(resultat,"*");break;
  case DIVISION : strcat(resultat,"/");break;
  case EGAL : strcat(resultat,"==");break;
  case DIFFERENT : strcat(resultat,"==");break;
  case PLUS_PETIT : strcat(resultat,"<");break;
  case PLUS_PETIT_OU_EGAL : strcat(resultat,"<=");break;
  case PLUS_GRAND : strcat(resultat,">");break;
  case PLUS_GRAND_OU_EGAL : strcat(resultat,">=");break;
  case OU : strcat(resultat,"ou");break;
  case ET : strcat(resultat,"et");break;      
  }
  strcat(resultat,"(");
  strcat(resultat,tempD);
  strcat(resultat,")");
  free(tempG);
  free(tempD);
  return resultat;
}

char* EXP_enChaine(EXP_Expression exp) {
  char temp[50];
  VAL_Valeur v;
  char *resultat;
  
  if (EXP_estUneConstante(exp)) {
    v=EXP_obtenirConstante(exp);
    switch (VAL_obtenirType(v)) {
    case ENTIER : sprintf(temp,"%ld",VAL_obtenirValeurEntiere(v)); break;
    case REEL : sprintf(temp,"%f",VAL_obtenirValeurReelle(v)); break;
    case BOOLEEN :
      if (VAL_obtenirValeurBooleenne(v))
	strcpy(temp,"VRAI");
      else
	strcpy(temp,"FAUX");
    }
    resultat = (char*)malloc(strlen(temp)+1);
    resultat[0]='\0';
    strcpy(resultat,temp);
  } else {
    if (EXP_estUnIdentifiant(exp)) {
      resultat = (char*)malloc(strlen(EXP_obtenirIdentifiant(exp))+1);
      resultat[0]='\0';
      strcpy(resultat,EXP_obtenirIdentifiant(exp));
    } else {
      if (EXP_estUneOperationUnaire(exp)) {
	resultat = EXP_operationUnaireEnChaine(exp);
      } else {
	resultat = EXP_operationBinaireEnChaine(exp);
      }
    }
  }
  return resultat;
}

void EXP_evaluerExpression(EXP_Expression expression, MEM_Memoire memoire, VAL_Valeur *pValeur, ERR_Erreur *pErreur);

void EXP_evaluerOperationUnaire(EXP_Expression expression, MEM_Memoire memoire, VAL_Valeur *pValeur, ERR_Erreur *pErreur) {
  EXP_OperateurUnaire operateur;
  EXP_Expression operande;
  VAL_Valeur v;
  EXP_obtenirOperationUnaire(expression, &operateur, &operande);
  EXP_evaluerExpression(operande, memoire, &v, pErreur);
  if (!ERR_uneErreurAEteProvoque(*pErreur)) {
    switch (operateur) {
    case MOINS :
      if (VAL_obtenirType(v) == BOOLEEN)
	*pErreur = ERR_erreur(TYPE_INCOMPATIBLE,"Type incompatible");
      else
	if (VAL_obtenirType(v) == ENTIER)
	  *pValeur = VAL_valeurEntiere(-VAL_obtenirValeurEntiere(v));
	else
	  *pValeur = VAL_valeurReelle(-VAL_obtenirValeurReelle(v));	
      break;
    case NON :
      if (VAL_obtenirType(v) == BOOLEEN)
	*pValeur = VAL_valeurBooleenne(!VAL_obtenirValeurBooleenne(v));
      else
	*pErreur = ERR_erreur(TYPE_INCOMPATIBLE,"Type incompatible");
      break;
    }
  }
}

void EXP_evaluerOperationBinaire(EXP_Expression expression, MEM_Memoire memoire, VAL_Valeur *pValeur, ERR_Erreur *pErreur) {
  EXP_OperateurBinaire operateur;
  EXP_Expression operandeG,operandeD;
  VAL_Valeur vG,vD;   
  EXP_obtenirOperationBinaire(expression, &operateur, &operandeG, &operandeD);
  EXP_evaluerExpression(operandeG, memoire, &vG, pErreur);
  if (!ERR_uneErreurAEteProvoque(*pErreur)) {
    EXP_evaluerExpression(operandeD, memoire, &vD, pErreur);
    if (!ERR_uneErreurAEteProvoque(*pErreur)) {
      if (VAL_obtenirType(vG) != VAL_obtenirType(vD))
	*pErreur = ERR_erreur(TYPE_INCOMPATIBLE,"Type incompatible");
      else
	switch (VAL_obtenirType(vG)) {
	case ENTIER :
	  switch (operateur) {
	  case ADDITION :
	    *pValeur = VAL_valeurEntiere(VAL_obtenirValeurEntiere(vG)+VAL_obtenirValeurEntiere(vD));
	    break;
	  case SOUSTRACTION :
	    *pValeur = VAL_valeurEntiere(VAL_obtenirValeurEntiere(vG)-VAL_obtenirValeurEntiere(vD));
	    break;
	  case MULTIPLICATION :
	    *pValeur = VAL_valeurEntiere(VAL_obtenirValeurEntiere(vG)*VAL_obtenirValeurEntiere(vD));
	    break;
	  case DIVISION :
	    if (VAL_obtenirValeurEntiere(vD) != 0)
	      *pValeur = VAL_valeurEntiere(VAL_obtenirValeurEntiere(vG)/VAL_obtenirValeurEntiere(vD));
	    else
	      *pErreur = ERR_erreur(DIVISION_PAR_ZERO,"Division par 0");
	    break;
	  case EGAL :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurEntiere(vG) == VAL_obtenirValeurEntiere(vD));
	    break;
	  case DIFFERENT :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurEntiere(vG) != VAL_obtenirValeurEntiere(vD));
	    break;  
	  case PLUS_PETIT :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurEntiere(vG) < VAL_obtenirValeurEntiere(vD));
	    break;
	  case PLUS_GRAND :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurEntiere(vG) > VAL_obtenirValeurEntiere(vD));
	    break;
	  case PLUS_PETIT_OU_EGAL :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurEntiere(vG) <= VAL_obtenirValeurEntiere(vD));
	    break;
	  case PLUS_GRAND_OU_EGAL :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurEntiere(vG) >= VAL_obtenirValeurEntiere(vD));
	    break;	    
	  default :
	    *pErreur = ERR_erreur(TYPE_INCOMPATIBLE,"Type incompatible");
	    break;
	  }
	  break;
	case REEL :
	  switch (operateur) {
	  case ADDITION :
	    *pValeur = VAL_valeurEntiere(VAL_obtenirValeurReelle(vG)+VAL_obtenirValeurReelle(vD));
	    break;
	  case SOUSTRACTION :
	    *pValeur = VAL_valeurEntiere(VAL_obtenirValeurReelle(vG)-VAL_obtenirValeurReelle(vD));
	    break;
	  case MULTIPLICATION :
	    *pValeur = VAL_valeurEntiere(VAL_obtenirValeurReelle(vG)*VAL_obtenirValeurReelle(vD));
	    break;
	  case DIVISION :
	    if (VAL_obtenirValeurReelle(vD) != 0.0)
	      *pValeur = VAL_valeurEntiere(VAL_obtenirValeurReelle(vG)/VAL_obtenirValeurReelle(vD));
	    else
	      *pErreur = ERR_erreur(DIVISION_PAR_ZERO,"Division par 0");
	    break;
	  case EGAL :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurReelle(vG) == VAL_obtenirValeurReelle(vD));
	    break;
	  case DIFFERENT :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurReelle(vG) != VAL_obtenirValeurReelle(vD));
	    break;  
	  case PLUS_PETIT :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurReelle(vG) < VAL_obtenirValeurReelle(vD));
	    break;
	  case PLUS_GRAND :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurReelle(vG) > VAL_obtenirValeurReelle(vD));
	    break;
	  case PLUS_PETIT_OU_EGAL :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurReelle(vG) <= VAL_obtenirValeurReelle(vD));
	    break;
	  case PLUS_GRAND_OU_EGAL :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurReelle(vG) >= VAL_obtenirValeurReelle(vD));
	    break;	    
	  default :
	    *pErreur = ERR_erreur(TYPE_INCOMPATIBLE,"Type incompatible");
	    break;
	  }	  
	  break;
	case BOOLEEN :
	  switch (operateur) {
	  case ET :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurBooleenne(vG) && VAL_obtenirValeurBooleenne(vD));
	    break;
	  case OU :
	    *pValeur = VAL_valeurBooleenne(VAL_obtenirValeurBooleenne(vG) || VAL_obtenirValeurBooleenne(vD));
	    break;
	  default :
	    *pErreur = ERR_erreur(TYPE_INCOMPATIBLE,"Type incompatible");
	    break;
	  }	  	  
	  break;
	}
    }
  }
}

void EXP_evaluerOperation(EXP_Expression expression, MEM_Memoire memoire, VAL_Valeur *pValeur, ERR_Erreur *pErreur) {
  if (EXP_estUneOperationUnaire(expression)) {
    EXP_evaluerOperationUnaire(expression, memoire, pValeur, pErreur);
  } else {
    EXP_evaluerOperationBinaire(expression, memoire, pValeur, pErreur);
  }
}

void EXP_evaluerExpression(EXP_Expression expression, MEM_Memoire memoire, VAL_Valeur *pValeur, ERR_Erreur *pErreur) {
  VAR_Variable *variable;
  if (EXP_estUneConstante(expression))
    *pValeur=EXP_obtenirConstante(expression);
  else
    if (EXP_estUnIdentifiant(expression)) {
      variable=MEM_obtenirVariable(memoire,EXP_obtenirIdentifiant(expression));
      if (variable == NULL) {
	*pErreur=ERR_erreur(VARIABLE_NON_INITIATLISEE,"Variable non initialisee");
      } else {
	*pValeur=VAR_obtenirValeur(*variable);
      }
    } else {
	EXP_evaluerOperation(expression, memoire, pValeur, pErreur);
    }
}

void EXP_detruire(EXP_Expression* exp) {
  if (!EXP_estUneConstante(*exp)) {
    if (EXP_estUnIdentifiant(*exp)) {
      free((*exp)->identifiant);
    } else {
      if (EXP_estUneOperationUnaire(*exp)) {
	EXP_detruire(&((*exp)->operation.operationUnaire.operande));
      } else {
	EXP_detruire(&((*exp)->operation.operationBinaire.operandeGauche));
	EXP_detruire(&((*exp)->operation.operationBinaire.operandeDroite));
      }
    }
  }
  free(*exp);  
  *exp=NULL;
}
