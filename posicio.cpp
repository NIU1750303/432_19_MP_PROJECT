#include "posicio.h"

Posicio::Posicio() : Posicio(0, 0) {}
Posicio::Posicio(const std::string& pos) : Posicio(pos[1] - '1', pos[0] - 'a') {}
Posicio::Posicio(int fila, int columna) : m_fila(fila), m_columna(columna) {}

int Posicio::getFila() const { return m_fila; } 
int Posicio::getColumna() const { return m_columna; };
void Posicio::setFila(int fila) { m_fila = fila; }
void Posicio::setColumna(int columna) { m_columna = columna; }

bool Posicio::operator==(const Posicio& altra) const
{
    return m_fila == altra.m_fila && m_columna == altra.m_columna;
}

std::string Posicio::toString() const
{
    return std::string(1, 'a' + m_columna) + std::string(1, '1' + m_fila);
}

std::ostream& operator<<(std::ostream& os, const Posicio& p) {
    os << p.toString();
    return os;
}