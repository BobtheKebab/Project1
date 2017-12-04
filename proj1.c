#include "parser.c"

char * cleanser( char * line );
int direct(char * line);
int redirect(char * command, int src, int desc);
int run( char * line );
int command_cd(char * path);


//SHELL
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
  char line[256];
  printf("\nWelcome to AKSH. Type commands.\n");
  printf("===================================================\n");
  int EXIT = 1;

  while (EXIT) {
    printf("$ ");
    //get user input
    fgets(line, 256, stdin);
    char * ready = cleanser(line);
    EXIT = direct(ready);
  }
    return EXIT;  
}



//FUNCTIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



/*===============================================                     
  char * cleanser()

  INPUTS: char * line
  RETURNS: Same string with extra whitespace removed

  Uses strsep to remove extra newline char, then traverses through line
  and removes all insignicant whitespaces after a space, semicolon,
  redirect and pipe symbols, as well as before the null terminator.
  ===============================================*/

char * cleanser( char * line ) {
  //get rid of that ending newline
  char * cleaned = line;
  strsep(&cleaned, "\n");
  //delete whitespace and spaces after ; >/< and |
  char * start = line;
  //marker that this should now be a valid char
  int DELETE = 0; 
  while (*line) {
    //delete spaces if they occurred in front of symbols or after ' ' & symbols
    while(DELETE) {
      if (*line == ';' | *line == '>' | *line == '<' | *line == '|') {
	strcpy( line-1, line );
      }
      else if (*line == ' ') {
	strcpy( line, line+1 );
      }
      else if (!*line) {
	strcpy( line-1, line );
	return start;
      }else {
	DELETE = 0;
      }
    }
    //; ' ' > < | and NULL shouldn't have spaces after them or before
    if (*line == ' ' | *line == ';' | *line == '>' | *line == '<') {
      DELETE = 1;
    }
    if (*line == ' ' && !*(line+1)) {
      strcpy( line, line+1 );
    }
    line++;
  }
  return start;
}



/*===============================================                     
  int direct()

  INPUTS: char * line
  RETURNS: Integer 0 (exit) or 1 (continue, successful).

  Categorizes lines into different commands: multiple commands, redirect
  commands, piping commands, or regular commands using IF ELSE statements.
  Takes appropriate actions for those categories, and calls run.
  ===============================================*/

int direct(char * line) {
  //first, get rid of the newline symbol
  char ** commands;
  //multiple commands:
  if (strchr(line, ';')) {
    int target = count_args(line, ';');
    commands = parse_args(line, ';');
    int count = 0;
    //run all 
    while (count < target) {
      run(commands[count]);
      count++;
    }
    free(commands);
  }
  //redirect stdout to file
  else if (strchr(line, '>')) {
    commands = parse_args(line, '>');
    int fd = open(commands[1], O_CREAT | O_WRONLY, 0644);
    redirect(commands[0], fd, STDOUT_FILENO);
    free(commands);
  }
  //redirect stdin to file
  else if (strchr(line, '<')) {
    commands = parse_args(line, '<');
    int fd = open(commands[1], O_RDONLY);
    redirect(commands[0], fd, STDIN_FILENO);
    free(commands);
  }
  //| but technically redirect stdout to stdin
  else if (strchr(line, '|')) {
    commands = parse_args(line, '|');
    FILE * stdout = popen(commands[0], "r");
    redirect(commands[1], (*stdout)._fileno, STDIN_FILENO);
    pclose(stdout);
    free(commands);
  }
  //regular command
  else {
    return run(line);
  }
  return 1;
}



/*===============================================                     
  int redirect()

  INPUTS: char * command
  	  int src
	  int desc 
  RETURNS: 1 

  Dups the desc file, dup2s the src to the desc, runs command, then dup2s
  the copied desc file into desc again.
  ===============================================*/

int redirect(char * command, int src, int desc) {
  int temp = dup(desc);
  dup2(src, desc);
  run(command);
  dup2(temp, desc);
  return 1;
}



/*===============================================                     
  int run()

  INPUTS: char * line
  RETURNS: Integer 0 (exit) or 1 (continue, successful).

  Line must be a single, plain command that may be eventually fed to execvp.
  Echo is given to execvp as a two string array: "echo", <string>. Cd is not
  given to execvp, it calls function command_cd. Exit does not call execvp,
  it returns 0 for exit. Otherwise, it's a plain command that is broken
  down by spaces using parse_args and a child process feeds it to execvp.
  ===============================================*/

int run( char * line ) {
  char copied_line[256];
  strcpy(copied_line, line);
  //put line in correct format
  char ** args = parse_args( copied_line, ' ' );
  int f;
  //echo should really be followed with one long string
  if (!strcmp(args[0], "echo")) {
    args[1] = line+5;
    args[2] = 0;
  }
  //cd or exit or reg command
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
    //child runs command
    if (!f) {
      execvp(args[0], args);
      free(args);
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



/*===============================================                     
  int command_cd()

  INPUTS: char * line
  RETURNS: 1, successful

  Calls chdir with the path, the second part of the line after the first
  space, before returning 0.
  ===============================================*/

int command_cd(char * path) {
  char * seg = path;
  strsep(&seg, " ");
  chdir(seg);
  return 1;
}








