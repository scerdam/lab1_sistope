#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// LLamar al programa comparador dentro del fork una vez creado el proceso
fork();
    execv("./", "comparator_program", size_line_file, searched_string);

int main (int argc, char **argv) {

  char *file, *searched_string = NULL;
  int n_processes, size_line_file, flag_show_results = 0;

  int index;
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "i:n:c:p:d")) != -1)
    switch (c)
      {
      case 'i':
        file = optarg;
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
  printf ("file = %s, searched_string = %s, n_processes = %d,  size_line_file = %d, flag_show_results = %d\n",
          file, searched_string, n_processes, size_line_file, flag_show_results );
//

  for (index = optind; index < argc; index++)
    printf ("No existe opcion para agumento: %s\n", argv[index]);
  return 0;
}
