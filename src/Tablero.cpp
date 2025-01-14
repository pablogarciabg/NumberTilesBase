//
// Created by Pablo Garcia & Ruben Flete on 07/12/2024.
//

#include <iostream>
#include <cmath>

using namespace std;

#include "Tablero.h"
#include "casilla.h"
#include "entorno.h"
#include "juego.h"


void pasarColumnaBase0(int &col) {
    if (col >= 1) {
        col--;
    }
    if (col == MAX_COLUMNAS) { //Suponemos que nunca se introducen datos incorrectos

        col = MAX_COLUMNAS - 1;
    }
    if (col == 0) { //Suponemos que nunca se introducen datos incorrectos

        col = 0;
    }
}

void pasarFilasBase0(int &fila) {
    if (fila >= 1) {
        fila--;
    }
    if (fila == MAX_FIL) { //Suponemos que nunca se introducen datos incorrectos

        fila = MAX_FIL - 1;
    }
    if (fila == 0) { //Suponemos que nunca se introducen datos incorrectos

        fila = 0;
    }
}


void vaciarTablero(tablero &t) {

    for (int col = 0; col < MAX_COLUMNAS; col++) {
        t[col].ocupadas = 0;
        for (int fila = 0; fila < MAX_FIL; fila++) {
            vaciarCasilla(t[col].fila[fila]);
        }
    }
}

//Siempre quita la última fila ocupada
void quitarValorTablero(tablero &t, int col) {

    pasarColumnaBase0(col);

    //Siempre se elimina la última casilla de una columna.
    t[col].fila[t[col].ocupadas - 1] = 0;
    t[col].ocupadas--;

}

void recalcularOcupadas(tablero &t,int columna) {
    int total=0;
    for (int fila = 1; fila <= MAX_FIL;fila++) {
       if (obtenerValorTablero(t,fila,columna)!=0) {
           total++;
       }
    }

    t[columna-1].ocupadas=total;
}

void compactarColumna(tablero &t,int columna) {

    for (int fila = 1; fila <= MAX_FIL; ++fila) {
        if (obtenerValorTablero(t,fila,columna)==0) {
            //Buscar la siguiente fila llena
            bool enc=false;
            int filaLlena = fila+1;
            while (!enc && filaLlena<=MAX_FIL) {
                if (obtenerValorTablero(t,filaLlena,columna)!=0) {
                    int aux = obtenerValorTablero(t,filaLlena,columna);
                    //Intercambiar valores entre fila y filaLlena
                    reemplazarValorTablero(t,columna,fila,aux);
                    reemplazarValorTablero(t,columna,filaLlena,0);
                    enc=true;
                } else {
                    filaLlena++;
                }
            }
        }
    }

}
//Elimina una casilla, subiendo el resto hacia arriba
void eliminarValorTablero(tablero &t, int fila, int col) {

    //Comprobar si la fila eliminada === última fila.
      //a) Si es última fila, llamar a quitarValorTablero
      //b) Si no es la última, poner a 0 esta fila, y subir el resto hacia arriba.
      //  Recorrer desde fila actual hacia abajo, y subir una fila hacia arriba

    if (fila == obtenerValorOcupadas(t,col)) {
        //Estamos en la ultima
        quitarValorTablero(t,col);
    } else {
        //No estoy en la ultima, y tengo que desplazar el hueco hasta el final
        reemplazarValorTablero(t,col, fila,0);

        compactarColumna(t,col);
        recalcularOcupadas(t,col);

    }
}


void iniciarTableroAleatorio(tablero &t, int nfilas, int ncolumnas, int filasIniciales, int comoIniciar) {

    srand(time(NULL));

    for (int col = 0; col < ncolumnas; col++) { //columnaS
        for (int fila = 0; fila < nfilas; fila++) {
            ponerValor(t[col].fila[fila], pow(2, 1 + rand() % comoIniciar));


        }
        t[col].ocupadas = filasIniciales;
    }

    //Inicializacion del resto de casillas a 0, estan vacias
    for (int col = 0; col < ncolumnas; col++) {
        for (int fila = filasIniciales; fila < nfilas; fila++) {
            ponerValor(t[col].fila[fila], 0);
        }
    }
}

/*
 * Encarga de fusionar las 2 últimas casillas de una columna.
 */
void fusionFilaAdyacentes(tablero &t, int colActiva, int valorActual, int valorPrevio) {

    int sumaValor;
    sumaValor = valorPrevio + valorActual;
    t[colActiva].fila[t[colActiva].ocupadas - 2] = sumaValor;
    t[colActiva].ocupadas =
            t[colActiva].ocupadas - 1; //Poner valor tablero suma+1 a ocupadas, pero en caso de fusión no es requerido.
    for (int fila = t[colActiva].ocupadas; fila < MAX_FIL; ++fila) {
        t[colActiva].fila[fila] = 0;
    }
}

void fusionTriple(tablero &t, int columna, int fila, int &puntuacion) {

    int valorIzq, valorDer, valorSuperior, valorActual,resultadoFusion,totalPuntuacion;

    valorIzq = obtenerValorTablero(t, fila, columna - 1);
    valorDer = obtenerValorTablero(t, fila, columna + 1);
    valorSuperior = obtenerValorTablero(t, fila - 1, columna);
    valorActual= obtenerValorTablero(t, fila, columna);

    resultadoFusion =  valorSuperior + valorDer + valorIzq + valorActual; //2^x < resultdoFusion < 2^x+1

    //Eliminar las casillas fusionadas
    eliminarValorTablero(t, fila, columna - 1);
    eliminarValorTablero(t, fila, columna + 1);
    eliminarValorTablero(t, fila, columna);
    quitarValorTablero(t, columna);
    resultadoFusion = aproximarValorPotencia(t, resultadoFusion);
    puntuacion = puntuacion + resultadoFusion;
    ponerValorTablero(t, columna, resultadoFusion);

    cout<<"fusionTripe aplicada\n";
}

void fusionDobleIzq(tablero &t, int columna, int fila, int &puntuacion) {

    int valorIzq, valorSuperior,valorActual, resultadoFusion;
    valorIzq = obtenerValorTablero(t, fila, columna - 1);
    valorSuperior = obtenerValorTablero(t, fila - 1, columna);
    valorActual= obtenerValorTablero(t, fila, columna);


    resultadoFusion = valorSuperior + valorIzq + valorActual;

    //Eliminar las casillas fusionadas
    eliminarValorTablero(t, fila, columna - 1); //izq
    quitarValorTablero(t, columna); //actual
    quitarValorTablero(t, columna); //superior
    resultadoFusion = aproximarValorPotencia(t, resultadoFusion);
    puntuacion = puntuacion + resultadoFusion;
    ponerValorTablero(t, columna, resultadoFusion);  //poner la fusion

    cout<<"fusionDobleIzq aplicada\n";
}

void fusionDobleDer(tablero &t, int columna, int fila, int &puntuacion) {

    int valorDer, valorSuperior, valorActual, resultadoFusion;
    valorDer = obtenerValorTablero(t, fila, columna + 1);
    valorSuperior = obtenerValorTablero(t, fila - 1, columna);
    valorActual = obtenerValorTablero(t, fila, columna);

    resultadoFusion = valorSuperior + valorDer + valorActual;

    //Eliminar las casillas fusionadas
    eliminarValorTablero(t,fila, columna + 1); //der
    quitarValorTablero(t, columna);
    quitarValorTablero(t, columna);
    resultadoFusion = aproximarValorPotencia(t, resultadoFusion);
    puntuacion = puntuacion + resultadoFusion;
    ponerValorTablero(t, columna, resultadoFusion);


    cout<<"fusionDobleDer aplicada\n";
}

void fusionSimpleDer(tablero &t, int columna, int fila, int &puntuacion) {

    int valorDer, resultadoFusion, valorActual;
    valorDer = obtenerValorTablero(t, fila, columna + 1);
    valorActual= obtenerValorTablero(t, fila, columna);


    resultadoFusion = valorActual+ valorDer;

    //Eliminar las casillas fusionadas
    eliminarValorTablero(t, fila, columna + 1); //der
    quitarValorTablero(t, columna);
    resultadoFusion = aproximarValorPotencia(t, resultadoFusion);
    puntuacion = puntuacion + resultadoFusion;
    ponerValorTablero(t, columna, resultadoFusion);


    cout<<"fusionSimpleDer aplicada\n";
}

void fusionSimpleIzq(tablero &t, int columna, int fila, int &puntuacion) {

    int valorIzq, resultadoFusion, valorActual;
    valorIzq = obtenerValorTablero(t, fila, columna -1);
    valorActual= obtenerValorTablero(t, fila, columna);


    resultadoFusion = valorActual + valorIzq;

    //Eliminar las casillas fusionadas
    eliminarValorTablero(t,fila, columna - 1); //izq
    quitarValorTablero(t, columna); //actual
    resultadoFusion = aproximarValorPotencia(t, resultadoFusion);
    puntuacion = puntuacion + resultadoFusion;
    ponerValorTablero(t, columna, resultadoFusion);


    cout<<"fusionSimpleIzq aplicada\n";
}

void fusionSimpleSup(tablero &t, int columna, int fila, int &puntuacion) {

    int resultadoFusion, valorActual, valorSup;
    valorSup = obtenerValorTablero(t, fila - 1, columna);
    valorActual= obtenerValorTablero(t, fila, columna);


    resultadoFusion = valorActual + valorSup;

    //Eliminar las casillas fusionadas
    quitarValorTablero(t, columna);
    quitarValorTablero(t, columna);
    resultadoFusion = aproximarValorPotencia(t, resultadoFusion);
    puntuacion = puntuacion + resultadoFusion;
    ponerValorTablero(t, columna, resultadoFusion);


    cout<<"fusionSimpleSup aplicada\n";
}

int aproximarValorPotencia (tablero &t, int valor){ //Usamos fila, ya que dentro llamamamos a "obtenerValorTablero"

    int MAX_EXPONENTE = 12;
    int maxPotencia = pow (2, MAX_EXPONENTE);
    int expAnterior;
    expAnterior = 1;
    int expPosterior;
    expPosterior = expAnterior + 1;

    bool reemplazado = false;
    int potenciaAnterior = pow (2, expAnterior);
    int potenciaSuperior = pow (2, expPosterior);


    while (!reemplazado && potenciaSuperior <= maxPotencia +1){
        if ((potenciaAnterior < valor) && (potenciaSuperior > valor)){
            valor = pow (2, expPosterior);
            reemplazado = true;
        }

        if (valor == pow(2, 0)){
            valor = 2;
            reemplazado = true;
        }

        expAnterior++;
        expPosterior = expAnterior + 1;
        potenciaAnterior = pow (2, expAnterior);
        potenciaSuperior = pow (2, expPosterior);

    }

    return valor;
}

void fusionDerIzq (tablero &t, int fila, int columna, int &puntuacion){

    int valorActual, valorDer, valorIzq, resultadoFusion;

    valorActual= obtenerValorTablero(t, fila, columna);
    valorDer= obtenerValorTablero(t,fila, columna+1);
    valorIzq= obtenerValorTablero(t, fila, columna-1);

    resultadoFusion=valorActual+valorDer+valorIzq;

    eliminarValorTablero(t, fila, columna-1);
    eliminarValorTablero(t, fila, columna+1);
    quitarValorTablero(t, columna);
    resultadoFusion = aproximarValorPotencia(t, resultadoFusion);
    puntuacion = puntuacion + resultadoFusion;
    ponerValorTablero(t, columna, resultadoFusion);




}

bool aplicarNuevoValorFila(tablero &t, int colActiva, int &puntuacion) {
//    pasarColumnaBase0(colActiva);
//    colActiva++;


    int filaCheck, valorActual = -1, valorSup= - 1, valorIzq= - 1, valorDer= - 1;
    bool hayFusion = false;


    if (obtenerValorOcupadas(t,colActiva) <= 1) {
        cout << "AplicarNuevoValorFila.No-existen-suficientes-filas-ocupadas\n";
        return hayFusion;
    }

    filaCheck = obtenerValorOcupadas(t,colActiva);  //TODO: CAMBIAR-BASE (t[colActiva].ocupadas-1)
    valorActual = obtenerValorTablero(t,filaCheck,colActiva);

    /* Caso 1:      4
        *         4 X 4
        *  Resultado sería 16
        *  Si izq y der y arriba == valor col/fila ==> aplicar fusión1
        */
    {
        if ((filaCheck-1)>=1) {
            valorSup = obtenerValorTablero(t, filaCheck - 1, colActiva);
        } else {
            valorSup=-1;
        }
        if ((colActiva-1)>=1) {
            valorIzq = obtenerValorTablero(t, filaCheck, colActiva - 1);
        } else {
            valorIzq=-1;
        }

        if ((colActiva+1)<=MAX_COLUMNAS) {
            valorDer = obtenerValorTablero(t, filaCheck, colActiva + 1);
        } else {
            valorDer=-1;
        }

        valorActual = obtenerValorTablero(t, filaCheck, colActiva);

        if (!hayFusion && valorActual == valorIzq && valorActual == valorDer && valorActual == valorSup) {
            hayFusion = true;
            fusionTriple(t, colActiva, filaCheck, puntuacion);
        }

    }

    /* Caso 2:      4
       *         4  X
       *  Resultado sería 16 (redondea a 16)
       *  Si (!hayFusion y (izq (no der) y arriba == valor), col/fila ==> aplicar fusión {
       */
    {
        if (!hayFusion && valorActual == valorIzq && valorActual == valorSup) {
            hayFusion = true;
            fusionDobleIzq(t, colActiva, filaCheck, puntuacion);
        }

    }

    /* Caso 3:   4
     *           X 4
     *  Resultado sería 16 (redondea a 16)
     */
    //Si (!hayFusion y ((no izq) der y arriba == valor), col/fila ==> aplicar fusión {
    //fusionDobleDer(t, col/fila)

    {
        if (!hayFusion && valorActual == valorDer && valorActual == valorSup) {
            hayFusion = true;
            fusionDobleDer(t, colActiva, filaCheck, puntuacion);
        }
    }

    /* Caso 7:
    *          4 X 4
    *  Resultado sería 12
    */

    {

        if (!hayFusion && valorActual == valorDer && valorActual == valorIzq) {
            hayFusion = true;
            fusionDerIzq(t, filaCheck, colActiva, puntuacion);
        }

        if (hayFusion ){
            cout<<"Iza:"<<valorIzq<<";Sup:"<<valorSup<<";Der:"<<valorDer<<"\n";
            cout<<"      Act:"<<valorActual<<"\n";
        }

    }

    /* Caso 4:
     *           X 4
     *  Resultado sería 8
     */
    //Si (!hayFusion y (der == valor), col/fila ==> aplicar fusión {
    //fusionDerSimple(t, col/fila)
    {
        if (!hayFusion && valorActual == valorDer) {
            hayFusion = true;
            fusionSimpleDer(t, colActiva, filaCheck, puntuacion);
        }
    }

    /* Caso 5:
     *         4 X
     *  Resultado sería 8
     */
    //Si (!hayFusion y (izq == valor), col/fila ==> aplicar fusión {
    //fusionSimpleIzq(t, col/fila)
    {
         cout<<valorIzq<<";"<<valorActual;
        if (!hayFusion && valorActual == valorIzq) {
            hayFusion = true;
            fusionSimpleIzq(t, colActiva, filaCheck, puntuacion);
        }
    }

    /* Caso 6:   4
     *           X
     *  Resultado sería 8
     */
    //Si (!hayFusion y (superior == valor), col/fila ==> aplicar fusión {
    //fusionSimpleSup(t, col/fila)

    {

        if (!hayFusion && valorActual == valorSup) {
            hayFusion = true;
            fusionSimpleSup(t, colActiva, filaCheck, puntuacion);
        }

        if (hayFusion ){
            cout<<"Iza:"<<valorIzq<<";Sup:"<<valorSup<<";Der:"<<valorDer<<"\n";
            cout<<"      Act:"<<valorActual<<"\n";
        }

    }



//    bool continuar = true;



//    while (continuar) {
//        cout << "aplicarNuevoValorFila: valorAct:" << valorActual << ";" << valorSup << "\n";
//        if (valorActual == valorSup) {
//            //aplicar fusión
//            cout << "Debería aplicar fusion\n";
//            fusionFilaAdyacentes(t, colActiva, valorActual, valorSup);
//            hayFusion = true;
//
//            //Una vez fusiona, habría que continuar
//
//            filaCheck = filaCheck - 1;
//            valorActual = t[colActiva].fila[filaCheck];
//            valorSup = t[colActiva].fila[filaCheck - 1];
//        } else {
//            continuar = false;
//        }
//    }



    return hayFusion;
}


void ponerValorTablero(tablero &t, int col, int valor) {

    pasarColumnaBase0(col);
    //Obtenemos ocupadas de esta forma ya que sino cambiariamos de base 2 veces
    int ocupadas = t[col].ocupadas;
    ponerValor(t[col].fila[ocupadas], valor);
    t[col].ocupadas++;
}

void reemplazarValorTablero (tablero &t, int columna, int fila, int valor){

    pasarColumnaBase0(columna);
    pasarFilasBase0(fila);

    t[columna].fila[fila] = valor;
    //No actauzalizamos ocupadas ya que este funcion SOLO se encargar de reemplazar un numero por otro

}

void dumpColumna(tablero &t, int nfilas, int col) {
    cout << "\nVolcado-columna: " << col << "\n filas: ";
    for (int fila = 0; fila < nfilas; fila++) {
        cout << t[col].fila[fila] << "; ";
    }
    cout << "Ocupadas:" << t[col].ocupadas << "\n";
}

void dumpTablero(tablero &t, int nfilas, int ncols)  {
    cout << "\nVolcado-tablero:\n";
    for (int fila = 0; fila < nfilas; fila++) {
        cout<<fila+1<<"- ";
        for (int coln = 0; coln < ncols; coln++) {
            cout<<t[coln].fila[fila]<<"\t";
        }
        cout<<"\n";
    }
    cout<<"---------------------------------\n   ";
    for (int coln = 0; coln < ncols; coln++) {
        cout<<t[coln].ocupadas<<"\t";
    }
}

int obtenerValorTablero(tablero t, int fila, int col) {

    pasarFilasBase0(fila);
    pasarColumnaBase0(col);

    return obtenerValorCasilla(t[col].fila[fila]);

}

int obtenerValorOcupadas(tablero t, int col) {

    pasarColumnaBase0(col);

    return t[col].ocupadas;
}

bool estaVaciaCasillaTablero(tablero t, int fila, int col) {

    pasarFilasBase0(fila);
    pasarColumnaBase0(col);

    bool vacia = false;
    if (obtenerValorCasilla(t[col].fila[fila]) == 0) {
        vacia = true;
    }
    return vacia;
}

void vaciarCasillaTablero(tablero &t, int fila, int col) {

    pasarFilasBase0(fila);
    pasarColumnaBase0(col);

    ponerValor(t[col].fila[fila], 0);

}

bool estaLlenaColumnaTablero(tablero t, int col) {

    pasarColumnaBase0(col);

    bool vacia = false;
    int fila = 1;

    while (!vacia){

        if (fila <= MAX_FILAS){
            if (obtenerValorTablero(t, fila, col) == 0){
                vacia = true;
            }
        }
        fila++;
    }

    return vacia;
}

int obtenerPosicionVaciaColumnaTablero(tablero t, int col) {

    pasarColumnaBase0(col);

    int fila = t[col].ocupadas;
    if (fila >= MAX_FIL) {
        fila = -2;
    }

    return fila + 1; //Devuelve en base 1
}

bool estaLlenoTablero(tablero t) {
    bool lleno;
    lleno = true;
    int filas = 0;
    int columnas = 0;
    int cont = 0;


    while (lleno == true && columnas < MAX_COLUMNAS) {
        while (lleno == true && filas < MAX_COLUMNAS) {
            if (obtenerValorCasilla(t[columnas].fila[filas]) != 0) {
                filas++;
                cont++;

            } else {
                lleno = false;
            }
        }
        columnas++;
    }

    if (cont == MAX_FIL) {
        lleno = true;
    }


    return lleno;
}


int obtenerNumFilas(tablero t) {
    return MAX_FIL;
}

int obtenerNumColumnas(tablero t) {
    return MAX_COLUMNAS;
}



/**/
void compactarTablero(tablero &t) {
    for (int col = 1; col <= MAX_COLUMNAS ; ++col) {
        compactarColumna(t,col);
    }
}

