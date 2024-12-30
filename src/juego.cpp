//
// Created by Pablo Garcia & Ruben Flete on 29/12/2024.
//

#include "juego.h"
#include "entorno.h"
#include "Tablero.h"
#include "cmath"
#include <iostream>

void convertirMatrizTablero(tablero &tab, int filas, int columnas, int filasIniciales, int m[MAX_FILAS][MAX_COL]) {

    for (int col = 1; col <= columnas; col++) {
        for (int fila = 1; fila <= filasIniciales; fila++) {
            ponerValorTablero(tab, fila, col, m[col - 1][fila - 1]);
//            tab[col].fila[fila]=m[col][fila];
        }
    }

}


void inicializarJuego(Juego &juego) { //Crea y pinta el tablero inicial, dependiendo de comoInciar

    //VAriable auxiliar para cargar datos iniciales del entorno a través del fichero de configuración
    int m[MAX_FILAS][MAX_COL];

    srand(time(NULL));

    //Indica como se inicializa el tablero, con datos aleatorios o con datos del fichero de configuración
    int comoIniciar;
    // El tablero las dimensiones reales vienen determinadas por nfilas y ncolumnas. Estos datos se leen del fichero de configuración
    int nfilas, ncolumnas, filasIniciales;

    juego.puntuacion = 0;

    vaciarTablero(juego.tab);

    if (entornoCargarConfiguracion(nfilas, ncolumnas, comoIniciar, filasIniciales, m)) {

        entornoIniciar(nfilas, ncolumnas);

        if (comoIniciar == 0) {
            convertirMatrizTablero(juego.tab, nfilas, ncolumnas, filasIniciales, m);

            //El tablero se rellena parcialmente con los datos de configuración
            for (int col = 0; col < ncolumnas; col++) { //col=columnas
                for (int fila = 0; fila < filasIniciales; fila++) { //fila=filas
                    entornoPonerNumero(fila, col, juego.tab[col].fila[fila]);
                }
            }

        } else {

            //El tablero se inicia con datos aleatorios
            iniciarTableroAleatorio(juego.tab, nfilas, ncolumnas, filasIniciales);

            for (int col = 0; col < ncolumnas; col++) { //col=columnas
                for (int fila = 0; fila < filasIniciales; fila++) { //fila=filas
                    entornoPonerNumero(fila, col, juego.tab[col].fila[fila]);
//                    entornoPonerNumero(fila, col, 4);
                }
            }
        }
    }

    juego.config.filasIniciales = filasIniciales;
    juego.config.totalColumnas = ncolumnas;
    juego.config.totalFilas = nfilas;
}

void play(Juego &juego) {

    const int BASE_INICIO = 1;
    int columna, fila;
    columna = BASE_INICIO;
    fila = juego.config.filasIniciales;

    string msg;
    msg = " ";
    bool salir = false;

    int valorLanzador = pow(2, 1 + rand() % 8);

    TipoTecla tecla;
    columna colActiva;

    entornoPonerNumeroLanzador(valorLanzador, columna - 1);
    entornoPonerPuntuacion(juego.puntuacion);

    while (!salir) {
        tecla = entornoLeerTecla();

        switch (tecla) {
            case TEnter: {
                entornoQuitarNumeroLanzador(columna - 1);


                int valorSuma = 0;
                int cont;
                cont = 0;

                if (juego.tab[columna - 1].ocupadas < juego.config.totalFilas) {

                    entornoPonerNumero(juego.tab[columna - 1].ocupadas, columna - 1, valorLanzador);
                    ponerValorTablero(juego.tab, fila, columna, valorLanzador);

                    int valorAnteriorVertical = juego.tab[columna - 1].ocupadas - 1;
                    int valorActualVertical = juego.tab[columna - 1].ocupadas;

                    if (valorAnteriorVertical == valorActualVertical) {
                        valorSuma = valorAnteriorVertical + valorActualVertical;
                        ponerValorTablero(juego.tab, fila, columna, valorSuma);
                        entornoPonerNumero(valorAnteriorVertical, columna - 1, valorSuma);
                    }
                }


                //Si el tablero se llena entonces, el juego acaba
                for (int col = 0; col < juego.config.totalColumnas; col++) {
                    if (juego.tab[col].ocupadas == juego.config.totalFilas) {
                        cont++;
                    }
                }
                if (cont == juego.config.totalColumnas) {
                    msg = "Has perdido";
                    salir = true;

                    entornoMostrarMensajeFin(msg);
                    entornoPausa(0.5);
                }



//                if (juego.tab[columna-1].fila[fila-1]==juego.tab[columna-1].fila[fila-2]){
//
//                    entornoEliminarNumero(fila-2, columna-1);
//
//                    juego.tab[columna-1].fila[fila-2] = juego.tab[columna-1].fila[fila-1] + juego.tab[columna-1].fila[fila-2];
//                    valorSuma=juego.tab[columna].fila[fila-1];
//
//                    entornoPonerNumero(fila-2, columna-1, valorSuma);
//                    juego.tab[columna-1].ocupadas--;
//                }




                valorLanzador = pow(2, 1 + rand() % 8);
                entornoPonerNumeroLanzador(valorLanzador, columna - 1);
            }

                break;

            case TDerecha:
                entornoQuitarNumeroLanzador(columna - 1);

                if (columna < juego.config.totalColumnas)
                    columna++;
                else
                    columna = BASE_INICIO;

                entornoPonerNumeroLanzador(valorLanzador, columna - 1);

                break;
            case TIzquierda:
                entornoQuitarNumeroLanzador(columna - 1);
                if ((columna <= juego.config.totalColumnas) && (columna > BASE_INICIO)) {
                    columna--;
                } else {
                    columna = juego.config.totalColumnas;
                }
                entornoPonerNumeroLanzador(valorLanzador, columna - 1);

                break;

            case TF1:
                break;
            case TF2:
                break;

            case TSalir:
                msg = "Has abandonado";
                salir = true;
                break;
            case TNada:
                break;
        }

    }


}