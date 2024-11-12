#ifndef PLATEAU_H
#define PLATEAU_H

#include <vector>
#include "Piece.h"

class Plateau
{
public:
    Plateau();
    void initialiser_plateau();
    void afficher_plateau() const; // Nouvelle méthode pour afficher le damier

private:
    std::vector<Piece> pieces;
};

#endif // PLATEAU_H
