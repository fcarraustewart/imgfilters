/**
 * Funciones para leer y escribir imágenes PGM desde y hacia almacenamiento externo.
 * Por ahora, las funciones de lectura deben ser usadas de a una imagen  a la vez; no se puede llamar a abrir_archivo_pgm con un nuevo nombre de archivo sin haber llamado a cerrar_archivo_pgm con el anterior.
 */
#ifndef PGM_H
#define PGM_H

/** codigo de retorno si todo sale bien */
#define PGM_OK 0

/** código de retorno si hubo algún problema */
#define PGM_ERROR 1

/** ancho de las imagenes usadas en la primera entrega del obligatorio */
#define ANCHO 512

/** altura de las imagenes usadas en la primera entrega del obligatorio */
#define ALTO  340

#define MAXVAL 255
/**
 * Abre el archivo PGM ubicado en la ruta ruta_archivo especificada. Devuelve 0 si todo salió bien o un número distinto de 0 si hubo algún error.
 *
 * @param  ruta_archivo Ruta a donde se encuentra la imagen en el sistema de archivos
 * @param pixeles Arreglo en donde se guardan los pixels leidos.
 * @return un valor distinto de 0 si hubo algún problema al abrir la imagen.
 */
int leer_archivo_pgm(char ruta_archivo[], int pixeles[]);


/**
 * Toma los pixels, el ancho, el alto y el valor máximo de pixel de una imagen y 
 * genera un archivo de imagen PGM en la ruta ruta_archivo especificada. Devuelve 
 * un valor distinto de 0 si hubo un error.
 * @param pixels de la imagen a guardar
 * @param ancho anchura de la imagen a guardar
 * @param alto altura de la imagen a guardar
 * @param mxaval maximo valor de pixel de la imagen a guardar
 * @param ruta_archivo lugar en disco donde se guardará la imagen
 * @return 0 si todo salió bien, código de error en otro caso
 */
int escribir_archivo_pgm(int pixels[], int ancho, int alto, int maxval, char ruta_archivo[]);

#endif
