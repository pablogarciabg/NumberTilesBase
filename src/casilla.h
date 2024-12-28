//
// Created by Pablo Garcia & Ruben Flete on 05/12/2024.
//

#ifndef UNI_PROJECTS_CASILLA_H
#define UNI_PROJECTS_CASILLA_H

#include <iostream>
using namespace std;

//Una casilla vacia, significa que el valor que contiene es 0
//Al crear una casilla, este inicialmente contiene el valor 0


typedef int casilla;


//PRE={Casilla vacia cuando contiene el valor 0}
//COMPLEJIDAD=O(1)
//POST={Crea una casilla}

void crearCasilla (casilla &csa);

//PRE={Valor>=0 && Valor=2^x}
//COMPLEJIDAD=O(1)
//POST={Asigna un valor a la casilla}

void ponerValor (casilla &csa, int num);

//PRE={}
//COMPLEJIDAD=O(1)
//POST={Deterimna si la celda indicada esta vacía(true) o llena (false)}

bool estaVacia (casilla csa);

//PRE={}
//COMPLEJIDAD=O(1)
//POST={Deveulve el valor que contiene la casilla}

int obtenerValorCasilla (casilla csa);

//PRE={}
//COMPLEJIDAD=O(1)
//POST={Elimina el valor que almacena una casilla determinada (Valor 0 = vacia)}

void vaciarCasilla (casilla &csa);





#endif //UNI_PROJECTS_CASILLA_H
