//
// Created by Pablo Garcia & Ruben Flete on 08/12/2024.
//

#include <iostream>

using namespace std;

#include "Tablero.h"
#include "cmath"


void pruebasVaciarTablero() {
    int fila;
    int columna;
    int cont;
    tablero t;

    cont = 0;

    vaciarTablero(t);

    for (columna = 0; columna < MAX_COLUMNAS; columna++) {
        for (fila = 0; fila < MAX_FIL; fila++) {
            if (obtenerValorTablero(t, fila, columna) != 0) {
                cont++;
            }
        }
    }

    if (cont != 0) {
        cout << "Error al vaciar el tablero\n";
    }
}

void pruebaPasarColumnaBase0() {
    int columna;
    int columna1; //Pasara por el cambio de base

    columna = 6;
    columna1 = 7;
    pasarColumnaBase0(columna1);
    if (columna != columna1) {
        cout << "Error en el cambio de base de columnas\n";
    }

    columna = 0;
    columna1 = 0;
    pasarColumnaBase0(columna1);
    if (columna != columna1) {
        cout << "Error en el cambio de base de columnas\n";
    }

    columna = 4;
    columna1 = 5;
    pasarColumnaBase0(columna1);
    if (columna != columna1) {
        cout << "Error en el cambio de base de columnas\n";
    }
}

void pruebaPasarFilaBase0() {
    int fila;
    int fila1; //Pasara por el cambio de base

    fila = 6;
    fila1 = 7;
    pasarFilasBase0(fila1);
    if (fila != fila1) {
        cout << "Error en el cambio de base de columnas\n";
    }

    fila = 0;
    fila1 = 0;
    pasarFilasBase0(fila1);
    if (fila != fila1) {
        cout << "Error en el cambio de base de columnas\n";
    }

    fila = 4;
    fila1 = 5;
    pasarFilasBase0(fila1);
    if (fila != fila1) {
        cout << "Error en el cambio de base de columnas\n";
    }
}


void pruebaIniciarTableroAleatorio() {

    tablero t;
    int fila;
    int columna;
    int filasInciales = 3;
    iniciarTableroAleatorio(t, fila, columna, filasInciales);

    bool correcto = true;
    int col = 0;

    //Comprobamos desde 0 hasta filas iniciales
    while (correcto && col < MAX_COLUMNAS) {
        //Comprobar las filas
        int fil = 0;
        while (correcto && fil < filasInciales) {
            if (obtenerValorCasilla(t[col].fila[fil]) == 0) {
                cout << "Error al iniciar numeros aleatorios: Fila= " << fil << " Columna= " << col
                     << " Deberia tener un valor distinto de 0\n";
                correcto = false;
            }
            fil++;
        }

        col++;
    }

    //Comprobamos desde filas iniciales hasta MAX
    correcto = true;
    col = 0;

    while (correcto && col < MAX_COLUMNAS) {
        //Comprobar las filas
        int fil = filasInciales;
        while (correcto && fil < MAX_FIL) {
            if (obtenerValorCasilla(t[col].fila[fil]) != 0) {
                cout << "Error al iniciar el resto del tablero: Fila= " << fil << " Columna= " << col
                     << " Tiene que tener el valor 0\n";
                correcto = false;
            }
            fil++;
        }

        col++;
    }
}

void pruebaPonerValorTablero01() {

    tablero t;
    int fila;
    int columna;
    int valorEsperado;

    fila = 2;
    columna = 4;
    valorEsperado = 16;

    ponerValorTablero(t, columna, valorEsperado);

    if (obtenerValorTablero(t, fila, columna) != valorEsperado) {
        cout << "Error al poner el valorEsperado " << valorEsperado << " en la fila " << fila << " y en la columna "
             << columna << "\n";
    }


}

void pruebaPonerValorTablero02() {
    tablero t;
    int fila;
    int columna;
    int valorEsperado;

    fila = 0;
    columna = 0;
    valorEsperado = 32;

    ponerValorTablero(t, columna, valorEsperado);

    if (obtenerValorTablero(t, fila, columna) != valorEsperado) {
        cout << "Error al poner el valorEsperado " << valorEsperado << " en la fila " << fila << " y en la columna "
             << columna << "\n";
    }
}

void pruebaPonerValorTablero03() {
    tablero t;
    int fila;
    int columna;
    int valorEsperado;

    fila = 7;
    columna = 7;
    valorEsperado = 128;

    ponerValorTablero(t, columna, valorEsperado);

    if (obtenerValorTablero(t, fila, columna) != valorEsperado) {
        cout << "Error al poner el valorEsperado " << valorEsperado << " en la fila " << fila << " y en la columna "
             << columna << "\n";
    }
}

void pruebaPonerValorTablero() {
    pruebaPonerValorTablero01();
    pruebaPonerValorTablero02();
    pruebaPonerValorTablero03();

}

void pruebaObtenerValorTablero01() {
    int fila;
    int columna;
    tablero t;
    int valor;

    fila = 0;
    columna = 0;
    valor = 16;

    ponerValorTablero(t, columna, valor);

    if (obtenerValorTablero(t, fila, columna) != valor) {
        cout << "Error al obtener el valor " << valor << " en la fila " << fila << " y en la columna " << columna
             << "\n";
    }


}

void pruebaObtenerValorTablero02() {
    int fila;
    int columna;
    tablero t;
    int valor;

    fila = 7;
    columna = 7;
    valor = 128;

    //pasarFilasBase0(fila);
    //pasarColumnaBase0(columna);

    ponerValorTablero(t, columna, valor);

    if (obtenerValorTablero(t, fila, columna) != valor) {
        cout << "Error al obtener el valor " << valor << " en la fila " << fila << " y en la columna " << columna
             << "\n";
    }

}

void pruebaObtenerValorTablero03() {

    int fila;
    int columna;
    tablero t;
    int valor;

    fila = 3;
    columna = 4;
    valor = 4;

    //pasarFilasBase0(fila);
    //pasarColumnaBase0(columna);

    ponerValorTablero(t, columna, valor);

    if (obtenerValorTablero(t, fila, columna) != valor) {
        cout << "Error al obtener el valor " << valor << " en la fila " << fila << " y en la columna " << columna
             << "\n";
    }
}

void pruebaObtenerValorTablero() {

    pruebaObtenerValorTablero01();
    pruebaObtenerValorTablero02();
    pruebaObtenerValorTablero03();

}

void pruebaEstaVaciaCasillaTablero01() {

    int nfila;
    int ncolumna;
    tablero t;
    int filasIniciales;

    filasIniciales = 3;

    iniciarTableroAleatorio(t, nfila, ncolumna, filasIniciales);

    int fila = 1;
    int columna = 1;

    if (estaVaciaCasillaTablero(t, fila, columna)) {
        cout << "Error, la casilla deberia estar llena en la fila " << fila << " y en la columna " << columna << "\n";
    }
}

void pruebaEstaVaciaCasillaTablero02() {

    int nfila;
    int ncolumna;
    tablero t;
    int filasIniciales;
    int fila;
    int columna;

    filasIniciales = 3;

    iniciarTableroAleatorio(t, nfila, ncolumna, filasIniciales);

    fila = 4;
    columna = 4;

    if (!estaVaciaCasillaTablero(t, fila, columna)) {
        cout << "Error, la casilla deberia estar vacia en la fila " << fila << " y en la columna " << columna << "\n";
    }
}

void pruebaEstaVaciaCasillaTablero() {

    pruebaEstaVaciaCasillaTablero01();
    pruebaEstaVaciaCasillaTablero02();

}

void pruebasVaciarCasillaTablero() {
    int fila = 2;
    int columna = 4;
    tablero t;
    int valor = 4;

    ponerValorTablero(t, columna, valor);

    vaciarCasillaTablero(t, fila, columna);

    if (obtenerValorTablero(t, fila, columna) != 0) {
        cout << "Error al Vaciar el valor en la fila " << fila << " y en la columna " << columna << "\n";
    }
}

void pruebasEstaLlenaColumnaTablero() {
    tablero t;
    int columna = 2;
    int valor = 128;

    pasarColumnaBase0(columna);

    //LLenamos la fila 2, para comprobar que funciona la funcion
    for (int fila = 0; fila < MAX_FIL; fila++) {
        ponerValorTablero(t, columna, valor);
    }

    estaLlenaColumnaTablero(t, columna);
    bool llena = true;
    int fila = 0;
    while (llena && fila < MAX_FIL) {
        if (obtenerValorTablero(t, fila, columna) == 0) {
            llena = false;
        } else {
            fila++;
        }
    }

    if (!llena) {
        cout << "Error, la columna 2, deberia estar llena\n";
    }
}

void pruebasObtenerPosicionVaciaColumnaTablero01() {

    tablero t;
    vaciarTablero(t);

    //Leer fichero configuración
    int tablero_cols = 4;
    int tablero_filas = 7;

    int fila;
    int columna = 3;

    pasarColumnaBase0(columna);

    //Llenamos el tablero para realizar las comprobaciones

    for (fila = 1; fila <= 4; fila++) {
        ponerValorTablero(t, columna, 5);
    }

    if (obtenerPosicionVaciaColumnaTablero(t, columna) != 5) {
        cout << "Error al obtener la primera casilla vacia de la columna " << columna << "\n";
    }
}

void pruebasObtenerPosicionVaciaColumnaTablero02() {

    tablero t;
    vaciarTablero(t);

    //Leer fichero configuración
    int tablero_cols = 4;
    int tablero_filas = 7;

    int fila;
    int columna;

    vaciarTablero(t);
    columna = 1;

    for (fila = 1; fila <= MAX_FIL; fila++) {
        ponerValorTablero(t, columna, 16);
    }

    if (obtenerPosicionVaciaColumnaTablero(t, columna) != -1) {
        cout << "Error al obtener la primera casilla vacia de la columna " << columna << "\n";
    }
}

void pruebasObtenerPosicionVaciaColumnaTablero03() {

    tablero t;
    vaciarTablero(t);

    //Leer fichero configuración
    int tablero_cols = 4;
    int tablero_filas = 7;

    int fila;
    int columna;

    vaciarTablero(t);
    columna = 5;

    for (fila = 1; fila <= MAX_FIL - 1; fila++) {
        ponerValorTablero(t, columna, 16);
    }

    if (obtenerPosicionVaciaColumnaTablero(t, columna) != MAX_FIL) {
        cout << "Error al obtener la primera casilla vacia de la columna " << columna << "\n";
    }

}

void pruebasObtenerPosicionVaciaColumnaTablero() {

    pruebasObtenerPosicionVaciaColumnaTablero01();
    pruebasObtenerPosicionVaciaColumnaTablero02();
    pruebasObtenerPosicionVaciaColumnaTablero03();
}

void pruebasEstaLlenoTablero() {
    int fila = 0;
    int columna = 0;
    tablero t;
    int filasIniciales = 3;

    pasarFilasBase0(fila);
    pasarFilasBase0(filasIniciales);
    pasarColumnaBase0(columna);

    iniciarTableroAleatorio(t, fila, columna, filasIniciales);

    if (estaLlenoTablero(t) == true) {
        cout << "Hay error al comprobar que el tablero esta lleno\n";
    }

    vaciarTablero(t);
    if (estaLlenoTablero(t) == true) {
        cout << "Hay error al comprobar que el tablero esta lleno\n";
    }

}

void pruebasObtenerNumFilas() {
    tablero t;
    int filasMAX = MAX_FIL;
    if (obtenerNumFilas(t) != filasMAX) {
        cout << "Error al devolver el numero de filas\n";
    }
}

void pruebasObtenerNumColumnas() {
    tablero t;
    int columnasMAX = MAX_COLUMNAS;
    if (obtenerNumColumnas(t) != columnasMAX) {
        cout << "Error al devolver el numero de columnas\n";
    }
}

void pruebaFusionCaso1() {
    cout << "\n-- inicio prueba fusion-casillas caso-1\n";

    tablero t;
    vaciarTablero(t);

    int columna;
    //CREAMOS EL ESCENARIO
    /*
     * 12   8   32
     * 2    4   16
     * 4    4   4
     * Insercion en fila 3, columna 2
     *
     */

    //
    columna = 1;
    ponerValorTablero(t, columna, 12);
    ponerValorTablero(t, columna, 2);
    ponerValorTablero(t, columna, 4);

    columna = 2;
    ponerValorTablero(t, columna, 8);
    ponerValorTablero(t, columna, 4);
    ponerValorTablero(t, columna, 4);

    columna = 3;
    ponerValorTablero(t, columna, 32);
    ponerValorTablero(t, columna, 16);
    ponerValorTablero(t, columna, 4);

    //Actuar
    int colActuar = 2;
    int resultadoEsperado = 16;
    aplicarNuevoValorFila(t, colActuar);

    //Verificar
    if (obtenerValorOcupadas(t,colActuar) != 2) {
        cout << "Error al obtener ocupadas en columna 2, caso 1\n";
    }
    if (obtenerValorOcupadas(t,colActuar-1) != 2) {
        cout << "Error al obtener ocupadas en columna 1, caso 1\n";
    }
    if (obtenerValorOcupadas(t,colActuar+1) != 2) {
        cout << "Error al obtener ocupadas en columna 3, caso 1\n";
    }

    if (obtenerValorTablero(t, 2, colActuar) != resultadoEsperado) {
        cout << "Error en la fusion de casillas, caso 1\n";
    }

    cout << "-- fin prueba fusion-casillas caso-1\n";
}



void pruebaFusionCaso2() {
    cout << "\n-- inicio prueba fusion-casillas caso-2\n";

    tablero t;
    vaciarTablero(t);

    int columna;
    //CREAMOS EL ESCENARIO
    /*
     * 4  2  8
     * 64 4  16
     * 4  4  <-Insercion aqui
     */

    //
    columna = 1;
    ponerValorTablero(t, columna, 4);
    ponerValorTablero(t, columna, 64);
    ponerValorTablero(t, columna, 4);

    columna = 2;
    ponerValorTablero(t, columna, 2);
    ponerValorTablero(t, columna, 4);
    ponerValorTablero(t, columna, 4);

    columna = 3;
    ponerValorTablero(t, columna, 8);
    ponerValorTablero(t, columna, 16);

    //Actuar
    int colActuar = 2;
    int resultadoEsperado = 16;
    aplicarNuevoValorFila(t, colActuar);

    //Verificar
    if (obtenerValorOcupadas(t,colActuar) != 2) {
        cout << "Error al obtener ocupadas en columna 2, caso 2\n";
    }
    if (obtenerValorOcupadas(t,colActuar-1) != 2) {
        cout << "Error al obtener ocupadas en columna 1, caso 2\n";
    }

    if (obtenerValorTablero(t, 2, colActuar) != 12) {
        cout << "Error en la fusion de casillas, caso 2\n";
    }

    cout << "-- fin prueba fusion-casillas caso-2\n";
}

void pruebaFusionCaso3() {
    cout << "\n-- inicio prueba fusion-casillas caso-3\n";

    tablero t;
    vaciarTablero(t);

    int columna;
    //CREAMOS EL ESCENARIO
    /*
     * 16   8   32
     * 2    4   16
     * 16   4   4
     * Insercion en fila 3, columna 2
     *
     */

    //
    columna = 1;
    ponerValorTablero(t, columna, 16);
    ponerValorTablero(t, columna, 2);
    ponerValorTablero(t, columna, 16);

    columna = 2;
    ponerValorTablero(t, columna, 8);
    ponerValorTablero(t, columna, 4);
    ponerValorTablero(t, columna, 4);

    columna = 3;
    ponerValorTablero(t, columna, 32);
    ponerValorTablero(t, columna, 16);
    ponerValorTablero(t, columna, 4);

    //Actuar
    int colActuar = 2;
    int resultadoEsperado = 16;
    aplicarNuevoValorFila(t, colActuar);

    //Verificar
    if (obtenerValorOcupadas(t,colActuar) != 2) {
        cout << "Error al obtener ocupadas en columna 2, caso 3\n";
    }
    if (obtenerValorOcupadas(t,colActuar+1) != 2) {
        cout << "Error al obtener ocupadas en columna 3, caso 1\n";
    }

    if (obtenerValorTablero(t, 2, colActuar) != 12) {
        cout << "Error en la fusion de casillas, caso 3\n";
    }

    cout << "-- fin prueba fusion-casillas caso-3\n";
}

void pruebaFusionCaso4() {
    cout << "\n-- inicio prueba fusion-casillas caso-4\n";

    tablero t;
    vaciarTablero(t);

    int columna;
    //CREAMOS EL ESCENARIO
    /*
     * 16   8   32
     * 2    32  16
     * 16   4   4
     * Insercion en fila 3, columna 2
     *
     */

    //
    columna = 1;
    ponerValorTablero(t, columna, 16);
    ponerValorTablero(t, columna, 2);
    ponerValorTablero(t, columna, 16);

    columna = 2;
    ponerValorTablero(t, columna, 8);
    ponerValorTablero(t, columna, 32);
    ponerValorTablero(t, columna, 4);

    columna = 3;
    ponerValorTablero(t, columna, 32);
    ponerValorTablero(t, columna, 16);
    ponerValorTablero(t, columna, 4);

    //Actuar
    int colActuar = 2;
    int resultadoEsperado = 8;
    aplicarNuevoValorFila(t, colActuar);

    //Verificar
    if (obtenerValorOcupadas(t,colActuar) != 3) {
        cout << "Error al obtener ocupadas en columna 2, caso 4\n";
    }
    if (obtenerValorOcupadas(t,colActuar+1) != 2) {
        cout << "Error al obtener ocupadas en columna 3, caso 4\n";
    }

    if (obtenerValorTablero(t, 3, colActuar) != resultadoEsperado) {
        cout << "Error en la fusion de casillas, caso 4\n";
    }

    cout << "-- fin prueba fusion-casillas caso-4\n";
}

void pruebaFusionCaso5() {
    cout << "\n-- inicio prueba fusion-casillas caso-5\n";

    tablero t;
    vaciarTablero(t);

    int columna;
    //CREAMOS EL ESCENARIO
    /*
     * 16   8   32
     * 2    32  16
     * 4    4   64
     * Insercion en fila 3, columna 2
     *
     */

    //
    columna = 1;
    ponerValorTablero(t, columna, 16);
    ponerValorTablero(t, columna, 2);
    ponerValorTablero(t, columna, 4);

    columna = 2;
    ponerValorTablero(t, columna, 8);
    ponerValorTablero(t, columna, 32);
    ponerValorTablero(t, columna, 4);

    columna = 3;
    ponerValorTablero(t, columna, 32);
    ponerValorTablero(t, columna, 16);
    ponerValorTablero(t, columna, 64);

    //Actuar
    int colActuar = 2;
    int resultadoEsperado = 8;
    aplicarNuevoValorFila(t, colActuar);

    //Verificar
    if (obtenerValorOcupadas(t,colActuar) != 3) {
        cout << "Error al obtener ocupadas en columna 2, caso 5\n";
    }
    if (obtenerValorOcupadas(t,colActuar-1) != 2) {
        cout << "Error al obtener ocupadas en columna 1, caso 5\n";
    }

    if (obtenerValorTablero(t, 3, colActuar) != resultadoEsperado) {
        cout << "Error en la fusion de casillas, caso 5\n";
    }

    cout << "-- fin prueba fusion-casillas caso-5\n";
}

void pruebaFusionCaso6() {

    cout << "\n-- inicio prueba fusion-casillas caso-6\n";

    tablero t;
    vaciarTablero(t);
    int columna;
    //CREAMOS EL ESCENARIO
    /*
     * 4    2   8
     * 64   32  4
     *          4    <-Insercion aqui
     *
     * ESCENARIO RESULTANTE
     * 4    2   8
     * 64   32  8
     */

    columna = 1;
    ponerValorTablero(t, columna, 4);
    ponerValorTablero(t, columna, 64);

    columna = 2;
    ponerValorTablero(t, columna, 2);
    ponerValorTablero(t, columna, 32);

    columna = 3;
    ponerValorTablero(t, columna, 8);
    ponerValorTablero(t, columna, 4);


    //Actuar
    ponerValorTablero(t, columna, 4);
    aplicarNuevoValorFila(t, columna);

    //Verificar
    // a) total ocupadas columna=3 es 2;
    if (obtenerValorOcupadas(t, columna) != 2) {
        cout << "Error al obtener ocupadas en columna 3, caso 6\n";
    }

    // b) valor fila=2 en columna=3 es 8;
    if (obtenerValorTablero(t, 1, columna) != 8) {
        cout << "Error en la fusion de casillas, caso 6\n";
    }

    cout << "-- fin prueba fusion-casillas caso-6\n";

}

void pruebaFusionCaso7() {

    cout << "\n-- inicio prueba fusion-casillas caso-7\n";

    tablero t;
    vaciarTablero(t);
    int columna;
    //CREAMOS EL ESCENARIO
    /*
     * 4    2   8
     * 64   32  64
     * 4    4   4
     * Insercion en columna 2 y fila 3
     *
     * ESCENARIO RESULTANTE
     * 4    2   8
     * 64   32  64
     *      12
     */

    columna = 1;
    ponerValorTablero(t, columna, 4);
    ponerValorTablero(t, columna, 64);
    ponerValorTablero(t, columna, 4);

    columna = 2;
    ponerValorTablero(t, columna, 2);
    ponerValorTablero(t, columna, 32);
    ponerValorTablero(t, columna, 4);

    columna = 3;
    ponerValorTablero(t, columna, 8);
    ponerValorTablero(t, columna, 64);
    ponerValorTablero(t, columna, 4);


    //Actuar

    int colActuar = 2;
    int resultadoEsperado = 16;
    aplicarNuevoValorFila(t, colActuar);

    //Verificar
    if (obtenerValorOcupadas(t,colActuar) != 3) {
        cout << "Error al obtener ocupadas en columna 2, caso 7\n";
    }
    if (obtenerValorOcupadas(t,colActuar-1) != 2) {
        cout << "Error al obtener ocupadas en columna 1, caso 7\n";
    }
    if (obtenerValorOcupadas(t,colActuar+1) != 2) {
        cout << "Error al obtener ocupadas en columna 3, caso 7\n";
    }

    if (obtenerValorTablero(t, 3, colActuar) != resultadoEsperado) {
        cout << "Error en la fusion de casillas, caso 7\n";
    }

    cout << "-- fin prueba fusion-casillas caso-7\n";

}

void pruebaFusionCasillas() { //Tablero 6x5
    pruebaFusionCaso1();
    pruebaFusionCaso2();
    pruebaFusionCaso3();
    pruebaFusionCaso4();
    pruebaFusionCaso5();
    pruebaFusionCaso6();
    pruebaFusionCaso7();

}

void pruebaAproximarValorPotencia(){

    cout<<"-- incio de las pruebas aproximar valor potencia\n";
    tablero t;
    int num, numAproximado, resultadoEsperado;

    num = 5;
    resultadoEsperado = 8;
    numAproximado = aproximarValorPotencia(t, num);
    if (numAproximado != resultadoEsperado){
        cout<< "Error al aproximar el valor "<< num;
    }

    num = 14;
    resultadoEsperado = 16;
    numAproximado = aproximarValorPotencia(t, num);
    if (numAproximado != resultadoEsperado){
        cout<< "Error al aproximar el valor "<< num;
    }

    num = 25;
    resultadoEsperado = 32;
    numAproximado = aproximarValorPotencia(t, num);
    if (numAproximado != resultadoEsperado){
        cout<< "Error al aproximar el valor "<< num;
    }

    num = 55;
    resultadoEsperado = 64;
    numAproximado = aproximarValorPotencia(t, num);
    if (numAproximado != resultadoEsperado){
        cout<< "Error al aproximar el valor "<< num;
    }

    num = 85;
    resultadoEsperado = 128;
    numAproximado = aproximarValorPotencia(t, num);
    if (numAproximado != resultadoEsperado){
        cout<< "Error al aproximar el valor "<< num;
    }

    num = 200;
    resultadoEsperado = 256;
    numAproximado = aproximarValorPotencia(t, num);
    if (numAproximado != resultadoEsperado){
        cout<< "Error al aproximar el valor "<< num;
    }


    cout<<"-- fin de las pruebas aproximar valor potencia\n";

}


void pruebasGeneralesTablero() {

    cout << "----------INCIO DE LAS PRRUEBAS GENERALES TABLERO----------\n";

    cout << "\n";

    cout << "INCIO PRUEBAS VACIAR TABLERO\n";
    pruebasVaciarTablero();
    cout << "FIN PRUEBAS VACIAR TABLERO\n";

    cout << "\n";

    cout << "INCIO DE LAS PRUEBAS CAMBIO DE BASE COLUMNA \n";
    pruebaPasarColumnaBase0();
    cout << "FIN DE LAS PRUEBAS CAMBIO DE BASE COLUMNA \n";

    cout << "\n";

    cout << "INCIO DE LAS PRUEBAS CAMBIO DE BASE FILA \n";
    pruebaPasarFilaBase0();
    cout << "FIN DE LAS PRUEBAS CAMBIO DE BASE FILA \n";

    cout << "\n";

    cout << "INCIO DE LAS PRUEBAS INICIAR TABLERO\n";
//    pruebaIniciarTableroAleatorio();
    cout << "FIN DE LAS PRUEBAS INICIAR TABLERO\n";

    cout << "\n";

    cout << "INCIO DE LAS PRUEBAS PONER VALOR TABLERO\n";
//    pruebaPonerValorTablero();
    cout << "FIN DE LAS PRUEBAS PONER VALOR TABLERO\n";

    cout << "\n";

    cout << "INCIO DE LAS PRUEBAS OBTENER VALOR TABLERO \n";
//    pruebaObtenerValorTablero();
    cout << "FIN DE LAS PRUEBAS OBTENER TABLERO\n";

    cout << "\n";

    cout << "INCIO DE LAS PRUEBAS ESTA VACIA CASILLA TABLERO \n";
//    pruebaEstaVaciaCasillaTablero();
    cout << "FIN DE LAS PRUEBAS ESTA VACIA CASILLA TABLERO\n";

    cout << "\n";

    cout << "INCIO DE LAS PRUEBAS VACIAR CASILLA TABLERO \n";
//    pruebasVaciarCasillaTablero();
    cout << "FIN DE LAS PRUEBAS VACIAR CASILLA TABLERO\n";

    cout << "\n";

    cout << "INCIO DE LAS PRUEBAS ESTA LLENA COLUMNA TABLERO \n";
//    pruebasEstaLlenaColumnaTablero();
    cout << "FIN DE LAS PRUEBAS ESTA LLENA COLUMNA TABLERO\n";

    cout << "\n";

    cout << "INCIO DE LAS PRUEBAS OBTENER FILA VACIA TABLERO \n";
//    pruebasObtenerPosicionVaciaColumnaTablero();
    cout << "FIN DE LAS PRUEBAS OBTENER FILA VACIA TABLERO\n";

    cout << "\n";

    cout << "INCIO DE LAS PRUEBAS ESTA LLENO TABLERO \n";
//    pruebasEstaLlenoTablero();
    cout << "FIN DE LAS PRUEBAS ESTA LLENO TABLERO\n";

    cout << "\n";

    cout << "INCIO DE LAS PRUEBAS OBTENER EL NUMERO DE FILAS TABLERO\n";
//    pruebasObtenerNumFilas();
    cout << "FIN DE LAS PRUEBAS OBTENER EL NUMERO DE FILAS TABLERO\n";

    cout << "\n";

    cout << "\nINCIO DE LAS PRUEBAS OBTENER EL NUMERO DE COLUMNAS TABLERO\n";
//    pruebasObtenerNumColumnas();
    cout << "FIN DE LAS PRUEBAS OBTENER EL NUMERO DE COLUMNAS TABLERO\n";

    cout << "\nINCIO DE LAS PRUEBAS FUSION VALORES TABLERO\n";
    pruebaFusionCasillas();
    cout << "FIN DE LAS PRUEBAS FUSION VALORES TABLERO\n";

    cout << "\n";

    cout << "\nINCIO DE LAS PRUEBAS APROXIMAR VALOR POTENCIA\n";
    pruebaAproximarValorPotencia();
    cout << "FIN DE LAS PRUEBAS APROXIMAR VALOR POTENCIA\n";

    cout << "\n----------FIN DE LAS PRRUEBAS GENERALES TABLERO----------\n";
}



