#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pgm.h"
#ifndef IMAGEN_H
#define IMAGEN_H


/*Tipos nuevos*/

typedef unsigned int Pixel;

typedef enum codigo_error{
PNM_OK=0,
PNM_ARCHIVO_INEXISTENTE=1,
PNM_ERROR_LECTURA=2,
PNM_ENCABEZADO_INVALIDO=3,
PNM_DATOS_INVALIDOS=4,
PNM_ERROR_ESCRITURA=5
} CodigoError;

typedef enum canal{
ROJO=0, VERDE=1, AZUL=2
} Canal;

typedef enum tipo_imagen{
GRISES=0, COLOR=1
} TipoImagen;

typedef struct imagen{
	TipoImagen tipo;
	int ancho;
	int alto;
	int valor_maximo;
	int * pixels;
} Imagen;


/*Filtros anteriores*/

void negativo(int *entrada, int m, int n, int t, int *salida);
void reflejo(int *entrada, int m, int n, int p, int *salida);
void copia(int *entrada, int m, int n, int *salida);
void bordes(int *entrada, int m, int n, int t, int g, int *salida);


/*Nuevas declaraciones*/
unsigned char rgb[4]; /*Variable externa para las funciones rgb2enteros*/
void enteros2RGB(int n);
int RGB2enteros(unsigned char r, unsigned char g, unsigned char b, unsigned char e);
void imagen2BW(int *entrada, int m, int n, int *salida);
void imagen2RBG(Imagen* pi);

int inicializar_imagen(int ancho, int alto, TipoImagen tipo, Imagen* pnew);
void destruir_imagen(Imagen* pimg);
void duplicar_imagen(const Imagen* pin, Imagen* pout);

CodigoError leer_imagen(const char* ruta, Imagen* pimg);
CodigoError escribir_imagen(const Imagen* pimg, const char* ruta);

#endif

