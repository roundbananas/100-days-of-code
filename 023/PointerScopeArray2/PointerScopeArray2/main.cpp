//
//  main.cpp
//  PointerScopeArray2
//
//  Created by Carl Turner on 4/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//The structure of code below reflects structure of SunDefender, before I tried to move pointer initialisation into a separate function within run().

#include <iostream>
/*****
 CAN PUT FORWARD DECLARATIONS IN SEPARATE HEADER FILE(S)
*****/
//declare a pointer to an int
//initialise it will null (good practice)
//Enemy* enemies = nullptr;
int* aPointer = nullptr;

//declare a function that returns a pointer
//Enemy* createPlatoon(int numEnemies, int numMountains, VertexArray& mountainsVA);
int* aFunction(int parameter1, int parameter2);

void update(int *ptr); //this function to demonstrate it doesn't matter if you pass the pointer or not. You can still manipulate an out of scope variable using a pointer.

void updateWithoutPassingVariable();

/*****
 CAN PUT FUNCTION DEFINITIONS IN SEPARATE CPP FILES(S)
 *****/

//define the function that returns a pointer
int* aFunction(int parameter1, int parameter2)
{
    int* aPointerToReturn = new int[2];
    aPointerToReturn[0] = parameter1;
    aPointerToReturn[1] = parameter2;
    return aPointerToReturn;
}

void updateWithoutPassingVariable()
{
    std::cout << "\n\n UPDATE_WITHOUT_PASSING_VARIABLE()";
    int anotherNewValue = 70000;
    aPointer[0] = anotherNewValue;
    std::cout << "\nNew value of element 1 in array: " << aPointer[0];
}

void update(int *ptr)
{
    std::cout << "\n\n UPDATE()";
    int anotherNewValue = 7;
    aPointer[1] = anotherNewValue;
    std::cout << "\nNew value of element 2 in array: " << aPointer[1];
}

void run()
{
    std::cout << "\n\n RUN()";
    //initialise pointer by calling a function that returns a pointer
    //WHY: we want to initialise it with more than just a simple value
    //enemies = createPlatoon(m_NumEnemies, m_NumMountains, m_mtnArrayDigital);

    int argument1 = 3;
    int argument2 = 5;
    aPointer = aFunction(argument1, argument2);
    
    std::cout << "\nValue of element 1 in array: " << aPointer[0];
    std::cout << "\nValue of element 1 in array: " << *(aPointer + 0);
    
    //use pointer to change a value
    int newValue = 4;
    aPointer[0] = newValue;
     std::cout << "\nNew value of element 1 in array: " << aPointer[0];
    
    //run update() to do something else with the pointer, while in run()
    updateWithoutPassingVariable();
    update(aPointer);
  
    
}

/*****
 MAIN LOOP IN MAIN.CPP
 *****/
int main() {
    std::cout << "\n\n MAIN()";
    run();
    std::cout << "\n\n MAIN()";
    //Pointer is in scope because it is forward declared, globally to the main().
    
    std::cout << "\nPointer's own address: " << &aPointer;
    std::cout << "\nThe pointer's value (ie the address of the variable it points to): " << aPointer;
    std::cout << "\nValue of element 1 in array:" << *(aPointer + 0);
    std::cout << "\nValue of element 2 in array:" << *(aPointer + 1);
    std::cout << "\n";
    return 0;
}
