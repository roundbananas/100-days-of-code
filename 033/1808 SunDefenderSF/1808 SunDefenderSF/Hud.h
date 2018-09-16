//
//  Hud.h
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 10/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

// Create font objects to hold font.
// Create text objects to hold different Hud/UI elements
// Create public functions to initialise the Hud objects, set/update them (called from Update() function in game engine, and to get the values for drawing (called by Render())

#ifndef Hud_h
#define Hud_h

#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
    Font m_TitleFont;
    Font m_SubTitleFont;
    Font m_ParagraphFont;
    
    Text m_TitleText;
    Text m_SynopsisText;
    Text m_HowToPlayHeadingText;
    Text m_HowToPlayInstructions;
    Text m_LevelUpText;
    Text m_GameOverText;
    Text m_AuthorText;
    
    Text m_ScoreText;
    Text m_LevelText;
   
    
public:
    Hud();
    Text getTitle();
    Text getSynopsis();
    Text getHowToHeading();
    Text getHowToInstructions();
    Text getLevelUpText();
    Text getGameOverText();
    Text getAuthorText();
    
    Text getScore();
    Text getLevel();
    
    void setScore(int score);
    void setLevel(int level);
};

#endif /* Hud_h */
