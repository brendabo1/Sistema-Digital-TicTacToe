#ifndef POSITION_TRANSLATE
#define POSITION_TRANSLATE

/*consts for find value in vector*/
#define CORD_X 1
#define CORD_Y 0

/*consts for moves*/
#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'

/**
 * @param currentpos a array with 2 values, when 0 is y cordinate and 1 is x cordinate
 * @return true if the position is valid, false otherwise
*/
bool movetoright(int currentpos[]);

/**
 * @param currentpos a array when 0 is y cordinate and 1 is x cordinate
 * @return true if the position is valid, false otherwise
*/
bool movetoleft(int currentpos[]);

/**
 * @param currentpos a array with 2 values, when 0 is y cordinate and 1 is x cordinate
 * @return true if the position is valid, false otherwise
*/
bool movetoup(int currentpos[]);

/**
 * @param currentpos a array with 2 values, when 0 is y cordinate and 1 is x cordinate
 * @return true if the position is valid, false otherwise
*/
bool movetodown(int currentpos[]);

/**
 * @param currentposa array with 2 values, when 0 is y cordinate and 1 is x cordinate
 * @param move the move to be made, is a char
 * @param newPos pointer to array with 2 values for new cordinates, when 0 is cordinate y and 1 is cordinate x
 * @return 0 is have a error, 1 if the move is valid
*/
int getnewpos(int currentpos[], char move, int* newPos);

#endif