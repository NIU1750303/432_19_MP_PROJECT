#pragma once
#include <string>

class Posicio {
    public:
        Posicio();
        Posicio(const std::string& pos);
        Posicio(int fila, int columna);

        int getFila() const;
        int getColumna() const;
        void setFila(int fila);
        void setColumna(int columna);

        bool operator==(const Posicio& altra) const;
        std::string toString() const;

    private:
        int m_fila;
        int m_columna;
};

std::ostream& operator<<(std::ostream& os, const Posicio& p);