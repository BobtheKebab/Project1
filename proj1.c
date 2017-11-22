#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char ** parse_args( char * line);
int count_args(char * line);
int run( char * line );

char ** parse_args( char * line) {
  //allocate an array with 6 slots to store char pointers in
  char ** parsed = (char **) calloc(count_args(line), sizeof(char *));
  int index = 0;
  //hold the remaining line to parse; while there is more...
  char * seg = line; 
  while (seg) {
    //set the slot in parsed as the returned string segment by strsep
    parsed[index] = strsep(&seg, " ");
     index++;
  }
  //if all slots have args, last should be NULL
  return parsed;
}

int count_args(char * line) {
  int count;
  char * seg = line;
  while (seg) {
    strsep(&seg, " ");
    count++;
  }
  return count;
}

int run( char * line ) {
  
}

int main() {

  char * line;
  /*
  read(0, &line, 256);
  printf("%s", line);
  */
  fgets(&line, 256, 0);
  /*
    char args[500] = "ls -a -l";
  char ** command = parse_args(args);
  execvp(command[0], command);
  //memory should be freed after other process takes over?
  */
}
