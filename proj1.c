#include "parser.c"

//==============================================
// FUNCTION HEADERS

int run( char * line );
int command_cd(char * path);
int prepare(char * line);


//===============================================
int main() {
  char line[256];
  printf("\nWelcome to AKSH. Type commands.\n");
  printf("===================================================\n");
  int EXIT = 1;

  while (EXIT) {
    printf("$ ");
    //get user input
    fgets(line, 256, stdin);
    //remove new line from stdin
    /* char * cleaned = line; */
    /* cleaned = strsep(&cleaned, "\n"); */
    /* EXIT = run(cleaned); */
    EXIT = prepare(line);
  }
    return EXIT;  
}

//===============================================
//looks for symbols like ; or > or < and |
int prepare(char * line) {
  char ** commands;
  char * cleaned = line;
  cleaned = strsep(&cleaned, "\n");

  if (strchr(cleaned, ';')) {
    int target = count_args(cleaned, ';');
    commands = parse_args(cleaned, ';');
    int count = 0;
    while (count < target) {
      run(commands[count]);
      count++;
    }
    free(commands);
  } else {
    return run(cleaned);
  }
  return 1;
}

int run( char * line ) {
  char copied_line[256];
  strcpy(copied_line, line);
  //put line in correct format
  char ** args = parse_args( copied_line, ' ' );
  int f;

  if (!strcmp(args[0], "cd")) {
    free(args);
    return command_cd(line);
  }
  else if (!strcmp(args[0], "exit")) {
    free(args);
    return 0;
  }
  else {
    f = fork();
    //child
    if (!f) {
      execvp(args[0], args);
      return 0;
    }
    //parent waits
    else {
      int status;
      wait(&status);
      free(args);
      return 1;
    }
  }
}

//==============================================
int command_cd(char * path) {
  char * seg = path;
  strsep(&seg, " ");
  chdir(seg);
  return 1;
}








