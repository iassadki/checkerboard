#include "Plateau.h"
#include <iostream>
#include <cmath>

Plateau::Plateau() {}

void Plateau::initialiser_plateau()
{
    pieces.clear();

    // Placement des pièces blanches
    for (int row = 0; row < 3; ++row)
    {
        for (int col = (row % 2); col < 8; col += 2)
        {
            pieces.emplace_back("Blanc", Position(row, col));
        }
    }

    // Placement des pièces noires
    for (int row = 5; row < 8; ++row)
    {
        for (int col = (row % 2); col < 8; col += 2)
        {
            pieces.emplace_back("Noir", Position(row, col));
        }
    }
}

void Plateau::afficher_plateau() const
{
    std::string damier[8][8];

    // Initialiser le damier vide
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            damier[i][j] = "[ ]";
        }
    }

    // Placement des pieces sur le damier
    for (const auto &piece : pieces)
    {
        int x = piece.getPosition().getX();
        int y = piece.getPosition().getY();
        std::string symbole = piece.getCouleur() == "Blanc" ? "o" : "x";
        if (piece.estReine())
        {
            symbole = piece.getCouleur() == "Blanc" ? "O" : "X";
        }
        damier[x][y] = "[" + symbole + "]";
    }

    // Afficher le damier
    std::cout << "     0   1   2   3   4   5   6   7\n";
    std::cout << "   --------------------------------\n";
    for (int i = 0; i < 8; ++i)
    {
        std::cout << i << " | ";
        for (int j = 0; j < 8; ++j)
        {
            std::cout << damier[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool Plateau::deplacer_piece(Piece &piece, const Position &nouvelle_pos)
{
    if (!est_position_valide(nouvelle_pos))
    {
        return false;
    }

    if (getPieceAt(nouvelle_pos) != nullptr)
    {
        return false;
    }

    Position ancien_pos = piece.getPosition();

    if (abs(nouvelle_pos.getX() - ancien_pos.getX()) == 2)
    {
        Position pos_capturee = position_piece_capturee(ancien_pos, nouvelle_pos);
        Piece *piece_capturee = getPieceAt(pos_capturee);

        if (piece_capturee && piece_capturee->getCouleur() != piece.getCouleur())
        {
            retirer_piece(*piece_capturee);
        }
    }

    piece.setPosition(nouvelle_pos);

    if (!piece.estReine())
    {
        if ((piece.getCouleur() == "Blanc" && nouvelle_pos.getX() == 7) ||
            (piece.getCouleur() == "Noir" && nouvelle_pos.getX() == 0))
        {
            piece.setReine(true);
        }
    }

    return true;
}

void Plateau::retirer_piece(Piece &piece)
{
    for (auto it = pieces.begin(); it != pieces.end(); ++it)
    {
        if (it->getPosition().getX() == piece.getPosition().getX() &&
            it->getPosition().getY() == piece.getPosition().getY())
        {
            pieces.erase(it);
            break;
        }
    }
}

bool Plateau::est_deplacement_valide(const Position &depart, const Position &arrivee, const Joueur &joueur) const
{
    if (!est_position_valide(depart) || !est_position_valide(arrivee))
    {
        return false;
    }

    const Piece *piece = getPieceAt(depart);
    if (!piece)
    {
        return false;
    }

    if (piece->getCouleur() != joueur.getCouleur())
    {
        return false;
    }

    if (joueur_peut_capturer(joueur))
    {
        return est_capture_valide(depart, arrivee, piece->getCouleur());
    }

    return est_deplacement_simple_valide(depart, arrivee, piece->getCouleur());
}

Piece *Plateau::getPieceAt(const Position &pos)
{
    for (auto &piece : pieces)
    {
        if (piece.getPosition().getX() == pos.getX() &&
            piece.getPosition().getY() == pos.getY())
        {
            return &piece;
        }
    }
    return nullptr;
}

const Piece *Plateau::getPieceAt(const Position &pos) const
{
    for (const auto &piece : pieces)
    {
        if (piece.getPosition().getX() == pos.getX() &&
            piece.getPosition().getY() == pos.getY())
        {
            return &piece;
        }
    }
    return nullptr;
}

bool Plateau::est_position_valide(const Position &pos) const
{
    return pos.getX() >= 0 && pos.getX() < 8 && pos.getY() >= 0 && pos.getY() < 8;
}

bool Plateau::est_deplacement_simple_valide(const Position &depart, const Position &arrivee, const std::string &couleur) const
{
    int dx = arrivee.getX() - depart.getX();
    int dy = arrivee.getY() - depart.getY();

    if (!getPieceAt(depart)->estReine())
    {
        if (couleur == "Blanc" && dx <= 0)
            return false;
        if (couleur == "Noir" && dx >= 0)
            return false;
    }

    return abs(dx) == 1 && abs(dy) == 1;
}

bool Plateau::est_capture_valide(const Position &depart, const Position &arrivee, const std::string &couleur) const
{
    int dx = arrivee.getX() - depart.getX();
    int dy = arrivee.getY() - depart.getY();

    if (abs(dx) != 2 || abs(dy) != 2)
    {
        return false;
    }

    if (!getPieceAt(depart)->estReine())
    {
        if (couleur == "Blanc" && dx <= 0)
            return false;
        if (couleur == "Noir" && dx >= 0)
            return false;
    }

    Position pos_intermediaire(depart.getX() + dx / 2, depart.getY() + dy / 2);
    const Piece *piece_capturee = getPieceAt(pos_intermediaire);

    return piece_capturee && piece_capturee->getCouleur() != couleur;
}

Position Plateau::position_piece_capturee(const Position &depart, const Position &arrivee) const
{
    return Position(
        depart.getX() + (arrivee.getX() - depart.getX()) / 2,
        depart.getY() + (arrivee.getY() - depart.getY()) / 2);
}

bool Plateau::peut_capturer(const Piece &piece) const
{
    return !obtenir_captures_possibles(piece).empty();
}

std::vector<Position> Plateau::obtenir_captures_possibles(const Piece &piece) const
{
    std::vector<Position> captures;
    Position pos = piece.getPosition();

    std::vector<std::pair<int, int>> directions;
    if (piece.estReine())
    {
        directions = {{2, 2}, {2, -2}, {-2, 2}, {-2, -2}};
    }
    else if (piece.getCouleur() == "Blanc")
    {
        directions = {{2, 2}, {2, -2}};
    }
    else
    {
        directions = {{-2, 2}, {-2, -2}};
    }

    for (const auto &dir : directions)
    {
        Position nouvelle_pos(pos.getX() + dir.first, pos.getY() + dir.second);
        if (est_capture_valide(pos, nouvelle_pos, piece.getCouleur()))
        {
            captures.push_back(nouvelle_pos);
        }
    }

    return captures;
}

bool Plateau::joueur_peut_capturer(const Joueur &joueur) const
{
    for (const auto &piece : pieces)
    {
        if (piece.getCouleur() == joueur.getCouleur() && peut_capturer(piece))
        {
            return true;
        }
    }
    return false;
}