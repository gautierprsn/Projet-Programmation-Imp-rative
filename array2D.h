#ifndef _ARRAY2D_H
#define _ARRAY2D_H

typedef struct array2D array2D;

/*@requires 2 entiers h et w
   assigns nothing
   ensure crée un tableau de w colonnes et h lignes*/
array2D create(int w, int h);

/*@requires un tableau a
   assigns nothing
   ensure affiche le contenu du tableau*/
void printarray2D(array2D a);

/*@requires l'entier argc et une chaine de caractère
   assigns permet d'ouvrir un fichier en placant chaque caractère dans une case de la matrice
   ensure renvoie la matrice remplit des caracteres du fichier*/
array2D ouverturefichier(int argc, char*argv[]);

#endif
