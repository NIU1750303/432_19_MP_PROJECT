#include "moviment.h"
#include "posicio.h"

Moviment::Moviment() : m_nPassos(0), m_nCaptures(0) {}
Moviment::Moviment(const Posicio& origen, const Posicio& desti) : m_nCaptures(0), m_nPassos(0)
{
    afegeixPas(origen);
    afegeixPas(desti);
}

void Moviment::afegeixPas(const Posicio& p)
{
    m_passos[m_nPassos++] = p;
}

void Moviment::afegeixCaptura(const Posicio& p)
{
    m_captures[m_nCaptures++] = p;
}

int Moviment::getNumPassos() const { return m_nPassos; }
int Moviment::getNumCaptures() const { return m_nCaptures; }
void Moviment::getRuta(Posicio passos[], int& n) const
{
    n = m_nPassos;
    for (int i = 0; i < m_nPassos; ++i) 
        passos[i] = m_passos[i];
}
void Moviment::getCaptures(Posicio captures[], int& n) const
{
    n = m_nCaptures;
    for (int i = 0; i < m_nCaptures; ++i) {
        captures[i] = m_captures[i];
    }
}

Posicio Moviment::getOrigen() const
{
    if (m_nPassos > 0)
        return m_passos[0];
    return Posicio(); 
}

Posicio Moviment::getDesti() const 
{
    if (m_nPassos > 0)
        return m_passos[m_nPassos - 1];
    return Posicio();
}