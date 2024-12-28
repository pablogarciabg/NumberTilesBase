//
// Created by Usuario on 05/12/2024.
//

#include <iostream>
using namespace std;

struct casilla {
    int valor;
};

typedef casilla tipoFila[7];

struct columna {
    int ocupadas;
    tipoFila filas;
};

typedef columna tablero[7];


struct prueba{
    int opcupadas;
    int numero;
};

void insertarValorTablero(casilla c,tablero &t,int col) {
    int primeraCasillaLibre = t[col].ocupadas;
    t[col].filas[primeraCasillaLibre].valor=c.valor;
    t[col].ocupadas+=1;
}

/*


*/
