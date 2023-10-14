#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arbre.h"


/*******************************************************************************

      Cette proc�dure permet d'afficher le contenu d'un dictionnaire

********************************************************************************/

void dicoAfficher(TArbre a,char mot[],int niveau){

    //Si l'arbre est vide.
    if(!arbreEstVide(a)){
        mot[niveau] = arbreRacineLettre(a);
        //Si c'est la fin du mot.
        if(arbreRacineLettre(a)=='\0'){
            printf("-%s (%d)\n",mot,arbreRacineNbOcc(a));
        }
        /*Si le mot n'est pas termin� :
            1) D�placer au sous arbre gauche pour afficher le reste du mot.
            2) D�placer au sous arbre droite pour afficher, soit le differents parties du mot soit un nouveau mot.
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

               Cette proc�dure permet d'ajouter un mot au dictionnaire

********************************************************************************/

void dicoInsererMot(char mot[], TArbre *pa){

    TArbre tmp_arbre ;

    //Si l'arbre est vide
    if(arbreEstVide(*pa)){
        /*Si le mot est termin� :
            On cr�e le n�ud avec le nombre d'occurrence est �gale � 1.
        */
        if(*mot == '\0'){
            *pa = arbreCons(*mot,1,arbreConsVide(),arbreConsVide());
        }
        /*Si le mot n'est pas termin� :
            1) On cr�e le n�ud avec le nombre d'occurrence est �gale � 0.
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
        //Si la premiere lettre du mot est �agle la lettre du racine.
        if(*mot == arbreRacineLettre(*pa)){
            /*Si le mot est termin� :
                1) On recr�e le n�ud avec le nombre d'occurrence est �gale � l'ancienne valeur incr�ment� par 1.
            */
            if(*mot == '\0'){
                tmp_arbre = *pa;
                *pa = NULL;
                *pa = arbreCons('\0',(arbreRacineNbOcc(tmp_arbre)+1),arbreFilsGauche(tmp_arbre),arbreFilsDroit(tmp_arbre));
            }
            else{
                /*Si le mot n'est pas termin� :
                    1) On d�place au sous arbre gauche.
                    2) On refait le m�me encha�nement.
                */
                tmp_arbre = arbreConsVide();
                tmp_arbre = arbreFilsGauche(*pa);
                dicoInsererMot(mot+1,&tmp_arbre);
                *pa = arbreCons(*mot,0,tmp_arbre,arbreFilsDroit(*pa));
            }
        }
        //Si la premiere lettre du mot est diff�rent de la lettre du racine.
        else{
            /*Si la lettre du n�ud est inf�rieur la premiere lettre du mot :
                1) On cr�e un nouveau n�ud, avec la premiere lettre du mot.
                2) Placer l'arbre passer en param�tre au droite de nouveau arbre cr��.
                3) Remplacer l'arbre passer en param�tre par la nouvelle arbre.
            */
            if((int)arbreRacineLettre(*pa) < (int)(*mot)){
                tmp_arbre = arbreConsVide();
                tmp_arbre = arbreFilsDroit(*pa);
                dicoInsererMot(mot,&tmp_arbre);
                *pa = arbreCons(arbreRacineLettre(*pa),arbreRacineNbOcc(*pa),arbreFilsGauche(*pa),tmp_arbre);
            }
            /*Si la lettre du n�ud est inf�rieur la premiere lettre du mot :
                1) On cr�e un nouveau n�ud, avec la lettre courant.
                2) Si on trouve le caract�re de fin du cha�ne, on met le nombre d'occurence � 1. 0 sinon.
                3) On fait le m�me encha�nement pour le reste des lettres du mot.
            */
            else{
                //Si le mot est termin�.
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

      Cette fonction permet de d�terminer le nombre d'occurrences d'un mot

********************************************************************************/

int dicoNbOcc(char mot[], TArbre a){

    //Condition d'arr�t, tester si le n�ud est vide.
    if(arbreEstVide(a)){
        return 0;
    }
    //Si la lettre du n�ud et la premiere lettre du mot ne sont pas �gaux.
    else if(arbreRacineLettre(a) != *mot){
        //Si la lettre du n�ud est sup�rieur la premiere lettre du mot.
        if((int)arbreRacineLettre(a) > (int)(*mot)){
            return 0;
        }
         //Si la lettre du n�ud est inf�rieur la premiere lettre du mot.
        else{
            return dicoNbOcc(mot,arbreFilsDroit(a));
        }
    }
    //Si la lettre du n�ud et la premiere lettre du mot sont �gaux.
    else {
        //Si le mot est termin�.
        if(*mot == '\0' ){
            return arbreRacineNbOcc(a);
        }
        //Si le mot n'est pas termin�.
        else{
           return dicoNbOcc(mot+1,arbreFilsGauche(a));
        }
    }
}

/*******************************************************************************

   Cette fonction vous permet de sp�cifier le nombre total de diff�rents mots

********************************************************************************/

int dicoNbMotsDifferents(TArbre a){

    //Condition d'arr�t, tester si le n�ud est vide.
    if(arbreEstVide(a)){
        return 0;
    }else{

        /*
            Retour Le nombre n'occurence de diff�rents mots :
                1) Faire l'addition du nombre totale de diff�rents mots de sous arbre gauche et de sous arbre droite.
                2) En ajoutant 1 si le n�ud contient le caract�re de fin de cha�ne '\0', 0 sinon.
        */
        return (arbreRacineLettre(a) == '\0' ? 1 : 0) + dicoNbMotsDifferents(arbreFilsGauche(a)) + dicoNbMotsDifferents(arbreFilsDroit(a));
    }

}

/*******************************************************************************

         Cette fonction vous permet de sp�cifier le nombre total de mots

********************************************************************************/

int dicoNbMotsTotal(TArbre a){

    //Condition d'arr�t, tester si le n�ud est vide.
    if(arbreEstVide(a)){
        return 0;
    }else{
        /*
            Retour Le nombre n'occurence de diff�rents mots :
                1) Faire l'addition du nombre totale de mots de sous arbre gauche et de sous arbre droite.
                2) En ajoutant le nombre d'occurences du n�ud courant.
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

                    Cette fonction permet de d�truiren l'arbre

********************************************************************************/

int nombreAleatoire(int nombreMax)
{
    srand(time(NULL));
    return (rand() % nombreMax);
}
