//
//  main.cpp
//  SimpleReferences
//
//  Created by Carl Turner on 21/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//Simple example of reference
//A reference is an alias, that allows making changes to variables from outside of the scope they exist in.

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

void PrintNameA(string& _name)
{
    cout << "Player's name is :" << _name << endl;
}

void UpdateName(string _name, string _newName)
{
    _name = _newName;
}

void UpdateNameA(string& _name, string _newName) //first function parameter is an address
{
    _name = _newName;
}

int main() {
    playerCharacteristics player;   //instantiate a player
    string& rName = player.name;    //declare a reference (alias) to the player's name. Call the alias 'rName'.

    //The following lines show you can use either the alias or the variable name in the same way.
    cout << "1. (pass by value): ";
    PrintName(rName);               //pass the reference by value. name is John
    
    //When we pass by value, a copy of the value is sent to the function. The original value is not changed
    cout << "2. (pass by value, using the variable): ";
    UpdateName(player.name, "Sam"); //pass the variable by value. Name is still John.
    PrintName(player.name);
    
    cout << "3. (pass by value, using the reference):  ";
    UpdateName(rName, "Sam");       //pass the reference by value. Name is still John
    PrintName(rName);

    /*The following lines use a function that takes an address. BUT you still pass either the alias or the variable name in the same way.
     When the function takes an address, it is the original value that is used/changed by the function*/
    cout << "4. (Update name: pass by address, using the reference):  ";
    UpdateNameA(rName, "Sam");  //pass by address. Name updated to Sam.
    PrintName(rName);
    
    cout << "5. (Update name: pass by address, using the variable):  ";
    UpdateNameA(player.name, "Tim"); //pass by address. Name updated to Tim.
    PrintName(rName);
    
    cout << "6. (Print name: pass by address, using the reference):  ";
    PrintNameA(rName);
    cout << "7. (Print name: pass by address, using the variable):  ";
    PrintNameA(player.name);
    return 0;
}
