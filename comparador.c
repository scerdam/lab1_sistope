#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void escritor(FILE *salidaP, int afirmacion){
    if(afirmacion){
      fprintf(salidaP,"SI\n");

    }
    else{
       fprintf(salidaP,"NO\n");
    }
}

void buscador(char* i, char * chain, char* nombreFp, int posLinea, int lines, int cant, int numProceso){
  char buf[5];
  char *name = concat(i, "_rp.txt");
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

int main(int argc, char **argv){

  char *file_name = argv[1]; //entrada
  int start_line = atoi(argv[2]); //pos
  int lines_number = atoi(argv[3]); // lineas
  char *i = argv[4]; // id
  char *searched_string = argv[5]; //cadena

 // Ejmplo llamada con argv   --->  ./comparador ejemplo.txt 1 5 0001 AAAA

 char * cadena = "AAAA";
 char * entrada = "ejemplo1.txt";
  int pos = 0;
  int lineas = 3;
  int id = 0;


  buscador(i,"AAAA",entrada,1,10,62,1); // posicion 0, lineas 10, 60 caracteres
  return 0;
}
