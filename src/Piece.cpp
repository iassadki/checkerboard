#include "Piece.h"

Piece::Piece(const std::string &couleur, const Position &position)
    : couleur(couleur), est_reine(false), position(position) {}

bool Piece::estReine() const
{
    return est_reine;
}

void Piece::setReine(bool est_reine)
{
    this->est_reine = est_reine;
}

Position Piece::getPosition() const
{
    return position;
}

void Piece::setPosition(const Position &pos)
{
    position = pos;
}

// Implémentation du getter pour la couleur
std::string Piece::getCouleur() const
{
    return couleur;
}
