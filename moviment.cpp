#include "moviment.h"
using namespace std;

Moviment::Moviment() {}

Moviment::Moviment(const Posicio& origen) { m_ruta.push_back(origen); }

void Moviment::afegeixPas(const Posicio& novaPosicio) { m_ruta.push_back(novaPosicio); }

void Moviment::afegeixCaptura(const Posicio& posCapturada) { m_captures.push_back(posCapturada);}

Posicio Moviment::getOrigen() const 
{ 
    if (!m_ruta.empty())
        return m_ruta[0];
    return Posicio();
}

Posicio Moviment::getDesti() const 
{
    if (!m_ruta.empty())
        return m_ruta.back();
    return Posicio();
}

vector<Posicio> Moviment::getRuta() const { return m_ruta; }

vector<Posicio> Moviment::getCaptures() const { return m_captures; }

string Moviment::toString() const 
{ 
    string resultat;
    for (size_t i = 0; i < m_ruta.size(); ++i) 
    {
        resultat += m_ruta[i].toString();
        if (i < m_ruta.size() - 1)
            resultat += " -> ";
    }
    return resultat;
}
