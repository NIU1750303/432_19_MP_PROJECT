#include "tauler.hpp"
#include <fstream>
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

                    if (dinsDelTauler(nf, nc) && m_tauler[nf][nc].esBuida()) {
                        Posicio p1(i, j), p2(nf, nc);
                        Moviment m(p1, p2);
                        f.afegeixMovimentValid(m);
                    }
                }

                for (int k = 0; k < 2; k++) {
                    int nf = i + 2 * df[k];
                    int nc = j + 2 * dc[k];
                    int mf = i + df[k];
                    int mc = j + dc[k];

                    if (dinsDelTauler(nf, nc) && m_tauler[nf][nc].esBuida() && !m_tauler[mf][mc].esBuida()) {
                        if (m_tauler[mf][mc].getColor() != color) {
                            Posicio p1(i, j), p2(nf, nc);
                            Moviment m(p1, p2);
                            m.afegeixCaptura(Posicio(mf, mc));
                            f.afegeixMovimentValid(m);
                        }
                    }
                }
            }
            else if (tipus == TIPUS_DAMA) {
                int df[4] = {1, 1, -1, -1};
                int dc[4] = {1, -1, 1, -1};

                for (int k = 0; k < 4; ++k) {
                    int nf = i + df[k];
                    int nc = j + dc[k];
                    while (dinsDelTauler(nf, nc) && m_tauler[nf][nc].esBuida()) {
                        Posicio p1(i, j), p2(nf, nc);
                        Moviment m(p1, p2);
                        f.afegeixMovimentValid(m);
                        nf += df[k];
                        nc += dc[k];
                    }

                    if (dinsDelTauler(nf, nc) && !m_tauler[nf][nc].esBuida() && m_tauler[nf][nc].getColor() != color) {
                        int nf2 = nf + df[k];
                        int nc2 = nc + dc[k];
                        if (dinsDelTauler(nf2, nc2) && m_tauler[nf2][nc2].esBuida()) {
                            Posicio p1(i, j), p2(nf2, nc2);
                            Moviment m(p1, p2);
                            m.afegeixCaptura(Posicio(nf, nc));
                            f.afegeixMovimentValid(m);
                        }
                    }
                }
            }
        }
    }
}


void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) const 
{
    nPosicions = 0;
    int fila = origen.getFila();
    int columna = origen.getColumna();
    const Fitxa& f = m_tauler[fila][columna];

    if (f.esBuida())
        return;

    Moviment moviments[20];
    int nMovs = 0;
    f.getMoviments(moviments, nMovs);

    for (int i = 0; i < nMovs; ++i) {
        posicionsPossibles[nPosicions++] = moviments[i].getDesti();
    }
}


string Tauler::toString() const 
{
    string result = "";
    for (int i = 7; i >= 0; i--) 
    {
        result += string(1, '0' + i + 1) + ": ";
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
    result += "  a b c d e f g h";
    return result;
}

bool Tauler::dinsDelTauler(const int& fila, const int& columna) const
{
    return fila >= 0 && fila < N_FILES && columna >= 0 && columna < N_COLUMNES;
}

bool Tauler::hiHaCapturesDisponibles(ColorFitxa color) const {
    for (int i = 0; i < N_FILES; ++i) {
        for (int j = 0; j < N_COLUMNES; ++j) {
            const Fitxa& f = m_tauler[i][j];
            if (f.esBuida() || f.getColor() != color) continue;
            TipusFitxa tipus = f.getTipus();
            if (tipus == TIPUS_NORMAL) {
                int dir = (color == COLOR_BLANC ? 1 : -1);
                for (int dc = -1; dc <= 1; dc += 2) {
                    int mi = i + dir, mj = j + dc;
                    int ei = i + 2*dir, ej = j + 2*dc;
                    if (dinsDelTauler(mi,mj) && dinsDelTauler(ei,ej)) {
                        const Fitxa& medio = m_tauler[mi][mj];
                        if (!medio.esBuida() && medio.getColor() != color
                            && m_tauler[ei][ej].esBuida()) {
                            return true;
                        }
                    }
                }
            } else { // dama
                static const int dfn[4] = {1,1,-1,-1};
                static const int dcn[4] = {1,-1,1,-1};
                for (int d = 0; d < 4; ++d) {
                    int ni = i + dfn[d], nj = j + dcn[d];
                    while (dinsDelTauler(ni,nj) && m_tauler[ni][nj].esBuida()) {
                        ni += dfn[d]; nj += dcn[d];
                    }
                    if (dinsDelTauler(ni,nj)) {
                        const Fitxa& bloque = m_tauler[ni][nj];
                        if (!bloque.esBuida() && bloque.getColor() != color) {
                            int ei = ni + dfn[d], ej = nj + dcn[d];
                            if (dinsDelTauler(ei,ej) && m_tauler[ei][ej].esBuida()) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Tauler::bufaFitxa(const Posicio& origen) {
    m_tauler[origen.getFila()][origen.getColumna()] = Fitxa();
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) {
    // 1) validar destino
    Posicio dests[MAX_MOVIMENTS];
    int nPos = 0;
    getPosicionsPossibles(origen, nPos, dests);
    bool valido = false;
    for (int i = 0; i < nPos; ++i)
        if (dests[i] == desti) { valido = true; break; }
    if (!valido) return false;

    // 2) actualizo movimientos y busco máxima captura
    actualitzaMovimentsValids();
    Fitxa& f = m_tauler[origen.getFila()][origen.getColumna()];
    Moviment movs[MAX_MOVIMENTS];
    int nm = 0;
    f.getMoviments(movs, nm);

    int maxCap = 0;
    for (int i = 0; i < nm; ++i) {
        int c = movs[i].getNumCaptures();
        if (c > maxCap) maxCap = c;
    }

    // 3) elijo el movimiento concreto
    Moviment* sel = nullptr;
    for (int i = 0; i < nm; ++i) {
        if (movs[i].getDesti() == desti 
            && movs[i].getNumCaptures() == maxCap) {
            sel = &movs[i];
            break;
        }
    }

    // 4) aplico capturas
    Posicio caps[MAX_CAPTURES];
    int nc = 0;
    sel->getCaptures(caps, nc);
    for (int k = 0; k < nc; ++k) {
        const Posicio& p = caps[k];
        m_tauler[p.getFila()][p.getColumna()] = Fitxa();
    }

    // 5) muevo y promuevo si toca
    Fitxa temp = f;
    m_tauler[origen.getFila()][origen.getColumna()] = Fitxa();
    m_tauler[desti.getFila()][desti.getColumna()] = temp;
    if (temp.getTipus() == TIPUS_NORMAL) {
        if ((temp.getColor() == COLOR_BLANC && desti.getFila() == N_FILES-1) ||
            (temp.getColor() == COLOR_NEGRE && desti.getFila() == 0)) {
            m_tauler[desti.getFila()][desti.getColumna()].promouADama();
        }
    }

    // 6) si había captura obligatoria y no capturó, "bufar"
    if (maxCap == 0 && hiHaCapturesDisponibles(temp.getColor())) {
        bufaFitxa(origen);
    }

    return true;
}
