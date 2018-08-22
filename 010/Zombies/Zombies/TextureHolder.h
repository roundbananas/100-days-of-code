//
//  TextureHolder.h
//  Zombies
//
//  Created by Carl Turner on 21/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef TextureHolder_h
#define TextureHolder_h

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
private:
    //a map container from the Standard Template Library (STL) that holds related pairs of string and texture
    //Texture is an SFML type
    std::map<std::string, Texture> m_Textures;
    
    //delcare a static pointer of the same type as the class itself, the one and only instance
    //prefixes: m = member variable, s = singleton
    //This means the TextureHolder class contains an object that is the same type as itself
    //static means the pointer can be used without an instance of the class
    static TextureHolder* m_s_Instance;
    
public:
    TextureHolder(); //prototype for default constructor
    
    //declare a function that returns a reference to a Texture. So it returns a reference, not a copy of a graphic (ie saves memory)
    //static means the function can be used without an instance of the class
    //the function takes a string of constant reference, whcih means the reference is constant (can't be changed)
    static Texture& GetTexture(std::string const& filename);
};

#endif /* TextureHolder_h */
