#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define Pierre 1
#define Feuille 2
#define Ciseaux 3
#define Quitter 0

// Déclaration des fonctions de base.

void menu();
int choixJoueur(const char *nomJoueur);// ---> (const char *nomJoueur) : pointeur vers le tableau de caractère

// Fonction pour les choix et la mises à jour des résultats.
void afficherResultat
(int choixJoueur1,int choixJoueur2, 
char *nomJoueur1, char *nomJoueur2, 
int *victoiresJoueur1, int *victoiresJoueur2); // pointeur pour modifier les valeurs des variables pour les victoires.

int main() {
    // Tableaux de caractères pour stocker le nom des joueurs.
    char joueur1[20], joueur2[20]; 

    // "enregistre" le choix des joueurs
    int choixJoueur1, choixJoueur2; 

    // Initialisation des victoires à 0.
    int victoiresJoueur1 = 0, victoiresJoueur2 = 0;

    //srand(time(NULL)); // Initialisation de la génération aléatoire pour la version contre le PC

    printf("---------------------- ShiFuMi ! --------------------\n\n");
    
    // Demander les noms des joueurs
    printf("Entrez le nom du joueur 1 : ");
    // recupération du nom du joueur1
    fgets(joueur1, 20, stdin);
    // Retire le saut de ligne causé par fgets
    joueur1[strlen(joueur1)-1] = 0;  

    printf("Entrez le nom du joueur 2 : ");
    // recupération du nom du joueur2
    fgets(joueur2, 20, stdin);
    // Retire le saut de ligne causé par fgets
    joueur2[strlen(joueur2)-1] = 0; 
    
    //system("clear");  

    // Condition pour quitter le jeu
    while (1) {
        // Pour Joueur 1 
        printf("\n%s ?\n", joueur1);
        choixJoueur1 = choixJoueur(joueur1);
        if (choixJoueur1 == 0) {
            printf("\nVous avez décidé de quitter le jeux...\n\n");
            printf("---------------------- GAME OVER ! --------------------\n");
            break;
        }
        // Pour Joueur 2
        printf("\n%s ?\n", joueur2);
        choixJoueur2 = choixJoueur(joueur2);
        if (choixJoueur2 == 0) {
            printf("---------------------- GAME OVER ! --------------------\n");
            break;
        }
        // Affichage du résultat du tour
        afficherResultat(choixJoueur1, choixJoueur2, joueur1, joueur2, &victoiresJoueur1, &victoiresJoueur2);
    }

    return 0;
}

// Affiche le menu des choix pour chaque joueur
void menu() {
    printf("1.Pierre\n");
    printf("2.Feuille\n");
    printf("3.Ciseaux\n");
    printf("0.Quitter\n");
}

// Fonction qui permettent d'obtenir le choix du joueur

int choixJoueur(const char *nomJoueur) {
    int choix;
    char buffer[255];
    memset(buffer,0,sizeof(buffer)); // Remplis de 0 les 255 octets du tableau buf

    while (1) {
        menu();
        
        fgets(buffer, sizeof(buffer), stdin);

        // Conversion de la chaîne de caractères en entier
        choix = atoi(buffer);  

        // Quitter la partie si le joueur tape 0
        if (choix == 0) {
            return 0;  
        } 
        // Retourner le choix valide 
        else if (choix >= 1 && choix <= 3) {
            return choix;  
        } 
        else {
            printf("\nChoix invalide, veuillez recommencer \n\n");
        } 
    }
}

/*Fonction d'affichage des différentes possibilitées, résultat du tour et mise à jour des victoires, déclarées au début*/ 
void afficherResultat(int choixJoueur1, int choixJoueur2, char *nomJoueur1, char *nomJoueur2, int *victoiresJoueur1, int *victoiresJoueur2) 
{
    printf("\n%s fait ", nomJoueur1);

    // différents cas pour joueur1
    switch (choixJoueur1) {
        case Pierre:
            printf("Pierre\n");
            break;
        case Feuille:
            printf("Feuille\n");
            break;
        case Ciseaux:
            printf("Ciseaux\n");
            break;
    }

    printf("%s fait ", nomJoueur2);

    // différents cas pour joueur2
    switch (choixJoueur2) {
        case Pierre:
            printf("Pierre\n");
            break;
        case Feuille:
            printf("Feuille\n");
            break;
        case Ciseaux:
            printf("Ciseaux\n");
            break;
    }

    // Comparaison des choix et détermination du gagnant
    if (choixJoueur1 == choixJoueur2) {
        printf("\nEgalité !\n");
    } 
    else {
        switch (choixJoueur1) {

            // PIERRE
            case Pierre:
                if (choixJoueur2 == Feuille) {
                    printf("\nFeuille > Pierre\n");
                    printf("%s à GAGNE !\n", nomJoueur2);
                    (*victoiresJoueur2)++;
                } 
                else {
                    printf("\nPierre > Ciseaux\n");
                    printf("%s à GAGNE !\n", nomJoueur1);
                    (*victoiresJoueur1)++;
                }
                break;

            // FEUILLE   
            case Feuille:
                if (choixJoueur2 == Ciseaux) {
                    printf("\nCiseaux > Feuille\n");
                    printf("%s à GAGNE !\n", nomJoueur2);
                    (*victoiresJoueur2)++;
                } else {
                    printf("\nFeuille > Pierre\n");
                    printf("%s à GAGNE !\n", nomJoueur1);
                    (*victoiresJoueur1)++;
                }
                break;

            // CISEAUX    
            case Ciseaux:
                if (choixJoueur2 == Pierre) {
                    printf("\nPierre > Ciseaux\n");
                    printf("%s à GAGNE !\n", nomJoueur2);
                    (*victoiresJoueur2)++;
                } else {
                    printf("\nCiseaux > Feuille\n");
                    printf("%s à GAGNE !\n", nomJoueur1);
                    (*victoiresJoueur1)++;
                }
                break;
            default:
                break;
        }
    }

    // Affichage des victoires
    printf("\nVictoires :\n");
    printf("%s : %d\n", nomJoueur1, *victoiresJoueur1);
    printf("%s : %d\n", nomJoueur2, *victoiresJoueur2);

    return;
}
