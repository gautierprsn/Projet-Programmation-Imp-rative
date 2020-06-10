#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "array2D.h"
#include "ensemble.h"
#define taillefichier 1000
#define STACKMAX 1000

struct position{
  int x,y;
  // x:numero de lignes, y:numero de colonnes

};
typedef struct position position;

//w:nbre de colonne, h=nbredeligne
struct array2D{
  int h,w;
  int **content;
};
typedef struct array2D array2D;

struct stack {
  int *t;
  int top;
  int size;
};

typedef struct stack stack;



struct ensemble{
  position curseur;
  array2D tableau;
  int directory;
  int caractere;
  stack s;
};

typedef struct ensemble ensemble;

/*@ requires nothing
    assigns nothing
    ensure crée une pile vide de taille modifiable*/
stack createstack(){
  stack r;
  r.top=-1;
  r.size=1;
  r.t=malloc(sizeof(int));
  return r;
}


/*@ requires une pile s
    assigns nothing
    ensure renvoie si la pile est vide */
int stackvide(stack s){
  return (s.top<0);
}

/*@ requires s adresse valide
    assigns *s
    ensure *s de taille new_size */
void resize(stack *s, int new_size){
  int *tmp;
  int i;
  tmp=malloc(new_size*sizeof(int));
  for (i=0;i<=s->top;i+=1)
    tmp[i]=s->t[i];
  free(s->t);
  s->size=new_size;
  s->t=tmp;}


/*@ requires un entier a, une pile s
    assigns empile l'entier a en tête de pile
    ensure on a la pile avec l'entier a */
void empile(int a, stack *s){
  if (s->top >= s->size-1) resize(s, 2 * s->size);
  (*s).top=(*s).top+1;
  (*s).t[(*s).top] = a;
}


/*@requires une pile s
   assigns nothing
   ensure renvoie le sommet de la pile */
int depile(struct stack *s){
  if(s->top<0) return 0;
  int r= s->t[s->top];
  s->top= s->top-1;
  return r;
}

/*@ requires une pile s
    assigns duplique le sommet
    ensure la pile a voit son sommet duplique*/ 
void dupliquesommet(stack *s){
  resize(s,s->size+1); //on augmente la pile de 1 élément puisqu'on duplique le sommet
  int a=depile(s);
  empile(a,s);
  empile(a,s);}



/*@requires une pile s
   assigns nothing
   ensure affiche la pile s */
void printstack(stack s){
  int i;
  for(i=s.top; i>=0; i-=1)
    printf("%i (%c)|",s.t[i],s.t[i]);
  printf("\n");
}

/*@requires 2 entiers a et b
   assigns nothing
   ensure renvoie le reste de la division euclidienne de a par b si a>b, de b par a sinon*/
int reste(int a, int b){
  if (a==0) return 0xbadc0de;
  if (a>b) return a%b;
  else return b%a;
}

/*@requires 2 entiers a et b
   assigns nothing
   ensure renvoie le quotient de la division euclidiene de a par b si a>b, de b par a sinon*/
int quotient(int a, int b){
  if (a==0) return 42;
  if (a>b) return a/b;
  else return b/a;
}

/*@requires 2 entiers h et w
   assigns nothing
   ensure crée un tableau de w colonnes et h lignes*/
array2D create(int w, int h){
  array2D r;
  r.w=w;
  r.h=h;
  r.content=(int **)malloc(h*sizeof(int*));
  for(int i=0;i<h;i+=1)
    r.content[i]=(int*)malloc(w*sizeof(int));
  return r;
}

/*@requires un tableau a
   assigns nothing
   ensure affiche le contenu du tableau*/
void printarray2D(array2D a){
  int i,j;
  for (i=0; i<a.h;i+=1){
    for(j=0; j<a.w;j+=1)
      printf("%c",a.content[i][j]);
    printf("\n");}
}


/*@requires un caractère a
   assigns nothing
   ensure renvoie la position du premier espace dans une chaine de caractere*/
int premierespacedanschaine(char *a){
  int c=1;
  int i=0;
  //cette boucle se termine à condition que la chaine rentrée en argument possède un espace puisque à chaque itération, on avance d'un indice donc on va rencontrer l'espace
  while (a[i] !=' '){ c+=1; i+=1;}
  return c;}// c correspond au premier espace dans la chaine

/*@requires une chaine a
   assigns nothing
   ensure renvoie la longueur d'une chaine a*/
int finchaine(char *a){
  int i=0;
  //cette boucle se termine puisque toutes chaines de caractère se termine par '\0'
  while (a[i] !='\0') i+=1;
  return i;}//renvoie la longueur de la chaine


/*@requires une chaine a, un entier correspondant à la position initiale de l'extraction et à celle finale
   assigns renvoie une chaine extraite
   ensure renvoie la sous chaine de a*/
char *extractionchaine(char *a, int debut, int fin){
  char *extract=NULL;
  int i;
  extract=malloc((fin-debut+1)*sizeof(char));//on alloue la place nécessaire pour la chaine extraite
  for (i=debut;i<fin;i+=1)
    extract[i-debut]=a[i];
  return extract;}

/*@requires un caractère a
   assigns converti un nombre vu comme un caractère en un entier
   ensure renvoie l'entier associé au caractère*/
int conversion(char *a){
  int entier=atoi(a);
  return entier;
}

/*@requires l'entier argc et une chaine de caractère
   assigns permet d'ouvrir un fichier en placant chaque caractère dans une case de la matrice
   ensure renvoie la matrice remplit des caracteres du fichier*/
array2D ouverturefichier(int argc, char*argv[]){
  FILE* fichier=NULL;
  char chaine[256];
  fichier=fopen(argv[1],"r");
  char *ligne1=fgets(chaine,256,fichier);//on extrait la première ligne du fichier
  char *nombredeligne = extractionchaine(ligne1,premierespacedanschaine(ligne1), finchaine(ligne1)); //on extrait la seconde partie de la chaine extraite (apres le premier espace) qui correspond au nombre de lignes du fichier
  char *nombredecolonne= extractionchaine(ligne1, 0, premierespacedanschaine(ligne1));//on extrait ici la première partie ie le nombre de colonnes
  
  array2D fichierdansmatrice=create(conversion(nombredecolonne),conversion(nombredeligne));
  // on crée l'espace pour la matrice
  array2D tmp=create(conversion(nombredecolonne)+1,conversion(nombredeligne));
  //on crée une matrice temporaire
  

   for(int k=0; k<conversion(nombredeligne); k+=1){
    for(int j=0; j<conversion(nombredecolonne)+1; j+=1)
      tmp.content[k][j]=fgetc(fichier);

  }
  
  for(int k=0; k<conversion(nombredeligne); k+=1){
    for(int j=0; j<conversion(nombredecolonne); j+=1)
      fichierdansmatrice.content[k][j]=tmp.content[k][j];//on remplit la matrice sans les retour à la ligne et sans la premiere ligne (celle de la taille du fichier) puisqu'on l'a extraite avec le fgets. Avec fgetc, on remplit chaque case avec un caractère.
  }
 
  for(int i=0; i<=quotient(conversion(nombredecolonne),5);i+=1){
    if (i<2)
    printf("%d    ",5*i);
    else printf("%d   ",5*i);}
  
  printf("\n");
  
  for(int i=0; i<=quotient(conversion(nombredecolonne),5);i+=1){
    if (i<2) printf("%s    ","|");
    else printf("%s    ","|");
  }
  printf("\n");

   
  // ces 2 boucles for précédentes permettent la mise en page souhaitée.

  printf("\n");
  printarray2D(fichierdansmatrice);
  printf("\n");

  return fichierdansmatrice;}


/*@requires un ensemble e
   assigns nothing
   ensure renvoie la position du curseur dans la matrice */
void positioncurseur(ensemble e){
  printf("la position du curseur est: [%i;%i]\n",e.curseur.x,e.curseur.y);
}

/*@requires un ensemble e
   assigns modifie la position du curseur 
   ensure renvoie l'ensemble avec le  nouveau curseur associé*/
ensemble deplacementdroit(ensemble e){
  e.curseur.y=(e.curseur.y+1);//le curseur se déplace d'une case sur la droite
  if (e.curseur.y >e.tableau.w) e.curseur.y =0;// si le curseur est en dehors des cases de la matrice, il revient à la première colonnes.
  e.directory=2;//on garde l'inertie du déplacement
  return e;
  }

/*@requires un ensemble e
   assigns deplace le curseur juste en dessous
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementbas(ensemble e){
  e.curseur.x=e.curseur.x+1;//le curseur se déplace d'une case vers le bas
  if (e.curseur.x>e.tableau.h) e.curseur.x =0;// si le curseur est en dehors des cases de la matrice, il revient à la première ligne.
  e.directory=4;//on garde l'inertie du déplacement
  return e;
 
}

/*@requires un ensemble e
   assigns deplace le curseur a gauche
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementgauche(ensemble e){
  e.curseur.y=e.curseur.y-1;//le curseur se déplace d'une case vers la gauche
  if (e.curseur.y<0) e.curseur.y =e.tableau.w;// si le curseur est en dehors des cases de la matrice, il revient à la dernière colonne.
  e.directory=6;//on garde l'inertie du déplacement
  return e;
  }

/*@requires un ensemble e
   assigns deplace le curseur juste au dessus
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementhaut(ensemble e){
  e.curseur.x=e.curseur.x-1;//le curseur se déplace d'une case vers le haut
  if (e.curseur.x<0) e.curseur.x =e.tableau.h;// si le curseur est en dehors des cases de la matrice, il revient à la dernière ligne.
  e.directory=0;//on garde l'inertie du déplacement 
  return e;
}

/*@requires un ensemble e
   assigns deplace le curseur au dessus a droite
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementdiaghautdroit(ensemble e){
  //ce déplacement est une association d'un déplacement a droite et d'un déplacement en haut
  e.curseur.x=e.curseur.x-1;
  e.curseur.y=e.curseur.y+1;
  //on fait attention aux limites de la matrice
  if (e.curseur.y >e.tableau.w) e.curseur.y =0;
  if (e.curseur.x<0) e.curseur.x =e.tableau.h;
  e.directory=1;//on garde l'inertie
  return e;
  }

/*@requires un ensemble e
   assigns deplace le curseur au dessus a gauche
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementdiaghautgauche(ensemble e){
  //on associe un déplacement à gauche et en haut
  e.curseur.x=e.curseur.x-1;
  e.curseur.y=e.curseur.y-1;
  if (e.curseur.x<0) e.curseur.x =e.tableau.h;
  if (e.curseur.y<0) e.curseur.y =e.tableau.w;
  e.directory=7;//on conserve l'inertie
  return e;
  }

/*@requires un ensemble e
   assigns deplace le curseur en dessous à droite
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementdiagbasdroit(ensemble e){
  //on associe un déplacement en bas et à droite
  e.curseur.x=e.curseur.x+1;
  e.curseur.y=e.curseur.y+1;
  if (e.curseur.x>e.tableau.h) e.curseur.x =0;
  if (e.curseur.y>e.tableau.w) e.curseur.y =0;
  e.directory=3;//on conserve l'inertie
  return e;
  }

/*@requires un ensemble e
   assigns deplace le curseur en dessous à gauche
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementdiagbasgauche(ensemble e){
  //on associe un déplacement en bas et à gauche
  e.curseur.x=e.curseur.x+1;
  e.curseur.y=e.curseur.y-1;
  if (e.curseur.x>e.tableau.h) e.curseur.x =0;
  if (e.curseur.y<0) e.curseur.y =e.tableau.w;
  e.directory=5;//on conserve l'inertie
  return e;
  }

/*@requires un ensemble e
   assigns effectue le deplacement souhaité en fonction de la direction
   ensure renvoie e avec la nouvelle position du curseur et le deplacement fait */
ensemble deplacement(ensemble e){
  //cette fonction regroupe tous les déplacements possibles et effectue un déplacement particulier en fonction de l'entier associé à e.directory.
  switch(e.directory){
  case 0:
    e=deplacementhaut(e);
    break;
  case 1:
    e=deplacementdiaghautdroit(e);
    break;
  case 2:
    e=deplacementdroit(e);
    break;
  case 3:
    e=deplacementdiagbasdroit(e);
    break;
  case 4:
    e=deplacementbas(e);
  break;
  case 5:
    e=deplacementdiagbasgauche(e);
    break;
  case 6:
    e=deplacementgauche(e);
    break;
  case 7:
    e=deplacementdiaghautgauche(e);
    break;};
  return e;
}

/*@requires nothing
  assigns nothing
  ensure un nombre aléatoire entre 0 et 7*/

int aleatoire(){
  int a=rand()%8;
  return a;}


/*@requires un ensemble e, une pile s
   assigns effectue les differentes actions en fonction du caractère sur lequel on se trouve
   ensure nothing*/
ensemble differentcas(ensemble e){
  //cette fonction effectue les différentes actions en fonction du caractère sur lequel on se trouve.
  //ici, on initialise tous les entiers dont on aura besoin dans notre switch.
  int a, b;
  int x,y,z;
  int c;
  switch(e.caractere){//le switch se fait notre caractere
  case 43://correspond au caractère "+", on dépile 2 entiers et on empile leur somme
    a = depile(&e.s);
    b= depile(&e.s);
    empile(a+b,&e.s);
    break;
    
  case 45://correspond au caractère "-", on dépile 2 entiers(a puis b) et on empile la différence b-a
    a =depile(&e.s);
    b = depile(&e.s);
    empile(b-a,&e.s);
    break;
    
  case 42://correspond au caractère "*", on dépile 2 entiers et on empile leur produit
    a =depile(&e.s);
    b = depile(&e.s);
    empile(a*b,&e.s);
    break;
    
  case 58://correspond au caractère ":", on dépile 2 entiers et on empile le quotient de b par a
    a = depile(&e.s);
    b = depile(&e.s);
    empile(quotient(a,b),&e.s);
    break;
    
  case 37://correspond au caractère "%", on dépile 2 entiers et on empile le reste de b par a
    a =depile(&e.s);
    b = depile(&e.s);
    empile(reste(a,b),&e.s);
    break;
    
  case 33 ://correspond au caractère "!", on dépile un entier et on empile 1 si c'est 0, 0 sinon.
    a  =depile(&e.s);
    if (a==0) empile (1,&e.s);
    else empile(0,&e.s);
    break;
    
  case 96://correspond au caractère "`", on dépile 2 entiers a et b et on empile 1 si b>a, 0 sinon.
    a = depile(&e.s);
    b = depile(&e.s);
    if (b>a) empile(1,&e.s);
    else empile(0,&e.s);
    break;
    
  case 62://correspond au caractère ">", on change la direction vers la droite
    e.directory=2;
    break;
    
  case 60://correpond au caractère "<", on change la direction vers la gauche
    e.directory=6;
    break;
    
  case 94://correspond au caractère "^", on change la direction vers le haut
    e.directory=0;
    break;
    
  case 118://correspond au caractère "v", on change la direciton vers le bas
    e.directory=4;
    break;
    
  case 63://correspond au caractère "?", on choisit une direction aléatoire entre 0 et 7.
    e.directory=aleatoire();
    break;
    
  case 39://correspond au caractère "," on dépile un entier a et la direction change en fontion du reste de a par 8.
    a=depile(&e.s);
    e.directory=a%8;
    break;
    
  case 93://correspond au caractère "]", on tourne à gauche de 45° donc l'entier correspondant à la direction diminue de 1 
    e.directory=e.directory-1;
    //on extrait les cas ou la direction peut etre inférieure à 0
    if (e.directory==-1) e.directory=7;
    break;
    
  case 91://correspond au caractère "[", on tourne à droite de 45° donc l'entier correspondant à la direction augmente de 1.
    e.directory=e.directory+1;
    //on extrait les cas ou la direction peut etre supérieure à 8 en cherchant le reste par 8
    if (e.directory>=8) e.directory=e.directory%8;
    break;
    
  case 95://correspond au caractère "_", on dépile un entier et on change la direction vers la droite si c'est 0, vers la gauche sinon
    a=depile(&e.s);
    if (a==0) e.directory=2;
    else e.directory=6;
    break;
    
  case 124://correspond au caractère "|", on dépile un entier et on change la direction vers le bas si c'est 0, vers le haut sinon
    a=depile(&e.s);
    if (a==0) e.directory=4;
    else e.directory=0;
    break;
    
  case 47://correspond au caractère "/", on dépile un entier et on change la direction dans la diagionale supérieure droite si c'est 0, dans la diagonale inférieure gauche sinon.
    a=depile(&e.s);
    if (a==0)
      {e.directory=1;
      }
    else e.directory=5;
    break;
    
  case 92://correspond au caractère "\", on dépile un entier et on change la direction vers la diagonale inférieurdroite  si c'est 0, dans la diagonale supérieur gauche sinon.
    a=depile(&e.s);
    if(a==0) e.directory=3;
    else e.directory=7;
    break;
    
  case 34://correspond au caractère " " ", on empile la valeur ASCII suivant en gardant la meme direction jusqu'a atteindre un autre ".
     x=e.curseur.x;
     y=e.curseur.y;
     //on change le caractère sur lequel on est sinon, on ne rentre par dans la boucle while
     if(e.directory==0) e.caractere=e.tableau.content[x-1][y];
     if(e.directory==1) e.caractere=e.tableau.content[x-1][y+1];
     if(e.directory==2) e.caractere=e.tableau.content[x][y+1];
     if(e.directory==3) e.caractere=e.tableau.content[x+1][y+1];
     if(e.directory==4) e.caractere=e.tableau.content[x+1][y];
     if(e.directory==5) e.caractere=e.tableau.content[x+1][y-1];
     if(e.directory==6) e.caractere=e.tableau.content[x][y-1];
     if(e.directory==7) e.caractere=e.tableau.content[x-1][y-1];
     
     while(e.caractere!=34){//cette boucle se termine puisqu'on va croiser un autre "
       //on avance dans la même direction et on affiche les caractères rencontrés en fonction de notre sens de déplacement et en fonction du caractère rencontré
       if(e.directory==0) {printf("%c",e.caractere); e=deplacementhaut(e); e.caractere=e.tableau.content[e.curseur.x][e.curseur.y];}
     if(e.directory==1) {e=deplacementdiaghautdroit(e); e.caractere=e.tableau.content[e.curseur.x][e.curseur.y];}
     if(e.directory==2) {e=deplacementdroit(e); e.caractere=e.tableau.content[e.curseur.x][e.curseur.y];}
     if(e.directory==3) {e=deplacementdiagbasdroit(e); e.caractere=e.tableau.content[e.curseur.x][e.curseur.y];}
     if(e.directory==4) {printf("%c",e.caractere); e=deplacementbas(e); e.caractere=e.tableau.content[e.curseur.x][e.curseur.y];}
     if(e.directory==5) {if (e.caractere!= 79 && e.caractere!=32) printf("%c",e.caractere); e=deplacementdiagbasgauche(e); e.caractere=e.tableau.content[e.curseur.x][e.curseur.y];}
     if(e.directory==6) {if (e.caractere!= 79 && e.caractere!=32) printf("%c",e.caractere); e=deplacementgauche(e); e.caractere=e.tableau.content[e.curseur.x][e.curseur.y];}
     if(e.directory==7) {if (e.caractere!= 79 && e.caractere!=32) printf("%c",e.caractere); e=deplacementdiaghautgauche(e); e.caractere=e.tableau.content[e.curseur.x][e.curseur.y];}
     if (e.caractere!=34) empile(e.caractere,&e.s);//on empile la valeur ASCII de tous les caractères rencontrés hors guillemet;
          
    }
    break;
       
  case 61://correspond au caractère "=", on duplique le sommet de la pile
    if (stackvide(e.s)==1) {empile(0,&e.s); empile(0,&e.s);}
    else dupliquesommet(&e.s);
    break;
    
  case 36://correspond au caractère "$", on échange les 2 valeurs au sommet de la pile.
    // si c'est vide, on empile 2 fois 0
    if (e.s.top <0) {empile(0,&e.s); empile(0,&e.s);}
    else if (e.s.top<1) { a=depile(&e.s); if (e.s.top<0) {empile(a,&e.s); empile(0,&e.s);}}// si il y a qu'un seul élément, on empile 0 au dessus.
    else{
    a=depile(&e.s);
    b=depile(&e.s);
    empile(a,&e.s);
    empile(b,&e.s);}
    break;
    
  case 59:// correspond au caractère ";", on retire la valeur du sommet de la pile.
    if (e.s.top<0) break;
    else depile(&e.s);
    break;
    ;
    
  case 46://corresond au caractère ".", on dépile un entier et affiche sa valeur.
    printf("l'entier depilé est %d\n",depile(&e.s));
    break;

    
  case 44://correspond au caractère ",", on dépile un entier et on affiche le caractère correspondant au code ASCII. 
    a=depile(&e.s)%256;
    printf("%c",a);
    break;

    
  case 35://correspond au caractère "#", on dépile un entier n et on saute les n prochains caractères dans la direction acutelles
    a=depile(&e.s);
    if (e.directory==0) e.curseur.x-=a;
    if (e.directory==4) e.curseur.x+=a;
    if (e.directory==2) e.curseur.y+=a;
    if (e.directory==6) e.curseur.y-=a;
    if (e.directory==1){
      e.curseur.x-=a;
      e.curseur.y+=a;}
    if (e.directory==3){
      e.curseur.x+=a;
      e.curseur.y+=a;}
    if (e.directory==5){
      e.curseur.x+=a;
      e.curseur.y-=a;}
    if (e.directory==7){
      e.curseur.x-=a;
      e.curseur.y-=a;};
    // si on est en dehors de la matrice, on se replace dedans en fonction du reste de la division de la position du curseur avec la taille de la matrice.
    if (e.curseur.x>e.tableau.h) e.curseur.x=(e.curseur.x)%(e.tableau.h);
    if (e.curseur.y>e.tableau.w) e.curseur.y=(e.curseur.y)%(e.tableau.w);
    break;

    
  case 103:// correspond au caractère "g", on dépile 2 entiers x et y et on empile la valeur du code ASCII associé au caractère placé en position [x][y]
    x=depile(&e.s);
    y=depile(&e.s);
    if (x>e.tableau.h || y>e.tableau.w) empile(0,&e.s); // si on se situe hors de la matrice, on empile 0
    else empile(e.tableau.content[x][y],&e.s);
    break;
    
  case 112://correspond au caractère "p", on dépile 3 entiers x y et z, et on écrit le code ASCII de z à la position [x][y] si c'est dans la matrice, et si c'est en dehors,on fait rien.  
    x=depile(&e.s);
    y=depile(&e.s);
    z=depile(&e.s);
    if (x>e.tableau.h || y>e.tableau.w) break;
     else e.tableau.content[x][y]=z;
    break;
    
  case 38://correspond au caractère "&", on demande à l'utilisateur d'entrer un entier et on empile cet entier.
    printf("Rentrer un entier: \n");
    scanf("%d",&a);
    empile(a,&e.s);
    break;
    
  case 126://correspond au caractère "~", on demande à l'utilisateur d'entrer un caractère et on empile la valeur ASCII du caractère.
    printf("Rentrer un caractère: \n");    
    a=scanf("%d",&c);
    empile(c,&e.s);
    break;
    
  case 48://correspond a l'entier "0", on empile 0
    a=0;
    empile(a,&e.s);
    break;
  case 49://correspond a l'entier "1", on empile 1
    a=1;
    empile(a,&e.s);
    break;
  case 50://correspond a l'entier "2", on empile 2
    a=2;
    empile(a,&e.s);
    break;
  case 51://correspond a l'entier "3", on empile 3
    a=3;
    empile(a,&e.s);
    break;
  case 52://correspond a l'entier "4", on empile 4
    a=4;
    empile(a,&e.s);
    break;
  case 53://correspond a l'entier "5", on empile 5
    a=5;
    empile(a,&e.s);
    break;
  case 54://correspond a l'entier "6", on empile 6
    a=6;
    empile(a,&e.s);
    break;
  case 55://correspond a l'entier "7", on empile 7
    a=7;
    empile(a,&e.s);
    break;
  case 56://correspond a l'entier "8", on empile 8
    a=8;
    empile(a,&e.s);
    break;
  case 57://correspond a l'entier "9", on empile 9
    a=9;
    empile(a,&e.s);
    break;
    
  case 32:
    break;
  };
  return e;
}



    
    
  

int main(int agrc, char*argv[]){
  if (argv[1]==NULL) { printf("aucun fichier en argument\n"); return EXIT_FAILURE ;}
  ensemble e;
  char c[STACKMAX];
  e.s=createstack();
  e.tableau=ouverturefichier(agrc,argv);
  printf("x=%d y=%d \n",e.tableau.h,e.tableau.w);
  e.curseur.x=0;
  e.curseur.y=0;
  e.directory=2;
  e.caractere=e.tableau.content[0][0];
  // cette boucle se termine puisqu'on va arriver au caractère @ après un certain nombre d'itérations
  while (e.caractere !=64){
    printf("rentrer une instruction parmis celles ci : step, run, quit, restart, stepn. \n");
    scanf("%s",c);

    if (strcmp(c,"step")==0){//correspond à l'instruction step, on avance d'une étape.;
      e.tableau=ouverturefichier(agrc,argv);
      e.caractere=e.tableau.content[e.curseur.x][e.curseur.y];
      e=differentcas(e);
      e=deplacement(e);     
      printf("%d\n",e.directory);
      printf("x=%d;y=%d\n",e.curseur.x,e.curseur.y-1);
      printf("%c\n",e.caractere);
      printstack(e.s);
    }
    
  if (strcmp(c,"run")==0){//permet de finir de parcourir tout le programme sans faire d'étape
    while(e.caractere !=64){
       e.caractere=e.tableau.content[e.curseur.x][e.curseur.y];
       e=differentcas(e);
       e=deplacement(e);
    }
  }

  if (strcmp(c,"restart")==0){//on réinitialise tout et on revient au point de départ
    e.curseur.x=0;
    e.curseur.y=0;
    e.directory=2;
    e.caractere=e.tableau.content[0][0];
    e.s=createstack();}


  if (strcmp(c,"stepn")==0){// permet de réaliser n étapes d'un coup
    printf("combien d'étapes souhaitez vous faire ?\n");
    int nbre;
    scanf("%d",&nbre);
    while(nbre!=0 && e.caractere !=64){
      nbre -=1;
      if(e.tableau.content[e.curseur.x][e.curseur.y]!=64){
	e.tableau=ouverturefichier(agrc,argv);
	e.caractere=e.tableau.content[e.curseur.x][e.curseur.y];
	e=differentcas(e);
	e=deplacement(e);}
    printf("%d\n",e.directory);
    printf("x=%d;y=%d\n",e.curseur.x,e.curseur.y-1);
    printf("%c\n",e.caractere);
    printstack(e.s);}}
   
	
  
  if (strcmp(c,"quit")==0){//permet de quitter le debogueur.
    e.caractere=64;}
  printf("\n");


    
  }}
  
