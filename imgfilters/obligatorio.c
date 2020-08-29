#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pgm.h"
#include "imagen.h"

int main(int argc, char* argv[]){
 if(argc != 5){
  printf("Error! Cantidad de argumentos debe ser 5.\n");
  return -1;
 } else{ 
    Imagen *pixeles_in;
    Imagen *pixeles_out;
    int parametro = atoi(argv[2]); 
    int cinvalido=1;
    int x;
    CodigoError c=0;
    pixeles_in=malloc(sizeof(Imagen));
    pixeles_out=malloc(sizeof(Imagen));
	/*LEER ENTRADA:*/
	if( (c=(leer_imagen(argv[3], pixeles_in)))==0 ){
		/*Inicializar salida y aplicar filtros:*/
	    if( (x=(inicializar_imagen(pixeles_in->ancho, pixeles_in->alto, pixeles_in->tipo, pixeles_out)))==0 ){
			if(0==strcmp(argv[1],"copia")){
					copia(pixeles_in->pixels, pixeles_in->ancho, pixeles_in->alto, pixeles_out->pixels);
					cinvalido=0;
			}
			if(0==strcmp(argv[1],"negativo")){
					negativo(pixeles_in->pixels, pixeles_in->ancho, pixeles_in->alto, pixeles_in->valor_maximo, pixeles_out->pixels);
					cinvalido=0;
			}
			if(0==strcmp(argv[1],"reflejo")){
					reflejo(pixeles_in->pixels, pixeles_in->ancho, pixeles_in->alto, parametro, pixeles_out->pixels);
					cinvalido=0;
			}
		
			if(0==strcmp(argv[1],"bordes")){
					if(pixeles_in->tipo==0){
						bordes(pixeles_in->pixels, pixeles_in->ancho, pixeles_in->alto, pixeles_in->valor_maximo, parametro, pixeles_out->pixels);
						cinvalido=0;
					} else {
						imagen2BW(pixeles_in->pixels, pixeles_in->ancho, pixeles_in->alto, pixeles_in->pixels);
						bordes(pixeles_in->pixels, pixeles_in->ancho, pixeles_in->alto, pixeles_in->valor_maximo, parametro, pixeles_out->pixels);
						cinvalido=0;
					}
			}
			if(0==strcmp(argv[1],"caricatura")){
					caricatura(pixeles_in, parametro, pixeles_out);
					cinvalido=0;
			}
			if(cinvalido){
					printf("El comando que se quiso invocar es invalido.\n");
					destruir_imagen(pixeles_in);
					destruir_imagen(pixeles_out);			
			return -1;
			}	 /*end ifs*/		


			
	  	/*ESCRIBIR EN SALIDA:*/
			if( (c=(escribir_imagen(pixeles_out, argv[4])))==0 ){		
				printf("Exito! El filtro %s fue realizado sin problemas.\nLa imagen de salida fue generada en la ruta: %s\n", argv[1], argv[4]);
				destruir_imagen(pixeles_in);
				destruir_imagen(pixeles_out);
				return 0; /*exito*/
			} else {
				printf("Error al escribir imagen"); 
				destruir_imagen(pixeles_in);
				destruir_imagen(pixeles_out);
				return -1;
			}		
	    } else {
			printf("Error al inicializar imagen"); 
			destruir_imagen(pixeles_in);
			destruir_imagen(pixeles_out);
	 		return -1;
 		}
	} else {
		printf("Error al leer imagen");
		destruir_imagen(pixeles_in);
		destruir_imagen(pixeles_out);
		return -1;}
	
 	}/*end else*/










}/*end main*/
