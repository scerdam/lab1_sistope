#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void escritor(char *nucleotidos,FILE *salidaP, int afirmacion, int largo){
    char *adn = (char*)malloc(sizeof(char)*(largo+1)); // Proceso para
    strncpy(adn,nucleotidos,strlen(nucleotidos)-1); //  quitar salto de linea debido a estetica de resultado
    if(afirmacion){
      fprintf(salidaP,"%s SI\n",adn); // Se encontro cadena

    }
    else{
       fprintf(salidaP,"%s NO\n",adn); // No se encontro cadena
    }
}

void buscador(int numProceso,char * chain, char* nombreFp, int posLinea, int lines, int cant){
  /* Proceso de nombrar archivo*/
  char buf[5];
  char *name = "rp";
  char *txt = ".txt";
  char * guion = "_";
  char nameOut [100];
  strcpy(nameOut,name);
  sprintf(buf,"%d",numProceso);
  strcat(nameOut,guion); strcat(nameOut,chain);strcat(nameOut,guion);strcat(nameOut,buf);strcat(nameOut,txt);
  /* Fin de nombrar archivo*/
  FILE *fp = fopen(nombreFp,"r");
   int queLinea  = posLinea*cant-cant+(posLinea-1); // Posiciona al inicio de la linea impuesta, expresion (posLinea-1) debido a los saltos de linea


  fseek(fp,queLinea,SEEK_CUR); //Ver si cambia, se posiciona en la linea correcta
  int lineas = lines;// Auxiliar
  char *ce = chain;// Auxiliar
  char * linea;// Auxiliar


  FILE * salidaFp = fopen(nameOut,"w");
  while(lineas !=0){ // Mientras existan lineas
      linea = (char*)malloc(sizeof(char)*(cant+2)); //Reservar memoria para una linea con salto de linea y null-pointer al final
      fgets(linea,cant+2,fp); // Almacenar la linea
      if(strstr(linea,ce) != NULL){ // Si se encuentra la cadena en esta linea (funcion strsrt(char * aBuscar, char * loBuscado))
        escritor(linea,salidaFp,1,cant); //Se escribe el archivo SI
      }
      else{
       escritor(linea,salidaFp,0,cant); // NO
      }

      lineas--; // Descuenta lineas
      free(linea); // Free memoria de aux

    }
    fclose(salidaFp); //Cerrar salida
    fclose(fp); // Cerrar archivo de lectura

  }


int main(int argc, char **argv){

    char *file_name = argv[1]; //entrada
    int start_line = atoi(argv[2]); //pos
    int lines_number = atoi(argv[3]); // lineas a leer
    int i = atoi(argv[4]); // id
    char *searched_string = argv[5]; //cadena
    int length_line_file = atoi(argv[6]); // tamaño(largo)

   // Ejmplo llamada con argv   --->  ./comparador ejemplo.txt 1 5 0001 AAAA


  buscador(i,searched_string,file_name,start_line,lines_number,length_line_file); // posicion 0, lineas 10, 60 caracteres
  return 0;
}
