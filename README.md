# Projet: Ecriture dans le terminal en grosses lettres
Ce petit projet permet d'écrire dans le terminal en utilisant des grosses lettres. 

## Compilation
> [!NOTE]
>Une compilation classique avec gcc suffit.

## Informations générales

Vous retrouverez le fichier lettres, celui-ci contient tous les caractères alphanumériques. Chacun d’entre eux est représenté par 8 nombres. Lorsqu’on les décompose en binaire, on obtient le caractère affiché par des 1.

![image](https://github.com/user-attachments/assets/2ea175cd-be27-455e-abf5-b5320c2d575f)
*Exemple pour le chiffre 2*

## Execution du programme

Quand on exécute le programme, on doit donner : le caractère avec lequel on veut écrire, et le nombre de lettres par ligne.

![image](https://github.com/user-attachments/assets/b8648905-cc7d-4e93-8340-f595352fef33)

# Exemples

![image](https://github.com/user-attachments/assets/781b2fc3-2a31-40c4-b3ce-1592bfcc3bca)
*Execution avec 15 caractères par lignes*

> [!WARNING]
>Il faut bien réflechir au nombre de lettres par lignes avant d'écrire une phrase, si on choisis mal, on peut couper certains mots.

![image](https://github.com/user-attachments/assets/7f5f0cc7-6cf3-4fad-9300-64d34834ed83)
*Execution avec 5 caractères par lignes*

## Ce que ce projet m'a apporté

Grâce à ce projet, j’ai appris à découper une matrice pour afficher les n*K premières cases d’une matrice sur une première ligne (n étant le nombre de lignes de la matrice et K le nombre de cases par ligne), puis un deuxième bloc de taille n * K, etc.

J’ai également appris à ouvrir un fichier .txt en C quand on nous donne seulement le nom du fichier sans l’extension. (Un simple strcat suffit, mais il fallait y penser).

## Difficultés rencontrées

Globalement, peu de difficultés, la plus grande étant de penser à comment mettre en œuvre le projet, de quelles fonctions j’aurais besoin, etc.

La fonction print_bloc (qui affiche seulement un bloc d’une matrice puis revient à la ligne pour afficher un autre bloc, etc.) était la plus difficile à coder. J’avais commencé par distinguer deux cas :

- le cas où le nombre de colonnes (m) de la matrice est divisible par K (K étant le nombre de colonnes du bloc) ;
- le cas où m ne l’est pas.


Mais cela causait beaucoup de problèmes, donc j’ai préféré partir sur une simple boucle while et un compteur qui sera toujours un multiple de K (0K, 1K, 2K, etc.).
