#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

/*******************************************************************************

                               Les structures des données

********************************************************************************/

//Structure des noeuds
typedef struct noeud {
    char lettre;
    int nombre_occurrence;
    struct noeud *fils_gauche;
    struct noeud *fils_droite;
}noeud;

//Structure de l'arbre
typedef struct noeud* TArbre;

/*******************************************************************************

                Les signatures des fonctions et des procédures

********************************************************************************/

TArbre arbreConsVide(void);
int arbreEstVide(TArbre a);
TArbre arbreCons(char c, int n, TArbre fg, TArbre fd);
char arbreRacineLettre(TArbre a);
int arbreRacineNbOcc(TArbre a);
TArbre arbreFilsGauche(TArbre a);
TArbre arbreFilsDroit(TArbre a);
void arbreSuppr(TArbre *a);



#endif // ARBRE_H_INCLUDED
