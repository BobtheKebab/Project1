#include "parser.c"

//==============================================
// FUNCTION HEADERS

int run( char * line );
int command_cd(char * path);


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
    char * cleaned = line;
    cleaned = strsep(&cleaned, "\n");
    EXIT = run(cleaned);
  }
    return EXIT;  
}

int run( char * line ) {
  char copied_line[256];
  strcpy(copied_line, line);
  //put line in correct format
  char ** args = parse_args(copied_line);
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
  char * seg = line;
  strsep(&seg, " ");
  chdir(seg);
  return 1;
}





  //create child to run process
    /*
  char** args;
  if (strstr(line, ";")) {
    args = parse_args(line, ";");
    int count = 0, target = count_args(line, ";");
    while (count < target) {
      run(args[count]);
      count++;
    }
  } else {
    //put line in correct format
    args = parse_args(line, " ");
    int f;

    //create child to run process
    f = fork();
    */


