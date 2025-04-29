#include "fitxa.h"
#include "moviment.h"
#include "iostream"

Fitxa::Fitxa() : Fitxa(COLOR_BLANC, TIPUS_EMPTY) {}

Fitxa::Fitxa(ColorFitxa color, TipusFitxa tipus) : m_color(color), m_tipus(tipus), m_nMoviments(0) {}

TipusFitxa Fitxa::getTipus() const { return m_tipus; }
ColorFitxa Fitxa::getColor() const { return m_color; }
void Fitxa::setTipus(TipusFitxa tipus) { m_tipus = tipus; }
void Fitxa::setColor(ColorFitxa color) { m_color = color; }

void Fitxa::afegeixMovimentValid(Moviment moviment)
{
    m_movimentsValids[m_nMoviments++] = moviment;
}
void Fitxa::esborraMoviments() { m_nMoviments = 0; }
void Fitxa::getMoviments(Moviment destins[], int& n) const
{
    n = m_nMoviments;
    for (int i = 0; i < m_nMoviments; ++i) {
        destins[i] = m_movimentsValids[i];
    }
}
int Fitxa::getNumMoviments() const { return m_nMoviments; };

void Fitxa::promouADama() { m_tipus = TIPUS_DAMA; };

bool Fitxa::esBuida() const { return m_tipus == TIPUS_EMPTY; };

void Fitxa::mostraMoviments() const
{
    for (int i = 0; i < m_nMoviments; ++i) {
        std::cout << m_movimentsValids[i].getOrigen().toString() << ">>" << m_movimentsValids[i].getDesti().toString() << std::endl;
    }
}