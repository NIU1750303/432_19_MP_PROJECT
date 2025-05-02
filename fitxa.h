//fitxa.h
#pragma once
#include "moviment.h"
#include "posicio.h"

#define MAX_MOVIMENTS 10

typedef enum {
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
} TipusFitxa;

typedef enum {
    COLOR_NEGRE,
    COLOR_BLANC
} ColorFitxa;

class Fitxa {
public:
    Fitxa();
    Fitxa(ColorFitxa color, TipusFitxa tipus);

    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    void setTipus(TipusFitxa tipus);
    void setColor(ColorFitxa color);

    void afegeixMovimentValid(Moviment moviment);
    void esborraMoviments();
    void getMoviments(Moviment destins[], int& n) const;
    int getNumMoviments() const;

    void promouADama();

    bool esBuida() const;

    void mostraMoviments() const;
private:
    ColorFitxa m_color;
    TipusFitxa m_tipus;
    Moviment m_movimentsValids[MAX_MOVIMENTS];
    int m_nMoviments;
};
