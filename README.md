# AKSH #
Systems Project 01
by Ahbab Ashraf and Kristin Lin

#### Features: ####
	Forks and executes commands!
	Parses multiple commands on one line!
	Redirects using >, <!

#### Attempted: ####
	Multiple redirections on one line

#### Bugs: ####
	1. When executing ./a.out with other file as input, please
	   exit and a newline, or else program will be caught in loop
	2. UNPREDICTABLE during redirection when test calls are from file
	   rather than STDIN
	3. If test call resulted in error, exit might have to be called
	   several times before functioning.

#### Files & Function Headers: ####
                  
###### parser.c ######
- - - -

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

###### proj1.c ######
- - - -

	Handles the forking an executing of commands...

