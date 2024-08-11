#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


/* Renvoie le nom du fichier contenant les données nécessaires
pour dessiner le caractère c.
Renvoie NULL si le caractère n'est pas un espace, une lettre, ou un chiffre.*/
char* img_filename(char c){
    char* filename = malloc(20*sizeof(char));
    filename[0] = '\0';
    strcat(filename,"lettres/"); //Pour accéder au fichier lettres
    filename[8] = c;
    filename[9] = '\0';
    bool char_chiffre = (48<=c && c<=57); //Booléen indiquant si le caractère est un chiffre (En utilisant une table ASCII)
    bool char_lettre_min = (97<=c && c<=122); //Booléen indiquant si le caractère est une lettre miniscule
    bool char_lettre_maj = (65<=c && c<=90);
    if( c==0 ||  char_chiffre || char_lettre_min){
        strcat(filename, ".txt");
        return filename;
    }
    else if(char_lettre_maj){
        filename[9] = c;
        filename[10] = '\0';
        strcat(filename, ".txt");
        return filename;
    }
    else{
        return NULL;
    }
}

/* Affiche la matrice G de n lignes et m colonnes par blocs de K colonnes.
Par exemple, si G est la matrice suivante:
AAABBBCCC
AAABBBCCC
alors print_bloc(G, 2, 9, 5) affichera:
AAABB
AAABB
BCCC
BCCC
*/
void print_bloc(char** G, int n, int m, int K){
    int nb_decoupe;
    int mult_K =0;
    while(mult_K<m){
        for(int i=0; i<n; i++){
            for(int j=0; j<K; j++){
                if(mult_K+j < m){
                    printf("%c", G[i][j+mult_K]);
                }
            }
            printf("\n");
        }
        mult_K = mult_K + K;
    }
}


/*Tranforme un entier en binaire et stock le résultat dans un tableau*/
int* int_to_bin(int n){
    int* tab = malloc(8*sizeof(int));
    for(int i=7; i>=0;i--){
        if(n==0){
            tab[i] =0;
        }
        else{
            tab[i] = n%2;
            n=n/2;
        }
    }
    return tab;
}





/* Génère une grille de pixels 8x8 pour le caractère `forme`,
utilisant c pour les pixels actifs */
char** grille_pixels(char forme, char c){
    char* filename = img_filename(forme);
    FILE* f = fopen(filename, "r");
    if (f == NULL){
      perror("Fichiers pour les lettres introuvables: vérifiez que le dossier lettres/ est dans le même dossier que l'exécutable");
      exit(1);
    }

    //On crée la matrice dans laquelle on va stocker nos pixels pour représenter un char
    char** mat_pixel = malloc(8*sizeof(char*));
    for(int i=0; i<8; i++){
        mat_pixel[i] = malloc(8*sizeof(char));
    }

    for(int j=0; j<8; j++){
        int n;
        fscanf(f, "%d", &n);
        int* bin = int_to_bin(n);
        for(int k=0; k<8; k++){
            if(bin[k] ==1){
                mat_pixel[j][k] = c;
            }
            else{
                mat_pixel[j][k] = ' ';
            }
            
        }
        free(bin);
    }

    free(filename);
    fclose(f);
    return mat_pixel;
}

/* Libère la mémoire allouée pour G une matrice de n lignes */
void free_mat(char** G, int n){
   for (int i = 0; i < n; ++i){
      free(G[i]);
   }
   free(G);
}

/* Recopie le contenu de la grille tampon dans la grille G,
   avec la case (i, j) de G contenant la case (0, 0) de tampon (qui est de taille n*m).  
   Par exemple si G contient
   ABCD
   EFGH
   IJKL
   et tampon contient
   ZZ
   YY
   alors après avoir appelé recopier(G, tampon, 2, 2, 1, 2), G contient:
   ABCD
   EFZZ
   IJYY
   */
void recopier(char** G, char** tampon, int n, int m, int i, int j){
    for(int k =0; k<n; k++){
        for(int l=0; l<m; l++){
            G[i+k][j+l] = tampon[k][l];
        }
    }
}


/* Génère une grille 2D de taille 8 x 8n (où n est la longueur de phrase)
   représentant la phrase, où chaque caractère est représenté par une image
   de 8 par 8 pixels, chaque pixel étant le caractère pix  */
char** generer_grille(char* phrase, char pix){
    //Initialisation de la matrice
    char** mat = malloc(8*sizeof(char*));
    int n = strlen(phrase);
    for(int i=0; i<8; i++){
        mat[i] = malloc(8*n*sizeof(char));
        for (int j = 0; j < n*8; ++j){
            mat[i][j] = ' ';
        }
    }

    //On colle la matrice actuelle avec chaque caractèrede la phrase
    for(int i=0; i<n; i++){
        char forme = phrase[i];
        if(forme != ' ' && forme != '\t'){
            recopier(mat, grille_pixels(forme, pix), 8, 8, 0, i*8);
        }
    }
    return mat;
}


int main(int argc, char** argv){
    if (argc != 3){
      printf("Usage: %s [caractère] [lettres par ligne]\n", argv[0]);
      exit(1);
    }
    int K = atoi(argv[2]);
    char pix = argv[1][0];

    char* phrase = NULL;
    size_t size = 0;
    printf("Rentrez une phrase: ");
    int n = getline(&phrase, &size, stdin) - 1;
    phrase[n] = '\0'; // remplace le retour à la ligne
  
    char** G = generer_grille(phrase, pix);
    printf("\n");
    print_bloc(G, 8, 8*n, 8*K);

    free_mat(G, 8);
    free(phrase);
    return 0;
}