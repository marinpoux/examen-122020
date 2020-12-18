#include "define.h"
/*modele
//BUT   :
//ENTREE:
//SORTIE:
*/

int nbRand(int n_min, int n_max){
//BUT   : generer un nombre aleatoir compris entre min et max
//ENTREE: 2 entiers
//SORTIE: 1 entier

    int nb_Temp=rand()%n_max+n_min;

    return nb_Temp;
}


void intro(){
//BUT   : introduire le jeu au joueur
//ENTREE: /
//SORTIE: /

    char rep;

    printf("\nMonk C, monstre antediluvien, s'est echappe... il rode dans la region.\n");
    printf("Vous etes le responsable d'un groupe de pisteurs. Ceux-ci vous informent des traces qu'ils decouvrent : \n");
    printf("Ou, et surtout depuis quand le monstre est passe par un endroit... Mais attention !\n");
    printf("Monk C est intelligent, et si vous n'y prenez pas garde, il aneantira vos pisteurs un a un...\n");

    printf("\nAfin d'ameliorer votre experience, il est conseille de jouer en plein ecran !\n");

    //reponse du joueur; permet de "mettre l'affichage en pause"
    printf("\n(ENTREE pour commencer la partie)\n");
    scanf("%c", &rep); fflush(stdin);

}


void resultat(int fin, int nb_pisteurs, int tour){
//BUT   : afficher le resultat final du jeu
//ENTREE: la valeur de la fin obtenue, le nombre de pisteurs joues, le nombre de tours ecoules
//SORTIE: /

    system("CLS");

    printf("\n  PARTIE TERMINEE\n\n");

    if(fin==1){ //victoire

        printf("Victoire ! Vous etes parvenus a traquer et mettre fin au monstre !\n");

        if(nb_pisteurs==1){

            printf("Felicitation particulierement pour y etre parvenu avec un seul pisteur !\n");
        }
    } else if(fin==2){

        printf("Dommage, vous avez perdu ! Le monstre a eu raison de tous vos pisteurs...\n");
    }

    printf("La partie a dure en tout %d tours\n", tour);
}


int rejouer(){
//BUT   : proposer une nouvelle partie au joueur
//ENTREE: /
//SORTIE: 1 entier

    int re=0;   //valeur a renvoyer
    char rep;   //stocke la reponse du joueur

    printf("\nSouhaitez-vous rejouer ?\n Oui(o) / Non(n) : ");
    scanf("%c", &rep), fflush(stdin);

    while((rep!='o')&&(rep!='n')){  //saisie invalide

        printf("\nSaisie invalide !\n Oui(o) / Non(n) : ");
        scanf("%c", &rep), fflush(stdin);
    }

    if(rep=='o'){   //le joueur souhaite rejouer

        re=1;
    }

    return re;
}
