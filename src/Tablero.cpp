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


void pasarColumnaBase0(int &col) {
    if (col >= 1) {
        col--;
    }
    if (col == MAX_COLUMNAS) { //Suponemos que nunca se introducen datos incorrectos

        col = MAX_COLUMNAS - 1;
    }
    if (col == 0) { //Suponemos que nunca se introducen datos incorrectos

        col = 0;
    }
}

void pasarFilasBase0(int &fila) {
    if (fila >= 1) {
        fila--;
    }
    if (fila == MAX_FIL) { //Suponemos que nunca se introducen datos incorrectos

        fila = MAX_FIL - 1;
    }
    if (fila == 0) { //Suponemos que nunca se introducen datos incorrectos

        fila = 0;
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

void quitarValorTablero(tablero &t, int col) {

    pasarColumnaBase0(col);

    //Siempre se elimina la última casilla de una columna.
    t[col].fila[t[col].ocupadas - 1] = 0;
    t[col].ocupadas--;

}


void iniciarTableroAleatorio(tablero &t, int nfilas, int ncolumnas, int filasIniciales) {

    srand(time(NULL));

    for (int col = 0; col < ncolumnas; col++) { //columnaS
        for (int fila = 0; fila < nfilas; fila++) {
            ponerValor(t[col].fila[fila], pow(2, 1 + rand() % 8));


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
void fusionFilaAdyacentes(tablero &t, int colActiva, int valorActual, int valorPrevio) {

    int sumaValor;
    sumaValor = valorPrevio + valorActual;
    t[colActiva].fila[t[colActiva].ocupadas - 2] = sumaValor;
    t[colActiva].ocupadas =
            t[colActiva].ocupadas - 1; //Poner valor tablero suma+1 a ocupadas, pero en caso de fusión no es requerido.
    for (int fila = t[colActiva].ocupadas; fila < MAX_FIL; ++fila) {
        t[colActiva].fila[fila] = 0;
    }
}

void fusionTriple(tablero &t, int columna, int fila) {

    int valorIzq, valorDer, valorSuperior, valorActual,resultadoFusion;
    valorIzq = obtenerValorTablero(t, fila, columna - 1);
    valorDer = obtenerValorTablero(t, fila, columna + 1);
    valorSuperior = obtenerValorTablero(t, fila - 1, columna);
    valorActual= obtenerValorTablero(t, fila, columna);

    resultadoFusion =  valorSuperior + valorDer + valorIzq + valorActual; //2^x < resultdoFusion < 2^x+1

    //Eliminar las casillas fusionadas
    quitarValorTablero(t, columna - 1);
    quitarValorTablero(t, columna + 1);
    quitarValorTablero(t, columna);
    quitarValorTablero(t, columna);
    ponerValorTablero(t, columna, resultadoFusion);
}

void fusionDobleIzq(tablero &t, int columna, int fila) {

    int valorIzq, valorSuperior,valorActual, resultadoFusion;
    valorIzq = obtenerValorTablero(t, fila, columna - 1);
    valorSuperior = obtenerValorTablero(t, fila - 1, columna);
    valorActual= obtenerValorTablero(t, fila, columna);


    resultadoFusion = valorSuperior + valorIzq + valorActual;

    //Eliminar las casillas fusionadas
    quitarValorTablero(t, columna - 1);
    quitarValorTablero(t, columna);
    quitarValorTablero(t, columna);
    ponerValorTablero(t, columna, resultadoFusion);
}

void fusionDobleDer(tablero &t, int columna, int fila) {

    int valorDer, valorSuperior, valorActual, resultadoFusion;
    valorDer = obtenerValorTablero(t, fila, columna + 1);
    valorSuperior = obtenerValorTablero(t, fila - 1, columna);

    resultadoFusion = valorSuperior + valorDer + valorActual;

    //Eliminar las casillas fusionadas
    quitarValorTablero(t, columna + 1);
    quitarValorTablero(t, columna);
    quitarValorTablero(t, columna);
    ponerValorTablero(t, columna, resultadoFusion);
}

void fusionSimpleDer(tablero &t, int columna, int fila) {

    int valorDer, resultadoFusion, valorActual;
    valorDer = obtenerValorTablero(t, fila, columna + 1);
    valorActual= obtenerValorTablero(t, fila, columna);


    resultadoFusion = valorActual+ valorDer;

    //Eliminar las casillas fusionadas
    quitarValorTablero(t, columna + 1);
    quitarValorTablero(t, columna);
    ponerValorTablero(t, columna, resultadoFusion);
}

void fusionSimpleIzq(tablero &t, int columna, int fila) {

    int valorIzq, resultadoFusion, valorActual;
    valorIzq = obtenerValorTablero(t, fila, columna + 1);
    valorActual= obtenerValorTablero(t, fila, columna);


    resultadoFusion = valorActual + valorIzq;

    //Eliminar las casillas fusionadas
    quitarValorTablero(t, columna - 1);
    quitarValorTablero(t, columna);
    ponerValorTablero(t, columna, resultadoFusion);
}

void fusionSimpleSup(tablero &t, int columna, int fila) {

    int resultadoFusion, valorActual, valorSup;
    valorSup = obtenerValorTablero(t, fila - 1, columna);
    valorActual= obtenerValorTablero(t, fila, columna);


    resultadoFusion = valorActual + valorSup;

    //Eliminar las casillas fusionadas
    quitarValorTablero(t, columna);
    quitarValorTablero(t, columna);
    ponerValorTablero(t, columna, resultadoFusion);
}



bool aplicarNuevoValorFila(tablero &t, int colActiva) {
//    pasarColumnaBase0(colActiva);
//    colActiva++;


    int filaCheck, valorActual, valorSup, valorIzq, valorDer;
    bool hayFusion = false;


    if (t[colActiva-1].ocupadas <= 1) {
        cout << "AplicarNuevoValorFila.No-existen-suficientes-filas-ocupadas\n";
        return hayFusion;
    }

    filaCheck = t[colActiva-1].ocupadas;  //TODO: CAMBIAR-BASE (t[colActiva].ocupadas-1)
    valorActual = obtenerValorTablero(t,filaCheck,colActiva);

    /* Caso 1:      4
        *         4 X 4
        *  Resultado sería 16
        *  Si izq y der y arriba == valor col/fila ==> aplicar fusión
        */
    {

        valorSup = obtenerValorTablero(t, filaCheck - 1, colActiva);
        valorIzq = obtenerValorTablero(t, filaCheck, colActiva - 1);
        valorDer = obtenerValorTablero(t, filaCheck, colActiva + 1);

        if (!hayFusion && valorActual == valorIzq && valorActual == valorDer && valorActual == valorSup) {
            hayFusion = true;
            fusionTriple(t, colActiva, filaCheck);
        }

    }

    /* Caso 2:      4
       *         4  X
       *  Resultado sería 16 (redondea a 16)
       *  Si (!hayFusion y (izq (no der) y arriba == valor), col/fila ==> aplicar fusión {
       */
    {
        valorSup = obtenerValorTablero(t, filaCheck - 1, colActiva);
        valorIzq = obtenerValorTablero(t, filaCheck, colActiva - 1);

        if (!hayFusion && valorActual == valorIzq && valorActual == valorSup) {
            hayFusion = true;
            fusionDobleIzq(t, colActiva, filaCheck);
        }

    }

    /* Caso 3:   4
     *           X 4
     *  Resultado sería 16 (redondea a 16)
     */
    //Si (!hayFusion y ((no izq) der y arriba == valor), col/fila ==> aplicar fusión {
    //fusionDobleDer(t, col/fila)

    {
        valorSup = obtenerValorTablero(t, filaCheck - 1, colActiva);
        valorDer = obtenerValorTablero(t, filaCheck, colActiva + 1);

        if (!hayFusion && valorActual == valorDer && valorActual == valorSup) {
            hayFusion = true;
            fusionDobleDer(t, colActiva, filaCheck);
        }
    }

    /* Caso 4:
     *           X 4
     *  Resultado sería 8
     */
    //Si (!hayFusion y (der == valor), col/fila ==> aplicar fusión {
    //fusionDerSimple(t, col/fila)
    {
        valorDer = obtenerValorTablero(t, filaCheck, colActiva + 1);

        if (!hayFusion && valorActual == valorDer) {
            hayFusion = true;
            fusionSimpleDer(t, colActiva, filaCheck);
        }
    }

    /* Caso 5:
     *         4 X
     *  Resultado sería 8
     */
    //Si (!hayFusion y (izq == valor), col/fila ==> aplicar fusión {
    //fusionSimpleIzq(t, col/fila)
    {
        valorIzq = obtenerValorTablero(t, filaCheck, colActiva -1);

        if (!hayFusion && valorActual == valorIzq) {
            hayFusion = true;
            fusionSimpleIzq(t, colActiva, filaCheck);
        }
    }

    /* Caso 6:   4
     *           X
     *  Resultado sería 8
     */
    //Si (!hayFusion y (superior == valor), col/fila ==> aplicar fusión {
    //fusionSimpleSup(t, col/fila)

    {

        if (!hayFusion && valorActual == valorSup) {
            hayFusion = true;
            fusionSimpleSup(t, colActiva, filaCheck);
        }

    }

//    bool continuar = true;



//    while (continuar) {
//        cout << "aplicarNuevoValorFila: valorAct:" << valorActual << ";" << valorSup << "\n";
//        if (valorActual == valorSup) {
//            //aplicar fusión
//            cout << "Debería aplicar fusion\n";
//            fusionFilaAdyacentes(t, colActiva, valorActual, valorSup);
//            hayFusion = true;
//
//            //Una vez fusiona, habría que continuar
//
//            filaCheck = filaCheck - 1;
//            valorActual = t[colActiva].fila[filaCheck];
//            valorSup = t[colActiva].fila[filaCheck - 1];
//        } else {
//            continuar = false;
//        }
//    }

    return hayFusion;
}


void ponerValorTablero(tablero &t, int col, int valor) {

    pasarColumnaBase0(col);

    //ponerValor(t[col].fila[fila], valor);

    //Asigna a la fila siguiente libre (valor ocupadas en base 1) el valor a poner en la columna.
    t[col].fila[t[col].ocupadas] = valor;

    t[col].ocupadas = t[col].ocupadas + 1;
}

void dumpColumna(tablero &t, int nfilas, int col) {
    cout << "\nVolcado-columna: " << col << "\n filas: ";
    for (int fila = 0; fila < nfilas; fila++) {
        cout << t[col].fila[fila] << "; ";
    }
    cout << "Ocupadas:" << t[col].ocupadas << "\n";
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
    if (fila >= MAX_FIL) {
        fila = -2;
    }

    return fila + 1; //Devuelve en base 1
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
