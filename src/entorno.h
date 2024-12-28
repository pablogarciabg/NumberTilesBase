/**

	INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
	Curso 2024/2025

	Nombre: entorno.h
	Descripción: Especificación del TAD Entorno para el proyecto Number Tiles
	     	 	 encargado del manejo de la interfaz del juego.
	     	 	 Versión de allegro 5
	Autor:	Profesores de las asignaturas
    Fecha:	21/11/2024
*/

#ifndef ENTORNO_H_
#define ENTORNO_H_

#include <iostream>
using namespace std;


// -------------------------------------------------------------
// Definición de constantes públicas
// -------------------------------------------------------------

/*
 *  La constante MAX_FILAS define el número máximo de filas del tablero
 *  La constante MAX_COL define el número máximo de columnas del tablero
 */
const int MAX_FILAS = 7;
const int MAX_COL   = 7;


// -------------------------------------------------------------
// Definicion de tipos
// -------------------------------------------------------------

/**
 *   Este es el tipo devuelto por la operacion LeerTecla que indica la tecla
 *   de los cursores o teclas válidas que se ha pulsado
 */
enum TipoTecla {TNada, TEnter, TIzquierda, TDerecha, TSalir,TF1, TF2};


// ----------------------------------------------------------------
// Declaración de la interfaz pública (módulos que se pueden usar)
// ----------------------------------------------------------------


 /*
  *	PRE:  { 3 <= filas <= MAX_FILAS,  5 <= columnas <= MAX_COL }
  *	DESCRIPCIÓN: Inicia la interfaz gráfica del juego, preparada para
  *		  un tablero de filas x columnas casillas.
  */
void entornoIniciar (int filas, int columnas);

 /*
  *	DESCRIPCIÓN: Libera los recursos usados por el entorno gráfico
  */
void entornoTerminar ();

/*
 *	PRE: Archivo numberTiles.cnf correcto y en la carpeta raíz del proyecto
 *	     (NO SE COMPRUEBAN ERRORES EN LOS DATOS)
 *	POST: Devuelve:
 *	        true:  si se carga correctamente la configuración del juego,
 *		    false: en caso contrario.
 *   PARÁMETROS:
 *		Si la configuración se lee de forma correcta se devolverá:
 *		   numFilas:	     número de filas del tablero del juego
 *		   numColumnas:	     número de columnas del tablero del juego
 *		   comoIniciar:      si es 0, el tablero se inicia leyendo los valores del fichero de configuración
 *		   					 si es positivo (>0) el tablero se generará aleatoriamente con potencias de 2
 *		   					 entre 2 y 2 elevado a comoIniciar
 *		   filasIniciales:   número de filas del tablero con valores iniciales
 *		   m:				 matriz que contiene los valores numéricos del tablero del juego. Solo si comoIniciar es 0.
 *
 *		Por omisión, el archivo numberTiles.cnf se encuentra en el directorio  del proyecto
 */
bool entornoCargarConfiguracion ( int &numFilas, int &numColumnas,int &comoIniciar,int &filasIniciales, int m[MAX_FILAS][MAX_COL]);

/*
  *	PRE:  0 <= fila < MAX_FILAS,  0 <= columna < MAX_COL, numero es una potencia de 2
  *	DESCRIPCIÓN: Coloca en la posición indicada por fila y columna de la pantalla gráfica el número indicado
  *	dentro de un recuadro
*/
void entornoPonerNumero         ( int fila, int columna, int numero);

/*
  *	PRE: { 0 <= fila < MAX_FILAS,  0 <= columna < MAX_COL, numero es una potencia de 2 }
  *	DESCRIPCIÓN: Elimina de la posición indicada por fila y columna de la pantalla gráfica el número existente
*/
void entornoEliminarNumero      ( int fila, int columna);

/*
  *	PRE: { 0 <= fila < MAX_FILAS,  0 <= columna < MAX_COL, numero es una potencia de 2 }
  *	DESCRIPCIÓN: Coloca en la posición indicada por fila y columna el numero indicado
  *	dentro de un recuadro de color blanco.
  *	Sirve para la ampliación F2
*/
void entornoPonerNumeroPista    ( int fila, int columna, int numero);

/*
 * PRE: { 0 <= columna < MAX_COL,  numero es una potencia de 2 }
 * DESCRIPCIÓN: Coloca en la posición (columna) del lanzador el número indicado dentro de un recuadrado
 */
void entornoPonerNumeroLanzador  ( int numero, int columna);

/*
  *	PRE:  { 0 <= columna < MAX_COL }
  *	DESCRIPCIÓN: Elimina el numero existente de la columna del lanzador
*/
void entornoQuitarNumeroLanzador ( int columna);

/*
 * PRE: { valor >= 0 }
 * DESCRIPCIÓN: Muestra el valor indicado como puntuación en el marcador situado en la parte superior del tablero
 */
void entornoPonerPuntuacion      ( int valor);

/*
  *	PRE:  { 0 <= valor <= 3 }
  *	DESCRIPCIÓN: Muestra el número de veces que se puede desechar un numero del lanzador
  *	             en un círculo a la derecha del lanzador
  *	             Sirve para la ampliación F1
*/
void entornoContadorAyuda        ( int valor);

/*
 * PRE: { }
 * POST:Devuelve el valor enumerado de TipoTecla que corresponde a la tecla que se haya pulsado
 */
TipoTecla entornoLeerTecla      ();


/*
 * PRE: {"msg" está correctamente inicializado}
 * DESCRIPCIÓN: Muestra el mensaje "msg" en el centro de la ventana para indicar que ha finalizado el juego
 */
void entornoMostrarMensajeFin  (string msg);


/*
 * PRE: {0 < pausa}
 * DESCRIPCIÓN: para la ejecución durante "pausa" segundos
 */
void entornoPausa         (float pausa);

#endif
