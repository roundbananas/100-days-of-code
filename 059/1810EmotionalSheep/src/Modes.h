



//
//  Modes.h
//
//  Created by Carl Turner on 22/10/18.
//
#ifndef Modes_h
#define Modes_h

enum Control
{
    RC_MODE,   //can be driven like an RC car by user
    AUTONOMOUS //moves autonomously, using sensors for collision avoidance
};

enum Mood
{
    IDLE,     //doing nothing
    HAPPY,    //singing and illuminated white colour with red slow beating heart colour
    FEARFUL,  //says please don't hurt me, heart beats faster, backs away slowly
    TERRIFIED //turns bloody red, screams and limps away
};

typedef struct
{
    Control control;
    Mood mood;
    unsigned long startedAt;
} Mode;

#endif