#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void escritor(FILE *salidaP, int afirmacion){
    if(afirmacion){
      fprintf(salidaP,"SI\n");

    }
    else{
       fprintf(salidaP,"NO\n");
    }
}

void buscador(char * chain, char* nombreFp,FILE *salidasP, int pos, int lines, int cant){
  FILE *fp = fopen(nombreFp,"r");
  fseek(fp,pos,SEEK_CUR); //Ver si cambia, se posiciona en la linea correcta
  int lineas = lines;// Aux
  char *ce = chain;// Aux
  char * linea;
  char a;
  while(lineas !=0){ // Mientras existan lineas
      linea = (char*)malloc(sizeof(char)*cant); //Reservar memoria para una linea
      fgets(linea,cant,fp); // Almacenar la linea
      if(strstr(linea,ce) != NULL){ // Si se encuentra la cadena en esta linea (funcion strsrt(char * aBuscar, char * loBuscado))
        escritor(salidasP,1); //Se escribe el archivo SI
      }
      else{
        escritor(salidasP,0); // NO
      }

      lineas--; // Descuenta lineas
      free(linea); // Free memoria de aux

    }
    fclose(fp);
    fseek(fp,pos+cant*lines,SEEK_CUR); // La posicion + todo lo que se recorrio de lineas
  }

int main(){
 char * cadena = "AAAA";
 char * entrada = "ejemplo1.txt";
  int pos = 0;
  int lineas = 3;
  int id = 0;

  FILE * salidaFp = fopen("salida.txt","w");
  buscador("AAAA",entrada,salidaFp,0,10,60); // posicion 0, lineas 10, 60 caracteres
  return 0;
  fclose(salidaFp);
}
