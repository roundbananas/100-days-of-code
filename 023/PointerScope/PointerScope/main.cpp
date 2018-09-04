//
//  main.cpp
//  PointerScope
//
//  Created by Carl Turner on 4/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include <iostream>

int* aPointer = nullptr;

void run()
{
    aPointer = new int;
    int aValue = 5;
    *aPointer = aValue;
    
}

int main() {

    run();
    
    std::cout << "\nPointer's own address: " << &aPointer;
    std::cout << "\nThe pointer's value (ie the address of the variable it points to): " << aPointer;
    std::cout << "\nValue the pointer points to: " << *aPointer;
    std::cout << "\n";
    return 0;
}
