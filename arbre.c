#include <stdlib.h>
#include "arbre.h"

/*******************************************************************************

                Cette fonction permet de construire une arbre vide

********************************************************************************/

TArbre arbreConsVide(void){

    //Retour la valeur NULL pour inialiser/créer une arbre.
    return NULL;

}

/*******************************************************************************

            Cette fonction permet de tester si l'arbre est vide

********************************************************************************/

int arbreEstVide(TArbre a){

    //Retour 1 si le racine est vide, 0 sinon.
    return a==NULL;

}

/*******************************************************************************

                Cette fonction permet de créer un nouveau nœud

********************************************************************************/

TArbre arbreCons(char c, int n, TArbre fg, TArbre fd){

    //Initialisation du nœud.
    TArbre a = arbreConsVide();

    //Allocation du zone mémoire.
    a = (TArbre)malloc(sizeof(noeud));

    //Initialisation de valeurs du nœud.
    a->lettre = c;
    a->fils_gauche = fg;
    a->fils_droite = fd;
    a->nombre_occurrence = n;

    return a;

}

/*******************************************************************************

              Cette fonction permet de renvoyer le caractère du racine

********************************************************************************/

char arbreRacineLettre(TArbre a){

    //Retour le caractère du racine.
    return a->lettre;

}

/*******************************************************************************

        Cette fonction permet de renvoyer le nombre d'occurrence du racine

********************************************************************************/

int arbreRacineNbOcc(TArbre a){

    //Retour le nombre d'occurrence du racine.
    return a->nombre_occurrence;

}

/*******************************************************************************

              Cette fonction permet de renvoyer le fils gauche du racine

********************************************************************************/

TArbre arbreFilsGauche(TArbre a){

    //Retour le fils gauche du racine.
    return a->fils_gauche;

}

/*******************************************************************************

             Cette fonction permet de renvoyer le fils droit du racine

********************************************************************************/

TArbre arbreFilsDroit(TArbre a){

    //Retour le fils droit du racine.
    return a->fils_droite;

}

/*******************************************************************************

                    Cette procédure permet de détruire l'arbre

********************************************************************************/

void arbreSuppr(TArbre *a){

    //Si le racine est vide.
    if(!arbreEstVide(*a)){

       //Suppression de sous arbre gauche.
        arbreSuppr(arbreFilsGauche(*a));

       //Suppression de sous arbre droite
        arbreSuppr(arbreFilsDroit(*a));

        //Libération de zone mémoire.
        free(*a);

        *a=NULL;
    }

}
