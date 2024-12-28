//
// Created by Usuario on 05/12/2024.
//

#include <iostream>
#include "casilla.h"
using namespace std;


void crearCasilla (casilla &csa){

    csa=0;
}

void ponerValor (casilla &csa, int num){
    csa=num;
}

bool estaVacia (casilla csa){
    bool vacia;
    if (csa==0){
        vacia=true;
    } else {
        vacia=false;
    }
    return vacia;
}

int obtenerValorCasilla (casilla csa){
    return csa;
}

void vaciarCasilla (casilla &csa){
   csa=0;
}

