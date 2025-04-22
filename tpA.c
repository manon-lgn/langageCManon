#include <stdio.h> //pour les entrées/sortie(printf,scanf)
#include <stdlib.h> //pour utilisé rand(nbr aléatoire) et srand (initialiser rand)
#include <time.h> //pour gérer l'heure, nombres aléatoire
#include <string.h> //pour les chaînes de caractères
#define FICHIER_SCORES "scores.txt" //nom du fichier où il y a les scores

//appel de toutes les fonctions utilisées dans le programme
void Addition(int *score,const char *nom);//void :retourne rien, fait une action
void Soustraction(int *score);
void Multiplication(int *score);
void Divisions(int *score);
void AfficherTableMultiplication();
void JeuTableMultiplication(int *score);
void SauvegarderScore(const char *nom, int score);
void AfficherScores();
int RecupererScore(const char *nom);//renvoie une valeur entière(score =...)
void AfficherDernierScore(const char *nom);
void JeuNombreEnLettre(int *score);
void JeuConversionLongueur(int *score);


int main(){
 int i,choix;
 int score =0;
 char nom[50];

 srand (time(NULL));//initialise le générateur de nombres aléatoires(Donne une graine différente à chaque exécution grâce à l'heure actuelle)

 //Demande le nom du joueur
 printf("Entrez votre nom : ");
    scanf("%s", nom);
    //récupère le score précedent
    score = RecupererScore(nom);
    printf("votre score est de : %d\n", score);

 do {
        printf("\n+---------------------------------+\n");
        printf("|1 : Addition                       |\n");
        printf("|2 : Soustraction                   |\n");
        printf("|3 : Multiplication                 |\n");
        printf("|4 : Tables des multiplications     |\n");
        printf("|5 : Divisions                      |\n");
        printf("|6 : Jeu tables                     |\n");
        printf("|7 : Ecriture des grands nombres    |\n");
        printf("|8 : Conversion des longueurs       |\n");
        printf("|0 : Sortir du jeu                  |\n");
        printf("+-----------------------------------+\n");
        printf("Votre score actuel (%s) : %d\n", nom, score);//affiche le score
        printf("Quel est votre choix ? ");
        scanf("%d", &choix);

        //appelle les fonctions selon le choix de l'utilisateur
        switch (choix) {
            case 1: Addition(&score,nom); break;
            case 2: Soustraction(&score);break;
            case 3: Multiplication(&score);break;
            case 4: AfficherTableMultiplication();break;
            case 5: Divisions(&score);break;
            case 6: JeuTableMultiplication(&score);break;
            case 7: JeuNombreEnLettre(&score); break;
            case 8: JeuConversionLongueur(&score); break;
            case 0: printf("Merci de votre visite. Votre score est de %d points.\n", score);break;
            default:printf("Choix invalide\n");
        }
    } while (choix != 0);

    //sauvegarde le score à la fin
    SauvegarderScore(nom, score);

    //question bonus: permet d'afficher tous les scores de tous les joueurs ou uniquement le dernier
     char reponse;
    printf("Voulez-vous voir tous les scores ? (O/N) : ");
    scanf(" %c", &reponse);

    if (reponse == 'O' || reponse == 'o') {
        AfficherScores();
    } else {
        AfficherDernierScore(nom);
    }

    return 0;
}


void Addition(int *score, const char *nom) {
    int nb1, nb2, reponse, essais =0, resultat;
    nb1 = rand() % 101,//génération des nombres aléatoires
    nb2 = rand() % 101,
    resultat = nb1 + nb2;

    do {
        essais++;//agrémente l'essai de 1 si c'est faux
        printf("\nCombien fait %d + %d ? ", nb1, nb2);
        scanf("%d", &reponse);

        if (reponse == resultat) {
            if (essais == 1) {//donne les points attribuer en fonction du nombres d'essais
                printf("Bravo +10 points\n");
                (*score) += 10;
            } else if (essais == 2) {
                printf("Correct +5 points\n");
                (*score) += 5;
            } else {
                printf("Correct +1 point\n");
                (*score) += 1;
            }
            //sauvegarde le score
            SauvegarderScore(nom, *score);
            return;// on quitte la fonction ici si la réponse est correcte (rien à la fin du return car c'est une fonction qui ne retourne rien)
        } else {
            printf("Mauvaise reponse\n");
        }
    } while (essais < 3);
}

void Soustraction(int *score){
    int nb1, nb2, resultat, reponse, essais =0;
    nb1 = rand() % 101;//génère les nombres aléatoires
    nb2 = rand() % 101;
    //s'assure que nb1 soit plus grand que nb2 pour ne pas avoir de résultat négatif
    if (nb1 < nb2) {
        int temp = nb1;
        nb1 = nb2;
        nb2 = temp;
    }
    resultat = nb1 - nb2;
    printf("\nCombien fait %d - %d ? ", nb1, nb2);
    printf("\nEntrez le resultat : ");
    //permet au joueur d'avoir 3 essais
    while (essais < 3) {
        printf("Essai %d : ", essais + 1);
        scanf("%d", &reponse);

        //attribue les points en fonction du nombre d'essais
        if (reponse == resultat) {
            if (essais == 0) {
                *score += 10;
                printf("Bravo +10 points.\n");
            } else if (essais == 1) {
                *score += 5;
                printf("Correct +5 points.\n");
            } else {
                *score += 1;
                printf("Correct +1 point.\n");
            }
            return;// on quitte la fonction ici si la réponse est correcte
        } else {
            printf("Mauvaise reponse.\n");
        }
        essais++; //incrémente le nombre d'essais
    }
}

void Multiplication(int *score) {
    int nb1, nb2, resultat, reponse, essais=0;
    nb1 = rand() % 101;//génère nombres aléatoires
    nb2 = rand() % 101;
    resultat = nb1 * nb2;
    printf("\nCombien fait %d x %d ? ", nb1, nb2);
    printf("\nEntrez le resultat : ");
    //le joueur a 3 essais
   while (essais < 3) {
        printf("Essai %d : ", essais + 1);
        scanf("%d", &reponse);
        //attribue les points en fonction du nombre d'essais
        if (reponse == resultat) {
            if (essais == 0) {
                *score += 10;
                printf("Bravo +10 points.\n");
            } else if (essais == 1) {
                *score += 5;
                printf("Correct +5 points.\n");
            } else {
                *score += 1;
                printf("Correct +1 point.\n");
            }
            return;// on quitte la fonction ici si la réponse est correcte
        } else {
            printf("Mauvaise reponse.\n");
        }
        essais++;
    }
}

void Divisions(int *score){
    int nb2, nb1, resultat, reponse, essais=0;

    // Génère une division sans reste en choisissant un multiple
    nb2 = rand() % 10 + 1;   // Diviseur entre 1 et 10
    int multiple = rand() % 10 + 1; //multiplicateur entre 1 et 10(permet de créer nb1 comme un multiple de nb2)
    nb1 = nb2 * multiple;//multiplie les deux pour créer un dividende (le nombre à diviser)
    resultat = nb1 / nb2;//fait la division entière(faire tout ça pour éviter les virgules et que donc ça tombe juste)
    printf("\nCombien fait %d / %d ? ", nb1, nb2);
    printf("\nEntrez le resultat : ");
    // Le joueur a 3 essais
    while (essais < 3) {
        printf("Essai %d : ", essais + 1);
        scanf("%d", &reponse);
        //attribue les points en fonction du nombre d'essais
        if (reponse == resultat) {
            if (essais == 0) {
                *score += 10;
                printf("Bravo +10 points.\n");
            } else if (essais == 1) {
                *score += 5;
                printf("Correct +5 points.\n");
            } else {
                *score += 1;
                printf("Correct +1 point.\n");
            }
            return;// on quitte la fonction ici si la réponse est correcte
        } else {
            printf("Mauvaise reponse.\n");
        }
        essais++;
    }
}

void AfficherTableMultiplication() {
    int n;
    do {
        // Demande à l'utilisateur un nombre entre 1 et 10
        printf("\nChoisissez une table de multiplication (entre 1 et 10) : ");
        scanf("%d", &n);
        if (n < 1 || n > 10) {
            printf("Erreur. Veuillez entrer un nombre entre 1 et 10.\n");
        }
    } while (n < 1 || n > 10);
    // Affiche la table choisie
    printf("\nTable de multiplication de %d :\n", n);
    for (int i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", n, i, n * i);
    }
}

void JeuTableMultiplication(int *score) {
    int n, reponse, correct = 1, essais;
    // Choix de la table entre 1 et 10
    do {
        printf("\nChoisissez une table de multiplication (entre 1 et 10) : ");
        scanf("%d", &n);
        if (n < 1 || n > 10) {
            printf("Erreur ! Veuillez entrer un nombre entre 1 et 10.\n");
        }
    } while (n < 1 || n > 10);
    printf("\nExercice : Donnez les resultats de la table de %d\n", n);
    // Pour chaque ligne de la table écire le "nbr x nbr"
    for (int i = 1; i <= 10; i++) {
        essais = 0;
        printf("%d x %d = ? ", n, i);
        //le joueur a 3 essais
        while (essais < 3) {
            printf("Essai %d : ", essais + 1);
            scanf("%d", &reponse);
            //attribue les points en fonction du nombre d'essais
            if (reponse == n * i) {
                if (essais == 0) {
                    *score += 10;
                    printf("Gagne +10 points\n");
                } else if (essais == 1) {
                    *score += 5;
                    printf("Correct +5 points\n");
                } else {
                    *score += 1;
                    printf("Correct +1 point\n");
                }
                break;// sort de la BOUCLE WHILE uniquement(permet de continuer la boucle for pour les autres opérations)
            } else {
                printf("Mauvaise reponse.\n");
            }
            essais++;
        }

        if (essais == 3) {
        }
    }
}




void SauvegarderScore(const char *nom, int score) {
    FILE *f = fopen(FICHIER_SCORES, "a");//ouvrir le fichier en mode ajout
    if (f == NULL) {//si le fichier n’a pas pu être ouvert alors fopen retourne null
        printf("Erreur lors de l'ouverture du fichier\n");
        return;//arrète la fonction ici si il y a un problème
    }

    time_t now = time(NULL);//récupère l'heure
    struct tm *t = localtime(&now);//récupère la date

    // Écrit la ligne dans le fichier : nom date heure score
    fprintf(f, "%s %02d/%02d/%04d %02d:%02d:%02d %d\n",//02: entier sur 2 lignes. 04: entier sur 4 lignes
            nom, t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,//jour du mois 1 à 31, mois (ajout de 1 car janvier = 0 en C), année (car tm_year = nombre d’années depuis 1900 jusqu'a maintenant)
            t->tm_hour, t->tm_min, t->tm_sec, score);

    fclose(f);//ferme le fichier
    printf("Score sauvegarder avec succes\n");
}

void AfficherScores() {
    FILE *f = fopen(FICHIER_SCORES, "r");//ouverture du fichier en lecture
    if (f == NULL) {
        printf("Aucun score enregistre pour le moment.\n");
        return;//arrêt si erreur
    }

    char ligne[100];// pour stocker chaque ligne du fichier
    printf("\n--- Scores enregistres ---\n");
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
    //fonction qui lit une ligne du fichier f et la stocke dans la variable ligne. (sizeof(ligne)=La taille maximale à lire)Si il ya encore des lignes a lire alors la boucle continue
        printf("%s", ligne); // Affiche chaque ligne
    }
    fclose(f);//ferme le fichier
}

int RecupererScore(const char *nom) {
    FILE *f = fopen(FICHIER_SCORES, "r");//ouvrir le fichier score
    if (f == NULL) {//s'il n'apparaît pas on retourne zero
        return 0;
    }

    char nomFichier[50];
    int score = 0, dernierScore = 0;
    char date[20], heure[20];

    while (fscanf(f, "%s %s %s %d", nomFichier, date, heure, &score) == 4) { //Boucle qui lit chaque ligne du fichier(4 lignes)
        if (strcmp(nomFichier, nom) == 0) {
            dernierScore = score;//on met a jour si c'est le bon nom
        }
    }

    fclose(f);//On ferme le fichier une fois que la lecture est terminée
    return dernierScore;//retourne le dernier score
}

void AfficherDernierScore(const char *nom) {
    FILE *f = fopen(FICHIER_SCORES, "r");// Lecture du fichier
    if (f == NULL) {//verifie si on peut l'ouvrir
        printf("Aucun score enregistre pour le moment.\n");
        return;//stop si erreur
    }

    char nomFichier[50];
    int score = 0, dernierScore = 0;
    char date[20], heure[20];
    while (fscanf(f, "%s %s %s %d", nomFichier, date, heure, &score) == 4) {//Boucle qui lit chaque ligne du fichier(4 lignes)
        if (strcmp(nomFichier, nom) == 0) {// Compare le nom dans le fichier au nom
            dernierScore = score;//on met a jour si c'est le bon nom
        }
    }

    fclose(f);//On ferme le fichier

    if (dernierScore == 0) {//le dernier score ne correspond à aucun nom
        printf("Aucun score trouvé");
    } else {
        printf("\n--- Score de %s ---\n", nom);
        printf("Date : %s %s\n", date, heure);
        printf("Score : %d\n", dernierScore);
    }
}

void JeuNombreEnLettre(int *score) {
    const char *lettres[] = {
        "mille cent vingt",
        "quatre mille deux cent",
        "dix mille cinq",
        "quarante-deux mille cent dix",
        "cent mille",
        "deux cent trente mille",
        "quatre cent mille trente",
        "neuf cent quatre-vingt-dix neuf mille neuf cent quatre-vingt-dix neuf"
    };

    int chiffres[] = {1120, 4200, 10005, 42110, 100000, 230000, 400030, 999999};//valeurs présentes dans le tableau
    int taille = sizeof(chiffres) / sizeof(int);//le nombre d’éléments dans le tableau (divise la taille totale du tableau par la taille(sizeof) d’un seul élément)

    int indice = rand() % taille;  // Choisit un nombre au hasard présent dans le tableau
    int reponse;
    int essais = 0;

    printf("\nEcris le nombre suivant en chiffres :\n%s\n", lettres[indice]);
    // L'utilisateur a 3 essais pour répondre
    do {
        printf("Entrer le resultat : ");
        printf ("Essai %d : ", essais + 1);
        scanf("%d", &reponse);
        essais++;

        if (reponse == chiffres[indice]) {
            if (essais == 1) {
                printf("Bravo +10 points\n");
                *score += 10;
            } else if (essais == 2) {
                printf("Correct +5 points\n");
                *score += 5;
            } else {
                printf("Correct +1 point\n");
                *score += 1;
            }
            return;// on quitte la fonction ici si la réponse est correcte
        } else {
            printf("Mauvaise reponse.\n");
        }
    } while (essais < 3);
}

void JeuConversionLongueur(int *score) {
    const char *unites[] = {"mm", "cm", "dm", "m", "dam", "hm", "km"};//Déclare un tableau de chaînes de caractères avec chaîne est constante (non modifiable) et chaîne est un pointeur vers une suite de caractères
    double facteurs[] = {0.001, 0.01, 0.1, 1.0, 10.0, 100.0, 1000.0};//éléments du tableau
    int nb_unites = 7;//Nombre total d’unités utilisé pour faire des choix aléatoires(double pour les nombres à virgule)

    int indice_source = rand() % nb_unites;//unité de départ (source)
    int indice_cible;//unité d'arrivée (cible)

    // S'assurer que les deux unités soient différentes
    do {
        indice_cible = rand() % nb_unites;
    } while (indice_cible == indice_source);

    int valeur = rand() % 101;//choisit un nbr aléatoire

    // Calcul de la bonne réponse(Conversion : source, mètre un,ité cible)
    double valeur_en_m = valeur * facteurs[indice_source];//conversion en mètres
    double valeur_cible = valeur_en_m / facteurs[indice_cible];//conversion en unité cible (demandée)

    int reponse_user;
    int essais = 0;
    int bonne_reponse = (int)(valeur_cible + 0.5); // arrondi pour éviter les erreurs

    printf("\nConvertis : %d %s = ? %s\n", valeur, unites[indice_source], unites[indice_cible]);
    // 3 essais pour convertir correctement
    do {
        printf("Entrer le resultat : ");
        printf("Essai %d : ", essais + 1);
        scanf("%d", &reponse_user);
        essais++;
        //attribue les points en fonction du nombre d'essais
        if (reponse_user == bonne_reponse) {
            if (essais == 1) {
                printf("Bravo +10 points\n");
                *score += 10;
            } else if (essais == 2) {
                printf("Correct +5 points\n");
                *score += 5;
            } else {
                printf("Correct +1 point\n");
                *score += 1;
            }
            return;// on quitte la fonction ici si la réponse est correcte
        } else {
            printf("Mauvaise reponse.\n");
        }
    } while (essais < 3);
}
