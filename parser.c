#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char ** parse_args( char * line);
int count_args(char * line);


char ** parse_args( char * line ) {
  
  //allocate an array with count_args slots to store char pointers in
  int num =  count_args(line);
  char** parsed = (char **) calloc(count_args(line), sizeof(char *));
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
  int count = 1;
  while (*line) {
    if (*line == ' ') {
      count++;
    }
    line++;
  }
  return count;
}
