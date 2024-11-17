#include "Jeu.h"
#include <iostream>
#include <limits>

Jeu::Jeu()
    : joueur_blanc("Blanc"), joueur_noir("Noir"), joueur_actuel(&joueur_blanc), plateau()
{
}

void Jeu::demarrer()
{
    std::cout << "Début de la partie de dames !\n";
    plateau.initialiser_plateau();

    while (!partie_terminee())
    {
        plateau.afficher_plateau();
        std::cout << "\nC'est au tour du joueur " << joueur_actuel->getCouleur() << "\n";

        effectuer_tour();

        if (!partie_terminee())
        {
            changerJoueur();
        }
    }

    terminer();
}

void Jeu::effectuer_tour()
{
    Position depart, arrivee;
    bool deplacement_valide = false;

    do
    {
        if (saisir_deplacement(depart, arrivee))
        {
            if (plateau.est_deplacement_valide(depart, arrivee, *joueur_actuel))
            {
                Piece *piece = plateau.getPieceAt(depart);
                if (piece)
                {
                    deplacement_valide = plateau.deplacer_piece(*piece, arrivee);

                    // Vérifier s'il y a d'autres captures possibles après une capture
                    if (deplacement_valide && abs(arrivee.getX() - depart.getX()) == 2)
                    {
                        while (plateau.peut_capturer(*piece))
                        {
                            plateau.afficher_plateau();
                            std::cout << "\nVous pouvez effectuer une autre capture avec cette pièce !\n";
                            Position nouvelle_arrivee;
                            if (saisir_deplacement(arrivee, nouvelle_arrivee))
                            {
                                if (plateau.est_deplacement_valide(arrivee, nouvelle_arrivee, *joueur_actuel))
                                {
                                    deplacement_valide = plateau.deplacer_piece(*piece, nouvelle_arrivee);
                                    arrivee = nouvelle_arrivee;
                                }
                                else
                                {
                                    std::cout << "Déplacement invalide.\n";
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                std::cout << "Déplacement invalide.\n";
            }
        }
    } while (!deplacement_valide);
}

bool Jeu::saisir_deplacement(Position &depart, Position &arrivee)
{
    try
    {
        int x1, y1, x2, y2;

        std::cout << "Entrez la position de départ (ligne colonne) : ";
        if (!(std::cin >> x1 >> y1))
        {
            throw std::runtime_error("Entrée invalide");
        }

        std::cout << "Entrez la position d'arrivée (ligne colonne) : ";
        if (!(std::cin >> x2 >> y2))
        {
            throw std::runtime_error("Entrée invalide");
        }

        depart = Position(x1, y1);
        arrivee = Position(x2, y2);

        return true;
    }
    catch (const std::exception &)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrée invalide. Veuillez entrer des nombres entre 0 et 7.\n";
        return false;
    }
}

void Jeu::changerJoueur()
{
    joueur_actuel = (joueur_actuel == &joueur_blanc) ? &joueur_noir : &joueur_blanc;
}

bool Jeu::partie_terminee() const
{
    // Vérifier si un joueur n'a plus de pièces
    int pieces_blanches = 0;
    int pieces_noires = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            const Piece *piece = plateau.getPieceAt(Position(i, j));
            if (piece)
            {
                if (piece->getCouleur() == "Blanc")
                {
                    pieces_blanches++;
                }
                else
                {
                    pieces_noires++;
                }
            }
        }
    }

    if (pieces_blanches == 0)
    {
        std::cout << "\nLe joueur Noir a gagné !\n";
        return true;
    }
    if (pieces_noires == 0)
    {
        std::cout << "\nLe joueur Blanc a gagné !\n";
        return true;
    }

    // Vérifier si le joueur actuel peut faire un mouvement
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            const Piece *piece = plateau.getPieceAt(Position(i, j));
            if (piece && piece->getCouleur() == joueur_actuel->getCouleur())
            {
                // Vérifier les mouvements possibles pour cette pièce
                for (int di = -2; di <= 2; di++)
                {
                    for (int dj = -2; dj <= 2; dj++)
                    {
                        if (di != 0 && dj != 0)
                        { // Mouvement diagonal
                            Position arrivee(i + di, j + dj);
                            if (plateau.est_deplacement_valide(Position(i, j), arrivee, *joueur_actuel))
                            {
                                return false; // Il existe au moins un mouvement valide
                            }
                        }
                    }
                }
            }
        }
    }

    // Si on arrive ici, le joueur actuel ne peut pas bouger
    std::cout << "\nLe joueur " << (joueur_actuel == &joueur_blanc ? "Noir" : "Blanc") << " a gagné par blocage !\n";
    return true;
}

void Jeu::terminer()
{
    std::cout << "La partie est terminée !\n";
    plateau.afficher_plateau();
}