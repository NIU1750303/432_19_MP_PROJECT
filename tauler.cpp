#include "tauler.h"
#include <fstream>
#include <iostream>

using namespace std;

Tauler::Tauler() 
{
    for (int i = 0; i < N_FILES; ++i) 
    {
        for (int j = 0; j < N_COLUMNES; ++j) 
            m_tauler[i][j] = Fitxa();
    }
}

void Tauler::inicialitza(const string& nomFitxer) 
{
    ifstream fitxer(nomFitxer);
    if (!fitxer.is_open()) 
    {
        cerr << "No s'ha pogut obrir el fitxer: " << nomFitxer << endl;
        return;
    }

    char tipus;
    string pos;

    while (fitxer >> tipus >> pos) 
    {
        if (pos.length() != 2)
            continue;

        Posicio p(pos);
        int fila = p.getFila();
        int col = p.getColumna();

        ColorFitxa color;
        TipusFitxa tipusFitxa;

        switch (tipus) 
        {
            case 'O':
                color = COLOR_BLANC;
                tipusFitxa = TIPUS_NORMAL;
                break;
            case 'D':
                color = COLOR_BLANC;
                tipusFitxa = TIPUS_DAMA;
                break;
            case 'X':
                color = COLOR_NEGRE;
                tipusFitxa = TIPUS_NORMAL;
                break;
            case 'R':
                color = COLOR_NEGRE;
                tipusFitxa = TIPUS_DAMA;
                break;
            default:
                continue;
        }

        m_tauler[fila][col] = Fitxa(color, tipusFitxa);
    }

    fitxer.close();
}

string Tauler::toString() const 
{
    string resultat;

    for (int j = N_COLUMNES - 1; j >= 0; --j)
    {
        resultat += static_cast<char>('a' + j);
        resultat += "   ";

        for (int i = 0; i < N_FILES; ++i)
        {
            string c;
            const Fitxa& f = m_tauler[i][j];

            if (!f.esBuida()) 
            {
                if (f.getTipus() == TIPUS_DAMA)
                    c = (f.getColor() == COLOR_BLANC) ? "D" : "R";
                else
                    c = (f.getColor() == COLOR_BLANC) ? "O" : "X";
            } 
            else 
            {
                bool negra = (i + j) % 2 == 1;
                c = negra ? "■" : "□";
            }

            resultat += c + " ";
        }

        resultat += "\n";
    }

    resultat += "\n    1 2 3 4 5 6 7 8\n";

    return resultat;
}



