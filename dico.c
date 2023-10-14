#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arbre.h"


/*******************************************************************************

      Cette procédure permet d'afficher le contenu d'un dictionnaire

********************************************************************************/

void dicoAfficher(TArbre a,char mot[],int niveau){

    //Si l'arbre est vide.
    if(!arbreEstVide(a)){
        mot[niveau] = arbreRacineLettre(a);
        //Si c'est la fin du mot.
        if(arbreRacineLettre(a)=='\0'){
            printf("-%s (%d)\n",mot,arbreRacineNbOcc(a));
        }
        /*Si le mot n'est pas terminé :
            1) Déplacer au sous arbre gauche pour afficher le reste du mot.
            2) Déplacer au sous arbre droite pour afficher, soit le differents parties du mot soit un nouveau mot.
        */
        else{
            dicoAfficher(arbreFilsGauche(a),mot,niveau+1);
            //Si une nouvelle lettre pour les mots.
            if(!niveau){
                printf("\n");
            }
            dicoAfficher(arbreFilsDroit(a),mot,niveau);
        }
    }
}



/*******************************************************************************

               Cette procédure permet d'ajouter un mot au dictionnaire

********************************************************************************/

void dicoInsererMot(char mot[], TArbre *pa){

    TArbre tmp_arbre ;

    //Si l'arbre est vide
    if(arbreEstVide(*pa)){
        /*Si le mot est terminé :
            On crée le nœud avec le nombre d'occurrence est égale à 1.
        */
        if(*mot == '\0'){
            *pa = arbreCons(*mot,1,arbreConsVide(),arbreConsVide());
        }
        /*Si le mot n'est pas terminé :
            1) On crée le nœud avec le nombre d'occurrence est égale à 0.
            2) On complete le reste de lettres du mot.
        */
        else{
            tmp_arbre = arbreConsVide();
            dicoInsererMot(mot+1,&tmp_arbre);
            *pa = arbreCons(*mot,0,tmp_arbre,arbreConsVide());
        }
    }
    //Si l'arbre n'est pas vide.
    else{
        //Si la premiere lettre du mot est éagle la lettre du racine.
        if(*mot == arbreRacineLettre(*pa)){
            /*Si le mot est terminé :
                1) On recrée le nœud avec le nombre d'occurrence est égale à l'ancienne valeur incrémenté par 1.
            */
            if(*mot == '\0'){
                tmp_arbre = *pa;
                *pa = NULL;
                *pa = arbreCons('\0',(arbreRacineNbOcc(tmp_arbre)+1),arbreFilsGauche(tmp_arbre),arbreFilsDroit(tmp_arbre));
            }
            else{
                /*Si le mot n'est pas terminé :
                    1) On déplace au sous arbre gauche.
                    2) On refait le même enchaînement.
                */
                tmp_arbre = arbreConsVide();
                tmp_arbre = arbreFilsGauche(*pa);
                dicoInsererMot(mot+1,&tmp_arbre);
                *pa = arbreCons(*mot,0,tmp_arbre,arbreFilsDroit(*pa));
            }
        }
        //Si la premiere lettre du mot est différent de la lettre du racine.
        else{
            /*Si la lettre du nœud est inférieur la premiere lettre du mot :
                1) On crée un nouveau nœud, avec la premiere lettre du mot.
                2) Placer l'arbre passer en paramétre au droite de nouveau arbre créé.
                3) Remplacer l'arbre passer en paramétre par la nouvelle arbre.
            */
            if((int)arbreRacineLettre(*pa) < (int)(*mot)){
                tmp_arbre = arbreConsVide();
                tmp_arbre = arbreFilsDroit(*pa);
                dicoInsererMot(mot,&tmp_arbre);
                *pa = arbreCons(arbreRacineLettre(*pa),arbreRacineNbOcc(*pa),arbreFilsGauche(*pa),tmp_arbre);
            }
            /*Si la lettre du nœud est inférieur la premiere lettre du mot :
                1) On crée un nouveau nœud, avec la lettre courant.
                2) Si on trouve le caractére de fin du chaîne, on met le nombre d'occurence à 1. 0 sinon.
                3) On fait le même enchaînement pour le reste des lettres du mot.
            */
            else{
                //Si le mot est terminé.
                if(*mot == '\0'){
                    *pa = arbreCons(*mot,1,arbreConsVide(),*pa);
                }
                else{
                //Si n'est pas la fin du mot.
                    tmp_arbre = arbreConsVide();
                    dicoInsererMot(mot+1,&tmp_arbre);
                    *pa = arbreCons(*mot,0,tmp_arbre,*pa);
                }
            }
        }
    }
}

/*******************************************************************************

      Cette fonction permet de déterminer le nombre d'occurrences d'un mot

********************************************************************************/

int dicoNbOcc(char mot[], TArbre a){

    //Condition d'arrêt, tester si le nœud est vide.
    if(arbreEstVide(a)){
        return 0;
    }
    //Si la lettre du nœud et la premiere lettre du mot ne sont pas égaux.
    else if(arbreRacineLettre(a) != *mot){
        //Si la lettre du nœud est supérieur la premiere lettre du mot.
        if((int)arbreRacineLettre(a) > (int)(*mot)){
            return 0;
        }
         //Si la lettre du nœud est inférieur la premiere lettre du mot.
        else{
            return dicoNbOcc(mot,arbreFilsDroit(a));
        }
    }
    //Si la lettre du nœud et la premiere lettre du mot sont égaux.
    else {
        //Si le mot est terminé.
        if(*mot == '\0' ){
            return arbreRacineNbOcc(a);
        }
        //Si le mot n'est pas terminé.
        else{
           return dicoNbOcc(mot+1,arbreFilsGauche(a));
        }
    }
}

/*******************************************************************************

   Cette fonction vous permet de spécifier le nombre total de différents mots

********************************************************************************/

int dicoNbMotsDifferents(TArbre a){

    //Condition d'arrêt, tester si le nœud est vide.
    if(arbreEstVide(a)){
        return 0;
    }else{

        /*
            Retour Le nombre n'occurence de différents mots :
                1) Faire l'addition du nombre totale de différents mots de sous arbre gauche et de sous arbre droite.
                2) En ajoutant 1 si le nœud contient le caractère de fin de chaîne '\0', 0 sinon.
        */
        return (arbreRacineLettre(a) == '\0' ? 1 : 0) + dicoNbMotsDifferents(arbreFilsGauche(a)) + dicoNbMotsDifferents(arbreFilsDroit(a));
    }

}

/*******************************************************************************

         Cette fonction vous permet de spécifier le nombre total de mots

********************************************************************************/

int dicoNbMotsTotal(TArbre a){

    //Condition d'arrêt, tester si le nœud est vide.
    if(arbreEstVide(a)){
        return 0;
    }else{
        /*
            Retour Le nombre n'occurence de différents mots :
                1) Faire l'addition du nombre totale de mots de sous arbre gauche et de sous arbre droite.
                2) En ajoutant le nombre d'occurences du nœud courant.
        */
        return arbreRacineNbOcc(a) + dicoNbMotsTotal(arbreFilsGauche(a)) + dicoNbMotsTotal(arbreFilsDroit(a));
    }
}

/***************************************************************************************

   Cette fonction vous permet de choisir par hasard un mot depuis le fichier "dico.txt"

****************************************************************************************/
int piocherMot(char *motPioche)
{
    FILE* dico = NULL;
    int nombreMots = 0, numMotChoisi = 0, i = 0;
    int caractereLu = 0;
    dico = fopen("dico.txt", "r");
    if (dico == NULL)
    {
        printf("\nImpossible de charger le dictionnaire de mots");
        return 0;
    }
    do
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            nombreMots++;
    } while(caractereLu != EOF);

    numMotChoisi = nombreAleatoire(nombreMots);
    rewind(dico);
    while (numMotChoisi > 0)
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            numMotChoisi--;
    }
    fgets(motPioche, 100, dico);
    motPioche[strlen(motPioche) - 1] = '\0';
    fclose(dico);
    return 1;
}

/*******************************************************************************

                    Cette fonction permet de détruiren l'arbre

********************************************************************************/

int nombreAleatoire(int nombreMax)
{
    srand(time(NULL));
    return (rand() % nombreMax);
}
