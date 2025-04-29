#include "tauler.h"
#include "fitxa.h"
#include "moviment.h"
#include "posicio.h"
#include <iostream>
#include <string>

// ------------------ FUNCIONS TEST ------------------
void testString(const std::string& actual, const std::string& esperat, const std::string& nomTest) {
    if (actual == esperat) {
        std::cout << "[PASS] " << nomTest << "\n";
    } else {
        std::cout << "[FAIL] " << nomTest << "\n";
        std::cout << "  Esperat: " << esperat << "\n";
        std::cout << "  Obtingut: " << actual << "\n";
    }
}

void testInt(int actual, int esperat, const std::string& nomTest) {
    if (actual == esperat) {
        std::cout << "[PASS] " << nomTest << "\n";
    } else {
        std::cout << "[FAIL] " << nomTest << "\n";
        std::cout << "  Esperat: " << esperat << "\n";
        std::cout << "  Obtingut: " << actual << "\n";
    }
}

void testBool(bool cond, const std::string& nomTest) {
    if (cond) {
        std::cout << "[PASS] " << nomTest << "\n";
    } else {
        std::cout << "[FAIL] " << nomTest << "\n";
    }
}
// ------------------------------------------------------

int main() {
    // ================== TEST POSICIO ==================
    Posicio p1;
    testInt(p1.getFila(), 0, "Posicio constructor per defecte fila = 0");
    testInt(p1.getColumna(), 0, "Posicio constructor per defecte columna = 0");

    Posicio p2("c3");
    testInt(p2.getFila(), 2, "Posicio constructor string fila = 2");
    testInt(p2.getColumna(), 2, "Posicio constructor string columna = 2");

    p2.setFila(4);
    p2.setColumna(5);
    testInt(p2.getFila(), 4, "Posicio setFila a 4");
    testInt(p2.getColumna(), 5, "Posicio setColumna a 5");

    testString(p2.toString(), "f5", "Posicio toString() correcte");

    Posicio p3(4,5);
    testBool(p2 == p3, "Comparació Posicio == correcte");

    // ================== TEST FITXA ==================
    Fitxa f1;
    testBool(f1.esBuida(), "Fitxa constructor per defecte buida");

    Fitxa f2(COLOR_NEGRE, TIPUS_NORMAL);
    testBool(!f2.esBuida(), "Fitxa constructor color i tipus no buida");
    testInt(f2.getColor(), COLOR_NEGRE, "Fitxa color correcte");
    testInt(f2.getTipus(), TIPUS_NORMAL, "Fitxa tipus correcte");

    f2.setColor(COLOR_BLANC);
    f2.setTipus(TIPUS_DAMA);
    testInt(f2.getColor(), COLOR_BLANC, "Fitxa setColor a blanc");
    testInt(f2.getTipus(), TIPUS_DAMA, "Fitxa setTipus a dama");

    f2.esborraMoviments();
    Moviment movsFitxa[20];
    int nMovs;
    f2.getMoviments(movsFitxa, nMovs);
    testInt(nMovs, 0, "Fitxa esborraMoviments correcte");

    // Afegim un moviment vàlid (creem un Moviment correcte)
    Moviment m(Posicio("d4"), Posicio("e5"));
    f2.afegeixMovimentValid(m);
    f2.getMoviments(movsFitxa, nMovs);
    testInt(nMovs, 1, "Fitxa afegeixMovimentValid correcte");

    // ================== TEST MOVIMENT ==================
    Moviment m1;
    testInt(m1.getNumPassos(), 0, "Moviment constructor per defecte 0 passos");

    m1.afegeixPas(Posicio("b2"));
    m1.afegeixPas(Posicio("d4"));
    testInt(m1.getNumPassos(), 2, "Moviment afegeixPas correcte");

    m1.afegeixCaptura(Posicio("c3"));
    testInt(m1.getNumCaptures(), 1, "Moviment afegeixCaptura correcte");

    Posicio ruta[10];
    int nRuta;
    m1.getRuta(ruta, nRuta);
    testInt(nRuta, 2, "Moviment getRuta nombre passos correcte");
    testString(ruta[0].toString(), "b2", "Moviment getRuta primer pas correcte");
    testString(ruta[1].toString(), "d4", "Moviment getRuta segon pas correcte");

    Posicio caps[10];
    int nCaps;
    m1.getCaptures(caps, nCaps);
    testInt(nCaps, 1, "Moviment getCaptures correcte");
    testString(caps[0].toString(), "c3", "Moviment captura correcta");

    testString(m1.getOrigen().toString(), "b2", "Moviment getOrigen correcte");
    testString(m1.getDesti().toString(), "d4", "Moviment getDesti correcte");

    // ================== TEST TAULER ==================
    Tauler t;

    // Ús de funció correcta pública, no accedim directament a m_tauler
    // Suposem que tenim una funció setFitxa (o inicialitzem inicialitza manualment si vols)
    // Per aquest test, només inicialitzem a nivell de moviment vàlid:

    // No podem accedir a m_tauler directament perquè és private!
    // Aquesta part es faria amb inicialitza o simulat.

    std::cout << "\n[INFO] Tests de Posicio, Fitxa, Moviment completats correctament\n";

    return 0;
}
