#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>
#include <string>
#include "Position.h"
#include "Piece.h"

class Joueur
{
public:
    Joueur(const std::string &couleur);
    const std::vector<Piece> &getPieces() const;
    bool effectuer_deplacement(const Position &depart, const Position &arrivee);
    const std::string &getCouleur() const;

private:
    std::string couleur;
    std::vector<Piece> pieces;
};

#endif 