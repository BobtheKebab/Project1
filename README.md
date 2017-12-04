# AKSH #
Systems Project 01
by Ahbab Ashraf and Kristin Lin

#### Features: ####
- Forks and executes commands--including cd and exit!
- Parses multiple commands on one line!
- Redirects using >, <!
- Simple pipes | !

#### Notes: ####
- When executing ./a.out with other file as input, please
  exit and a newline, or else program will be caught in loop

#### Attempted: ####
- Multiple redirections/pipes on one line

#### Bugs: ####
- Unpredictable during redirection when test calls are from file
  rather than STDIN
- If a test call resulted in error, exit might have to be called
  several times before functioning.
- `ls -l -a` does not work (although `ls -la` does)
- `$ `, which indicates the program awaiting next input may appear in output
  unpredictably during piping

#### Files & Function Headers: ####

###### parser.c ######
```
/*===============================================                  
  char ** parse_args()

  INPUTS: char * line
  	  char target
  RETURNS: Array of strings, line cut into segments depending on target

  Line is broken up into smaller string segments where target appears. 
  Each segment is placed in an index of the returned array.                     
===============================================*/

/*===============================================                     
  int count_args()

  INPUTS: char * line
          char target
  RETURNS: Integer of times target is found in line

  A counter variable keeps track of the times target is found as function
  traverses through line, array of chars.                    
  ===============================================*/
```
  
###### proj1.c ######
```
/*===============================================                     
  char * cleanser()

  INPUTS: char * line
  RETURNS: Same string with extra whitespace removed

  Uses strsep to remove extra newline char, then traverses through line
  and removes all insignicant whitespaces after a space, semicolon,
  redirect and pipe symbols, as well as before the null terminator.
  ===============================================*/

/*===============================================                     
  int direct()

  INPUTS: char * line
  RETURNS: Integer 0 (exit) or 1 (continue, successful).

  Categorizes lines into different commands: multiple commands, redirect
  commands, piping commands, or regular commands using IF ELSE statements.
  Takes appropriate actions for those categories, and calls run.
  ===============================================*/

/*===============================================                     
  int redirect()

  INPUTS: char * command
  	  int src
	  int desc 
  RETURNS: 1 

  Dups the desc file, dup2s the src to the desc, runs command, then dup2s
  the copied desc file into desc again.
  ===============================================*/

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

/*===============================================                     
  int command_cd()

  INPUTS: char * line
  RETURNS: 1

  Calls chdir with the path, the second part of the line after the first
  space, before returning 0.
  ===============================================*/

```