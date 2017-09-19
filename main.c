#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int countLines(const char *file_name);
int getStartLine(int i,int n_processes, int file_lines );
int getLinesToRead(int i,int n_processes, int file_lines );

int main (int argc, char **argv){

  char *file_name, *searched_string = NULL;
  int n_processes, length_line_file, flag_show_results = 0;

  int index;
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "i:n:c:p:d")) != -1)
    switch (c)
      {
      case 'i':
        file_name = optarg;
        break;
      case 'n':
        n_processes = atoi(optarg);
        break;
      case 'c':
        length_line_file = atoi(optarg);
        break;
      case 'p':
        searched_string = optarg;
        break;
      case 'd':
        flag_show_results = 1;
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Opcion con caracter desconocido `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }


  for (index = optind; index < argc; index++) printf ("No existe opcion para agumento: %s\n", argv[index]);

  int status_p_compiler;
  pid_t p_compiler;
  p_compiler =fork();

  if(p_compiler==0){
    execlp("gcc", "gcc","-o", "comparator", "comparador.c",(const char *)NULL);   //Proceso que compila el programa comparador antes de crear los procesos que lo usaran
    exit(0);
  }

  int file_lines = countLines(file_name);  //mientras el proceso hijo compila el comparador contamos las lineas del archivo de entrada

  waitpid(p_compiler, &status_p_compiler, 0); //El proceso padre espera al proceso que compila el programa comparador

  pid_t wpid;
  int status;

  int i=0;

  for(i = 0; i<n_processes; i++){
    if(fork() == 0){

      //printf("Proceso %d , linea de partida = %d, lineas a escanear = %d\n", i, getStartLine(i,n_processes,file_lines),getLinesToRead(i,n_processes,file_lines));

      int start_line = getStartLine(i,n_processes,file_lines);
      int lines_number = getLinesToRead(i,n_processes,file_lines);

      char str_i[15];   // Se parsean los datos que entraran como argumento al programa comparador
      sprintf(str_i, "%d", i);

      char str_start_line[15];
      sprintf(str_start_line, "%d", start_line);

      char str_lines_number[15];
      sprintf(str_lines_number, "%d", lines_number);

      char str_length_line_file[15];
      sprintf(str_length_line_file, "%d", length_line_file);

      execlp("./comparator", "comparator", file_name, str_start_line, str_lines_number,str_i, searched_string,str_length_line_file, (const char *)NULL);

      exit(0);
    }
  }

  while ((wpid = wait(&status)) > 0);

  // Resto del codigo

  return 0;
}

int getStartLine(int i,int n_processes, int file_lines ){
  int line = 0;

  if(i==0) line = 1;
  else{
    if(i<n_processes){
      line = (file_lines/n_processes)*i +1;
    }
    else{
      line = -1;
    }
  }

  return line;

}

int getLinesToRead(int i,int n_processes, int file_lines ){
  int line = 0;

  if(i<n_processes-1){
    line = (file_lines/n_processes);
  }
  else{
    line = file_lines - (file_lines/n_processes)*i-1;
  }


  return line;

}

int countLines(const char *file_name){
     int ch = 0;
     int count = 0;
     FILE *fileHandle;

     if ((fileHandle = fopen(file_name, "r")) == NULL) {
        return -1;
     }

     do {
        ch = fgetc(fileHandle);
        if ( ch == '\n')
           count++;
     } while (ch != EOF);
     count++;
     fclose(fileHandle);

     return count;
}
