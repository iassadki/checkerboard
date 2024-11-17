#ifndef PLATEAU_H
#define PLATEAU_H

#include <vector>
#include "Piece.h"
#include "Joueur.h"

class Plateau
{
public:
    Plateau();
    void initialiser_plateau();
    void afficher_plateau() const;
    bool deplacer_piece(Piece &piece, const Position &nouvelle_pos);
    void retirer_piece(Piece &piece);
    bool est_deplacement_valide(const Position &depart, const Position &arrivee, const Joueur &joueur) const;
    Piece *getPieceAt(const Position &pos);
    const Piece *getPieceAt(const Position &pos) const;
    bool peut_capturer(const Piece &piece) const;
    std::vector<Position> obtenir_captures_possibles(const Piece &piece) const;
    bool joueur_peut_capturer(const Joueur &joueur) const;

private:
    std::vector<Piece> pieces;
    bool est_position_valide(const Position &pos) const;
    bool est_deplacement_simple_valide(const Position &depart, const Position &arrivee, const std::string &couleur) const;
    bool est_capture_valide(const Position &depart, const Position &arrivee, const std::string &couleur) const;
    Position position_piece_capturee(const Position &depart, const Position &arrivee) const;
};

#endif // PLATEAU_H