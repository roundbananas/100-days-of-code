//
//  ZombieArena.cpp
//  Zombies
//
//  Created by Carl Turner on 19/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"

using namespace sf;

int main()
{
    //the game will be in one of four states
    enum class State
    {
        PAUSED, LEVELING_UP, GAME_OVER, PLAYING
    };
    //start with GAME_OVER state
    State state = State::GAME_OVER;
    
    //Get screen resolution and create an SFML window
    Vector2f resolution; //Holds resolution of the monitor on which the program is running
 //   resolution.x = VideoMode::getDesktopMode().width;
 //   resolution.y = VideoMode::getDesktopMode().height;
    
    resolution.x = 1920;
    resolution.y = 1080;
    
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena"); //, Style::Fullscreen
    
    //Create an SFML view for the main action
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
    
    //Clock for timing everything
    Clock clock;
    //Variable to hold how long has the PLAYING state been active
    Time gameTimeTotal;
    
    //Where is the mouse in relation to the game world (the game world moves around during play)
    Vector2f mouseWorldPosition; //the f indicates float. This type holds two floats.
    //where is the mouse relative to the screen coords
    Vector2i mouseScreenPosition; //i = int. this type holds two ints.
    
    //Instantiate a player
    Player player;
    
    //The boundaries of the arena
    IntRect arena;
    
    //Create background
    VertexArray background;
    //Load the texture for the background
    Texture textureBackground;
    textureBackground.loadFromFile(resourcePath() + "background_sheet.png");
    
    //The main game loop
    while (window.isOpen())
    {
        /************
         HANDLE INPUT
         ************/
        
        //Handle Events
        Event event; //use event to poll for system events
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                //pause a game while playing
                if (event.key.code == Keyboard::Return && state == State::PLAYING)
                {
                    state = State::PAUSED;
                }
                //restart while paused
                else if (event.key.code == Keyboard::Return && state == State::PAUSED)
                {
                    state = State::PLAYING;
                    //Reset the clock so there isn't a frame jump.
                    //(while we're paused the clock keeps running)
                    clock.restart();
                }
                
                //start a new game while in GAME_OVER state
                else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
                {
                    state = State::LEVELING_UP;
                }
                
                if (state == State::PLAYING)
                {
                    
                }
            }
        } //END EVENT POLLING
        
        //Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        
        //Handle controls while playing
        if (state == State::PLAYING)
        {
            //handle pressing WASD keys
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                player.moveUp();
            }
            else
            {
                player.stopUp();
            }
            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                player.moveDown();
            }
            else
            {
                player.stopDown();
            }
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                player.moveRight();
            }
            else
            {
                player.stopRight();
            }
        } //End WASD Handling
        
        //Handle levelling up state
        if(state == State::LEVELING_UP)
        {
            if (event.key.code == Keyboard::Num1)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num2)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num3)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num4)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num5)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num6)
            {
                state = State::PLAYING;
            }
            
            //***
            
            if (state == State::PLAYING)
            {
                //Prepare the level
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;
                
                //Pass the vertex array by reference to createBackground function
                //syntax: createBackground(VertexArray& rVA, IntRect arena), so background is passed by reference and arena is passed by value
                int tileSize = createBackground(background, arena);
                
                //Spawn the player in middle of arena
                //by passing all the info to the player
                player.spawn(arena, resolution, tileSize);
                
                //Reset the clock so there isn't a frame jump
                clock.restart();
            }
        } //End Handling levelling up
        
        /************
         UPDATE THE FRAME
         ************/
        
        if (state == State::PLAYING)
        {
            //update the dt and game time
            Time dt = clock.restart();
            gameTimeTotal += dt;
            
            //make a decimal fraction of 1 from the dt
            float dtAsSeconds = dt.asSeconds();
            
            //Where's the mouse
            mouseScreenPosition = Mouse::getPosition(); //Mouse::getPosition() is a static function. We can call it without an instance of the Mouse class.
            //convert mouse position to world coords of mainView
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);
          
            //Update the player
            player.update(dtAsSeconds, Mouse::getPosition());
            
            //Make note of the player's new position
            Vector2f playerPosition(player.getCenter());
            
            //Make view centre around player
            mainView.setCenter(player.getCenter());
        }//End Updating the scene
        
        /************
         DRAW THE SCENE
         ************/
    
        if (state == State::PLAYING)
        {
            window.clear();
            
            //set mainView to be displayed in the window
            //and draw everything related to mainView
            window.setView(mainView);
            
            window.draw(background, &textureBackground);
            
            window.draw(player.getSprite());
        }
        
        if (state == State::LEVELING_UP)
        {
            
        }
        if (state == State::PAUSED)
        {
            
        }
        if (state == State::GAME_OVER)
        {
            
        }
        
        window.display();
        
    }//END MAIN GAME LOOP
    return 0;
}
