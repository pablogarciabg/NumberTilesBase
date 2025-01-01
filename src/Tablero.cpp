//
// Created by Pablo Garcia & Ruben Flete on 07/12/2024.
//

#include <iostream>
#include <cmath>

using namespace std;

#include "Tablero.h"
#include "casilla.h"
#include "entorno.h"
#include "juego.h"


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
    if (fila == MAX_FIL){ //Suponemos que nunca se introducen datos incorrectos

        fila= MAX_FIL - 1;
    }
    if (fila==0){ //Suponemos que nunca se introducen datos incorrectos

        fila=0;
    }
}


void vaciarTablero(tablero &t) {

    for (int col = 0; col < MAX_COLUMNAS; col++) {
        t[col].ocupadas = 0;
        for (int fila = 0; fila < MAX_FIL; fila++) {
            vaciarCasilla(t[col].fila[fila]);
        }
    }
}


void iniciarTableroAleatorio(tablero &t, int nfilas, int ncolumnas, int filasIniciales) {

    srand(time(NULL));

    for (int col = 0; col < ncolumnas; col++) { //columnaS
        for (int fila = 0; fila < nfilas; fila++) {
            ponerValor( t[col].fila[fila] , pow(2, 1 + rand() % 8));


        }
        t[col].ocupadas = filasIniciales;
    }

    //Inicializacion del resto de casillas a 0, estan vacias
    for (int col = 0; col < ncolumnas; col++) {
        for (int fila = filasIniciales; fila < nfilas; fila++) {
            ponerValor(t[col].fila[fila], 0);
        }
    }
}

/*
 * Encarga de fusionar las 2 últimas casillas de una columna.
 */
void fusionFilaAdyacentes (tablero &t, int colActiva, int valorActual, int valorPrevio){

    int sumaValor;
    sumaValor = valorPrevio + valorActual;
    t[colActiva].fila[t[colActiva].ocupadas-2]=sumaValor;
    t[colActiva].ocupadas=t[colActiva].ocupadas-1; //Poner valor tablero suma+1 a ocupadas, pero en caso de fusión no es requerido.
    for (int fila = t[colActiva].ocupadas; fila < MAX_FIL; ++fila) {
        t[colActiva].fila[fila]=0;
    }
}

bool aplicarNuevoValorFila(tablero &t,int colActiva) {
    pasarColumnaBase0(colActiva);

    int filaCheck, valorActual, valorPrevio;
    bool hayFusion=false;


    if (t[colActiva].ocupadas<=1) {
        cout<<"AplicarNuevoValorFila.No-existen-suficientes-filas-ocupadas\n";
        return hayFusion;
    }

    filaCheck=t[colActiva].ocupadas-1;
    valorActual = t[colActiva].fila[filaCheck];
    valorPrevio = t[colActiva].fila[filaCheck-1];

    bool continuar=true;

    while (continuar) {
       cout<<"aplicarNuevoValorFila: valorAct:"<<valorActual<<";"<<valorPrevio<<"\n";
       if (valorActual==valorPrevio) {
           //aplicar fusión
           cout<<"Debería aplicar fusion\n";
           fusionFilaAdyacentes(t, colActiva, valorActual, valorPrevio);
           hayFusion=true;

           //Una vez fusiona, habría que continuar

           filaCheck=filaCheck-1;
           valorActual = t[colActiva].fila[filaCheck];
           valorPrevio = t[colActiva].fila[filaCheck-1];
       }
       else {
           continuar=false;
       }
    }

    return hayFusion;
}



void ponerValorTablero(tablero &t, int col, int valor) {

    pasarColumnaBase0(col);

    //ponerValor(t[col].fila[fila], valor);

    //Asigna a la fila siguiente libre (valor ocupadas en base 1) el valor a poner en la columna.
    t[col].fila[t[col].ocupadas]=valor;

    t[col].ocupadas = t[col].ocupadas + 1;
}

void dumpColumna(tablero &t, int nfilas,int col) {
    cout<<"\nVolcado-columna: "<<col<<"\n filas: ";
    for (int fila=0; fila < nfilas; fila++) {
        cout<<t[col].fila[fila]<<"; ";
    }
    cout<<"Ocupadas:"<<t[col].ocupadas<<"\n";
}

int obtenerValorTablero(tablero t, int fila, int col) {

    pasarFilasBase0(fila);
    pasarColumnaBase0(col);

    return obtenerValorCasilla(t[col].fila[fila]);

}

int obtenerValorOcupadas(tablero t, int col) {

    pasarColumnaBase0(col);

    return t[col].ocupadas;
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
    while (llena == true && fila < MAX_FIL) {

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
    if (fila >= MAX_FIL){
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

    if (cont == MAX_FIL) {
        lleno = true;
    }


    return lleno;
}

int obtenerNumFilas(tablero t) {
    return MAX_FIL;
}

int obtenerNumColumnas(tablero t) {
    return MAX_COLUMNAS;
}
