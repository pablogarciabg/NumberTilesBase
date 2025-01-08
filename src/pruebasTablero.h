//
// Created by Pablo Garcia & Ruben Flete on 08/12/2024.
//

#ifndef UNI_PROJECTS_PRUEBASTABLERO_H
#define UNI_PROJECTS_PRUEBASTABLERO_H
#include "Tablero.h"

#include <iostream>
using namespace std;
#include <cmath>

//DESC:Llamamos a la funcion vaciar tablero y comprobamos qu eel tablero esta vacio
void pruebasVaciarTablero();

//DESC: Damos diferentes valores a la variuable columna y comprobamos que funciona el módulo
void pruebaPasarColumnaBase0();

//DESC: Damos diferentes valores a la variable fila y comprobamos que funciona el módulo
void pruebaPasarFilaBase0();

//DESC: Inciamos el tablero de forma aletoria y comprobamos que las filas que estan llena y vacias
void pruebaIniciarTableroAleatorio();

//DESC: Ponemos diferentes valores en el tablero y comprobamos que se insertar conrrectamente con obtenerValorTablero
void pruebaPonerValorTablero(); //Dividido en varias pruebas

void pruebaPonerValorTablero01();
void pruebaPonerValorTablero02();
void pruebaPonerValorTablero03();

//DESC: Ponemos diferentes valores en el tablero y comprobamos que el modulo de los mimos numeros que hemos puesto
void pruebaObtenerValorTablero(); //Divido en varias pruebas

void pruebaObtenerValorTablero01();
void pruebaObtenerValorTablero02();
void pruebaObtenerValorTablero03();

//DESC: Inciamos el tablero de forma aleatoria y comprobamos que el modulo funcia en difrentes posiciones del tablero
void pruebaEstaVaciaCasillaTablero(); //Dividido en varias pruebas

void pruebaEstaVaciaCasillaTablero01();
void pruebaEstaVaciaCasillaTablero02();

//DESC: Ponemos valores en el tablero y comprobamos que el modulo los borra
void pruebasVaciarCasillaTablero();

//DESC: Ponemos valores en las columnas y comprobamos que el modulo funciona bien
void pruebasEstaLlenaColumnaTablero ();

//DESC: Poenmos valores en las columnas y comprobamos que el modulo funciona bien
void pruebasObtenerPosicionVaciaColumnaTablero(); //Divido en varias pruebas

void pruebasObtenerPosicionVaciaColumnaTablero01();
void pruebasObtenerPosicionVaciaColumnaTablero02();
void pruebasObtenerPosicionVaciaColumnaTablero03();

//DESC: Llenamos el tablero de diferesntes formas, y comprobamos que el modulo funciona correctamente
void pruebasEstaLlenoTablero();

//DESC: Comrpobamos que el modulo devuelve el numero de filas reasles
void pruebasObtenerNumFilas();

//DESC: Comrpobamos que el modulo devuelve el numero de columnas reasles
void pruebasObtenerNumColumnas();

//DESC: Creamos diferentes escenacrios y llamamos al modulo aplicarNuevoValorFila, y comrpbamos que funciona correctamente
void pruebaFusionCasillas();

//DESC: Ponemos un valor en el tablero y luego lo quitamos con el modulo diseñado, posteriormente comprobamos que se ha eliminado correcatmente
void pruebaQuitarValorTablero ();

//DESC: Ponemos el valor en el tablero, lo reemplazamos, y comprobamos que se ha realizado correctmente
void pruebaReemplazarValorTablero ();

//DESC: Probamos diferentes valores y llamamos al modulo para comprobar que funciona correcatmente
void pruebaAproximarValorPotencia();

//DESC: Creamos un escenario y llamamos la modulo para comprobar que lo imprime correcatmente
void pruebasDumpColumna ();

//DESC: Creamos un escenario y llamamos la modulo para comprobar que lo imprime correcatmente
void pruebasDumpTablero ();

//DESC: Creamos un esceario y llamamos al modulo, para comprobar que funciona correctamente
void pruebaCompactarTablero();


//DESC: Llamamos a todos las pruebas en este modulo
void pruebasGeneralesTablero();






#endif //UNI_PROJECTS_PRUEBASTABLERO_H
