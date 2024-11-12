#include "Joueur.h"

Joueur::Joueur(const std::string &couleur) : couleur(couleur) {}

const std::vector<Piece> &Joueur::getPieces() const
{
    return pieces;
}
