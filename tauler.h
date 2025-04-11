#pragma once
#include <string>
#include "fitxa.h"
#include "posicio.h"
#include "moviment.h"

#define N_FILES 8
#define N_COLUMNES 8

class Tauler {
public:
    Tauler();

    void inicialitza(const std::string& nomFitxer);
    void actualitzaMovimentsValids();
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) const;
    std::string toString() const;
    
private:
    Fitxa m_tauler[N_FILES][N_COLUMNES];

    bool dinsDelTauler(int fila, int col) const;
    void netejaMovimentsValids();
};
