#include "tauler.h"
#include <iostream>

int main() {
    Tauler t;

    t.inicialitza("./arxius/inicial.txt");
    std::cout << t.toString() << std::endl;

    return 0;
}
