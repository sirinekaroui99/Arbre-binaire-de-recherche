#ifndef DICO_H_INCLUDED
#define DICO_H_INCLUDED

#include "arbre.h"

/*******************************************************************************

                 Les signatures des fonctions et des procédures

********************************************************************************/

void dicoAfficher(TArbre a,char mot[],int niveau);
void dicoInsererMot(char mot[], TArbre *pa);
int dicoNbOcc(char mot[], TArbre a);
int dicoNbMotsDifferents(TArbre a);
int dicoNbMotsTotal(TArbre a);
int piocherMot(char *motPioche);
int nombreAleatoire(int nombreMax);

#endif // DICO_H_INCLUDED
