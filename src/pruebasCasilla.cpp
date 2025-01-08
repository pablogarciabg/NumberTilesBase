//
// Created by Pablo Garcia & Ruben Flete on 05/12/2024.
//

#include <iostream>
using namespace std;

#include "casilla.h"
#include "pruebasCasilla.h"


void pruebaCrearCasilla(){
    casilla csa;
    crearCasilla(csa);

    if (obtenerValorCasilla(csa)!=0){
        cout<<"Error, la casilla no ha sido creada con exito";
    }


}

void pruebaPonerValor (){
    casilla csa;
    ponerValor(csa, 8);
    if (obtenerValorCasilla(csa)!=8){
        cout<<"Error al poner el valor 8 en la casilla";
    }

}

void pruebaEstaVacia (){
    casilla csa;
    crearCasilla(csa);

    if (estaVacia(csa)==false){
        cout<<"Error al detectar si la casilla esta llena o vacia";
    }

}

void pruebaObtenerValorCasilla (){
    casilla csa;

    ponerValor(csa, 10);
    if (obtenerValorCasilla(csa)!=10){
        cout<<"Error al obtener el valor de la casilla";
    }
}

void pruebaVaciarCasilla(){
    casilla csa;

    ponerValor(csa, 8);
    vaciarCasilla(csa);

    if (obtenerValorCasilla(csa)!=0){
        cout<<"Error al vaciar la casilla";
    }

}



void pruebasGeneralesCasilla (){
    cout<<"---------INCIO DE LAS PRUEBAS GENERALES CASILLA---------"<<"\n";

    cout<<"INICIO DE LAS PRUEBAS CREAR CASILLAS"<<"\n";
    pruebaCrearCasilla();
    cout<<"\n";
    cout<<"FIN DE LAS PRUEBAS CREAR CASILLAS"<<"\n";

    cout<<"INICIO DE LAS PRUEBAS PONER VALOR"<<"\n";
    pruebaPonerValor();
    cout<<"\n";
    cout<<"FIN DE LAS PRUEBAS PONER VALOR"<<"\n";

    cout<<"INICIO DE LAS PRUEBAS ESTA VACIA"<<"\n";
    pruebaEstaVacia();
    cout<<"\n";
    cout<<"FIN DE LAS PRUEBAS ESTA VACIA"<<"\n";

    cout<<"INICIO DE LAS PRUEBAS OBTENER VALOR CASILLA"<<"\n";
    pruebaObtenerValorCasilla();
    cout<<"\n";
    cout<<"FIN DE LAS PRUEBAS OBTENER VALOR CASILLA"<<"\n";

    cout<<"INICIO DE LAS PRUEBAS VACIAR CASILLA"<<"\n";
    pruebaVaciarCasilla();
    cout<<"\n";
    cout<<"FIN DE LAS PRUEBAS VACIAR CASILLA"<<"\n";

    cout<<"---------FIN DE LAS PRUEBAS GENERALES CASILLA---------"<<"\n";
}




