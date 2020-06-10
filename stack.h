#ifndef _STACK_H
#define _STACK_H

typedef struct stack stack;

/*@ requires nothing
    assigns nothing
    ensure crée une pile vide de taille modifiable*/
stack createstack();

/*@ requires une pile s
    assigns nothing
    ensure renvoie si la pile est vide */
int stackvide(stack s);

/*@ requires s adresse valide
    assigns *s
    ensure *s de taille new_size */
void resize( stack *s, int new_size);

/*@ requires un entier a, une pile s
    assigns empile l'entier a en tête de pile
    ensure on a la pile avec l'entier a */
void empile (int a, stack *s);

/*@requires une pile s
   assigns nothing
   ensure renvoie le sommet de la pile */
int depile(stack *s);

/*@ requires une pile s
    assigns duplique le sommet
    ensure la pile a voit son sommet duplique*/
void dupliquesommet(stack *s);

/*@requires une pile s
   assigns nothing
   ensure affiche la pile s */
void printstack(stack s);

#endif
