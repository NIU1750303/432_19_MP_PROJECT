#include "fitxa.h"

Fitxa::Fitxa() 
{
    m_tipus = TIPUS_EMPTY;
    m_color = COLOR_BLANC;
}

Fitxa::Fitxa(ColorFitxa color, TipusFitxa tipus) 
{
    m_color = color;
    m_tipus = tipus;
}

ColorFitxa Fitxa::getColor() const { return m_color; }

TipusFitxa Fitxa::getTipus() const { return m_tipus; }

std::vector<Posicio> Fitxa::getMovimentsValids() const { return m_movimentsValids; }

void Fitxa::setColor(ColorFitxa color) { m_color = color; }

void Fitxa::setTipus(TipusFitxa tipus) { m_tipus = tipus; }

void Fitxa::setMovimentsValids(const std::vector<Posicio>& moviments) { m_movimentsValids = moviments; }

void Fitxa::afegeixMovimentValid(const Posicio& pos) { m_movimentsValids.push_back(pos);}

void Fitxa::esborraMoviments() { m_movimentsValids.clear(); }

void Fitxa::promouADama() 
{ 
    if (m_tipus == TIPUS_NORMAL)
        m_tipus = TIPUS_DAMA;
}

bool Fitxa::esBuida() const 
{
    return m_tipus == TIPUS_EMPTY;
}
