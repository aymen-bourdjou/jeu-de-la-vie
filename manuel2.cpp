#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> // Pour sf::sleep
#include "jeu_de_la_vie.h"
 
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
 
    // Création de la fenêtre SFML avec une taille réduite
    int largeurFenetre = 400;  
    int hauteurFenetre = 300;  
    sf::RenderWindow fenetre(sf::VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie");
    fenetre.setFramerateLimit(10);
 
    // Boucle principale
    for (int gen = 0; gen < generations; ++gen) {
       
        jeu.executer(1);
 
        // Affichage de la grille
        fenetre.clear();
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                sf::RectangleShape cellule(sf::Vector2f(10, 10));
                cellule.setPosition(j * 10, i * 10);
 
                // Détermine la couleur de la cellule
                if (grille.getCellule(i, j)) {
                    cellule.setFillColor(sf::Color::Green);
                } else {
                    cellule.setFillColor(sf::Color::Black);
                }
 
                // Vérifie si la cellule est dans la fenêtre avant de la dessiner
                if (cellule.getPosition().x < largeurFenetre && cellule.getPosition().y < hauteurFenetre) {
                    fenetre.draw(cellule);
                }
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
        sf::sleep(sf::milliseconds(100));
    }
 
    // Pause à la fin pour voir le résultat final
    bool enCours = true;
    while (enCours) {
        // Affichage de la grille finale
        fenetre.clear();
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                sf::RectangleShape cellule(sf::Vector2f(10, 10)); // Taille de chaque cellule
                cellule.setPosition(j * 10, i * 10); // Position de la cellule
 
                // Détermine la couleur de la cellule
                if (grille.getCellule(i, j)) {
                    cellule.setFillColor(sf::Color::Green); // Cellule vivante
                } else {
                    cellule.setFillColor(sf::Color::Black); // Cellule morte
                }
 
                // Vérifie si la cellule est dans la fenêtre avant de la dessiner
                if (cellule.getPosition().x < largeurFenetre && cellule.getPosition().y < hauteurFenetre) {
                    fenetre.draw(cellule);
                }
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
        sf::sleep(sf::milliseconds(100));    }
 
    return 0;
}