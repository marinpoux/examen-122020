#include "define.h"

int placement(int nb_pisteurs, int morts){
//BUT   : placer les elements sur le plateau
//ENTREE: 1 entier
//SORTIE: 1 entier (entree mise a jour)

    int ok=0;   //passe a 1 quand le joueur est pret ou que P_NB_MAX pisteurs sont places

    phase=1;    //phase de placement

    while(ok!=1){

        affichage(nb_pisteurs, morts, pisteurs[nb_pisteurs-1].num);

        placement_p(nb_pisteurs-1);

        //ajouter un pisteur (uniquement td nb_pisteurs<P_NB_MAX)
        if(nb_pisteurs<P_NB_MAX){

            ok=ajout_p(nb_pisteurs);

            if(ok==0){

                nb_pisteurs++;
            }
        } else {

            ok=1;
        }

        //printf("%d\n", ok);
    }

    maj_plateau(nb_pisteurs);

    placement_m();

    maj_plateau(nb_pisteurs);

    return nb_pisteurs;
}


void placement_p(int nb_pisteurs){
//BUT   : placer un pisteur
//ENTREE: 1 entier (nombre de pisteurs dans le jeu)
//SORTIE: /

    int xTemp=-1;
    int yTemp=-1;
    int ok=1;       //verification de la saisie

    printf("A quelles coordonnees souhaiteriez-vous placer ce pisteur ?\n");

        printf(" Colonne (1 a %d) : ", COLONNES);
        scanf("%d", &xTemp); fflush(stdin);

        printf(" Ligne (1 a %d) : ", LIGNES);
        scanf("%d", &yTemp); fflush(stdin);

        //printf("contenu: %c\n", jeu.tab_plateau[yTemp-1][xTemp-1]);

    if(((xTemp<1)||(xTemp>COLONNES)||(yTemp<1)||(yTemp>LIGNES))
       || (jeu.tab_plateau[yTemp-1][xTemp-1]=='P')){

        ok=0;
    }

    //coordonnees non valides
    while(ok!=1){
        if((xTemp<1)||(xTemp>COLONNES)||(yTemp<1)||(yTemp>LIGNES)){

            printf("Coordonnees non valides !\n");
        } else {

            printf("Cet emplacement est deja occupe !\n");
        }

        printf(" Colonne (1 a %d) : ", COLONNES);
        scanf("%d", &xTemp); fflush(stdin);

        printf(" Ligne (1 a %d) : ", LIGNES);
        scanf("%d", &yTemp); fflush(stdin);

        if(((xTemp>=1)&&(xTemp<=COLONNES)&&(yTemp>=1)&&(yTemp<=LIGNES))
            && (jeu.tab_plateau[yTemp-1][xTemp-1]!='P')){

            ok=1;
        }
    }

    //assignation des coordonnees saisies
    pisteurs[nb_pisteurs].coord.posX=xTemp-1;
    pisteurs[nb_pisteurs].coord.posY=yTemp-1;

    //printf("coord: x=%d y=%d\n", pisteurs[nb_pisteurs].coord.posX, pisteurs[nb_pisteurs].coord.posY);
}


int ajout_p(int nb_pisteurs){
//BUT   : placer un pisteur
//ENTREE: 1 entier (nombre de pisteurs dans le jeu), un pointeur pour ok
//SORTIE: 1 entier (nombre de pisteurs dans le jeu)

    char rep=' ';   //reponse saisie par l'utilisateur
    int ok=0;   //verification de la saisie

    printf("Vous avez %d pisteur(s). Voulez-vous creer un pisteur supplementaire ? (%d maximum)\n Oui(o) / Non(n) : ", nb_pisteurs, P_NB_MAX);
    scanf("%c", &rep); fflush(stdin);

    while((rep!='o')&&(rep!='n')){

        printf("Saisie non valide !\n Oui(o) / Non(n) : ");
        scanf("%c", &rep); fflush(stdin);
    }

    if(rep=='o'){

        ok=0;
    } else {

        ok=1;
    }

    return ok;
}


void placement_m(){
//BUT   : placer le monstre
//ENTREE: 1 entier (nombre de pisteurs)
//SORTIE: /

    int x_temp;
    int y_temp;
    int ok=0;   //verification de la validite de l'emplacement

    do{
        //generation des coordonnees
        x_temp=nbRand(0,(COLONNES-1));
        y_temp=nbRand(0, (LIGNES-1));

        ok=5;

        //comparaison aux emplacements des pisteurs
            //case aux coord
            if(jeu.tab_plateau[y_temp][x_temp]=='P'){
                ok--;
            }
            //case au-dessus
            if(jeu.tab_plateau[y_temp-1][x_temp]=='P'){
                ok--;
            }
            //case a gauche
            if(jeu.tab_plateau[y_temp][x_temp-1]=='P'){
                ok--;
            }
            //case a droite
            if(jeu.tab_plateau[y_temp][x_temp+1]=='P'){
                ok--;
            }
            //case en-dessous
            if(jeu.tab_plateau[y_temp+1][x_temp]=='P'){
                ok--;
            }
    } while(ok<5); //repetition tq toutes les cases concernees ne sont pas libres

    //assignation des coord
    monkC.coord.posX=x_temp;
    monkC.coord.posY=y_temp;
}
