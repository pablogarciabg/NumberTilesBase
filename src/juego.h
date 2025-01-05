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
    int comoIniciar;
};

struct Juego {
    Config config;
    tablero tab;
    int puntuacion;

};

//PRE={}
//COMPLEJIDAD=O()
//POST=
void inicializarJuego(Juego &juego);

//PRE={}
//COMPLEJIDAD=O()
//POST=
void play(Juego &juego);

#endif //NUMBERTILESBASE_JUEGO_H
