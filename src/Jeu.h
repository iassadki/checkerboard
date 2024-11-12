#ifndef JEU_H
#define JEU_H

#include "Plateau.h"
#include "Joueur.h"

class Jeu
{
public:
    Jeu();
    void lancer(); // Méthode pour lancer le jeu

private:
    Joueur joueur_blanc;
    Joueur joueur_noir;
    Joueur *joueur_actuel;
    Plateau plateau;

    void changerJoueur();
};

#endif // JEU_H
