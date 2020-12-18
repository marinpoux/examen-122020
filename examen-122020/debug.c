#include "define.h"

void affiche_traces(){
//BUT   : rafraichir l'ecran et afficher le plateau
//ENTREE: /
//SORTIE: /
    int i=0;
    int j=0;

    //afficher le bord superieur du plateau
    printf("\n");
    for(i=0; i<COLONNES+2;i++){
        printf("* ");
    }

    //afficher le contenu du plateau
    for(i=0; i<LIGNES;i++){
        printf("\n* ");  //retour chariot + affichage bord gauche en debut de ligne

        for(j=0; j<COLONNES;j++){
            //affichage du contenu du plateau
            printf("%d ", jeu.traces_M[i][j]);
        }
        printf("*");  //affichage bord droit en fin de ligne
    }

    //afficher le bord inferieur du plateau
    printf("\n");
    for(i=0; i<COLONNES+2;i++){
        printf("* ");
    }
    printf("\n");
}


void testswitch(){
//tester fonctionnement switch(case)
int num=0;

printf("num :");
scanf("%d", &num); fflush(stdin);

switch(num){
case 1:
    printf("num=1");
    break;
case 2:
    printf("num=2");
    break;
}
}
