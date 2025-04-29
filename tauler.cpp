#include "tauler.h"
#include "fitxa.h"
#include "iostream"
#include "moviment.h"
#include "posicio.h"
#include <fstream>
#include <ostream>
#include <string>
using namespace std;

Tauler::Tauler() 
{
    for(int i = 0; i < N_FILES; i++)
    {
        for(int j = 0; j < N_COLUMNES; j++)
            m_tauler[i][j] = Fitxa(COLOR_BLANC, TIPUS_EMPTY);
    }
}
void Tauler::inicialitza(const string& nomFitxer)
{
    char type_char;
    TipusFitxa type;
    ColorFitxa color;
    string position;
    ifstream fitxer(nomFitxer);
    while(!fitxer.eof())
    {
        fitxer >> type_char;
        switch (type_char) {
            case 'O':
                type = TIPUS_NORMAL;
                color = COLOR_BLANC;
                break;
            case 'X':
                type = TIPUS_NORMAL;
                color = COLOR_NEGRE;
                break;
            case 'D':
                type = TIPUS_DAMA;
                color = COLOR_BLANC;
                break;
            case 'R':
                type = TIPUS_DAMA;
                color = COLOR_NEGRE;
                break;
            default:
                break;
        }
        
        fitxer >> position;
        Posicio pos = Posicio(position);

       
        m_tauler[pos.getFila()][pos.getColumna()] = Fitxa(color, type);

    }
}
void Tauler::actualitzaMovimentsValids() 
{
    for (int i = 0 ; i < N_FILES; i++) {
        for (int j = 0; j < N_COLUMNES; j++) {
            Fitxa& f = m_tauler[i][j];
            if (f.esBuida()) continue;

            f.esborraMoviments();

            ColorFitxa color = f.getColor();
            TipusFitxa tipus = f.getTipus();

            if (tipus == TIPUS_NORMAL) {
                int dir = (color == COLOR_BLANC) ? 1 : -1;
                int df[2] = { dir, dir };
                int dc[2] = { -1, 1 };

                for (int k = 0; k < 2; k++) {
                    int nf = i + df[k];
                    int nc = j + dc[k];

                    // Moviment simple
                    if (dinsDelTauler(nf, nc) && m_tauler[nf][nc].esBuida()) {
                        f.afegeixMovimentValid(Moviment(Posicio(i, j), Posicio(nf, nc)));
                    }

                    // Captura
                    int midf = i + df[k];
                    int midc = j + dc[k];
                    int capf = i + 2 * df[k];
                    int capc = j + 2 * dc[k];

                    if (dinsDelTauler(capf, capc)) {
                        Fitxa& inter = m_tauler[midf][midc];
                        if (!inter.esBuida() && inter.getColor() != color && m_tauler[capf][capc].esBuida()) {
                            Moviment m(Posicio(i, j), Posicio(capf, capc));
                            m.afegeixCaptura(Posicio(midf, midc));
                            f.afegeixMovimentValid(m);
                        }
                    }
                }
            }

            else if (tipus == TIPUS_DAMA) {
                int df[4] = { -1, -1, 1, 1 };
                int dc[4] = { -1, 1, -1, 1 };

                for (int d = 0; d < 4; ++d) {
                    int nf = i + df[d];
                    int nc = j + dc[d];

                    // Moviments lliures
                    while (dinsDelTauler(nf, nc) && m_tauler[nf][nc].esBuida()) {
                        f.afegeixMovimentValid(Moviment(Posicio(i, j), Posicio(nf, nc)));
                        nf += df[d];
                        nc += dc[d];
                    }

                    // Captura simple
                    int midf = nf;
                    int midc = nc;
                    nf += df[d];
                    nc += dc[d];

                    if (dinsDelTauler(nf, nc) && 
                        !m_tauler[midf][midc].esBuida() &&
                        m_tauler[midf][midc].getColor() != color &&
                        m_tauler[nf][nc].esBuida()) {

                        Moviment m(Posicio(i, j), Posicio(nf, nc));
                        m.afegeixCaptura(Posicio(midf, midc));
                        f.afegeixMovimentValid(m);
                    }
                }
            }
        }
    }
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) 
{ 
    return true;
}
void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) const 
{
    int fila = origen.getFila();
    int col = origen.getColumna();

    if (!dinsDelTauler(fila, col)) {
        nPosicions = 0;
        return;
    }

    const Fitxa& f = m_tauler[fila][col];

    if (f.esBuida()) {
        nPosicions = 0;
        return;
    }

    // Obtenim tots els moviments vàlids
    Moviment movs[MAX_MOVIMENTS];
    int nMovs;
    f.getMoviments(movs, nMovs);

    nPosicions = 0;
    for (int i = 0; i < nMovs; ++i) {
        posicionsPossibles[nPosicions++] = movs[i].getDesti();
    }
}

string Tauler::toString() const 
{
    string result = "";
    for (int i = 7; i >= 0; i--) 
    {
        result += string(1, '0' + i + 1) + ":";
        for (int j = 0; j < N_COLUMNES; j++)
        {
            Fitxa f = m_tauler[i][j];
            switch (f.getTipus()) 
            {                
                case TIPUS_NORMAL:
                    if (f.getColor() == COLOR_BLANC) {
                        result += "O";
                    } else {
                        result += "X";
                    }
                    break;
                case TIPUS_DAMA:
                    if (f.getColor() == COLOR_BLANC) {
                        result += "D";
                    } else {
                        result += "R";
                   }
                    break;
                case TIPUS_EMPTY:
                    result += "_";
            }       
            result += " ";
        }   
        result += "\n";
    }
    result += "  A B C D E F G H";
    return result;
}

bool Tauler::dinsDelTauler(const int& fila, const int& columna) const
{
    return fila >= 0 && fila < N_FILES && columna >= 0 && columna < N_COLUMNES;
}