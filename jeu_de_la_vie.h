#pragma once
#include "grille.h"
 
class JeuDeLaVie {
private:
    Grille* grille;
 
public:
    JeuDeLaVie(Grille* g) : grille(g) {}
 
    void mettreAJour() {
        Grille nouvelleGrille(grille->getLignes(), grille->getColonnes());
       
        for (int i = 0; i < grille->getLignes(); ++i) {
            for (int j = 0; j < grille->getColonnes(); ++j) {
                int voisins = grille->compterVoisins(i, j);
                if (grille->getCellule(i, j) == 1) {
                    if (voisins < 2 || voisins > 3) {
                        nouvelleGrille.setCellule(i, j, 0);
                    } else {
                        nouvelleGrille.setCellule(i, j, 1);
                    }
                } else {
                    if (voisins == 3) {
                        nouvelleGrille.setCellule(i, j, 1);
                    } else {
                        nouvelleGrille.setCellule(i, j, 0);
                    }
                }
            }
        }
 
        for (int i = 0; i < grille->getLignes(); ++i) {
            for (int j = 0; j < grille->getColonnes(); ++j) {
                grille->setCellule(i, j, nouvelleGrille.getCellule(i, j));
            }
        }
    }
 
    void executer(int generations) {
        for (int i = 0; i < generations; ++i) {
            std::cout << "Génération " << i + 1 << ":" << std::endl;
            mettreAJour();
            grille->afficher();
            std::cout << std::endl;
        }
    }
};
