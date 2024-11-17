#ifndef JEU_H
#define JEU_H

#include "Plateau.h"
#include "Joueur.h"
#include <string>

class Jeu
{
public:
    Jeu();
    void demarrer();
    void terminer();

private:
    Joueur joueur_blanc;
    Joueur joueur_noir;
    Joueur *joueur_actuel;
    Plateau plateau;

    void changerJoueur();
    bool partie_terminee() const;
    void effectuer_tour();
    bool saisir_deplacement(Position &depart, Position &arrivee);
};

#endif 