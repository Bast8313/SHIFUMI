#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define Pierre 1
#define Feuille 2
#define Ciseaux 3
#define Quitter 0

#define FILENAME "sauvegarde"

// Déclaration des fonctions de base.
void menu();
int choixJoueur(const char *nomJoueur); 
int choixPC();
void afficherResultat(int choixJoueur1, int choixJoueur2, char *nomJoueur1, char *nomJoueur2, int *victoiresJoueur1, int *victoiresJoueur2);

// Fonction pour lire dans un fichier
void lire_score(int *victoiresJoueur1, int *victoiresJoueur2) {
    FILE *file = fopen(FILENAME, "r"); // ouvre le fichier en mode lecture
    if (file == NULL) {
        *victoiresJoueur1 = 0;
        *victoiresJoueur2 = 0;
    }
        fscanf(file, "%d %d", victoiresJoueur1, victoiresJoueur2);
        fclose(file);
}

// Fonction pour sauvegarder le score dans un fichier
void sauvegarder_score(int victoiresJoueur1, int victoiresJoueur2) {
    FILE *file = fopen(FILENAME, "w"); // ouvre le ficghier pour la sauvegarde

    // renvoie un pointeur vers le fichier (file) SI l'ouverture est réussie, ou NULL si elle échoue
    if (file != NULL) {
        fprintf(file, "%d %d", victoiresJoueur1, victoiresJoueur2);
        fclose(file);
    }
}

int main() {

    // Tableaux de caractères pour "stocker" le nom des joueurs.
    char joueur1[20], joueur2[20]; 


    // "enregistre" le choix des joueurs
    int choixJoueur1, choixJoueur2; 

    // Initialisation des victoires à 0.
    int victoiresJoueur1 = 0, victoiresJoueur2 = 0;


    // Initialisation de la génération aléatoire pour la version contre le PC
    srand(time(NULL)); 


    // Fonction pour pouvoir réinitialiser les scores
    char choixReinitialisation[255];
    printf("Voulez-vous réinitialiser les scores ? (O/N) : ");
    fgets(choixReinitialisation, 255, stdin);

    /*if (choixReinitialisation[0] == 'O' || choixReinitialisation[0] == 'o') {
        reinitialiser_score();  // appel de fonction pour Réinitialisation des scores
        victoiresJoueur1 = 0;
        victoiresJoueur2 = 0;
        printf("Scores réinitialisés à zéro.\n");
    } */


    printf("\n---------------------- ShiFuMi ! --------------------\n\n");

    // Demander si le joueur veut jouer contre le PC ou un autre joueur
    char choixMode[255]; // declaration d'un tableau , 
    printf("Tappez 1 pour jouer contre un autre joueur ou 2 pour jouer contre le PC : \n");
    fgets(choixMode, 255, stdin); //recup du choix du mode de jeux
    choixMode[strlen(choixMode)-1] = 0;
    
    // Si le joueur choisit de jouer contre un autre joueur
    if (choixMode[0] == '1') { 
        printf("\nEntrez le nom du joueur 1 : ");// recupération du nom du joueur1
        fgets(joueur1, 20, stdin);
        // Retire le saut de ligne causé par fgets
        joueur1[strlen(joueur1)-1] = 0; 
        
        printf("Entrez le nom du joueur 2 : ");
        // récupération du nom du joueur2
        fgets(joueur2, 20, stdin);
        // Retire le saut de ligne causé par fgets
        joueur2[strlen(joueur2)-1] = 0;  
    } 
    else { 
        printf("Entrez votre nom : ");
        fgets(joueur1, 20, stdin);
        joueur1[strlen(joueur1)-1] = 0;  
        // Retire le saut de ligne causé par fgets
        
        // le nom du joueur 2 devient PC !!!!!AAAHHHHHHHH J AI MIS 24h POUR SAVOIR OU LA FOUTRE CELLE-LAAA HAA X/ 
        strcpy(joueur2, "PC");  

    }

    // Appel de la fonction pour lire dans un fichier
    lire_score(&victoiresJoueur1, &victoiresJoueur2);

    // conditions pour quitter le jeu
    while (1) {
        // pour joueur1
        printf("\n%s ?\n", joueur1);
        choixJoueur1 = choixJoueur(joueur1); // renvoie la valeur choisie par le joueur
        if (choixJoueur1 == 0) {
            printf("\nVous avez décidé de quitter le jeu...\n\n");
            printf("---------------------- GAME OVER ! --------------------\n");
            break; // sorti de la boucle du programme
        }

        // pour joueur 2 ou PC

        if (choixMode[0] == '1') // si c'est contre un autre joueur
        {
            printf("\n%s ?\n", joueur2);
            choixJoueur2 = choixJoueur(joueur2);
        } 
        // si c'est contre le PC
        else { 
            printf("\nLe PC fait son choix...\n");
            choixJoueur2 = choixPC();
        }

        if (choixJoueur2 == 0) {
            printf("---------------------- GAME OVER ! --------------------\n");
            break;
        }

        // appel des fonctions pour l'affichage du résultat et la sauvegarde
        afficherResultat(choixJoueur1, choixJoueur2, joueur1, joueur2, &victoiresJoueur1, &victoiresJoueur2);
        sauvegarder_score(victoiresJoueur1, victoiresJoueur2);
    }

    return 0;
}

// affiche le menu des choix
void menu() {
    printf("1.Pierre\n");
    printf("2.Feuille\n");
    printf("3.Ciseaux\n");
    printf("0.Quitter\n");
}

// fonction qui permet d'obtenir le choix du joueur
int choixJoueur(const char *nomJoueur) {
    int choix;

    char buffer[255];
    memset(buffer, 0, sizeof(buffer));  // Remplis de 0 les 255 octets du tableau

    printf("%s\n", nomJoueur);
    
    while (1) {
        menu();
        fgets(buffer, sizeof(buffer), stdin);
        

        // Conversion de la chaîne de caractères en entier
        choix = atoi(buffer);  

        // quitter la partie si le joueur tape 0
        if (choix == 0) {
            return 0;  
        } 
        // retourne le choix valide
        else if (choix >= 1 && choix <= 3) {
            return choix;  
        } 
        else {
            printf("\nChoix invalide, veuillez recommencer \n\n");
        } 
    }
}

// Fonction pour générer un choix aléatoire pour le PC
int choixPC() {
    return rand() % 3 + 1;// Renvoie un nombre aléatoire entre 1 et 3 (Pierre, Feuille ou Ciseaux)
}

/*Fonction d'affichage des différentes possibilités, résultat du tour et mise à jour des victoires, déclarées au début*/
void afficherResultat(int choixJoueur1, int choixJoueur2, char *nomJoueur1, char *nomJoueur2, int *victoiresJoueur1, int *victoiresJoueur2) {
    printf("\n%s fait ", nomJoueur1);

    // différents cas pour joueur1
    switch (choixJoueur1) {
        case Pierre: printf("Pierre\n"); break;
        case Feuille: printf("Feuille\n"); break;
        case Ciseaux: printf("Ciseaux\n"); break;
    }

    printf("%s fait ", nomJoueur2);

    // différents cas pour joueur2
    switch (choixJoueur2) {
        case Pierre: printf("Pierre\n"); break;
        case Feuille: printf("Feuille\n"); break;
        case Ciseaux: printf("Ciseaux\n"); break;
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
                    (*victoiresJoueur2)++;
                } else {
                    printf("\nPierre > Ciseaux\n");
                    (*victoiresJoueur1)++;
                }
                break;

            // FEUILLE
            case Feuille:
                if (choixJoueur2 == Ciseaux) {
                    printf("\nCiseaux > Feuille\n");
                    (*victoiresJoueur2)++;
                } else {
                    printf("\nFeuille > Pierre\n");
                    (*victoiresJoueur1)++;
                }
                break;
            
            // CISEAUX
            case Ciseaux:
                if (choixJoueur2 == Pierre) {
                    printf("\nPierre > Ciseaux\n");
                    (*victoiresJoueur2)++;
                } else {
                    printf("\nCiseaux > Feuille\n");
                    (*victoiresJoueur1)++;
                }
                break;
        }
    }

    // affichage des victoires
    printf("\nVictoires :\n");
    printf("%s : %d\n", nomJoueur1, *victoiresJoueur1);
    printf("%s : %d\n", nomJoueur2, *victoiresJoueur2);
}
