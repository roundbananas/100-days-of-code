//
//  TextureHolder.cpp
//  Zombies
//
//  Created by Carl Turner on 21/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>
#include "TextureHolder.h"
#include <assert.h>         //include the "assert feature"

//declare a pointer of type TextureHolder called m_s_Instance
//initialise it to nullptr. nullptr is a keyword.
TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()      //constructor
{
    assert(m_s_Instance == nullptr);    //this ensures the pointer m_s_Instance = nullptr. If it doesn't the game will exit.
    m_s_Instance = this;    //assign the pointer to this instance.
    //So, we created an instance and then made a pointer that points to it. Because the pointer is part of the object, it actually points to the one and only instance of itself.
}

//define implementation of a reference to a Texture type, called TextureHolder::GetTexture()
sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
    //Get a reference to m_Textures using m_s_Instance
    //This is using the pointer to TextureHolder to access the private variable m_Textures.
    auto& m = m_s_Instance -> m_Textures;
    //m_Textures is a map, declared in TextureHolder.h
    //so, m is a reference to the map
    //auto is equivalent of map<string, Texture>
    
    //Create an iterator to hold a key-value-pair (kvp)
    // and search for the required kvp using the passed-in filename
    auto keyValuePair = m.find(filename);
    //m is a reference to the map
    //auto is equivalent to map<string, Texture>::iterator
    
    //Did we find a match?
    if (keyValuePair !=m.end()) //m is a reference to the map
    {
        //Yes. Return the texture (the second part of the kvp).
        //the kvp is defined by map<std::string, sf::Texture>
        return keyValuePair->second;
    }
    else
    {
        //filename not found
        //create a new kvp using the filename
        //auto is equivalent of map<string, Texture>
        //m is a reference to m_Textures, a map.
        //So, texture is a reference to the Texture element of the map.
        auto& texture = m[filename];
        //load the texture from file in the usual way
        texture.loadFromFile(filename);
        
        return texture;
    }
}
