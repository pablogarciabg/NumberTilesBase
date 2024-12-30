//
// Created by Usuario on 29/12/2024.
//

#ifndef NUMBERTILESBASE_JUEGO_H
#define NUMBERTILESBASE_JUEGO_H

#include <iostream>
#include "Tablero.h"
using namespace std;

struct Config {
    int totalColumnas;
    int totalFilas;
    int filasIniciales;
};

struct Juego {
    Config config;
    tablero tab;
    int puntuacion;
};


void inicializarJuego(Juego &juego);
void play(Juego &juego);

#endif //NUMBERTILESBASE_JUEGO_H
