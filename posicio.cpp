#include "posicio.h"
using namespace std;

Posicio::Posicio() : Posicio(0, 0) {}

Posicio::Posicio(const string& pos) : Posicio(pos[0] - 'a', pos[1] - '1') {}

Posicio::Posicio(int fila, int columna) : m_fila(fila), m_columna(columna) {}


int Posicio::getFila() const { return m_fila; }

int Posicio::getColumna() const { return m_columna; }

void Posicio::setFila(int fila) { m_fila = fila; }

void Posicio::setColumna(int columna) { m_columna = columna; }

bool Posicio::operator==(const Posicio& altra) const 
{ 
    return m_fila == altra.m_fila && m_columna == altra.m_columna;
}

string Posicio::toString() const 
{
    string pos = "";
    pos += static_cast<char>('a' + m_columna);
    pos += static_cast<char>('1' + m_fila);
    return pos;
}
