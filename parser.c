#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

char ** parse_args( char * line, char target);
int count_args( char * line, char target );


/*===============================================
  char ** parse_args()

  INPUTS: char * line
          char target
  Returns: Array of strings, line cut into segments depending on target

  Line is broken up into smaller string segments where target appears. 
  Each segment is placed in an index of the returned array
  ===============================================*/

char ** parse_args( char * line, char target ) {
  
  //allocate an array with count_args slots to store char pointers in
  int num =  count_args(line, target); 
  char** parsed = (char **) calloc(num, sizeof(char *));
  int index = 0;
  //hold the remaining line to parse; while there is more...
  char * seg = line; 
  while (seg) {
    //set the slot in parsed as the returned string segment by strsep
    parsed[index] = strsep(&seg, &target);
    index++;
  }
  //if all slots have args, last should be NULL
  return parsed;
}


/*===============================================
  int count_args()

  INPUTS: char * line
          char target
  Returns: Integer of times target is found in line

  A counter variable keeps track of the times target is found as function
  traverses through line, array of chars.
  ===============================================*/
int count_args(char * line, char target) {
  int count = 1;
  while (*line) {
    if (*line == target) {
      count++;
    }
    line++;
  }
  return count;
}
