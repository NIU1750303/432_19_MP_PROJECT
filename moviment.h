//moviment.h
#pragma once
#include "posicio.h"
#include <ostream>

#define MAX_PASSES 10
#define MAX_CAPTURES 10

class Moviment {
public:
    Moviment();
    Moviment(const Posicio& origen, const Posicio& desti);

    void afegeixPas(const Posicio& p);
    void afegeixCaptura(const Posicio& p);

    int getNumPassos() const;
    int getNumCaptures() const;
    void getRuta(Posicio passos[], int& n) const;
    void getCaptures(Posicio captures[], int& n) const;

    Posicio getOrigen() const;
    Posicio getDesti() const;


private:
    Posicio m_passos[MAX_PASSES];
    int m_nPassos;

    Posicio m_captures[MAX_CAPTURES];
    int m_nCaptures;
};
