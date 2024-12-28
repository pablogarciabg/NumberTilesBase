/**

 INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
 Curso 2024/2025

 Nombre: entorno.cpp
 Descripción: Implementación del TAD Entorno para el proyecto NumberTiles
 Encargado del manejo de la interfaz del juego.
 Autor:	Profesores de las asignaturas
 Fecha:	15/10/2024
 Fecha última modificación: 30/10/2024 Allegro5

 */

#include "entorno.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro5.h>


#include <fstream>
#include <cmath>
#include <unistd.h>

using namespace std;

// -------------------------------------------------------------
// Definicion de constantes privadas
// -------------------------------------------------------------
// Definición de colores que usa el entorno

const int COLOR_AZUL        = 1;
const int COLOR_BLANCO      = 2;
const int COLOR_NEGRO       = 3;
const int COLOR_GRIS        = 4;
const int COLOR_GRIS_CLARO  = 5;
const int COLOR_AZUL_ANIL   = 6;
const int COLOR_ROJO        = 7;

const int ANCHO_VENTANA = 600;
const int ALTO_VENTANA  = 650;

// Definicón de constantes para posicionar los números en el tablero

const int SEPARACION_FILAS_COL = 10;  // separacion entre las filas y columnas
const int ALTO_CASILLA         = 45;  // Tamaño de cada casilla del tablero
const int ANCHO_CASILLA        = 55;
const int TAMANO_CUADRADO      = 65;


const int SEPARACION_CUADRADROS = 20;


int ORIGEN_X           = 80 ;  // Origen de las x
int FIN_X              = 120;
int FIN_Y              = 120;
int POS_X              = 85;   // dentro del rectangulo
const int ORIGEN_Y     = 60 ;  // Origen de las y
const int POS_Y        = 85; // DENTRO DEL RECTANGULO

// valor del radio para el redondeo de las esquinas del rectangulo
const int RADIO = 12;
const int RADIO_PRAL = 20;

// definicion de las constantes para posicionar los marcadores
const int FILA_MARCADOR = 110;
const int COL_MARCADOR  = 24;

int NUM_CASILLAS_COL;

ALLEGRO_DISPLAY     *display;
ALLEGRO_FONT        *font, *fontNum;
ALLEGRO_EVENT_QUEUE *colaEventos = NULL;


// -------------------------------------------------------------
// Definición de módulos PRIVADOS
// -------------------------------------------------------------

// define el color en función de los valores makecol - allegro library
ALLEGRO_COLOR makecolor2(int color) {

	ALLEGRO_COLOR alColor;

	switch (color) {
	case COLOR_BLANCO:
		alColor = al_map_rgb (255, 255, 255);
		break;
	case COLOR_ROJO:
		alColor = al_map_rgb (190, 5, 5);
		break;
	case COLOR_NEGRO:
		alColor = al_map_rgb (10,    10,   10);
		break;
	case COLOR_AZUL:
		alColor = al_map_rgb_f (0.160,0.64,0.64);
		break;
	case COLOR_AZUL_ANIL:
		alColor = al_map_rgb (28,   76, 150);
		break;
	case COLOR_GRIS:
		alColor = al_map_rgb ( 47, 79, 79);
		break;
	case COLOR_GRIS_CLARO:
		alColor = al_map_rgb ( 192,192,192);
		break;
	default:
		alColor = al_map_rgb (255, 255, 255);
		break; //color blanco
	}

	return alColor;
}
void invertirFC(int &fila, int &columna) {
	int aux = columna;
	columna = fila;
	fila = aux;
}

// -------------------------------------------------------------
// Definición de la interfaz PÚBLICA
// -------------------------------------------------------------

void entornoIniciar(int filas, int columnas) {

	string msg;
	NUM_CASILLAS_COL = filas;
	int inc;

	if (al_init()) {
		al_install_keyboard();
		al_set_new_display_option(ALLEGRO_SINGLE_BUFFER, 1, ALLEGRO_SUGGEST);
		al_set_new_display_flags(ALLEGRO_WINDOWED);
		display = al_create_display(ANCHO_VENTANA, ALTO_VENTANA);
		al_init_primitives_addon();
		al_init_font_addon();
		al_init_ttf_addon();

		font = al_load_ttf_font("DroidSerif-Regular.ttf", 19, 0);
		fontNum = al_load_ttf_font("Roboto-Bold.ttf", 18, 0);

		al_clear_to_color(makecolor2(COLOR_BLANCO));
		al_set_window_title(display, "UEx Number Tiles");

		// se refresca la pantalla
		colaEventos = al_create_event_queue();
		al_register_event_source(colaEventos, al_get_keyboard_event_source());
		al_register_event_source(colaEventos,
				al_get_display_event_source(display));

		ORIGEN_X = ((ANCHO_VENTANA - ((columnas) * ANCHO_CASILLA)) / 2) - 40;
		FIN_X = (ORIGEN_X + (columnas + 1) * (ANCHO_CASILLA + SEPARACION_FILAS_COL)) - 35;
		FIN_Y = (filas + 1) * (ALTO_CASILLA + SEPARACION_FILAS_COL)	+ SEPARACION_FILAS_COL;
		// color del fondo azul degradado
		for (int i = 1; i < ANCHO_VENTANA; i++) {
			float blue = (float) i / 255 * 1.5;
			al_draw_line(i, 0, i, ALTO_VENTANA,	al_map_rgb_f(blue / 4, blue, blue), 0);
		}

		// Dibujar rectángulo grande
		al_draw_filled_rounded_rectangle(ORIGEN_X, ORIGEN_Y, FIN_X, FIN_Y,RADIO_PRAL, RADIO_PRAL, makecolor2(COLOR_AZUL));
		al_draw_rounded_rectangle(ORIGEN_X, ORIGEN_Y, FIN_X, FIN_Y, RADIO_PRAL,	RADIO_PRAL, makecolor2(COLOR_GRIS), 3);
		if ( filas <= 5)inc = 51;else inc = 22;

		// Dibujar las columnas dentro del  rectángulo
		POS_X = ORIGEN_X + (SEPARACION_FILAS_COL * 3) - 5;
		int x1 = ORIGEN_X + SEPARACION_FILAS_COL * 2;
		int y1 = ORIGEN_Y + SEPARACION_FILAS_COL * 2;
		int x2 = x1 + ANCHO_CASILLA;
		int y2 = (filas  * ((ALTO_CASILLA) + (SEPARACION_FILAS_COL))+inc);
		int r = 10;		for (int i = 0; i < columnas; i++) {
			al_draw_filled_rounded_rectangle(x1, y1, x2, y2, r, r,	makecolor2(COLOR_GRIS_CLARO));
			x1 = x1 + (ANCHO_CASILLA) + SEPARACION_FILAS_COL;
			x2 = x1 + ANCHO_CASILLA;
		}

		// rectangulo que sirve de lanzador
		x1 = POS_X + (0 * TAMANO_CUADRADO);
		y1 = POS_Y + ((filas + 2) * ALTO_CASILLA);
		x2 = (x1 + ANCHO_CASILLA) - SEPARACION_FILAS_COL;
		y2 = (y1 + ALTO_CASILLA) - SEPARACION_FILAS_COL;

		// rectangulo alargado que ocupa todo el lanzador
		al_draw_rounded_rectangle(x1 - 20, y1 - 5, FIN_X + 1, y2 + 6, 8, 8,	  makecolor2(COLOR_GRIS), 3);
		al_draw_filled_rounded_rectangle(x1 - 18, y1 - 4, FIN_X, y2 + 4, 8, 8,makecolor2(COLOR_AZUL));

		msg = "Cursores: ←, → Enter: selec. Esc: salir F1: desechar F2: pista ";

		al_draw_text(font, makecolor2(COLOR_NEGRO), 42, 600, ALLEGRO_ALIGN_LEFT,msg.c_str());
		al_flip_display();
	}
}


void valorAColor(int valor, int& r, int& g, int& b) {
    float logVal = log2(valor);
    float minLog = log2(2);
    float maxLog = log2(2048);

    // Normalizamos el logaritmo para que esté en el rango [0, 1]
    float normalized = (logVal - minLog) / (maxLog - minLog);
    // Ajustamos el hue para ampliar el rango de colores en un espectro más amplio (0-360)
    float hue = normalized * 360.0f;  // Hue ajustado entre 0 y 360 grados
    // Convertimos de HUE a RGB (tono, saturación, valor)
    float c = 1.0f;   // Saturación reducida para una mayor variedad de tonos
    float x = c * (1.0f - fabs(fmod(hue / 60.0f, 2.0f) - 1.0f)); // Valor intermedio de RGB
    float m = 0.1f;   // Luminosidad mínima más baja para más variedad de brillo
    float rPrime = 0.0f, gPrime = 0.0f, bPrime = 0.0f;
    if (hue < 60) {
        rPrime = c; gPrime = x - 0.2f; bPrime = 0.0f;
    } else if (hue < 120) {
        rPrime = x; gPrime = c; bPrime = 0.0f;
    } else if (hue < 180) {
        rPrime = 0.0f; gPrime = c -0.4f ; bPrime = x;
    } else if (hue < 240) {
        rPrime = 0.0f; gPrime = x; bPrime = c;
    } else if (hue < 300) {
        rPrime = x; gPrime = 0.0f; bPrime = c;
    } else {
        rPrime = c; gPrime = 0.0f; bPrime = x;
    }
    // Convertimos a RGB (0-255) añadiendo el componente de luminosidad m
    r = int((rPrime + m) * 255);
    g = int((gPrime + m) * 255);
    b = int((bPrime + m) * 255);
    // Limitar valores de RGB entre 0 y 255
    r = max(0, min(255, r));
    g = max(0, min(255, g));
    b = max(0, min(255, b));
}



void entornoPonerNumero(int fila, int columna, int numero) {
	invertirFC(fila, columna);
	string num;
	float base, altura, ptoMedioX, ptoMedioY;

	int R, G, B;
	valorAColor(numero, R, G, B);

	int x1 = POS_X + (fila * TAMANO_CUADRADO);
	int y1 = POS_Y + (columna * ALTO_CASILLA);
	int x2 = (x1 + ANCHO_CASILLA)- SEPARACION_FILAS_COL ;
	int y2 = (y1 + ALTO_CASILLA) - SEPARACION_FILAS_COL;

	float sombra = 4;

    al_draw_filled_rounded_rectangle(x1 + sombra, y1 + sombra,
	                                     x2 + sombra, y2  + sombra,
	                                     8, 8, makecolor2(COLOR_GRIS ));
	al_draw_filled_rounded_rectangle(x1, y1, x2, y2,8,8, al_map_rgb( R, G, B));
	al_draw_rounded_rectangle(x1, y1, x2, y2,8,8, makecolor2(COLOR_BLANCO),2);

	base      = (x2 - x1);
	altura    = (y2 - y1);
	ptoMedioX = ((base / 2.0) + x1);
	ptoMedioY = ((y2 + y1) / 2.0) - (altura / 2.0) + SEPARACION_FILAS_COL;
	if (numero > 8200) {
		int numReducido = numero / 1000;
		num = to_string(numReducido).c_str();
		num = num + " k";
	} else {
		num = to_string(numero).c_str();
	}

	al_draw_text(fontNum, makecolor2(COLOR_NEGRO), ptoMedioX, ptoMedioY-4,	ALLEGRO_ALIGN_CENTER, num.c_str());

	al_flip_display();

}

void entornoEliminarNumero(int fila, int columna){
	invertirFC(fila, columna);

	int x1 = POS_X + (fila    * TAMANO_CUADRADO);
	int y1 = POS_Y + (columna * ALTO_CASILLA);
	int x2 = (x1 + ANCHO_CASILLA)- SEPARACION_FILAS_COL ;
	int y2 = (y1 + ALTO_CASILLA) - SEPARACION_FILAS_COL;

	al_draw_filled_rectangle(x1-2, y1-2, x2+4, y2+4, makecolor2(COLOR_GRIS_CLARO));
	al_flip_display();
}


void entornoPonerNumeroPista    ( int fila, int columna, int numero){
	invertirFC(fila, columna);
	string num;
	float base, altura, ptoMedioX, ptoMedioY;

	int x1 = POS_X + (fila    * TAMANO_CUADRADO);
	int y1 = POS_Y + (columna * ALTO_CASILLA);
	int x2 = (x1 + ANCHO_CASILLA)-SEPARACION_FILAS_COL ;
	int y2 = (y1 + ALTO_CASILLA)- SEPARACION_FILAS_COL;

	float sombra = 4;

    al_draw_filled_rounded_rectangle(x1 + sombra, y1 + sombra,
	                                     x2 + sombra, y2  + sombra,
	                                     8, 8, makecolor2(COLOR_GRIS ));
	al_draw_filled_rounded_rectangle(x1, y1, x2, y2,8,8, makecolor2(COLOR_BLANCO));
	al_draw_rounded_rectangle(x1, y1, x2, y2,8,8, makecolor2(COLOR_ROJO),3);

	base      = (x2 - x1);
	altura    = (y2 - y1);
	ptoMedioX = ((base / 2.0) + x1);
	ptoMedioY = ((y2 + y1) / 2.0) - (altura / 2.0) + SEPARACION_FILAS_COL;
	if (numero > 8200) {
		int numReducido = numero / 1000;
		num = to_string(numReducido).c_str();
		num = num + " k";

	} else {
		num = to_string(numero).c_str();
	}

	al_draw_text(fontNum, makecolor2(COLOR_NEGRO), ptoMedioX, ptoMedioY-4,	ALLEGRO_ALIGN_CENTER, num.c_str());
	al_flip_display();

}

void entornoPonerNumeroLanzador (int numero, int columna){

		float base, altura, ptoMedioX, ptoMedioY;

		int x1 = POS_X + ( columna * TAMANO_CUADRADO);
		int y1 = POS_Y + ((NUM_CASILLAS_COL+2) * ALTO_CASILLA);
		int x2 = (x1 + ANCHO_CASILLA)- SEPARACION_FILAS_COL ;
		int y2 = (y1 + ALTO_CASILLA) - SEPARACION_FILAS_COL;

		int R, G, B;
    	valorAColor(numero, R, G, B);
		float sombra = 4;

	    al_draw_filled_rounded_rectangle(x1 + sombra, y1 + sombra,
		                                     x2 + sombra, y2  + sombra,
		                                     8, 8, makecolor2(COLOR_GRIS));
		al_draw_filled_rounded_rectangle(x1, y1, x2, y2,8,8, al_map_rgb ( R, G, B));
		al_draw_rounded_rectangle(x1, y1, x2, y2,8,8, makecolor2(COLOR_BLANCO),2);


		base      = (x2 - x1);
		altura    = (y2 - y1);
		ptoMedioX = ((base / 2.0) + x1);
		ptoMedioY = ((y2 + y1) / 2.0) - (altura / 2.0) + SEPARACION_FILAS_COL;

		al_draw_text(fontNum, makecolor2(COLOR_NEGRO), ptoMedioX, ptoMedioY-5,	ALLEGRO_ALIGN_CENTER, to_string(numero).c_str());
		al_flip_display();

}
void entornoQuitarNumeroLanzador ( int columna){

		int x1 = POS_X + (columna * TAMANO_CUADRADO);
		int y1 = POS_Y + ((NUM_CASILLAS_COL+2) * ALTO_CASILLA);
		int x2 = (x1 + ANCHO_CASILLA)- SEPARACION_FILAS_COL ;
		int y2 = (y1 + ALTO_CASILLA) - SEPARACION_FILAS_COL;

		al_draw_filled_rectangle(x1-4, y1-4, x2+4, y2+4, makecolor2(COLOR_AZUL));
		al_flip_display();
}

void entornoContadorAyuda        (int valor ){
		int x = FIN_X+10;
		int y =  POS_Y + ((NUM_CASILLAS_COL+2) * ALTO_CASILLA);
		al_draw_filled_circle(x, y + 18, 18, makecolor2(COLOR_ROJO));
		al_draw_circle(x, y + 18 , 18, makecolor2(COLOR_GRIS),3);
		al_draw_text(fontNum, makecolor2(COLOR_NEGRO), x , y + 8 ,	ALLEGRO_ALIGN_CENTER, to_string(valor).c_str());
		al_flip_display();
}

void entornoPonerPuntuacion(int valor) {
	string msg;
	msg = "Puntuación:  "+to_string(valor)+"  ";

	//int x = (ORIGEN_X + (FIN_X - ORIGEN_X))/3; // centrado en el rectangulo
	int x = POS_X + FIN_X/ANCHO_CASILLA;
	al_draw_filled_rounded_rectangle(x-20 , COL_MARCADOR, x + 220, COL_MARCADOR+30, RADIO, RADIO, makecolor2(COLOR_AZUL));
	al_draw_rounded_rectangle(x-20, COL_MARCADOR, x + 220, COL_MARCADOR+30, RADIO, RADIO, makecolor2(COLOR_GRIS),2);
	al_draw_text(font, makecolor2(COLOR_NEGRO),x + 10, COL_MARCADOR -1  , ALLEGRO_ALIGN_LEFT, msg.c_str());
	al_flip_display();
}

bool entornoCargarConfiguracion ( int &numFilas, int &numColumnas, int &comoIniciar, int &filasIniciales,int m[MAX_FILAS][MAX_COL]){
	bool leido;
	int i, j;
	ifstream fEntrada;
	string cadena, cad;
	fEntrada.open("./numberTiles.cnf");
	if (fEntrada.is_open()) {
		getline(fEntrada, cadena);
		numFilas = atoi(cadena.c_str());
		getline(fEntrada, cadena);
		numColumnas = atoi(cadena.c_str());
		getline(fEntrada, cadena);
		comoIniciar = atoi(cadena.c_str());
		getline(fEntrada, cadena);
		filasIniciales = atoi(cadena.c_str());
		for (i = 0; i < filasIniciales; i++){
				for (j = 0; j< numColumnas-1; j++){
					getline (fEntrada,cad,' ');
					m[i][j]= atoi(cad.c_str());
				}
				getline (fEntrada,cad);
				m[i][j]= atoi(cad.c_str());
				}
		leido = true;
		fEntrada.close();
	} else {
		cout << "Fichero de configuración no encontrado (<proyecto>/numberTiles.cnf)."<< endl;
		leido = false;
	}
	return leido;
}

void entornoMostrarMensajeFin(string msg) {
	int i, j;
		for (i = 0, j = 0; i < 40 && j < 40; i += 4, j += 4) {
			al_draw_filled_rectangle(i + (ORIGEN_X-10),     j + ORIGEN_Y   + 200,  ORIGEN_X     + 365 - i,  ORIGEN_Y+   320 -j,  makecolor2(COLOR_BLANCO));
			al_draw_filled_rectangle(i + (ORIGEN_X-10) + 2 ,j + ORIGEN_Y +2+ 200,  (ORIGEN_X-2) + 365 - i,  ORIGEN_Y -2 +320-j,  makecolor2(COLOR_GRIS_CLARO));
			usleep(25000); //25 milisegundos
			al_flip_display();
		}
	al_draw_text(font, makecolor2(COLOR_ROJO),ORIGEN_X+80,ORIGEN_Y+250, ALLEGRO_ALIGN_LEFT, msg.c_str());
	al_flip_display();
	usleep(500000); // medio segundo
}


TipoTecla entornoLeerTecla ( ) {
	TipoTecla tecla = TNada;
	ALLEGRO_EVENT evento;

	al_wait_for_event ( colaEventos, &evento );
	if ( evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
		tecla = TSalir;
	else if ( evento.type == ALLEGRO_EVENT_KEY_DOWN ) {
		switch ( evento.keyboard.keycode ) {
		case ALLEGRO_KEY_LEFT:
			tecla = TIzquierda;
			break;
		case ALLEGRO_KEY_RIGHT:
			tecla = TDerecha;
			break;
		case ALLEGRO_KEY_ESCAPE:
			tecla = TSalir;
			break;
		case ALLEGRO_KEY_ENTER:
			tecla = TEnter;
			break;
		case ALLEGRO_KEY_F1:
			tecla = TF1;
			break;
		case ALLEGRO_KEY_F2:
			tecla = TF2;
			break;
		default:
			tecla = TNada;
			break;
		}
	};
	return tecla;
}


void entornoPausa(float pausa) {
	al_rest(pausa);
}


void entornoTerminar(){
	al_destroy_display          (display);
	al_destroy_event_queue      (colaEventos);
	al_destroy_font				(font);
	al_destroy_font				(fontNum);
	al_shutdown_primitives_addon();
	al_shutdown_font_addon      ();
}



