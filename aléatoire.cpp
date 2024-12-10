#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> // Pour sf::sleep
#include <random>
#include <vector>
#include <iostream>
#include "jeu_de_la_vie.h"

// Fonction pour générer un tableau aléatoire de 0 et 1
std::vector<std::vector<int>> genererTableauAleatoire(int lignes, int colonnes) {
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    std::vector<std::vector<int>> tab(lignes, std::vector<int>(colonnes));
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            tab[i][j] = dis(gen);  
        }
    }
    return tab;
}

// Fonction pour afficher la grille
void afficherGrille(sf::RenderWindow& fenetre, const Grille& grille, int tailleCellule) {
    int lignes = grille.getLignes();
    int colonnes = grille.getColonnes();

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            sf::RectangleShape cellule(sf::Vector2f(tailleCellule, tailleCellule));
            cellule.setPosition(j * tailleCellule, i * tailleCellule);

            // Détermine la couleur de la cellule
            if (grille.getCellule(i, j)) {
                cellule.setFillColor(sf::Color::Blue); // Cellule vivante
            } else {
                cellule.setFillColor(sf::Color::White); // Cellule morte
            }

            cellule.setOutlineColor(sf::Color::Black); // Contour 
            cellule.setOutlineThickness(1);

            fenetre.draw(cellule);
        }
    }
}

int main() {
    int lignes, colonnes, generations;

    // Entrée utilisateur
    std::cout << "Entrez le nombre de lignes: ";
    std::cin >> lignes;
    std::cout << "Entrez le nombre de colonnes: ";
    std::cin >> colonnes;
    std::cout << "Entrez le nombre de générations: ";
    std::cin >> generations;

    // Initialisation de la grille
    std::vector<std::vector<int>> grilleInitiale = genererTableauAleatoire(lignes, colonnes);
    Grille grille(lignes, colonnes);

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            grille.setCellule(i, j, grilleInitiale[i][j]);
        }
    }

    JeuDeLaVie jeu(&grille);

    // Paramètres graphiques
    const int tailleCellule = 10;
    int largeurFenetre = colonnes * tailleCellule;
    int hauteurFenetre = lignes * tailleCellule;
    sf::RenderWindow fenetre(sf::VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie");
    fenetre.setFramerateLimit(10);

    // Boucle principale pour les générations
    for (int gen = 0; gen < generations; ++gen) {
        std::cout << "Génération " << gen + 1 << std::endl;
        jeu.executer(1);

        fenetre.clear();
        afficherGrille(fenetre, grille, tailleCellule);
        fenetre.display();

        sf::Event evenement;
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed) {
                fenetre.close();
                return 0;
            }
        }

        sf::sleep(sf::milliseconds(100)); 
    }

    // Pause pour afficher la grille finale
    while (fenetre.isOpen()) {
        fenetre.clear();
        afficherGrille(fenetre, grille, tailleCellule);
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
