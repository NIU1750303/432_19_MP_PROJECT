//tauler.hpp
#pragma once
#include <string>
#include "fitxa.h"
#include "posicio.h"

#define N_FILES 8
#define N_COLUMNES 8

class Tauler {
public:
    Tauler();
    void inicialitza(const std::string& nomFitxer);
    void mostra() const;
    void actualitzaMovimentsValids();
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) const;
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    void capturesSuccesives(int fila, int col, Moviment movActual, Moviment movs[], int& nMovs);
    std::string toString() const;

private:
    Fitxa m_tauler[N_FILES][N_COLUMNES];
    bool dinsDelTauler(const int& fila, const int& columna) const;
    bool hiHaCapturesDisponibles(ColorFitxa color) const;
    void bufaFitxa(const Posicio& origen);
};

