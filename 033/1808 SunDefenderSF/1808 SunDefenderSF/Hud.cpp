//
//  Hud.cpp
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 11/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Hud.h"
#include "ResourcePath.hpp"

Hud::Hud()
{
    //get window resolution to use for positioning text
    //***this is manual currently - set in Engine.cpp also. Need to centralise it to avoid error.
    Vector2u resolution;
    resolution.x = 1000;
    resolution.y = 1200;
    
    //load fonts
    m_TitleFont.loadFromFile(resourcePath() + "Lazer84.ttf");
    m_SubTitleFont.loadFromFile(resourcePath() + "good times rg.ttf");
    m_ParagraphFont.loadFromFile(resourcePath() + "OpenSans-Semibold.ttf");
    
    //Associate fonts with text objects and set size, colour, string, position
    //For each mode
    
    //IDLE Mode
    m_TitleText.setFont(m_TitleFont);
    m_TitleText.setCharacterSize(100);
    m_TitleText.setFillColor(Color::Magenta);
    m_TitleText.setString("       Sun\nDefender");
    
    FloatRect titleRect = m_TitleText.getLocalBounds();
    m_TitleText.setOrigin(titleRect.left + titleRect.width/2.0f, titleRect.top + titleRect.height/2.0f);
    m_TitleText.setPosition(resolution.x/2.0f, resolution.y/7.0f);
    m_TitleText.setRotation(-2.5);
    
    //Synopsis
    m_SynopsisText.setFont(m_ParagraphFont);
    m_SynopsisText.setCharacterSize(25);
    m_SynopsisText.setFillColor(Color::White);
    std::stringstream synopsisStream;
    synopsisStream <<
    "Intergalactic invaders have come to our planet!" <<
    "\nThey harvest sun energy using special sun-draining weapons." <<
    "\n\nUse your canons (equipped with ground-hugging lasers)" <<
    "\nto kill all the invaders, before the sun is extinguished," <<
    "\nand we are (prematurely) doomed.";
    m_SynopsisText.setString(synopsisStream.str());
    
    FloatRect synopsisRect = m_TitleText.getLocalBounds();
    m_SynopsisText.setOrigin(synopsisRect.left + synopsisRect.width/2.0f, synopsisRect.top + synopsisRect.height/2.0f);
    m_SynopsisText.setPosition(resolution.x/3.0f, 3 * resolution.y/8.0f);
    
    //How to play title
    m_HowToPlayHeadingText.setFont(m_SubTitleFont);
    m_HowToPlayHeadingText.setCharacterSize(50);
    m_HowToPlayHeadingText.setFillColor(Color::White);
    m_HowToPlayHeadingText.setString("How to Play");
    
    FloatRect howToRect = m_HowToPlayHeadingText.getLocalBounds();
    m_HowToPlayHeadingText.setOrigin(howToRect.left + howToRect.width/2.0f, howToRect.top + howToRect.height/2.0f);
    m_HowToPlayHeadingText.setPosition(resolution.x/2.0f, resolution.y/2.0f + 50);
    
    //How to play instructions
    m_HowToPlayInstructions.setFont(m_ParagraphFont);
    m_HowToPlayInstructions.setCharacterSize(35);
    m_HowToPlayInstructions.setFillColor(Color::White);
    m_HowToPlayInstructions.setString("       Press 1, 2, 3, 4 or 5 \nto fire your laser-canons.\n\n     Press Enter to start");
    
    FloatRect howInstructionsRect = m_HowToPlayInstructions.getLocalBounds();
    m_HowToPlayInstructions.setOrigin(howInstructionsRect.left + howInstructionsRect.width/2.0f, howInstructionsRect.top + howInstructionsRect.height/2.0f);
    m_HowToPlayInstructions.setPosition(resolution.x/2.0f, 6.7 * resolution.y/10.0f);
    
    //Author
    
    m_AuthorText.setFont(m_ParagraphFont);
    m_AuthorText.setCharacterSize(25);
    m_AuthorText.setFillColor(Color::White);
    m_AuthorText.setString("Created by Carl Turner 2018 \n        roundbananas.com");
    
    FloatRect authorRect = m_AuthorText.getLocalBounds();
    m_AuthorText.setOrigin(authorRect.left + authorRect.width/2.0f, authorRect.top + authorRect.height/2.0f);
    m_AuthorText.setPosition(resolution.x/2.0f, 8 * resolution.y/10.0f);
    
    //Score and level display in Playing, Game Over modes
    m_ScoreText.setFont(m_SubTitleFont);
    m_ScoreText.setCharacterSize(30);
    m_ScoreText.setFillColor(Color::White);
    
    FloatRect scoreRect = m_ScoreText.getLocalBounds();
    m_ScoreText.setOrigin(scoreRect.left, scoreRect.top);
    m_ScoreText.setPosition(20, 20);
    
    //Level
    m_LevelText.setFont(m_SubTitleFont);
    m_LevelText.setCharacterSize(30);
    m_LevelText.setFillColor(Color::White);
    
    FloatRect levelRect = m_LevelText.getLocalBounds();
    m_LevelText.setOrigin(levelRect.width, levelRect.top);
    m_LevelText.setPosition(resolution.x - 200, 20);
    
    //GAME OVER mode
    m_GameOverText.setFont(m_SubTitleFont);
    m_GameOverText.setCharacterSize(30);
    m_GameOverText.setFillColor(Color::White);
    m_GameOverText.setString("Your sun was extinguished! \n\n   Press Enter to try again \n   (or press escape to exit)");
    
    FloatRect overRect = m_GameOverText.getLocalBounds();
    m_GameOverText.setOrigin(overRect.left + overRect.width/2.0f, overRect.top + overRect.height/2.0f);
    m_GameOverText.setPosition(resolution.x /2.0f, resolution.y /2.0f);
    
    //LEVELLING UP mode
    m_LevelUpText.setFont(m_SubTitleFont);
    m_LevelUpText.setCharacterSize(30);
    m_LevelUpText.setFillColor(Color::White);
 //   m_LevelUpText.setString("LEVEL UP TEXT");

    std::stringstream levelUpStream;
    levelUpStream <<
    "You beat this wave!" <<
    "\n\nPress button to choose an Upgrade: " <<
    "\n1 : Faster canon recharging" <<
    "\n2 : Increase damage inflicted";
    m_LevelUpText.setString(levelUpStream.str());
    
    
    FloatRect levelUpRect = m_LevelUpText.getLocalBounds();
    m_LevelUpText.setOrigin(levelUpRect.left + levelUpRect.width/2.0f, levelUpRect.top + levelUpRect.height/2.0f);
    m_LevelUpText.setPosition(resolution.x /2.0f, 2* resolution.y /3.0f);
    
}

Text Hud::getTitle()
{
    return m_TitleText;
}

Text Hud::getSynopsis()
{
    return m_SynopsisText;
}

Text Hud::getHowToHeading()
{
    return m_HowToPlayHeadingText;
}

Text Hud::getHowToInstructions()
{
    return m_HowToPlayInstructions;
}

Text Hud::getLevelUpText()
{
    return m_LevelUpText;
}

Text Hud::getGameOverText()
{
    return m_GameOverText;
}

Text Hud::getAuthorText()
{
    return m_AuthorText;
}

Text Hud::getScore()
{
    return m_ScoreText;
}

Text Hud::getLevel()
{
    return m_LevelText;
}

void Hud::setScore(int score)
{
    std::stringstream scoreStream;
    scoreStream << "Score: " << score;
    m_ScoreText.setString(scoreStream.str());
}

void Hud::setLevel(int level)
{
    std::stringstream levelStream;
    levelStream << "Level: " << level;
    m_LevelText.setString(levelStream.str());
}
