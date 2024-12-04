#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> // Pour sf::sleep
#include <random>
#include <vector>
#include <iostream>
#include "jeu_de_la_vie.h"

// générer un tableau aléatoire de 0 et 1
std::vector<std::vector<int>> tableau(int xtab, int ytab) {
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    std::vector<std::vector<int>> tab(xtab, std::vector<int>(ytab));

    for (int i = 0; i < xtab; ++i) {
        for (int j = 0; j < ytab; ++j) {
            tab[i][j] = dis(gen);  
        }
    }
    return tab;
}

int main() {
    int lignes, colonnes;
    std::cout << "Entrez le nombre de lignes: ";
    std::cin >> lignes;
    std::cout << "Entrez le nombre de colonnes: ";
    std::cin >> colonnes;

    // Utilisation de la fonction tableau pour générer un tableau aléatoire
    std::vector<std::vector<int>> grilleInitiale = tableau(lignes, colonnes);
    Grille grille(lignes, colonnes);

    // Initialiser la grille avec le tableau généré aléatoirement
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            grille.setCellule(i, j, grilleInitiale[i][j]);  // Remplir la grille avec les valeurs du tableau aléatoire
        }
    }

    JeuDeLaVie jeu(&grille);
    int generations;
    std::cout << "Entrez le nombre de générations: ";
    std::cin >> generations;

    // Définir la taille de chaque cellule
    const int tailleCellule = 10;

    // Ajuster la taille de la fenêtre en fonction du nombre de lignes et de colonnes
    int largeurFenetre = colonnes * tailleCellule;  // Largeur de la fenêtre
    int hauteurFenetre = lignes * tailleCellule; // Hauteur de la fenêtre
    sf::RenderWindow fenetre(sf::VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie");
    fenetre.setFramerateLimit(10); // Limite de la fréquence d'images

    // Boucle principale
    for (int gen = 0; gen < generations; ++gen) {
        std::cout << "Génération " << gen + 1 << ":" << std::endl;
        // Exécute une génération du jeu
        jeu.executer(1);

        // Affichage de la grille
        fenetre.clear();
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                sf::RectangleShape cellule(sf::Vector2f(tailleCellule, tailleCellule)); // Taille de chaque cellule
                cellule.setPosition(j * tailleCellule, i * tailleCellule); // Position de la cellule

                // Détermine la couleur de la cellule
                if (grille.getCellule(i, j)) {
                    cellule.setFillColor(sf::Color::Blue); // Cellule vivante
                } else {
                    cellule.setFillColor(sf::Color::White); // Cellule morte
                }

                // Ajouter un contour noir à la cellule
                cellule.setOutlineColor(sf::Color::Black); 
                cellule.setOutlineThickness(1);            

                fenetre.draw(cellule);
            }
        }
        fenetre.display();

        // Gestion des événements
        sf::Event evenement;
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed) {
                fenetre.close();
            }
        }

        // Pause entre les générations
        sf::sleep(sf::milliseconds(1)); 
    }

    // Pause à la fin pour voir le résultat final
    bool enCours = true;
    while (enCours) {
        // Affichage de la grille finale
        fenetre.clear();
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                sf::RectangleShape cellule(sf::Vector2f(tailleCellule, tailleCellule)); // Taille de chaque cellule
                cellule.setPosition(j * tailleCellule, i * tailleCellule); // Position de la cellule

                // Détermine la couleur de la cellule
                if (grille.getCellule(i, j)) {
                    cellule.setFillColor(sf::Color::Blue); // Cellule vivante
                } else {
                    cellule.setFillColor(sf::Color::White); // Cellule morte
                }

                // Ajouter un contour noir à la cellule
                cellule.setOutlineColor(sf::Color::Black); // Contour noir
                cellule.setOutlineThickness(1);            // Épaisseur du contour

                fenetre.draw(cellule);
            }
        }
        fenetre.display();

        // Gestion des événements
        sf::Event evenement;
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed) {
                enCours = false; // Ferme la fenêtre
            }
        }

        // Pause pour permettre à l'utilisateur de voir le résultat final
        sf::sleep(sf::milliseconds(100)); // Pause de 100 millisecondes
    }

    return 0;
}
