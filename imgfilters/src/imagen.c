#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pgm.h"
#include "imagen.h"

int inicializar_imagen(int ancho, int alto, TipoImagen tipo, Imagen* pnew){
	
	if(pnew==NULL){
	return 1;
	} else{ 
		pnew->tipo=tipo;
		pnew->ancho=ancho;
		pnew->alto=alto;
		pnew->valor_maximo=255;
		pnew->pixels=(int*)malloc(sizeof(int)*ancho*alto);/*Reserva un lugar en memoria dinamica para la cantidad de pixels necesarios*/
			if(!(pnew->pixels)){
			  return 1;
			} else{ 
			  return 0;
			  }	
	}
}

void destruir_imagen(Imagen* pimg){
	pimg->tipo=0;
	pimg->ancho=0;
	pimg->alto=0;
	free(pimg->pixels);
	free(pimg);
	pimg->pixels=NULL;
	pimg=NULL;

}

void duplicar_imagen(const Imagen* pin, Imagen* pout){
	int x;
	if((x=inicializar_imagen(pin->ancho, pin->alto, pin->tipo, pout))!=0){
	printf("Error al duplicar imagen!");
	} else{ 
		x=0;
			while(x<=(pin->ancho*pin->alto)){
			(*pout).pixels[x]=(*pin).pixels[x];
			x++;		
		}
	}
		
	
}


CodigoError leer_imagen(const char* ruta, Imagen* pimg){
	CodigoError resultado=0;
	char magico[2];
	int c1, c2, c3;
	FILE *fp=NULL;
	fp=fopen(ruta, "r");
	if(fp==NULL)return 1;/*no existe*/
	fscanf(fp, "%s", &magico[0]); /*Primer string es un P2 o P6 */
	/*Defino el tipo de imagen con el codigo magico*/
	if(strcmp(magico,"P6")==0){
		pimg->tipo=1; /*Color*/
	} else if(strcmp(magico,"P2")==0){
		pimg->tipo=0; /*Gris*/
	} else{ 
		return 2;/*Error al leer el codigo magico*/
	}
	fscanf(fp, "%d", &c1);/*Ancho*/
	fscanf(fp, "%d", &c2);/*Alto*/
	fscanf(fp, "%d\n", &c3);/*valor_maximo*/
	/*Pasar las strings leidas a ints y guardarlas en pimg*/	
	pimg->ancho=c1;
	pimg->alto=c2;
	pimg->valor_maximo=c3;
	pimg->pixels=(int*)malloc(sizeof(int)*pimg->ancho*pimg->alto);/*Reservo memoria para los pixels*/
	if(pimg->tipo==1){
		c1=0;rgb[3]=0;
		while( (c1<=(pimg->alto*pimg->ancho)) && (rgb[2] != EOF ) ){
			rgb[2]=fgetc(fp);
			rgb[1]=fgetc(fp);
			rgb[0]=fgetc(fp);
			pimg->pixels[c1]=RGB2enteros(rgb[0],rgb[1],rgb[2],rgb[3]);
			c1++;	
		}
	} else{
		c1=0;
		while( (c1<=(pimg->alto*pimg->ancho))  ){
			fscanf(fp, "%d ", &(*pimg).pixels[c1]);
			c1++;
		}
	}
	fclose(fp);
	return resultado;
}

CodigoError escribir_imagen(const Imagen* pimg, const char* ruta){
	CodigoError resultado=0;
	int i=0;
	FILE *fp;
	fp=fopen(ruta, "w");
	if(fp != NULL){
		if(pimg->tipo==0){
			fprintf(fp, "%s\n", "P2");
		} else{
			fprintf(fp, "%s\n", "P6");
		} /*PMG codigo magico*/
		fprintf(fp, "%u %u\n", pimg->ancho, pimg->alto);
		fprintf(fp, "%u\n", pimg->valor_maximo);
		if(pimg->tipo==1){
			i=0;
			while( (i<=(pimg->alto*pimg->ancho)) && ( rgb[3] != EOF )&& ( rgb[2] != EOF )&& ( rgb[1] != EOF )&& ( rgb[0] != EOF ) ){
				enteros2RGB((*pimg).pixels[i]);				
				fputc(rgb[2],fp);
				fputc(rgb[1],fp);
				fputc(rgb[0],fp);
				i++;	
			}
		} else{
			i=0;
			while( (i<=(pimg->alto*pimg->ancho)) && 
				( rgb[3] != EOF )&& 
				( rgb[2] != EOF )&& 
				( rgb[1] != EOF )&& 
				( rgb[0] != EOF )
				)
			{
				fprintf(fp, "%d ", (*pimg).pixels[i] );
				i++;
				//fwrite(pimg->pixels, 4, pimg->ancho*pimg->alto, fp);
			}	
		}
			
		
		
	}  else {
		resultado=5;
	}
	fclose(fp);
	return resultado;
}



void enteros2RGB(int n){
	int e,r,g,b;
	
	b=n;
	g=n>>8;
	r=n>>16;
	e=n>>24;
	rgb[0]=(unsigned int)r;
	rgb[1]=(unsigned int)g;
	rgb[2]=(unsigned int)b;
	rgb[3]=(unsigned int)e;
	
}

int RGB2enteros(unsigned char r, unsigned char g, unsigned char b, unsigned char e){
	unsigned int red=r;
	unsigned int green=g;
	unsigned int blue=b;
	int extra=e;
	int n;
	
	blue=blue&0xff;
	green=green<<8;
	red=red<<16;
	extra=extra<<24;
	n=extra|red|green|blue;
		
	return n;
}

void imagen2BW(int *entrada, int m, int n, int *salida){
	int i=0; 
	int e; 

	rgb[3]=0;
	rgb[2]=0;
	rgb[1]=0;
	rgb[0]=0;
	while( i< ( m*n ) ){
		enteros2RGB(entrada[i]);
		salida[i]=(round)(0.2*rgb[0] + 0.7*rgb[1] + 0.1*rgb[2]);
		salida[i]=salida[i]&0x00ffffff;	
		e=rgb[3]<<24;e=e&0xff000000;
		salida[i]=salida[i]|e;
		i++;
	}
}
void imagen2RBG(Imagen* pi){}

void copia(int *entrada, int m, int n, int *salida){
	int i=0;
	while(i<=m*n){
		salida[i]=entrada[i];
		i++;	
	} /* End FOR*/

} /*End copia*/


void reflejo(int *entrada, int m, int n, int p, int *salida){
	int i=0;
	int j=0;
	int flag=1;
	while((i <= (n*m)/2) && (j>=0) && (p==1)){/*Reflejo v*/	
		if(flag){
			j=m*(n-1)-i;
			flag=0;
		}	
		salida[j]= entrada[i];
		salida[i]= entrada[j];	
		i++;
		j++;
		if(i%m==0){
			flag=1;	
		}
	} /* End while 1*/


    while((i<=(n*m-1)) && (j<=(n*m-1)) && (p==0)){/*Reflejo h*/
		if(flag){
			j=i+m-1;
			flag=0;
		}	
		salida[j]= entrada[i];	
		i++;
		j--;
		if(i%m==0){
			flag=1;	
		}
	} /* End while 0*/
 
	while((i<=(n*m-1)) && (j>=0) && (p==2)){/*Reflejo central*/
		if(flag){
			j=(n*m-1);
			flag=0;	
		}	
		salida[i]= entrada[j];	
		i++;
		j--;
	} /* End while 2*/

 if((p > 2) || (p < 0)){
	 printf("Error! El p ingresado no es correcto\n");
 } /* End IF mensaje de error*/

} /* End reflejo*/


void negativo(int *entrada, int m, int n, int t, int *salida){
	int i;
	int aux[4];
	rgb[3]=0;rgb[2]=0;rgb[1]=0;rgb[0]=0;

	for(i=0;(i <= (m*n));i++){
		enteros2RGB(entrada[i]);
		aux[0]=(unsigned int)((unsigned int)t-(unsigned int)rgb[0]);
		aux[1]=(unsigned int)((unsigned int)t-(unsigned int)rgb[1]);
		aux[2]=(unsigned int)((unsigned int)t-(unsigned int)rgb[2]);
		aux[3]=(unsigned int)((unsigned int)t-(unsigned int)rgb[3]);
		salida[i]= (RGB2enteros(aux[0],aux[1],aux[2],aux[3]));
	} /* End FOR*/
} /* End negativo*/


void bordes(int *entrada, int m, int n, int t, int g, int *salida){
	int i=0;
	int Vx[m*n];
	int Vy[m*n];
	//Vx=(int*)malloc(sizeof(int)*m*n);
	//Vy=(int*)malloc(sizeof(int)*m*n);
	int pos;
	
 /*Primero calculo las derivadas parciales Vx Vy:*/
 /*Vy*/ 
	for(pos=0;pos<=(m*n-1);pos++){
			if( (pos>(m-1)) && (pos<((n*m)-m)) ){			
			  Vy[pos]=entrada[pos+m]-entrada[pos-m]; /* Si no esta en un borde de y */
			} else{  /*Esta en un borde de y*/
			  	if(pos<(m)){
					/*Borde arriba(entrada[pos-m]=noexiste)*/
					Vy[pos]=entrada[pos+m]-entrada[pos]; /*Equivale a clipear la posicion-m (que no existe) con la posicion borde */
		
				} else {
					/*Borde abajo(entrada[pos+m]=noexiste)*/
					Vy[pos]=entrada[pos]-entrada[pos-m]; /*Equivale a clipear la posicion+m que no existe con la posicion borde */
				}/* end else */
	        }/* end else */

	} /* end for*/
 /*Vx*/	for(pos=0;pos<=(m*n-1);pos++){
			if( (pos%(m)!=0) && (pos%(m)!=(m-1)) ){			
			  Vx[pos]=entrada[pos+1]-entrada[pos-1]; /* Si no esta en un borde de x */
			
			} else{  /*Esta en un borde de x*/
			  	if(pos%m == 0){
					/*Borde a la izq(entrada[pos-1]=noexiste)*/
					Vx[pos]=entrada[pos+1]-entrada[pos]; /*Equivale a clipear la posicion-1 que no existe con la posicion borde */

				} 
				if(pos%m==(m-1)) {
					/*Borde a la derecha(entrada[pos+1]=noexiste)*/
					Vx[pos]=entrada[pos]-entrada[pos-1]; /*Equivale a clipear la posicion+1 que no existe con la posicion borde */
				}/* end else */
			}/* end else */

	} /* end for*/
			
	/*Luego cargamos salida[i] dependiendo del p*/
	
	if(g==0){ /*Derivada direccional x truncada*/
			for(i=0;i<=(m*n-1);i++){
				salida[i]=abs(Vx[i]);
				if(salida[i]>t){
					salida[i]=t;
				}			
			}
	}
	if(g==1){ /*Derivada direccional y truncada*/
			for(i=0;i<=(m*n-1);i++){
				salida[i]=abs(Vy[i]);
				if(salida[i]>t){
					salida[i]=t;
				}			
			}
	}
	
	if(g==2){/*Modulo truncado*/
			for(i=0;i<=(m*n-1);i++){		
				salida[i]=round(sqrt((Vx[i]*Vx[i])+(Vy[i]*Vy[i])));					
				if(salida[i]>t){
					salida[i]=t;
				}
			}
	}

	//free(Vx);
	//free(Vy);
	
	if(g>2||g<0){
		printf("Error! El p ingresado no es correcto");
	}

}  /* END BORDES */ 



void caricatura(Imagen* pin, int u, Imagen* pout){
	int x=0,i=0,j=0; int pos=0,c1=0,c2=0; int regiones=0;
	int m=pin->ancho, n=pin->alto, ultimo= m*n-1;
	int manterior=0; /* Esta variable se usa para determinar el borde horizontal mas cercano hacia la izq*/
	int msiguiente=ANCHO-1; /* Esta variable se usa para determinar el borde horizontal mas cercano hacia la derecha*/
	int jarriba=0; int jabajo=ultimo; /* Y estas determinan bordes verticales*/
	Imagen* pg;
	Imagen* pbw;
	Imagen* pe;
	pg=malloc(sizeof(Imagen));
	pbw=malloc(sizeof(Imagen));
	pe=malloc(sizeof(Imagen));
	if(u>0){
	    if( (x=(inicializar_imagen(m, n, 0, pbw)))==0 ){
	      	if( (x=(inicializar_imagen(m, n, 0, pg)))==0 ){
				if( (x=(inicializar_imagen(m, n, 0, pe)))==0 ){
					//CON IMAGENES INICIALIZADAS, BW>BORDES>ETIQUETADO>CARICATURA:
					imagen2BW(pin->pixels, m, n, pbw->pixels); /*Blanco y negro*/
					bordes((*pbw).pixels, m, n, pin->valor_maximo, 2, (*pg).pixels);/*Obtenemos G(i,j)*/
					
						//Etiquetado:
					for(i=0;(i <= ultimo);i++){
						(*pe).pixels[i]=0;
					    (*pout).pixels[i]=0;
					    i++;
				    } /*Inicializo pixels de pe en 0*/
					
					manterior=0; 
					msiguiente=m-1;
					int borde1, borde2, borde3;
					
					for(pos=0;(pos <= ultimo);pos++){//LOOP ETIQUETADO
							/* Para la pos actual, calculamos manterior */
						i=pos;		
						while(i%m != 0){
							i--;		
						}
						if(pos==0){manterior=0;}else{manterior=i;}
						i=pos;		
						while((i%m) != (m-1)){
							i++;		
						}
						if(pos==0){msiguiente=m-1;}else{msiguiente=i;}
						i=pos-m;		
						while(i<0){
							i+=(m);
							c1++;		
						}
						jarriba=i;
						i=pos+m;
						while(i>ultimo){
						i-=(m);
						c2++;		
						}
						jabajo=i;
						i=pos;
						borde1=0; borde2=0; borde3=0;
						/*Las variables bordes si son 1 es q en su pos hay un borde, -1 no existen*/
						  borde1=((*pg).pixels[i]>u); /*borde1 | i*/
						  if((i-1)>=manterior){
								borde2=((*pg).pixels[i-1]>u); /*borde2 | i-1*/
								} else{borde2=-1;}
						  if((i-m)>0){	borde3=((*pg).pixels[i-m]>u); /*borde3 | i-m*/
							     } else{borde3=-1;}



							if( (i!=0) && ( borde1==0 ) ){/*"i" no es borde*/
						
							 
								if(borde2==0){
								


								  if( borde3==0 ){/*No hay bordes ni arriba ni en "i" ni en "i-1"*/
											if((*pe).pixels[i-m]==(*pe).pixels[i-1]){
											(*pe).pixels[i]=(*pe).pixels[i-1]; 
											} else{
												(*pe).pixels[i]=(*pe).pixels[i-m];
												 
											//PEGAR DOS ETIQUETAS DIFERENTES:
												j=0;
												while( j<=ultimo ){
												if( (*pe).pixels[i-1] == (*pe).pixels[j] ){(*pe).pixels[j]=(*pe).pixels[i-m];}
												j++;
												}

					
											}
									

								  } else {/*Borde arriba pero no en "i" ni en "i-1"*/
										 (*pe).pixels[i]=(*pe).pixels[i-1];
										 
									}




								} else{ /*i-1 es borde*/
									
									if( borde3==0 ){/*No hay bordes ni arriba ni en "i"*/
												(*pe).pixels[i]=(*pe).pixels[i-m]; 		

								 	} else if( (borde3!=0) && (borde2!=0) ){/*Borde arriba y en "i-1"*/
										 (*pe).pixels[i]=regiones+1;
									 	 regiones++;

									 }
									}
							} else if((i==0)&&(borde1==0)){//Caso pos=0
									 (*pe).pixels[i]=regiones+1;
									 regiones++;	
							} 

						if( borde1==1 )(*pe).pixels[i]=0;
						if( borde2==1 )(*pe).pixels[i-1]=0;
						if( borde3==1 )(*pe).pixels[i-m]=0;

					} //for LOOP ETIQUETADO

					int x=0, c=0; int color[regiones+1]; int rojo[regiones+1];int azul[regiones+1];int verde[regiones+1];int total[regiones+1];int extra[regiones+1];
					//Ya etiquetada la imagen en pe, pasamos a pintar regiones con el color promedio de la misma:
					if(regiones!=0){
						
						if(pin->tipo==1){	//CARICATURA COLOR
							
							
							for(x=1;x<=regiones;x++){
								i=0; c=0; rojo[x]=0;verde[x]=0;azul[x]=0;
								while( (i<=ultimo) ){
									if( (*pe).pixels[i]==x ){
										c++;
										extra[x]+=(((*pin).pixels[i]&0xff000000)>>24);
										rojo[x]+=(((*pin).pixels[i]&0xff0000)>>16);
										verde[x]+=(((*pin).pixels[i]&0xff00)>>8);
										azul[x]+=(*pin).pixels[i]&0xff;
										
									}	
									i++;
								
								}
									if(c!=0)extra[x]=extra[x]/c;  extra[x]=extra[x]<<24;
									if(c!=0)rojo[x]=rojo[x]/c;  rojo[x]=rojo[x]<<16;
									if(c!=0)verde[x]=verde[x]/c;  verde[x]=verde[x]<<8;
									if(c!=0)azul[x]=azul[x]/c;  
									if(c!=0){color[x]=  ( extra[x] | rojo[x] | verde[x] | azul[x] ); } else{color[x]=-1;}
										
									
							}
						
							for(x=1;x<=regiones;x++){
								i=0; 
								while( (i<=ultimo) ){
									if( (*pe).pixels[i]==x ){
										if(color[x]!=-1)
											(*pout).pixels[i] =( color[x] );
									}	
									i++;
								
								}
							
							}

						} else{
								
							for(x=1;x<=regiones;x++){
								i=0; c=0; 
								while( (i<=ultimo) ){
									if( (*pe).pixels[i]==x ){
										c++;
										extra[x]+=((*pin).pixels[i]);
									}	
									i++;
									
								}
							 
								if(c!=0){
									color[x]=  ( extra[x]/c ); 
								} else{
									color[x]=-1;
								}
								
							
							}
						
							for(x=1;x<=regiones;x++){
								i=0; 
								while( (i<=ultimo) ){
									if( (*pe).pixels[i]==x ){
										if(color[x]!=-1)
											(*pout).pixels[i] =( color[x] );
									}	
									i++;
								}
							}
							
						}
					}
					destruir_imagen(pe);
					destruir_imagen(pbw);
					destruir_imagen(pg);
					return;
				} 
			}
		}

		//Error al inicializar imagen
		printf("Error al inicializar imagenes para el filtro caricatura");
		return;
	}
		//u<0
	printf("Error parametro umbral <= 0");
	return;
}

