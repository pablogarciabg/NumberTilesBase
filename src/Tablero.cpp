//
// Created by Pablo Garcia & Ruben Flete on 07/12/2024.
//

#include <iostream>
#include <cmath>

using namespace std;

#include "Tablero.h"
#include "casilla.h"
#include "entorno.h"



void pasarColumnaBase0(int &col){
    if (col >= 1){
        col--;
    }
    if (col == MAX_COLUMNAS){ //Suponemos que nunca se introducen datos incorrectos

        col=MAX_COLUMNAS-1;
    }
    if (col == 0){ //Suponemos que nunca se introducen datos incorrectos

        col=0;
    }
}

void pasarFilasBase0 (int &fila){
    if (fila >= 1){
        fila--;
    }
    if (fila==MAX_FILAS){ //Suponemos que nunca se introducen datos incorrectos

        fila=MAX_FILAS-1;
    }
    if (fila==0){ //Suponemos que nunca se introducen datos incorrectos

        fila=0;
    }
}


void vaciarTablero(tablero t) {

    for (int col = 0; col < MAX_COLUMNAS; col++) {
        t[col].ocupadas = 0;
        for (int fila = 0; fila < MAX_FILAS; fila++) {
            vaciarCasilla(t[col].fila[fila]);

        }
    }
}


void iniciarTableroAleatorio(tablero &t, int nfila, int ncol, int filasIniciales) {

    srand(time(NULL));

    for (int col = 0; col < MAX_COLUMNAS; col++) { //columnaS
        for (int fila = 0; fila < filasIniciales; fila++) {
            ponerValor( t[col].fila[fila] , pow(2, 1 + rand() % 5));


        }
        t[col].ocupadas = filasIniciales;
    }

    //Inicializacion del resto de casillas a 0, estan vacias
    for (int col = 0; col < MAX_COLUMNAS; col++) {
        for (int fila = filasIniciales; fila < MAX_FILAS; fila++) {
            ponerValor(t[col].fila[fila], 0);
        }
    }

}

void ponerValorTablero(tablero &t, int fila, int col, int valor) {

    pasarFilasBase0(fila);
    pasarColumnaBase0(col);

    ponerValor(t[col].fila[fila], valor);
    //t[col].fila[fila] = valor;
    t[col].ocupadas++;

}

int obtenerValorTablero(tablero t, int fila, int col) {

    pasarFilasBase0(fila);
    pasarColumnaBase0(col);

    return obtenerValorCasilla(t[col].fila[fila]);

}

bool estaVaciaCasillaTablero(tablero t, int fila, int col) {

    pasarFilasBase0(fila);
    pasarColumnaBase0(col);

    bool vacia = false;
    if (obtenerValorCasilla(t[col].fila[fila]) == 0) {
        vacia = true;
    }
    return vacia;
}

void vaciarCasillaTablero(tablero &t, int fila, int col) {

    pasarFilasBase0(fila);
    pasarColumnaBase0(col);

    ponerValor(t[col].fila[fila], 0);

}

bool estaLlenaColumnaTablero(tablero t, int col) {

    pasarColumnaBase0(col);

    bool llena = true;
    int cont = 0;
    int fila = 0;
    while (llena == true && fila < MAX_FILAS) {

        if (obtenerValorCasilla(t[col].fila[fila]) != 0) {
            cont++;
            fila++;
        } else {
            llena = false;
        }
    }

    return llena;
}

int obtenerPosicionVaciaColumnaTablero(tablero t, int col) {

    pasarColumnaBase0(col);

    int fila = t[col].ocupadas;
    if (fila>=MAX_FILAS){
        fila=-2;
    }

    return fila+1; //Devuelve en base 1
}

bool estaLlenoTablero(tablero t) {
    bool lleno;
    lleno = true;
    int filas = 0;
    int columnas = 0;
    int cont = 0;


    while (lleno == true && columnas < MAX_COLUMNAS) {
        while (lleno == true && filas < MAX_COLUMNAS) {
            if (obtenerValorCasilla(t[columnas].fila[filas]) != 0) {
                filas++;
                cont++;

            } else {
                lleno = false;
            }
        }
        columnas++;
    }

    if (cont == MAX_FILAS) {
        lleno = true;
    }


    return lleno;
}

int obtenerNumFilas(tablero t) {
    return MAX_FILAS;
}

int obtenerNumColumnas(tablero t) {
    return MAX_COLUMNAS;
}
