#pragma once
#include <vector>
#include <string>
#include "posicio.h"

class Moviment {
public:
    Moviment();
    Moviment(const Posicio& origen);

    void afegeixPas(const Posicio& novaPosicio);
    void afegeixCaptura(const Posicio& posCapturada);

    Posicio getOrigen() const;
    Posicio getDesti() const;
    std::vector<Posicio> getRuta() const;
    std::vector<Posicio> getCaptures() const;

    std::string toString() const;

private:
    std::vector<Posicio> m_ruta;
    std::vector<Posicio> m_captures;
};
