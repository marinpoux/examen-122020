#include "define.h"

void init(){
//BUT   : initialiser les variables du jeu (tableaux, types)
//ENTREE: /
//SORTIE: /

    init_plateau();

    //affiche_plateau();
    //affiche_traces();

    init_pisteurs();
    init_monstre();
}


void init_plateau(){
//BUT   : initialiser le type plateau
//ENTREE: 1 plateau
//SORTIE: 1 plateau initialise

    //initialisation du tableau d'entiers contenant les traces laissees par les pisteurs
    init_tab('d', 0, '0', jeu.traces_P, jeu.traces_P);

    //initialisation du tableau d'entiers contenant les traces laissees par le monstre
    init_tab('d', 0, '0', jeu.traces_M, jeu.traces_M);

    //initialisation du plateau de caracteres, representant le plateau a afficher a l'ecran
    init_tab('c', 0, ' ', jeu.tab_plateau, jeu.tab_plateau);
}


void init_pisteurs(){
//BUT   : initialiser le type pisteur
//ENTREE: 1 pisteur
//SORTIE: 1 pisteur initialise

    //initialisation de tous les pisteurs possibles (P_NB_MAX)
    for(int i=0;i<P_NB_MAX;i++){

        pisteurs[i].num=i+1;    //numero affiche a l'ecran pour distinguer le pisteur (1 a nb_pisteurs)
        pisteurs[i].coord.posX=-1;
        pisteurs[i].coord.posY=-1;
        pisteurs[i].icone='P';
        pisteurs[i].stat='v';
    }
}


void init_monstre(){
//BUT   : initialiser le type monstre
//ENTREE: 1 monstre
//SORTIE: 1 monstre initialise

    monkC.coord.posX=-1;
    monkC.coord.posY=-1;
    monkC.prcdt.posX=-1;
    monkC.prcdt.posY=-1;
    monkC.pv=M_PV;
    monkC.blesse=0;
}


void init_tab(char var, int d, char c, int tab_int[LIGNES][COLONNES], char tab_char[LIGNES][COLONNES]){
//BUT   : initialiser un tableau d'entiers ou de caracteres avec l'entier/le caractere entre
//ENTREE:
    //1 caractere: 'd'=entier, 'c'=caractere
    //1 entier et 1 caractere (pour remplir le tableau)
    //1 tableau d'entiers et 1 tableau de caracteres
//SORTIE: /

    for(int i=0;i<LIGNES;i++){          //lignes
        for(int j=0;j<COLONNES;j++){    //colonnes

            if(var=='d'){
                tab_int[i][j]=d;
            } else {
                tab_char[i][j]=c;
            }
        }
    }
}
