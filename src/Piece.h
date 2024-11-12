#ifndef PIECE_H
#define PIECE_H

#include "Position.h"
#include <string>

class Piece
{
public:
    Piece(const std::string &couleur, const Position &position);
    bool estReine() const;
    void setReine(bool est_reine);
    Position getPosition() const;
    void setPosition(const Position &pos);

    // Ajouter un accesseur pour obtenir la couleur de la pièce
    std::string getCouleur() const;

private:
    std::string couleur;
    bool est_reine;
    Position position;
};

#endif // PIECE_H
