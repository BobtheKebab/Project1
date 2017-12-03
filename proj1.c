#include "parser.c"

//==============================================
// FUNCTION HEADERS

int run( char * line );
int command_cd(char * path);
int direct(char * line);
char * cleanser( char * line );


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
    char * ready = cleanser(line);
    EXIT = direct(ready);
  }
    return EXIT;  
}

//===============================================
//for newline, whitespace, and spaces after ; 
char * cleanser( char * line ) {

  //get rid of that ending newline
  char * cleaned = line;
  strsep(&cleaned, "\n");

  //delete whitespace and spaces after ; >/< and |
  char * start = line;
  int DELETE = 0; //marker that this should now be a valid char
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
    //; ' ' and > shouldn't have spaces after them or before
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

//===============================================
//looks for symbols like ; or > or < and |
int direct(char * line) {

  //first, get rid of the newline symbol
  char ** commands;
  
  //if there's multiple commands:
  if (strchr(line, ';')) {
    //count how many internal commands
    int target = count_args(line, ';');
    //create an array of strings with each index carrying a command
    commands = parse_args(line, ';');
    int count = 0;
    //run them all
    while (count < target) {
      run(commands[count]);
      count++;
    }
    free(commands);
  } else if (strchr(line, '>')) {
    commands = parse_args(line, '>');
    int fd = open(commands[1], O_CREAT | O_WRONLY, 0644);
    int fdOut = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    run(commands[0]);
    dup2(fdOut, STDOUT_FILENO);
    free(commands);
  } else if (strchr(line, '<')) {
    commands = parse_args(line, '<');
    int fd = open(commands[1], O_RDONLY);
    int fdOut = dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
    run(commands[0]);
    dup2(fdOut, STDIN_FILENO);
    free(commands);
  } else if (strchr(line, '|')) {
    commands = parse_args(line, '|');
    char buf[100];
    buf[0] = '\0';
    char* temp;
    FILE* fp = popen(commands[0], "r");

    while (fgets(temp, sizeof(temp), fp)) {
      //printf("%s", temp);
      strcat(buf, temp);
    }
    fclose(fp);

    temp = commands[1];
    //printf("%s", temp);
    strcat(temp, " ");
    //printf("%s", temp);
    char* token = strtok(buf, "\n");
    while (token) {
      strcat(temp, token);
      strcat(temp, " ");
      token = strtok(NULL, "\n");
    }

    printf("%s", temp);
    run(temp);
  }
  //regular command
  else {
    return run(line);
  }
  return 1;
}


//===============================================
int run( char * line ) {
  char copied_line[256];
  strcpy(copied_line, line);
  //put line in correct format
  char ** args = parse_args( copied_line, ' ' );
  int f;

  if (!strcmp(args[0], "echo")) {
    args[1] = line+5;
    args[2] = 0;
  }
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

//==============================================
int command_cd(char * path) {
  char * seg = path;
  strsep(&seg, " ");
  chdir(seg);
  return 1;
}








