#pragma once
#include <vector>
#include "posicio.h"

typedef enum 
{
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
} 
TipusFitxa;

typedef enum 
{
    COLOR_NEGRE,
    COLOR_BLANC
} 
ColorFitxa;


class Fitxa 
{
    public:
        Fitxa();
        Fitxa(ColorFitxa color, TipusFitxa tipus);

        ColorFitxa getColor() const;
        TipusFitxa getTipus() const;
        std::vector<Posicio> getMovimentsValids() const;

        void setColor(ColorFitxa color);
        void setTipus(TipusFitxa tipus);
        void setMovimentsValids(const std::vector<Posicio>& moviments);

        void afegeixMovimentValid(const Posicio& pos);
        void esborraMoviments();
        void promouADama();

        bool esBuida() const;

    private:
        ColorFitxa m_color;
        TipusFitxa m_tipus;
        std::vector<Posicio> m_movimentsValids;
};
