//
//  main.cpp
//  PointerScope2
//
//  Created by Carl Turner on 4/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include <iostream>

int* aPointer = nullptr;

void run()
{
    aPointer = new int[2];
    int aValue[] = {5, 3};
    aPointer = aValue;
    std::cout << "\nValue of element 1 in array: " << aValue[0];
    std::cout << "\nValue of element 1 in array: " << *(aValue + 0);
    
}

int main() {
    
    run();
    
    std::cout << "\nPointer's own address: " << &aPointer;
    std::cout << "\nThe pointer's value (ie the address of the variable it points to): " << aPointer;
    std::cout << "\nValue the pointer points to: " << *(aPointer + 0);
  //The following two lines don't work, because aValue is out of scope.
   // std::cout << "\nValue of element 1 in array: " << aValue[0];
   // std::cout << "\nValue of element 1 in array: " << *(aValue + 0);
    std::cout << "\n";
    return 0;
}

