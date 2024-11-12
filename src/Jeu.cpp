#include <iostream>
#include <fstream>
#include "Joueur.cpp"
#include "Plateau.cpp"

using namespace std;

class Jeu {
private:
    Joueur joueur_actuel;
    Plateau plateau;

public:
    Jeu(Joueur joueur, Plateau p)
    {
        joueur_actuel = joueur;
        plateau = p;
    } 

    void setJoueurActuel(Joueur joueur)
    {
        joueur_actuel = joueur;
    }

    void setPlateau(Plateau p)
    {
        plateau = p;
    }
};

// Méthode demarrer
void demarrer()
{
    // On initialise le plateau
    Plateau plateau = Plateau();
    plateau.initialiser();

    // On initialise les joueurs
    Joueur joueur1 = Joueur("Joueur 1", "blanc");
    Joueur joueur2 = Joueur("Joueur 2", "noir");

    // On initialise le jeu
    Jeu jeu = Jeu(joueur1, plateau);

    // On commence le jeu
    jeu.setJoueurActuel(joueur1);
    plateau.afficher();
}

// Méthode terminer
void terminer()
{
    cout << "Merci d'avoir joué !" << endl;
}

// Méthode changer_joueur
void changer_joueur(Joueur joueur_actuel, Joueur joueur_suivant)
{
    joueur_actuel = joueur_suivant;
}

