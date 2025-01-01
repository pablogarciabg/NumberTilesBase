//============================================================================
// Name        : numberTiles.cpp
// Author      : 
// Version     :
// Description : Programa principal del proyecto Number Tiles
//============================================================================


#include "entorno.h"
#include "juego.h"
#include "Tablero.h"
//#include "casilla.h"
#include "pruebasTablero.h"

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

// Módulo donde se prueban algunas operaciones del entorno
// Se carga la configuración que hay en el fichero numberTiles.config
// Se inicia un tablero con la información de la configuración
// Se genera un número aleatorio en el lanzador, la parte inferior del tablero
// Se inicia elbucle de procesamiento de las teclas:
//       TDerecha: Se mueve el número del lanzador hacia la derecha
//       TSalir: Termina el programa con el mensaje de abandono
// Se aconseja modificar los valores del fichero de configuración para ver
// cómo cambia este ejemplo.
//

void ejemplo() {
	string msg;
	msg = " ";
	bool salir = false;

	TipoTecla tecla;

    //tablero t


	srand (time(NULL));

	int numFilas, numColumnas, comoIniciar, filasIniciales;

	int columna, fila;
	columna = 0;
	fila = 0;
	int m[MAX_FILAS][MAX_COL];
	int valor;

	// numFilas: número de filas del tablero
	// numColumnas: número de columnas del tablero
	// comoIniciar: si es 0, el tablero se inicia con los valores del fichero de configuracion guardados en m
	//          si es mayor que 0, el tablero se inicia con valores aleatorios potencias de 2 entre
	//          2 y (2 elevado a comoIniciar)
	// filasIniciales: número de filas iniciales con valores en el tablero
	// m: matriz de enteros con los valores iniciales para el tablero si comoIniciar es igual a 0

	if (entornoCargarConfiguracion(numFilas, numColumnas, comoIniciar, filasIniciales, m)){

        //convertir ese M en nuestro Tablero

		entornoIniciar(numFilas, numColumnas);


		// Pinta la pantalla completa
		for (fila = 0; fila < numFilas; fila++){
				for (columna = 0; columna < numColumnas; columna++){
					if (fila < filasIniciales){
						if (comoIniciar==0)
							entornoPonerNumero(fila,columna, m[fila][columna]);
						else
							entornoPonerNumero(fila, columna, pow(2, rand()%comoIniciar+1));
					}
					else{
						entornoEliminarNumero(fila, columna);
					}
				}
		}

		fila = 0;
		columna = 0; // columna de comienzo del valor en el lanzador

		valor = pow (2,(1 + rand() % 8 ) );
		entornoPonerNumeroLanzador(valor, columna);

		while (!salir) {
			tecla = entornoLeerTecla();

			switch (tecla) {
			case TEnter:
				//bool enc=false;
				//while (i<ocupadas){
					//if (m[fila][col]==0)
				//}


				break;
			case TDerecha:
				entornoQuitarNumeroLanzador(columna);

				if (columna < numColumnas - 1)
					columna++;
				else
					columna = 0;

				entornoPonerNumeroLanzador(valor, columna);

				break;
			case TIzquierda:
				entornoQuitarNumeroLanzador(columna);
				if ((columna <= numColumnas -1) && (columna>0)){
					columna--;
				}
				else {
					columna=numColumnas-1;
				}
				entornoPonerNumeroLanzador(valor, columna);

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

		entornoMostrarMensajeFin(msg);
		entornoPausa(1.5);
	}

	entornoTerminar();
}

//int playJuego() {
//
//
//    inicializarJuego(juego);
//}

int main() {

    Juego juego;

    inicializarJuego(juego);
    play(juego);

//    pruebasGeneralesTablero();

	return 0;
}


