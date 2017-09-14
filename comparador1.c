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

void buscador(char * chain, char* nombreFp, int posLinea, int lines, int cant, int numProceso){
  char buf[5];
  char *name = "rp.txt";
  FILE *fp = fopen(nombreFp,"r");
  int queLinea = posLinea*cant-cant;
  fseek(fp,queLinea,SEEK_CUR); //Ver si cambia, se posiciona en la linea correcta
  int lineas = lines;// Aux
  char *ce = chain;// Aux
  char * linea;
  sprintf(buf,"%d",numProceso); // para nombrar archivo

  FILE * salidaFp = fopen(name,"w");
 while(lineas !=0){ // Mientras existan lineas
      linea = (char*)malloc(sizeof(char)*cant); //Reservar memoria para una linea
      fgets(linea,cant,fp); // Almacenar la linea
      if(strstr(linea,ce) != NULL){ // Si se encuentra la cadena en esta linea (funcion strsrt(char * aBuscar, char * loBuscado))
        escritor(salidaFp,1); //Se escribe el archivo SI
      }
      else{
       escritor(salidaFp,0); // NO
      }

      lineas--; // Descuenta lineas
      free(linea); // Free memoria de aux

    }
    fclose(salidaFp);
    fclose(fp);

  }

int main(){
 char * cadena = "AAAA";
 char * entrada = "ejemplo1.txt";
  int pos = 0;
  int lineas = 3;
  int id = 0;


  buscador("AAAA",entrada,1,10,62,1); // posicion 0, lineas 10, 60 caracteres
  return 0;
}
