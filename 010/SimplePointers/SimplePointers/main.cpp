//
//  main.cpp
//  SimplePointers
//
//  Created by Carl Turner on 21/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//Simple example of pointers
//A pointer is a variable that holds a memory address.
//This program illustrates simple use of pointers. For something as simple as this it's slightly easier to use references, rather than pointers.
//Because, in order to pass a pointer to a function, the function must be declared as taking a pointer as one of its parameters. Whereas a reference is just an alias and can be passed to the same function as you'd pass the variable it references.

#include <iostream>
#include <string>

using namespace std;

struct playerCharacteristics
{
    int health = 10;
    bool alive = true;
    int score = 5;
    string name = "John";
};

void PrintName(string _name)
{
    cout << "Player's name is :" << _name << endl;
}

//to pass a pointer to the function, the function parameter must be declare as a pointer
void PrintNamePtr(string *_name)
{
    cout << "Player's name is :" << *_name << endl;
}

void UpdateName(string _name, string _newName)
{
    _name = _newName;
}

//to pass a pointer to the function, the function parameter must be declare as a pointer
void UpdateNamePtr(string *_name, string _newName)
{
    *_name = _newName;
}

int main() {
    playerCharacteristics player;   //instantiate a player
    string *pName = &player.name;    //declare a pointer to the player's name. Call the pointer 'pName'.
    
    //The following lines show you can use either the pointer or the actual variable name to retrieve the player's name. BUT in order to change the value of player.name we need to use the pointer OR the address of player.name (ie &player.name).
    cout << "1. (Get name, using pointer): ";
    PrintNamePtr(pName);               //pass the variable by pointer to its address. name is John
    
    //When we pass by value, a copy of the value is sent to the function. The original value is not changed
    cout << "2. (Try to change name to Sam, by passing by value): ";
    UpdateName(player.name, "Sam"); //pass the variable by value. Name is still John.
    PrintName(player.name);
    
    cout << "3. (Change name to Sam by passing address of the variable itself):  ";
    UpdateNamePtr(&player.name, "Sam");       //pass the address of the variable name itself. Name is updated to Sam. Because we passed the address of the variable we want to update, not a copy of the value.
    PrintNamePtr(&player.name);
    
    cout << "4. (Change name to Tim by passing address, using pointer):  ";
    UpdateNamePtr(pName, "Tim");  //pass by address. Name updated to Sam.
    PrintNamePtr(pName);
    
    return 0;
}


