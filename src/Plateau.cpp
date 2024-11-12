#include "Plateau.h"
#include <iostream>

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
    // Création d'un tableau temporaire pour le damier
    std::string damier[8][8];

    // Remplir le damier avec des cases vides
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            damier[i][j] = "[ ]"; // Par défaut, la case est vide
        }
    }

    // Ajouter les pièces dans le damier
    for (const auto &piece : pieces)
    {
        int x = piece.getPosition().getX();
        int y = piece.getPosition().getY();
        if (piece.getCouleur() == "Blanc")
        {
            damier[x][y] = "[o]"; // Marqueur pour une pièce blanche
        }
        else if (piece.getCouleur() == "Noir")
        {
            damier[x][y] = "[x]"; // Marqueur pour une pièce noire
        }
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
