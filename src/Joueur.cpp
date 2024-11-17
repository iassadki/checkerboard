#include "Joueur.h"

Joueur::Joueur(const std::string &couleur) : couleur(couleur) {}

const std::vector<Piece> &Joueur::getPieces() const
{
    return pieces;
}

bool Joueur::effectuer_deplacement(const Position &depart, const Position &arrivee)
{
    return true;
}

const std::string &Joueur::getCouleur() const
{
    return couleur;
}