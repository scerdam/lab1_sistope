#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// LLamar al programa comparador dentro del fork una vez creado el proceso
// fork();
//     execv("./", "comparator_program", size_line_file, searched_string);

int k = 5; // global variable
int line_start = 0;
int line_finish = 0;

int countLines(const char *file_name);
int getStartLine(int i,int n_processes, int file_lines );
int getLinesToRead(int i,int n_processes, int file_lines );

int main (int argc, char **argv) {

  char *file_name, *searched_string = NULL;
  int n_processes, size_line_file, flag_show_results = 0;


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
        size_line_file = atoi(optarg);
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
//
//  printf ("file = %s, searched_string = %s, n_processes = %d,  size_line_file = %d, flag_show_results = %d\n",
//          file, searched_string, n_processes, size_line_file, flag_show_results );
//

  for (index = optind; index < argc; index++)
    printf ("No existe opcion para agumento: %s\n", argv[index]);


    int file_lines = countLines(file_name);

    printf("KUALKER WEA EU PIROCA Lineas_archivo = %d \n", file_lines );

    pid_t wpid;
    int status;

    int i=0;

    //int line_files_aux =
    int lines_to_read = file_lines/n_processes;
    line_start = 0;
    line_finish = lines_to_read;

    for(i = 0; i<n_processes; i++){
      if(fork() == 0){

          line_start = line_finish;
          line_finish = lines_to_read*i +1;
          //printf("line partida = %d, line finish = %d\n", line_start,line_finish);

          printf("Proceso %d , linea de partida = %d, lineas a escanear = %d\n", i, getStartLine(i,n_processes,file_lines),getLinesToRead(i,n_processes,file_lines));

          int start_line = getStartLine(i,n_processes,file_lines);
          int lines_number = getLinesToRead(i,n_processes,file_lines);


          char str_i[12];
          sprintf(str_i, "%d", i);

          char str_start_line[12];
          sprintf(str_start_line, "%d", start_line);

          char str_lines_number[12];
          sprintf(str_lines_number, "%d", lines_number);

         //execlp("./comparator", "comparator",file_name, start_line, lines_number,i, searched_string, (const char *)NULL);
         execlp("./comparator", "comparator",file_name, str_start_line, str_lines_number,str_i, searched_string, (const char *)NULL);




          // printf("child %d %d\n", i, ++k);
          // sleep(1);
          // printf("done %d\n",i);
          exit(0);
      }
    }

    while ((wpid = wait(&status)) > 0);

    //printf ("Esto siempre se imprime al final \n");

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
