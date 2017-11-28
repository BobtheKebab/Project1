#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char ** parse_args( char * line);
int count_args(char * line);
int run( char * line );


int main() {
  char line[256];
  printf("\nWelcome to our shell.\nType commands. Press Ctrl+C to quit.\n");
  printf("=============================================================\n");
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

  /*
  char * a = "ls -l";
  char * b = "echo hello";
  char ** args = {a, b};
  run(args[0]);
  */


int run( char * line ) {
  char copied_line[sizeof(line)];
  strcpy(copied_line, line);
  
  //put line in correct format
  char ** args = parse_args(copied_line);
  int f;

  if (!strcmp(args[0], "cd")) {
    free(args);
    char * seg = line;
    strsep(&seg, " ");
    chdir(seg);
  }
  else if (!strcmp(args[0], "exit")) {
    free(args);
    return 0;
  }
  else {
    f = fork();
    //child
    if (!f) {
      //      printf("%d\n", args[2]);
      //      printf("%s\n", args[2]);
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


char ** parse_args( char * line ) {
  
  //allocate an array with count_args slots to store char pointers in
  int num =  count_args(line);
  printf("%d\n", num);
  char** parsed = (char **) calloc(count_args(line), sizeof(char *));
  int index = 0;

  //hold the remaining line to parse; while there is more...
  char * seg = line; 
  while (seg) {
    //set the slot in parsed as the returned string segment by strsep
    parsed[index] = strsep(&seg, " ");
    printf("%s\n", parsed[index]);
    index++;
  }

  //if all slots have args, last should be NULL
  return parsed;
}


int count_args(char * line) {
  int count = 1;
  while (*line) {
    if (*line == ' ') {
      count++;
    }
    line++;
  }
  return count;
}

