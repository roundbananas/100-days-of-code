//
//  Codes.h
//
//  Created by Carl Turner on 12/12/18.
//
// Codes used in serial communication to handle data. 
// This file is for reference, it's not actually used in the program.

/*  Note, if testing in the serial monitor, to assign a new value to the 
 *  array it seems you need to type the mode, strip and state value into 
 *  the serial monitor each time. Eg: to assign a position 
 *  of 23 to the BulletAHead on strip1 during Playing mode, you'd write 
 *  in serial monitor: PXA23
 */

#ifndef Codes_h
#define Codes_h

enum class Codes
{
	//Mode Codes
	I, //IDLE_MODE,
    C, //COUNTDOWN,
    P, //PLAYING,
    L, //LEVELLING_UP,
    G, //GAME_OVER

 	//Strip Codes
 	X, //Strip 1
 	Y, //Strip 2
 	Z, //Strip 3
  
 	//Sub state codes
 	Q, // Bullet A is on 
 	R, // Bullet B is on
 	S, // Explosion is on

 	A, // Bullet A head
 	a, // Bullet A tail

 	B, // Bullet B head
 	b, // Bullet B tail

 	E, // Explosion head
 	e  // Explosion tail
};

#endif
