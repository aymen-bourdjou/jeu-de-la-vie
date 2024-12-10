#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> // Pour sf::sleep
#include <iostream>
#include <stdexcept>
#include "jeu_de_la_vie.h"

// Fonction pour afficher la grille
void afficherGrille(sf::RenderWindow& fenetre, const Grille& grille, int largeurFenetre, int hauteurFenetre) {
    int lignes = grille.getLignes();
    int colonnes = grille.getColonnes();
    
    // Calcul de la taille dynamique des cellules
    float tailleCelluleX = static_cast<float>(largeurFenetre) / colonnes;
    float tailleCelluleY = static_cast<float>(hauteurFenetre) / lignes;

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            sf::RectangleShape cellule(sf::Vector2f(tailleCelluleX, tailleCelluleY));
            cellule.setPosition(j * tailleCelluleX, i * tailleCelluleY);

            // Détermine la couleur de la cellule
            if (grille.getCellule(i, j)) {
                cellule.setFillColor(sf::Color::Blue); // Cellule vivante
            } else {
                cellule.setFillColor(sf::Color::White); // Cellule morte
            }

            cellule.setOutlineColor(sf::Color::Black); // Contour noir
            cellule.setOutlineThickness(1);           // Épaisseur du contour

            fenetre.draw(cellule);
        }
    }
}

int main() {
    int lignes, colonnes;
    std::cout << "Entrez le nombre de lignes : ";
    std::cin >> lignes;
    std::cout << "Entrez le nombre de colonnes : ";
    std::cin >> colonnes;

    Grille grille(lignes, colonnes);
    try {
        grille.initialiserDepuisFichier("data.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    JeuDeLaVie jeu(&grille);
    int generations;
    std::cout << "Entrez le nombre de générations : ";
    std::cin >> generations;

    // Taille de la fenêtre SFML
    int largeurFenetre = 800;
    int hauteurFenetre = 600;
    sf::RenderWindow fenetre(sf::VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie");
    fenetre.setFramerateLimit(10);

    // Simulation des générations
    for (int gen = 0; gen < generations; ++gen) {
        jeu.executer(1);

        fenetre.clear();
        afficherGrille(fenetre, grille, largeurFenetre, hauteurFenetre);
        fenetre.display();

        sf::Event evenement;
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed) {
                fenetre.close();
                return 0;
            }
        }

        sf::sleep(sf::milliseconds(100)); // Pause entre les générations
    }

    // Pause pour afficher la grille finale
    while (fenetre.isOpen()) {
        fenetre.clear();
        afficherGrille(fenetre, grille, largeurFenetre, hauteurFenetre);
        fenetre.display();

        sf::Event evenement;
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed) {
                fenetre.close();
            }
        }

        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}
