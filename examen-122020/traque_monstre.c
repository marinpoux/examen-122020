#include "define.h"

int traque_M(int nb_pisteurs, int morts){
//BUT   : tour du monstre
//ENTREE: nombre de pisteurs total, nombre de pisteurs morts
//SORTIE: le nombre de morts

    phase=2;    //phase du monstre
    char rep;

    //maj de l'etat de blessure du monstre
    if((monkC.blesse>0) && (phase==4)){

        monkC.blesse--;
    }

    morts=chasse(nb_pisteurs, morts);          //verif si pisteur sur case ou autour
    if(morts!=nb_pisteurs){

        deplacement_M();      //monstre lit traces et se déplace

        //reponse du joueur; permet de "mettre l'affichage en pause"
        printf("Le monstre s'est deplace !\n");
        scanf("%c", &rep); fflush(stdin);

        morts=chasse(nb_pisteurs, morts);          //verif pisteur au nouvel emplacement
    }

    return morts;
}


int chasse(int nb_pisteurs, int morts){
//BUT   : verifier la presence de pisteurs a portee du monstre
//ENTREE: le nombre de pisteurs, le nombre de morts
//SORTIE: le nombre de morts

    char rep;    //stocker la saisie du joueur

    affichage(nb_pisteurs, morts, 0);

    printf("Le monstre observe ses alentours...\n");

    for(int i=0;i<nb_pisteurs; i++){
        //concerne uniquement les pisteurs vivants
        if(pisteurs[i].stat=='v'){

            if((monkC.coord.posX==pisteurs[i].coord.posX)&&(monkC.coord.posY==pisteurs[i].coord.posY)){
            //verification case du monstre
                morts=mort_P(i, nb_pisteurs, morts);
            }
            if((monkC.coord.posX==pisteurs[i].coord.posX)&&(monkC.coord.posY-1==pisteurs[i].coord.posY)){
            //verification case au-dessus
                morts=mort_P(i, nb_pisteurs, morts);
            }
            if((monkC.coord.posX-1==pisteurs[i].coord.posX)&&(monkC.coord.posY==pisteurs[i].coord.posY)){
            //verification case a gauche
                morts=mort_P(i, nb_pisteurs, morts);
            }
            if((monkC.coord.posX+1==pisteurs[i].coord.posX)&&(monkC.coord.posY==pisteurs[i].coord.posY)){
            //verification case a droite
                morts=mort_P(i, nb_pisteurs, morts);
            }
            if((monkC.coord.posX==pisteurs[i].coord.posX)&&(monkC.coord.posY+1==pisteurs[i].coord.posY)){
            //verification case en-dessous
                morts=mort_P(i, nb_pisteurs, morts);
            }
        }
    }

    //reponse du joueur; permet de "mettre l'affichage en pause"
    printf("(ENTREE pour fermer le rapport)");
    scanf("%c", &rep); fflush(stdin);

    return morts;
}


int mort_P(int ordre, int nb_pisteurs, int morts){
//BUT   : tuer un pisteur
//ENTREE: l'ordre du pisteur, le nombre de pisteurs, le nombre de morts
//SORTIE: le nombre de morts

    pisteurs[ordre].stat='m';
    morts++;

    printf("Le monstre a trouve le pisteur %d ! Il n'en fait qu'une bouchee !\n", pisteurs[ordre].num);
    printf("Il vous reste %d pisteurs pour traquer le monstre.\n", (nb_pisteurs-morts));

    return morts;
}


void deplacement_M(){
//BUT   : deplacer le monstre
//ENTREE: /
//SORTIE: /

    int fraicheur=0;    //permet de retenir la trache la plus fraiche voisine au monstre
    int traces[4]={0};  //tableau stockant les traces autour du monstre
    int choix=-1;

    coordonnees coord_temp[4];

    monkC.prcdt.posX=monkC.coord.posX;  //retenue des coord avant deplacement
    monkC.prcdt.posY=monkC.coord.posY;

    //attribution des coordonnees temporaires
    coord_temp[0].posX=monkC.coord.posX;   //case au-dessus
    coord_temp[0].posY=monkC.coord.posY-1;
    coord_temp[1].posX=monkC.coord.posX-1; //case a gauche
    coord_temp[1].posY=monkC.coord.posY;
    coord_temp[2].posX=monkC.coord.posX+1; //case a droite
    coord_temp[2].posY=monkC.coord.posY;
    coord_temp[3].posX=monkC.coord.posX;   //case en-dessous
    coord_temp[3].posY=monkC.coord.posY+1;

    //remplissage du tableau
    traces[0]=jeu.traces_P[monkC.coord.posY-1][monkC.coord.posX];   //traces au-dessus
    traces[1]=jeu.traces_P[monkC.coord.posY][monkC.coord.posX-1];   //traces a gauche
    traces[2]=jeu.traces_P[monkC.coord.posY][monkC.coord.posX+1];   //traces a droite
    traces[3]=jeu.traces_P[monkC.coord.posY+1][monkC.coord.posX];   //traces en-dessous

    //verification que les emplacements sont dans le plateau
    if(monkC.coord.posY==0){                    //si monstre colle au bord superieur

        traces[0]=-1;
    } else if(monkC.coord.posX==0){             //si monstre colle au bord gauche

        traces[1]=-1;
    } else if(monkC.coord.posX==COLONNES-1){    //si monstre colle au bord droit

        traces[2]=-1;
    } else if(monkC.coord.posY==LIGNES-1){      //si monstre colle au bord inferieur

        traces[3]=-1;
    }

    //verification et retenue du contenu des cases pour trouver une case appropriee
    for(int i=0;i<4;i++){

        if((traces[i]>0)){
        //uniquement s'il y a des traces dans la case
            if((fraicheur==0)||(fraicheur>traces[i])){
            //si fraicheur n'a pas encore change, ou si superieur a la valeur de la case
                fraicheur=traces[i];
                choix=i;
            }
        }
    }

    //si une case appropriee a ete trouvee
    if(fraicheur>0){
        //attribution de la case contenant les traces les plus fraiches
        monkC.coord.posX=coord_temp[choix].posX;
        monkC.coord.posY=coord_temp[choix].posY;

    } else {
        //si aucune case ne contenait de traces

        int ok=0;
        int n_rand;

        while(ok!=1){

            n_rand=nbRand(0,3);

            if(traces[n_rand]!=-1){ //on recommence si la case choisie n'est pas dans le plateau

                ok=1;
            }
        }

        //attribution de la case selectionnee
        monkC.coord.posX=coord_temp[n_rand].posX;
        monkC.coord.posY=coord_temp[n_rand].posY;
    }
}


int verif_P(int nb_pisteurs, int morts){
//BUT   : determiner s'il reste des pisteurs vivants
//ENTREE: le nombre de pisteurs, le nombre de morts
//SORTIE: un entier (fin)

    int fin=0;

    if(morts==nb_pisteurs){

        fin=2;
    }

    return fin;
}
