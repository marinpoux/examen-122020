#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

//LIB
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


//CONSTANTES
//**dimensions du plateau**
    #define COLONNES 29
    #define LIGNES 14
//**pisteurs**
    #define P_NB_MAX 10     //nombre maximum de pisteurs
    #define P_PM_MAX 4      //distance de deplacement max
    #define TIR_PROBA 40    //probabilite de reussir un tir
        //0: probabilite nulle (victoire impossible)
        //100: reussite assuree (easy mode)
    #define DOMMAGES 1      //dommages causes au monstre si tir reussi
//**monstre**
    #define M_PV 4          //points de vie du monstre
    #define TOURS_BLESSE 4  //nombre de tours ou le monstre est blesse et laisse une trace
    #define M_TRACES 16     //persistance des traces laissees par le monstre
    #define M_PM 1          //distance de deplacement du monstre


//TYPES
//**general**
    typedef enum etat{v=1,m}etat;
        //v: vivant
        //m: mort

    typedef struct coordonnees{
        int posX;   //colonne
        int posY;   //ligne
    }coordonnees;

//**pisteur**
    typedef struct pisteur{

        int num;            //nom du pisteur : numero suivant l'ordre de création
        coordonnees coord;  //position du pisteur
        char icone;         //representation du pisteur sur le plateau
            //'P': pisteur inactif
            //'!': pisteur en phase de rapport
            //'?': en attente d'ordre de déplacement
        etat stat;          //etat du pisteur (mort ou vif)
            //si etat=m, le pisteur n'est plus affiche ni joue
    }pisteur;

//**monstre**
     typedef struct monstre{

        coordonnees coord;  //position du monstre
        coordonnees prcdt;  //position du monstre au tour precedent
        int pv;             //points de vie du monstre
        int blesse;         //si different de 0, la case ou etait le monstre affiche '.'
     }monstre;

//**plateau**
    typedef struct plateau{

        int traces_P[LIGNES][COLONNES];     //tableau contenant les traces laissees par les pisteurs
        int traces_M[LIGNES][COLONNES];     //tableau contenant les traces laissees par le monstre
        char tab_plateau[LIGNES][COLONNES]; //tableau a afficher; contient positions des pisteurs
    }plateau;


//VARIABLES GLOBALES parce que je m'emmelle trop les pinceaux
    plateau jeu;                    //plateau contenant le jeu
    pisteur pisteurs[P_NB_MAX-1];   //pisteurs (peut contenir jusqu'a P_NB_MAX pisteurs)
    monstre monkC;                  //monstre

    int phase;    //phase de jeu en cours
        //0: intro+initialisation
        //1: placement
        //2: traque-rapport
        //3: traque-deplacement
        //4: monstre


//PROTOTYPE

int main();         //main.c
    void intro();   //methodes.c
    void init();    //init.c
        void init_plateau();
            void init_tab(char var, int d, char c, int tab_int[LIGNES][COLONNES],
                          char tab_char[LIGNES][COLONNES]);
        void init_pisteurs();
        void init_monstre();

    int placement(int nb_pisteurs, int morts);  //mise_en_place.c
        void placement_p(int nb_pisteurs);
            int ajout_p(int nb_pisteurs);
        void placement_m();

    int traque_P(int nb_pisteurs, int morts);   //traque_pisteur.c
        int rapport(int ordre, int nb_pisteurs, int morts);
            int essai_tir();
                int verif_M();
        void deplacement_P(int ordre, int nb_pisteurs, int morts);
            int dist_deplacement(char dir, char neg, char pos, int coord);

    int traque_M(int nb_pisteurs, int morts);   //traque_monstre.c
        int chasse(int nb_pisteurs, int morts);
            int mort_P(int ordre, int nb_pisteurs, int morts);
        void deplacement_M();

    int verif_P(int nb_pisteurs, int morts);    //traque_monstre.c

    void resultat(int fin, int nb_pisteurs, int tour);   //methodes.c

    int rejouer();      //methodes.c


int nbRand(int n_min, int n_max);   //methodes.c

void maj_plateau(int nb_pisteurs);  //mise_a_jour.c
void maj_usure();                   //mise_a_jour.c
void maj_traces(int nb_pisteurs);   //mise_a_jour.c

void affichage(int nb_pisteurs, int morts, int ordre); //affichage.c
    void regles();
    void affiche_plateau();

//**debug.c**
void affiche_traces();
void testswitch();

#endif // DEFINE_H_INCLUDED
