# AKSH #
Systems Project 01
by Ahbab Ashraf and Kristin Lin

#### Features: ####
	Forks and executes commands--including cd and exit!
	Parses multiple commands on one line!
	Redirects using >, <!
	Simple pipes | !

#### Attempted: ####
	Multiple redirections/pipes on one line

#### Bugs: ####
	1. When executing ./a.out with other file as input, please
	   exit and a newline, or else program will be caught in loop
	2. UNPREDICTABLE during redirection when test calls are from file
	   rather than STDIN
	3. If test call resulted in error, exit might have to be called
	   several times before functioning.
	4. `rm -rf` and `ls -l -a` do not work (although `ls -la` does)

#### Files & Function Headers: ####
                  
###### parser.c ######
- - - -
```
/*===============================================                  
  _char ** parse_args()_

  INPUTS: char * line
  char target
  RETURNS: Array of strings, line cut into segments depending on target

  Line is broken up into smaller string segments where target appears. 
  Each segment is placed in an index of the returned array.                     
===============================================*/

/*===============================================                     
  _int count_args()_

  INPUTS: char * line
          char target
  RETURNS: Integer of times target is found in line

  A counter variable keeps track of the times target is found as function
  traverses through line, array of chars.                    
  ===============================================*/
```
  
###### proj1.c ######
- - - -
```
/*===============================================                     
  _char * cleanser()_

  INPUTS: char * line
  RETURNS: Same tring with extra whitespace removed

  Uses strsep to remove extra newline char, then traverses through line
  and removes all insignicant whitespaces after a space, semicolon,
  redirect and pipe symbols, as well as before the null terminator.
  ===============================================*/

/*===============================================                     
  _int direct()_

  INPUTS: char * line
  RETURNS: Integer 0 (exit) or 1 (continue, successful).

  Categorizes lines into different commands: multiple commands, redirect
  commands, piping commands, or regular commands using IF ELSE statements.
  Takes appropriate actions for those categories, and calls run.
  ===============================================*/

/*===============================================                     
  _int run()_

  INPUTS: char * line
  RETURNS: Integer 0 (exit) or 1 (continue, successful).

  Line must be a single, plain command that may be eventually fed to execvp.
  Echo is given to execvp as a two string array: "echo", <string>. Cd is not
  given to execvp, it calls function command_cd. Exit does not call execvp,
  it returns 0 for exit. Otherwise, it's a plain command that is broken
  down by spaces using parse_args and a child process feeds it to execvp.
  ===============================================*/

/*===============================================                     
  _int command_cd()_

  INPUTS: char * line
  RETURNS: 1, successful

  Calls chdir with the path, the second part of the line after the first
  space, before returning 0.
  ===============================================*/

```