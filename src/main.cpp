//============================================================================
// Name        : main.cpp (from NumberTiles Game)
// Author      : Pablo Garcia & Ruben Flete
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "Tablero.h"
#include "casilla.h"
#include "pruebasCasilla.h"
#include "pruebasTablero.h"
#include "entorno.h"
#include <cmath>
#include <cstdlib>
#include "NumberTiles.h"


int main() {
	ejemplo();
	pruebasGeneralesCasilla();
	pruebasGeneralesTablero();

	return 0;
}

