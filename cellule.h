#pragma once
 
class Cellule {
private:
    int etat;
 
public:
    Cellule() : etat(0) {}
    int getEtat() const { return etat; }
    void setEtat(int s) { etat = s; }
};
