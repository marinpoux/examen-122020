#include "define.h"

int traque_P(int nb_pisteurs, int morts){
//BUT   : tour du joueur
//ENTREE: nombre de pisteurs total, nombre de pisteurs morts
//SORTIE: 1 entier (fin)

    int fin=0;  //0: partie en cours; valeur depend de victoire ou defaite

    phase=2;    //phase de traque-rapport

    //boucle repetee pour chaque pisteur cree (nb_pisteurs)
    for(int i=0;i<nb_pisteurs;i++){
        //uniquement si le monstre est encore vivant!
        //ET si le pisteur est encore vivant!!
        if((monkC.pv>0) && (pisteurs[i].stat=='v')){
        //if(fin==0){

            fin=rapport(i, nb_pisteurs, morts); //chaque pisteur fait son rapport
        }
    }

    phase=3;    //phase de traque-deplacement

    //boucle repetee pour chaque pisteur cree (nb_pisteurs)
    for(int i=0;i<nb_pisteurs;i++){
        //uniquement si le monstre est encore vivant!
        //ET si le pisteur est encore vivant!!
        if((monkC.pv>0) && (pisteurs[i].stat=='v')){
        //if(fin==0){

            deplacement_P(i, nb_pisteurs, morts);       //chaque pisteur se deplace
            maj_traces(nb_pisteurs);    //mise a jour des traces des pisteurs
        }
    }

    return fin;
}


int rapport(int ordre, int nb_pisteurs, int morts){
//BUT   : rapporter le contenu des 8 cases autour du pisteur
//ENTREE: l'ordre du pisteur, le nombre de pisteurs
//SORTIE: 1 entier (fin)

    int fin=0;

    int tir=0;

    int x=pisteurs[ordre].coord.posX;   //pos x du pisteur en cours
    int y=pisteurs[ordre].coord.posY;   //pos y du pisteur en cours

    int tab_num[8]={1,2,3,4,6,7,8,9};      //"noms" des cases alentoures au pisteur
    int tab_rapport[8]={0,0,0,0,0,0,0,0};   //tableau contenant les contenu des cases alentoures

    int rien=0;
    int tab_rien[8]={0,0,0,0,0,0,0,0};

    //modification de l'icone du pisteur + affichage
    pisteurs[ordre].icone='!';
    affichage(nb_pisteurs, morts, pisteurs[ordre].num);

    tab_rapport[0]=jeu.traces_M[y-1][x-1];
    tab_rapport[1]=jeu.traces_M[y-1][x];
    tab_rapport[2]=jeu.traces_M[y-1][x+1];
    tab_rapport[3]=jeu.traces_M[y][x-1];
    tab_rapport[4]=jeu.traces_M[y][x+1];
    tab_rapport[5]=jeu.traces_M[y+1][x-1];
    tab_rapport[6]=jeu.traces_M[y+1][x];
    tab_rapport[7]=jeu.traces_M[y+1][x+1];

    for(int i=0;i<8;i++){

        if((tab_rapport[i]==0)||(tab_rapport[i]>M_TRACES)){

            tab_rien[i]=tab_num[i];
            rien++;
        }
    }

    for(int i=0;i<rien;i++){

        if(i==0){

            printf("Rien en %d", tab_rien[i]);
        } else {

            printf(", %d", tab_rien[i]);
        }
    }

    printf("\n");

    for(int i=0;i<8;i++){

        if(tab_rapport[i]==M_TRACES){

            printf("MONSTRE EN %d !!\n", tab_num[i]);

            tir=1;
        }
        else if((tab_rapport[i]<M_TRACES)&&(tab_rapport[i]!=0)){

            printf("%d en %d\n", tab_rapport[i], tab_num[i]);
        }
    }

    if(tir==1){

        fin=essai_tir();
    }

    char rep;    //reponse du joueur; permet de "mettre l'affichage en pause"
    printf("(ENTREE pour fermer le rapport)");
    scanf("%c", &rep); fflush(stdin);

    //modification de l'icone du pisteur + affichage
    pisteurs[ordre].icone='P';

    return fin;
}


int essai_tir(){
//BUT   : tirer sur le monstre
//ENTREE:
//SORTIE:

    char rep=' ';    //stocker la saisie du joueur
    int fin=0;

    printf("Vous pouvez essayer de tirer sur le monstre. Voulez-vous tenter ?\n Oui(o) / Non(n) : ");
    scanf("%c", &rep); fflush(stdin);

    //verification saisie
    while((rep!='o')&&(rep!='n')){

        printf("Saisie invalide !\n Oui(o) / Non(n) : ");
        scanf("%c", &rep); fflush(stdin);
    }

    if(rep=='o'){   //utilisateur choisi de tirer

        int essai=nbRand(0, TIR_PROBA);

        if(essai>TIR_PROBA){    //valeur tiree superieure a probabilite de toucher

            printf("Dommage, le tir a rate !\n");
        } else {

            printf("Le tir a touche ! Le monstre perd %d PV, il lui en reste %d\n", DOMMAGES, monkC.pv);

            monkC.pv=monkC.pv-DOMMAGES; //appliquer les dommages causes
            monkC.blesse=TOURS_BLESSE;  //indiquer que le monstre vient d'etre blesse

            fin=verif_M();
        }

        //reponse du joueur; permet de "mettre l'affichage en pause"
        printf("(ENTREE pour fermer le rapport)");
        scanf("%c", &rep); fflush(stdin);
    }

    return fin;
}


int verif_M(){
//BUT   : verifier l'etat du monstre
//ENTREE: /
//SORTIE: 1 entier (fin)

    if(monkC.pv<0){

        return 1;
    } else {

        return 0;
    }
}


void deplacement_P(int ordre, int nb_pisteurs, int morts){
//BUT   : deplacer un pisteur
//ENTREE: l'ordre du pisteur, le nombre de pisteurs, le nombre de pisteurs morts
//SORTIE: /

    char dir;       //direction du pisteur, saisie par l'utilisateur
    int dist;       //distance de deplacement, saisie par l'utilisateur
    int dist_max;   //distance max que le pisteur peut parcourir

    //modification de l'icone du pisteur + affichage
    pisteurs[ordre].icone='?';
    affichage(nb_pisteurs, morts, pisteurs[ordre].num);

    //selection de la direction de deplacement du pisteur
    printf("Dans quelle direction souhaitez-vous deplacer le pisteur?\n Haut(h) / Bas(b) / Gauche(g) / Droite(d) : ");
    scanf("%c", &dir); fflush(stdin);

    //verification saisie
    while((dir!='h')&&(dir!='b')&&(dir!='g')&&(dir!='d')){

        printf("Saisie invalide !\n Haut(h) / Bas(b) / Gauche(g) / Droite(d) : ");
        scanf("%c", &dir); fflush(stdin);
    }

    //determiner la distance max de deplacement du pisteur, selon sa position et la direction du deplacement
    if((dir=='g')||(dir=='d')){

            dist_max=dist_deplacement(dir, 'g', 'd', pisteurs[ordre].coord.posX);
        } else {

            dist_max=dist_deplacement(dir, 'h', 'b', pisteurs[ordre].coord.posY);
        }

    //selection de la distance de deplacement du pisteur
    printf("De combien de cases souhaitez-vous deplacer le pisteur ?\n 0 a %d : ", dist_max);
    scanf("%d", &dist); fflush(stdin);

    //verification saisie
    while((dist<0)&&(dist>dist_max)){

        printf("Saisie invalide !\n 0 a %d : ", dist_max);
        scanf("%d", &dist); fflush(stdin);
    }

    //deplacement "negatif" selon direction du deplacement
    if((dir=='h')||(dir=='g')){

        dist=dist*(-1);
    }

    //application du deplacement au coordonnees du pisteur
    if((dir=='g')||(dir=='d')){

        pisteurs[ordre].coord.posX=pisteurs[ordre].coord.posX+(dist);
    } else {

        pisteurs[ordre].coord.posY=pisteurs[ordre].coord.posY+(dist);
    }

    //modification de l'icone du pisteur + affichage
    pisteurs[ordre].icone='P';
}


int dist_deplacement(char dir, char negf, char posf, int coord){
//BUT   : determiner la distance maximale que le pisteur peut parcourir selon sa position et la direction de deplacement
//ENTREE: la direction de déplacement (axe), les deux directions sur cet axe, la coord du pisteur sur cet axe (x ou y)
    //negf: 'h' ou 'g'
    //posf: 'b' ou 'd'
    //coord: posX ou posY
    //le tout en accord avec la dir entree!!
//SORTIE: la distance maximale que le pisteur peut parcourir, dans ce sens, a cette position

    int dist_max;   //distance max que le pisteur pourra parcourir

    int dimension;  //la dimension consideree (colonne ou ligne) dependra de l'orientation choisie
        if((dir=='g')||(dir=='d')){
            dimension=COLONNES;
        } else {
            dimension=LIGNES;
        }

    if((dir==negf)&&(coord<(P_PM_MAX-1))){  //calcul de dist_max par rapport au bord concerne

        dist_max=coord;

    } else if ((dir==posf)&&(coord>=(dimension-P_PM_MAX))){

        dist_max=dimension-coord-1;
    } else {

        dist_max=P_PM_MAX;
    }

    return dist_max;
}
