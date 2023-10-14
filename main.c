#include <stdio.h>
#include "arbre.h"
#include "dico.h"


/*******************************************************************************

       Cette procédure permet de tester les operations du dictionnaire

********************************************************************************/

void premier_test(TArbre *mon_dico){

    char buffer[100];
    TArbre dico = *mon_dico;

    strcpy(buffer, "gallon");
    dicoInsererMot(buffer, &dico);
    dicoAfficher(dico,buffer,0);
    printf("\n");

    strcpy(buffer, "munier");
    dicoInsererMot(buffer, &dico);
    dicoAfficher(dico,buffer,0);
    printf("\n");

    strcpy(buffer, "abenia");
    dicoInsererMot(buffer, &dico);
    dicoAfficher(dico,buffer,0);
    printf("\n");

    strcpy(buffer, "munier");
    dicoInsererMot(buffer, &dico);
    dicoAfficher(dico,buffer,0);
    printf("\n");

    strcpy(buffer, "mumu");
    dicoInsererMot(buffer, &dico);
    dicoAfficher(dico,buffer,0);
    printf("\n");

    strcpy(buffer, "alpha");
    dicoInsererMot(buffer, &dico);

    strcpy(buffer, "alphabeta");
    dicoInsererMot(buffer, &dico);
    strcpy(buffer, "al");
    dicoInsererMot(buffer, &dico);
    dicoAfficher(dico,buffer,0);
    printf("\n");

    printf("\"%s\" \t -> %d\n", "gallon", dicoNbOcc("gallon",dico));
    printf("\"%s\" \t\t -> %d\n", "mumu", dicoNbOcc("mumu",dico));
    printf("\"%s\" \t -> %d\n", "munier", dicoNbOcc("munier",dico));
    printf("\"%s\" \t -> %d\n", "gastro", dicoNbOcc("gastro",dico));
    printf("\"%s\" \t -> %d\n", "lespine", dicoNbOcc("lespine",dico));
    printf("\"%s\" \t\t -> %d\n", "aaa", dicoNbOcc("aaa",dico));
    printf("\n");

    *mon_dico = dico;
}

/*******************************************************************************

   Cette procédure permet de tester les differents operartions du dictionnaire

********************************************************************************/

void deuxieme_test(TArbre *mon_dico){

    char buffer[100];
    TArbre dico = *mon_dico;
    int nombre_mots = 0 ;
    //Nombre de mot à choisit
    const int NOMBRE_MOT =10;

    printf("\n\n========================= Debut du chargement du dictionnaire =========================\n\n");

    while(nombre_mots++<NOMBRE_MOT){
        sleep(1);
        piocherMot(buffer);
        printf("L'ajout de chaine numero %d \"%s\"\n",nombre_mots,buffer);
        dicoInsererMot(buffer, &dico);
    }

    printf("\n\n========================= Fin du chargement du dictionnaire ===========================\n\n");


    printf("\n\n========================= Debut d'affichage le contenu du dictionnaire =========================\n\n");

    dicoAfficher(dico,buffer,0);

    printf("\n\n========================= Fin d'affichage le contenu du dictionnaire ===========================\n\n");


    printf("\n\n========================= Debut d'affichage les statistiques du dictionnaire =========================\n\n");

    printf("%s -> %d\n", "Nombre des différents mots", dicoNbMotsDifferents(dico));
    printf("%s -> %d\n", "Nombre totale des mots", dicoNbMotsTotal(dico));

    nombre_mots = 0;

    while(nombre_mots++<5){
        sleep(1);
        piocherMot(buffer);
        printf("\nNombre d'occurrence du \"%s\" --> %d\n",buffer,dicoNbOcc(buffer,dico));
    }

    printf("\n\n========================= Fin d'affichage les statistiques du dictionnaire ===========================\n\n");

}

int main(int argc, char **argv)
{
    TArbre dico;
    dico = arbreConsVide();

    //premier_test(&dico);

    deuxieme_test(&dico);

}
