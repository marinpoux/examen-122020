#include "define.h"

int main()
{
    int jouer=1;

    while(jouer==1){

    //VARIABLES
        int nb_pisteurs=1;  //nombre de pisteurs dans le jeu; initialise a 0 (max=P_NB_MAX)
        int morts=0;        //nombre de pisteurs morts
        int fin=0;          //0: partie en cours; valeur depend de victoire ou defaite
        int tour=0;         //compteur de tours de jeu

        phase=0;


        //INTRODUCTION
        intro();

        //INITIALISATION
        init();

        //PLACEMENTS DES ELEMENTS
        nb_pisteurs=placement(nb_pisteurs, morts);

        while(fin==0){
        //boucle se repete tq monstre ou tous pisteurs encore vivants <-> tq partie pas finie

            maj_usure();    //usure des traces laissees
            tour++;         //maj du compteur

            //tour du joueur
            fin=traque_P(nb_pisteurs, morts);

            if(fin==0){     //n'est pas lance si la partie a ete finie pendant la phase de traque des pisteurs

                //tour du monstre
                morts=traque_M(nb_pisteurs, morts);

                fin=verif_P(nb_pisteurs, morts);
            }
        }

        resultat(fin, nb_pisteurs, tour);

        jouer=rejouer();

    }

    return 0;
}
