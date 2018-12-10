//MEGA
/*
Engine.h and cpp - remove led setup info. Just retain variables we need.

idle, countdown, gameover modes - move all current code related to led strips to ESP. Replace with code that sends the current mode to ESP, once.

DUring playing mode - create an array of values. Send each item in the array.

*/


// ESP
/* Render, depending on mode
read each value and put it into an array. When array is complete, update the strip.
 */



//WHAT DATA IS SENT?
/*
mode - for idle, countdown, gameover modes the led Strip behaviour is independant of player input. ESP can just do it if it knows current mode.




*/