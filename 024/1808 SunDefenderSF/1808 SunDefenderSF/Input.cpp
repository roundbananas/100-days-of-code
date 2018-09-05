//
//  Input.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//
//The game has 5 buttons. In playing mode they are used to fire each of the five canons. In Levelling_Up mode they are used to make power-up selections. In Game_Over and Idle mode, pressing any button will start a new game.
//There are two ways to get input. Events seem to be most appropriate.
//Events notify you when something happens ("this button was pressed", "the mouse has moved") - syntax "(event.type == sf::Event::KeyPressed)". (https://www.sfml-dev.org/tutorials/2.5/window-events.php) At this stage I think tracking button presses as Events will be enough for this game.
//The other type of input I could grab (using SFML) is real-time input (ie is a key CURRENTLY being pressed) - syntax "sf::Keyboard::isKeyPressed(sf::Keyboard::Left)". (https://www.sfml-dev.org/tutorials/2.5/window-inputs.php) This might be useful if I want the player to be able to hold down a button for rapid fire.

#include "Engine.h"
#include "GameMode.h"
#include "BattleGround.h"
#include <iostream>

void Engine::m_Input()
{
    
    Event event;
    while(m_Window.pollEvent(event))
    {
        if(event.type == Event::KeyPressed)
        {
            //Handle player quitting
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                m_Window.close();
            }
            
            //handle player starting the game
            //IDLE: "Press any button to start", GAME_OVER: "Press any button to play again"
            if((mode == GameMode::IDLE || mode == GameMode::GAME_OVER) && ((event.key.code == Keyboard::Num1) || (event.key.code == Keyboard::Num2) || (event.key.code == Keyboard::Num3) || (event.key.code == Keyboard::Num4)|| (event.key.code == Keyboard::Num5)))
            {
                /******
                 Initialise NEW game (ie at Level 0).
                 *******/
                
                loadLevel();
                mode = GameMode::PLAYING;
            }
            
            //Handle input while playing
            if(mode == GameMode::PLAYING)
            {
                if (event.key.code == Keyboard::Num1)
                {
                    //set canon to fired and not charged
                    std::cout <<"\nFIRE #1 !";
                    player[0].fireCanon();
                }
                if (event.key.code == Keyboard::Num2)
                {
                    //set canon to fired and not charged
                    player[1].fireCanon();
                }
                if (event.key.code == Keyboard::Num3)
                {
                    //set canon to fired and not charged
                    player[2].fireCanon();
                }
                if (event.key.code == Keyboard::Num4)
                {
                    //set canon to fired and not charged
                    player[3].fireCanon();
                }
                if (event.key.code == Keyboard::Num5)
                {
                    //set canon to fired and not charged
                    player[4].fireCanon();
                }
            }//END handle input while playing
                        
            //handle levelling up choice, and starting next level
            if (mode == GameMode::LEVELLING_UP)
            {
                if (event.key.code == Keyboard::Num1)
                {
                    //grant powerup type 1
                    mode = GameMode::PLAYING;
                }
                else if (event.key.code == Keyboard::Num2)
                {
                    //grant powerup type 2
                    mode = GameMode::PLAYING;
                }
                else if (event.key.code == Keyboard::Num3)
                {
                    //grant powerup type 3
                    mode = GameMode::PLAYING;
                }
                else if (event.key.code == Keyboard::Num4)
                {
                    //grant powerup type 4
                    mode = GameMode::PLAYING;
                }
                else if (event.key.code == Keyboard::Num5)
                {
                    //grant powerup type 5
                    mode = GameMode::PLAYING;
                }
                //if we were levelling up and we switched to playing mode, launch a new level
                if(mode == GameMode::PLAYING)
                {
                    //initialise next level
                    /***TO DO LATER: increase number, speed, types of enemies****/
                    
                    loadLevel();
                }
            }//END handle levelling up
        }//END event polling for a key press
    } //END all event polling
    
    //maybe include inpiut for managing rapid fire here later
}
