#include "define.h"

void affichage(int nb_pisteurs, int morts, int num){
//BUT   : rafraichir l'ecran et afficher l'interface
//ENTREE: le nombre de pisteurs, le nombre de morts, le num du pisteur actuel
//SORTIE: /

    system("CLS");  //effacer le contenu de la console pour plus de lisibilite

    printf("LA TRAQUE\n");

    //rappel des regles au joueur
    regles();

    //reinitialisation du contenu plateau
    init_tab('c', 0, ' ', jeu.tab_plateau, jeu.tab_plateau);

    //mise a jour des emplacements des elements
    maj_plateau(nb_pisteurs);

    //affichage du plateau
    affiche_plateau();

    if(num>0){

        printf("PISTEUR %d\n", num);
    } else {

        printf("TOUR DU MONSTRE\n");
    }

    //affiche_traces();

}


void regles(){
//BUT   : rappeler les regles au joueur (general + precisions en rapport avec la phase de jeu)
//ENTREE: 1 entier
//SORTIE: /

    printf("\nObjectif : Traquez et eliminez le monstre !\n\n");

    if(phase==1){   //phase de placement

        printf("Suivez les indications afin de placer vos pisteurs sur le plateau !\nVous pouvez placer jusqu'a %d pisteurs.\n", P_NB_MAX);
    }

    if(phase==2){   //phase de traque-rapport

        printf("Chaque pisteur fait sont rapport par rapport aux 8 cases qui l'entourent.\n");
        printf("Elles sont appelees de 1 a 8, de gauche a droite, de haut en bas.\n");
        printf("Plus les traces declarees sont de valeur elevees, plus elles sont fraiches... et plus le monstre est proche !\n");
        printf("Le pisteur actif est indique par un '!'.\n");
        printf("Si un pisteur appercoit le monstre, il pourra tenter de tirer dessus !\n");
        printf("Le monstre blesse laissera une trace derriere lui pendant %d tours.\n", M_TRACES);
    }

    if(phase==3){   //phase de traque-deplacement

        printf("Suivez les indication pour deplacer chaque pisteur.\n");
        printf("Le pisteur actif est indique par un '?'.\n");
        printf("Commencez par donner la direction du déplacement (haut, bas, gauche, droite).\n");
        printf("Attention, vous ne pouvez pas changer d'avis !\n");
        printf("Choisissez prudemment, si un pisteur tombe a proximite directe du monstre, s'en est fini de lui...\n");
        printf("Astuce : Vous ne craignez rien tant que vous vous trouvez en diagonale du monstre !\n");
    }

    if(phase==3){   //phase du monstre

        printf("C'est le tour du monstre, vous ne pouvez rien faire en attendant a part attendre... et croiser les doigts !\n");
        printf("Le monstre se deplace de %d une fois par tour.\n", M_PM);
        printf("Il regarde autour de lui avant et apres de se deplacer.\n");
        printf("Apres cela, c'est de nouveau au tour du joueur.\n");
    }

}


void affiche_plateau(){
//BUT   : afficher le plateau
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
            printf("%c ", jeu.tab_plateau[i][j]);
        }
        printf("*");  //affichage bord droit en fin de ligne
    }

    //afficher le bord inferieur du plateau
    printf("\n");
    for(i=0; i<COLONNES+2;i++){
        printf("* ");
    }
    printf("\n\n");
}
