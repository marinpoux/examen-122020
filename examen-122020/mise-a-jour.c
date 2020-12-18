#include "define.h"

void maj_plateau(int nb_pisteurs){
//BUT   : mettre a jour la position des elements sur le plateau a afficher
//ENTREE: le nombre de pisteurs
//SORTIE: /

    int x_temp=0;
    int y_temp=0;

    //si le monstre est blesse, un point est affiche sur la case ou il se trouvait precedement
    if(monkC.blesse>0){
        //doit etre ecrit en premier pour ne pas ecraser l'affichage de la position d'un pisteur!
        jeu.tab_plateau[monkC.prcdt.posY][monkC.prcdt.posX]='.';
    }

    //reecriture du tableau
    for(int i=0; i<nb_pisteurs;i++){

        //affichage uniquement des pisteurs vivants
        if(pisteurs[i].stat=='v'){

            x_temp=pisteurs[i].coord.posX;
            y_temp=pisteurs[i].coord.posY;

            jeu.tab_plateau[y_temp][x_temp]=pisteurs[i].icone;
        }
    }

    //jeu.tab_plateau[monkC.coord.posY][monkC.coord.posX]='M';//**debug**//
}


void maj_usure(){
//BUT   : mettre a jours les tableaux de traces suite a l'usure
//ENTREE: /
//SORTIE: /

    for(int i=0;i<LIGNES;i++){
        for(int j=0;j<COLONNES;j++){

            if(jeu.traces_M[i][j]>0){
                //les traces du monstre s'estompent
                jeu.traces_M[i][j]--;
            }

            if(jeu.traces_P[i][j]>0){
                //les traces des pisteurs persistent
                jeu.traces_P[i][j]++;
            }
        }
    }

    //nouvelle position du monstre
    jeu.traces_M[monkC.coord.posY][monkC.coord.posX]=16;
}


void maj_traces(int nb_pisteurs){
//BUT   : mettre a jours les tableaux de traces suite a un deplacement
//ENTREE: le nombre de pisteurs
//SORTIE: /

    for(int i=0;i<nb_pisteurs;i++){
        //concerne uniquement les pisteurs vivants!
        if(pisteurs[i].stat=='v'){
            //la case ou se trouve le pisteur prend la valeur 1=trace fraiche
            jeu.traces_P[pisteurs[i].coord.posY][pisteurs[i].coord.posX]=1;
        }

        //la case ou se trouve le monstre prend la valeur M_TRACES=trace fraiche
        jeu.traces_M[monkC.coord.posY][monkC.coord.posX]=M_TRACES;
    }
}
