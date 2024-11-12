#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>
#include "Piece.h"

class Joueur
{
public:
    Joueur(const std::string &couleur);
    const std::vector<Piece> &getPieces() const;

private:
    std::string couleur;
    std::vector<Piece> pieces;
};

#endif // JOUEUR_H
