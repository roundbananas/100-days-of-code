//
//  main.cpp
//  TWL
//
//  Created by Carl Turner on 24/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//
/* From SFML: resource files (images, sounds, fonts, ...) are copied to
*  application bundle. To get the path to these resources, use the
*  helper function `resourcePath()` from ResourcePath.hpp
*/


#include "Engine.h"

int main()
{
    //declare instance of Engine
    Engine engine;
    
    //Start engine
    engine.run();
    
    return 0;
}
