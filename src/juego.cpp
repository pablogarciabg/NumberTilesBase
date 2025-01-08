//
// Created by Pablo Garcia & Ruben Flete on 29/12/2024.
//

#include "juego.h"
#include "entorno.h"
#include "Tablero.h"
#include "cmath"
#include <iostream>
#include "pruebasCasilla.h"
#include "pruebasTablero.h"

void repintarTablero(Juego &juego) {
    for (int col = 0; col < juego.config.totalColumnas; ++col) {
        for (int fila = 0; fila < juego.config.totalFilas; ++fila) {
            entornoEliminarNumero(fila,col);
        }
    }

    for (int col = 0; col < juego.config.totalColumnas; ++col) {
        for (int fila = 0; fila < juego.tab[col].ocupadas; ++fila) {
            entornoPonerNumero(fila,col,juego.tab[col].fila[fila]);
        }
    }

    //Quitar las no ocupadas
//    for (int col = 0; col < juego.config.totalColumnas; ++col) {
//        for (int fila = obtenerValorOcupadas(juego.tab, col); fila < juego.config.totalFilas; ++fila) {
//            entornoEliminarNumero(fila,col);
//        }
//    }
}

void convertirMatrizTablero(tablero &tab, int filas, int columnas, int filasIniciales, int m[MAX_FILAS][MAX_COL]) {

    for (int col = 1; col <= columnas; col++) {
        for (int fila = 1; fila <= filasIniciales; fila++) {
            ponerValorTablero(tab, col, m[col - 1][fila - 1]);
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
            iniciarTableroAleatorio(juego.tab, nfilas, ncolumnas, filasIniciales, comoIniciar);

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
    juego.config.comoIniciar = comoIniciar;
}



void play(Juego &juego) {

    const int BASE_INICIO = 1;
    int columna, fila, puntuacion;
    columna = BASE_INICIO;
    fila= obtenerValorOcupadas(juego.tab, columna);

    puntuacion = 0;
    string msg;
    msg = " ";
    bool salir = false;
    int valorLanzador;

    if (juego.config.comoIniciar == 0){
        valorLanzador = pow(2, 1 + rand() % 12);
    } else {
        valorLanzador = pow(2, 1 + rand() % juego.config.comoIniciar);
    }


    TipoTecla tecla;

    entornoPonerNumeroLanzador(valorLanzador, columna - 1);
    entornoPonerPuntuacion(juego.puntuacion);

    while (!salir) {
        tecla = entornoLeerTecla();

        switch (tecla) {
            case TEnter: {


                int cont;
                cont = 0;

                if (juego.tab[columna-1].ocupadas < juego.config.totalFilas) {
                    dumpTablero(juego.tab,juego.config.totalFilas,juego.config.totalColumnas);

                    cout<<"colActiva:"<<columna<<" valorLanzador"<<valorLanzador<<"\n";
                    ponerValorTablero(juego.tab, columna, valorLanzador);

                    entornoPonerNumero(obtenerValorOcupadas(juego.tab,columna)-1, columna - 1, valorLanzador);

                    if (aplicarNuevoValorFila(juego.tab,columna, puntuacion)) {
                        repintarTablero(juego);
                        entornoPonerPuntuacion(puntuacion);
                        cout<<"Se ha repintado el tablero";

                    }

//                    dumpColumna(juego.tab,juego.config.totalFilas-1,columna-1);
                    dumpTablero(juego.tab,juego.config.totalFilas,juego.config.totalColumnas);



                    //dumpColumna(juego.tab,juego.config.totalFilas-1,columna-1);

                    //En este punto se ha finaliado el introducir valor en columna
                    valorLanzador = pow(2, 1 + rand() % juego.config.comoIniciar);
//                    entornoQuitarNumeroLanzador(columna - 1);

                    entornoPonerNumeroLanzador(valorLanzador,columna-1);

                }


                //Si el tablero se llena entonces, el juego acaba
                for (int col = 1; col <= juego.config.totalColumnas; col++) {
                    if (obtenerValorOcupadas(juego.tab, col) == juego.config.totalFilas) {
                        cont++;
                    }
                }
                if (cont == juego.config.totalColumnas) {
                    msg = "Has perdido";
                    salir = true;

                    entornoMostrarMensajeFin(msg);
                    entornoPausa(0.5);
                }





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
                entornoMostrarMensajeFin(msg);
                entornoPausa(0.5);
                break;
            case TNada:
                break;
        }

    }


}

int main (){
    Juego juego;

    inicializarJuego(juego);
    play(juego);
//    pruebasGeneralesCasilla();
//    pruebasGeneralesTablero();



    return 0;
}