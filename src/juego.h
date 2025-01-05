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
//COMPLEJIDAD=O(n^2)
//POST={Se encarga de pintar el tablero usando el entorno, es modulo se usa cada vez que se hace una fusion}
void repintarTablero (Juego &juego);


//PRE={}
//COMPLEJIDAD=O(n^2)
//POST={Se encarga de arrancar el entorno, leer el fichero de configuracion y pintar el tablero}
void inicializarJuego(Juego &juego);

//PRE={}
//COMPLEJIDAD=O(n)
//POST={Se encarga de llevar a cabo todas las operaciones, del juego, dependiendo de le tecla puslsada}
void play(Juego &juego);

#endif //NUMBERTILESBASE_JUEGO_H
