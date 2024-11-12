#include "Jeu.h"
#include <iostream>

Jeu::Jeu()
    : joueur_blanc("Blanc"), joueur_noir("Noir"), joueur_actuel(&joueur_blanc), plateau()
{
    plateau.initialiser_plateau(); // Initialise le plateau avec les pièces
}

void Jeu::lancer()
{
    std::cout << "État initial du damier :\n";
    plateau.afficher_plateau(); // Affiche le damier une seule fois
}
