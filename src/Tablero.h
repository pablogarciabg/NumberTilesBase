//
// Created by Pablo Garcia & Ruben Flete on 07/12/2024.
//

#ifndef UNI_PROJECTS_TABLERO_H
#define UNI_PROJECTS_TABLERO_H
#include "casilla.h"
//#include "juego.h"

#include <iostream>
using namespace std;

//Base 1: Filas y columnas empiezan en 1
//Base 0: Filas y columnas empiezan en 0
//Una casilla vacia, significa que el valor que contiene es 0

/*
 * IMPORTANTE: Todos los parametros de entrada y/o salida, asi como los valores de retorno estan en base 1
 * es, decir, que las filas y columnas empiezan en 1
 *
 */


const int MAX_FIL=7; //Valores entre 3 y 7
const int MAX_COLUMNAS=7; //Valores entre 5 y 7


typedef casilla TipoFila[MAX_FIL];

struct Columna{
    int ocupadas;
    TipoFila fila;
};

typedef Columna tablero[MAX_COLUMNAS];

//PRE={1<=col<=MAX_COLUMNAS}
//COMPLEJIDAD=O(1)
//POST={Pasa el numero de columna a base 0}
void pasarColumnaBase0(int &col);

//PRE={1<=fila<=MAX_FIL}
//COPLEJIDAD=O(1)
//POST={Pasa el numero de filas a base 0}
void pasarFilasBase0 (int &fila);

//PRE={}
//COMPLEJIDAD= O(n²)
//POST={Vacia el tablero}
void vaciarTablero (tablero &t);

//PRE={fila >= 0, ncolumnas >=0, filaInciales >=0}
//COMPLEJIDAD= O(n²)
//POST={Inicia el tablero}
void iniciarTableroAleatorio (tablero &t, int fila, int ncolumnas, int filasIniciales, int comoIniciar);

//PRE={1<= fila <= juego.config.totalFilas, 1<= fila <= juego.config.totalFilas}
//
//POST={SOLO se uasará cuando no tengamos que insertar un numero en funcion de las ocupadas, es decir, que reemplazamos un numero por otro}
void reemplazarValorTablero (tablero &t, int columna, int fila, int valor);

//PRE={fila >= 0, col >=0, valor=2^x (x>=1)}
//COMPLEJIDAD=O(1)
//POST={Asigna un valor a la casilla indicada}
void ponerValorTablero (tablero &t,int col, int valor);


//PRE={fila >= 0, col >=0}
//COMPLEJIDAD= O(1)
//POST={Devuelve el valor la casilla indicada}
int obtenerValorTablero (tablero t, int fila, int col);

//PRE={fila >= 0, col >=0}
//COMPLEJIDAD= O(1)
//POST={Indica si la casilla esta vacia (true) o llena (false)}
bool estaVaciaCasillaTablero (tablero t, int fila, int col);

//PRE={fila >= 0, col >=0}
//COMPLEJIDAD= O(1)
//POST={Vacia la casilla indicada}
void vaciarCasillaTablero (tablero &t, int fila, int col);

//PRE={col >=0}
//COMPLEJIDAD= O(n)
//POST={Indica si la columna esta llena (true) o no (false)}
bool estaLlenaColumnaTablero (tablero t, int col);

//PRE={col >=0}
//COMPLEJIDAD= O(1)
//POST={Devuelve la primera casilla vacia de la columna indicada}
int obtenerPosicionVaciaColumnaTablero (tablero t, int col);

//PRE={}
//COMPLEJIDAD= O(1)
//POST={Indica si el tablero esta lleno (true) o no (false)}
bool estaLlenoTablero (tablero t);

//PRE={}
//COMPLEJIDAD= O(1)
//POST={Devuelve el numero de filas que tiene el tablero}
int obtenerNumFilas (tablero t);

//PRE={}
//COMPLEJIDAD= O(1)
//POST={Devueve el numero de columnas que tiene el tablero}
int obtenerNumColumnas(tablero t);

//PRE={col>=1}
//COMPLEJIDAD=O(1)
//POST={Devuelve el numero de ocupadas de la columna determinada}
int obtenerValorOcupadas(tablero t, int col);


//PRE={}
//COMPLEJIDAD=O(n)
//POST={Se encarga de mostrar el valor que hay nen cada fila de ocupadas}
void dumpColumna(tablero &t, int nfilas,int col);


//PRE={}
//COMPLEJIDAD=O()
//POST={Hace una repersentacion del tablero, nos sirve, para ver como esta alamacenado el tablero en memoria}
void dumpTablero(tablero &t, int nfilas, int ncols) ;


//PRE={valor > 0}
//COMPLEJIDAD=O(n)
//POST={Se encarga de aproximar un valor a su potencia de dos correspondinte por arriba (2^x)}
int aproximarValorPotencia (tablero &t, int valor);


//PRE={colActiva>=1}
//COMPLEJIDAD=O(1)
//POST={Se encarga de verificar si es necesario realizar una fusion}
bool aplicarNuevoValorFila(tablero &t,int colActiva, int &puntuacion);


//PRE={columna >= 1, fila >= 1}
//COMPLEJIDAD=O(1)
//POST={Se encarga de realizar la fusion de casillas del caso 1(especificado en aplicarNuevoValorFila)}
void fusionTriple(tablero &t, int columna, int fila, int &puntuacion);


//PRE={columna >= 1, fila >= 1}
//COMPLEJIDAD=O(1)
//POST={Se encarga de realizar la fusion de casillas del caso 2(especificado en aplicarNuevoValorFila)}
void fusionDobleIzq(tablero &t, int columna, int fila, int &puntuacion);


//PRE={columna >= 1, fila >= 1}
//COMPLEJIDAD=O(1)
//POST={Se encarga de realizar la fusion de casillas del caso 3 (especificado en aplicarNuevoValorFila)}
void fusionDobleDer(tablero &t, int columna, int fila, int &puntuacion);


//PRE={columna >= 1, fila >= 1}
//COMPLEJIDAD=O(1)
//POST={Se encarga de realizar la fusion de casillas del caso 4 (especificado en aplicarNuevoValorFila)
void fusionSimpleDer(tablero &t, int columna, int fila, int &puntuacion);


//PRE={columna >= 1, fila >= 1}
//COMPLEJIDAD=O(1)
//POST= {Se encarga de realizar la fusion de casillas del caso 5 (especificado en aplicarNuevoValorFila)
void fusionSimpleIzq(tablero &t, int columna, int fila, int &puntuacion);


//PRE={columna >= 1, fila >= 1}
//COMPLEJIDAD=O(1)
//POST={Se encarga de realizar la fusion de casillas del caso 6 (especificado en aplicarNuevoValorFila)
void fusionSimpleSup(tablero &t, int columna, int fila, int &puntuacion);


//PRE={columna >= 1, fila >= 1}
//COMPLEJIDAD=O(1)
//POST={Se encarga de realizar la fusion de casillas del caso 7 (especificado en aplicarNuevoValorFila)
void fusionDerIzq (tablero &t, int fila, int columna, int &puntuacion);



void fusionFilaAdyacentes (tablero &t, int colActiva, int valorActual, int valorPrevio);

#endif //UNI_PROJECTS_TABLERO_H
