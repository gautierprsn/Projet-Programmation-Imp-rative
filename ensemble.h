#ifndef _ENSEMBLE_H
#define _ENSEMBLE_H

typedef struct ensemble ensemble;

/*@requires un ensemble e
   assigns nothing
   ensure renvoie la position du curseur dans la matrice */
void positioncurseur(ensemble e);

/*@requires un ensemble e
   assigns modifie la position du curseur 
   ensure renvoie l'ensemble avec le  nouveau curseur associé*/
ensemble deplacementdroit(ensemble e);

/*@requires un ensemble e
   assigns deplace le curseur juste en dessous
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementbas(ensemble e);

/*@requires un ensemble e
   assigns deplace le curseur a gauche
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementgauche(ensemble e);

/*@requires un ensemble e
   assigns deplace le curseur juste au dessus
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementhaut(ensemble e);

/*@requires un ensemble e
   assigns deplace le curseur au dessus a droite
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementdiaghautdroit(ensemble e);

/*@requires un ensemble e
   assigns deplace le curseur au dessus a gauche
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementdiaghautgauche(ensemble e);

/*@requires un ensemble e
   assigns deplace le curseur en dessous à droite
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementdiagbasdroit(ensemble e);

/*@requires un ensemble e
   assigns deplace le curseur en dessous à gauche
   ensure renvoie e avec la nouvelle position du curseur */
ensemble deplacementdiagbasgauche(ensemble e);

/*@requires un ensemble e
   assigns effectue le deplacement souhaité en fonction de la direction
   ensure renvoie e avec la nouvelle position du curseur et le deplacement fait */
ensemble deplacement(ensemble e);

/*@requires un ensemble e, une pile s
   assigns effectue les differentes actions en fonction du caractère sur lequel on se trouve
   ensure nothing*/
ensemble differentcas(ensemble e);

#endif
