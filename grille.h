#pragma once
#include <iostream>
#include <fstream>
#include "cellule.h"
 
class Grille {
private:
    int lignes;
    int colonnes;
    Cellule** grille;
 
public:
    Grille(int l, int c) : lignes(l), colonnes(c) {
        grille = new Cellule*[lignes];
        for (int i = 0; i < lignes; ++i) {
            grille[i] = new Cellule[colonnes];
        }
    }
 
    ~Grille() {
        for (int i = 0; i < lignes; ++i) {
            delete[] grille[i];
        }
        delete[] grille;
    }
 
    void initialiserDepuisFichier(const std::string& nomFichier) {
        std::ifstream fichier(nomFichier);
        if (!fichier.is_open()) {
            throw std::runtime_error("Erreur lors de l'ouverture du fichier.");
        }

 
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                int etat;
                fichier >> etat;
                grille[i][j].setEtat(etat);
            }
        }
 
        fichier.close();
    }
 
    void afficher() const {
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                std::cout << grille[i][j].getEtat() << "\t";
            }
            std::cout << std::endl;
        }
    }
 
    int getCellule(int x, int y) const {
        if (x < 0 || x >= lignes || y < 0 || y >= colonnes) return 0;
        return grille[x][y].getEtat();
    }
 
    void setCellule(int x, int y, int valeur) {
        if (x >= 0 && x < lignes && y >= 0 && y < colonnes) {
            grille[x][y].setEtat(valeur);
        }
    }
 
    int getLignes() const { return lignes; }
    int getColonnes() const { return colonnes; }
 
    int compterVoisins(int x, int y) const {
        int compte = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (!(i == 0 && j == 0)) {
                    compte += getCellule(x + i, y + j);
                }
            }
        }
        return compte;
    }
};
