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
//using namespace std;

class TextureHolder
{
private:
    //a map container from the Standard Template Library (STL) that holds related pairs of string and texture
    //Texture is an SFML type
    std::map<std::string, sf::Texture> m_Textures;
    
    //delcare a static pointer of the same type as the class itself, the one and only instance
    //prefixes: m = member variable, s = singleton
    //This means the TextureHolder class contains an object that is the same type as itself
    //static means the pointer can be used without an instance of the class
    static TextureHolder* m_s_Instance; //see how we use this in the TextureHolder.cpp
    
public:
    TextureHolder(); //prototype for default constructor
    
    //Declare a constructor that overrides the default constructor, to make the singleton work the way we want it to. A reference to a Texture type, called TextureHolder::GetTexture()
    //The GetTexture function returns a reference to a Texture.
    //Static means the function can be used without an instance of the class
    //The function takes a string of constant reference, which means the reference can't be changed.
    static Texture& GetTexture(std::string const& filename);
};

#endif /* TextureHolder_h */
