//
//  Timber.cpp
//  Timber
//
//  Created by Carl Turner on 18/8/18.
//  Following tutorial from https://www.udemy.com/learning-path-c-game-programming/
//

//#include <stdio.h> //was included by default when creating new cpp file
#include <SFML/Audio.hpp>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"

//make code easier to write. With the following line we don't need to write sf:: every time we use a variable or function from the sf namespace.
using namespace sf;

//Function declaration
void updateBranches(int seed); //this is a function prototype

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//Where is the player/branch? Left or right?
//define a class type called side.
enum class side{LEFT, RIGHT, NONE}; //used to describe position of individual branches as well as the player
side branchPositions [NUM_BRANCHES]; //each of the 6 branches can be one of the type 'side' (either LEFT, RIGHT or NONE)

int main()
{
    //Create a video mode object
    VideoMode vm(1920, 1080);
    
    //Create and open a window for the game
    RenderWindow window(vm, "Timber!!!"); //can add a third parameter: Style::Fullscreen
    
    /*
     *   Setup a graphic:
     *   1. Assign memory and loading a graphic, using Texture object
     *   2. Create a sprite object that we'll display in the window. The sprite contains the texture.
     *   3. set position of sprite
     *   4. draw the sprite
     *   5. display the sprite (think in layers)
     */
        //Create a texture to hold a graphic on the GPU
        Texture textureBackground;
    
        //Load a graphic into the texture
        textureBackground.loadFromFile(resourcePath() + "background.png");
    
        //create a sprite
        Sprite spriteBackground;
    
        //Attach the texture to the sprite
        spriteBackground.setTexture(textureBackground);
    
        //Set the spriteBackground to cover the screen
        spriteBackground.setPosition(0,0);
    
                //Make tree sprite
                Texture textureTree;
                textureTree.loadFromFile(resourcePath() + "tree.png");
                Sprite spriteTree;
                spriteTree.setTexture(textureTree);
                spriteTree.setPosition(810,0);
    
                // Add more trees
                Texture textureTree2;
                textureTree2.loadFromFile(resourcePath() + "tree2.png");
                Sprite spriteTree2;
                spriteTree2.setTexture(textureTree2);
                Sprite spriteTree3;
                spriteTree3.setTexture(textureTree2);
                Sprite spriteTree4;
                spriteTree4.setTexture(textureTree2);
                Sprite spriteTree5;
                spriteTree5.setTexture(textureTree2);
                Sprite spriteTree6;
                spriteTree6.setTexture(textureTree2);
    
                spriteTree2.setPosition(20, 0);
                spriteTree3.setPosition(300, -400);
                spriteTree4.setPosition(1300, -400);
                spriteTree5.setPosition(1500, -500);
                spriteTree6.setPosition(1900, 0);
    
                // Prepare the bee
                Texture textureBee;
                textureBee.loadFromFile(resourcePath() + "bee.png");
                Sprite spriteBee;
                spriteBee.setTexture(textureBee);
                spriteBee.setPosition(0, 800);
    
                // Is the bee currently moving?
                bool beeActive = false;
    
                // How fast can the bee fly
                float beeSpeed = 0.0f;
    
                // make 3 cloud sprites from 1 texture
                Texture textureCloud;
    
                // Load 1 new texture
                textureCloud.loadFromFile(resourcePath() + "cloud.png");
    
        //Make clouds using arrays
        const int NUM_CLOUDS = 6;
        Sprite clouds[NUM_CLOUDS];     //array of sprites to hold cloud sprites
        int cloudSpeeds[NUM_CLOUDS];   //array to hold cloud speeds
        bool cloudsActive[NUM_CLOUDS];  //array to hold help toggle individual clouds on/off
    
        for (int i = 0; i < NUM_CLOUDS; i++) //initialise each cloud
        {
            clouds[i].setTexture(textureCloud);
            clouds[i].setPosition(-300, i * 150); //set each cloud initial position off the screen
            cloudsActive[i] = false;
            cloudSpeeds[i] = 0;
            
        }
    
               /* // 3 New sprites withe the same texture
                Sprite spriteCloud1;
                Sprite spriteCloud2;
                Sprite spriteCloud3;
                spriteCloud1.setTexture(textureCloud);
                spriteCloud2.setTexture(textureCloud);
                spriteCloud3.setTexture(textureCloud);
    
                // Position the clouds off screen
                spriteCloud1.setPosition(0, 0);
                spriteCloud2.setPosition(0, 150);
                spriteCloud3.setPosition(0, 300);
    
                // Are the clouds currently on screen?
                bool cloud1Active = false;
                bool cloud2Active = false;
                bool cloud3Active = false;
    
                // How fast is each cloud?
                float cloud1Speed = 0.0f;
                float cloud2Speed = 0.0f;
                float cloud3Speed = 0.0f;
                */
    
    
    // Variables to control time itself
    Clock clock;
    
    //Time bar
    RectangleShape timeBar; //RectangleShape is an SFML class
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920/2) - timeBarStartWidth/2, 980); //make timebar sit in middle of screen. Magic numbers relate to window size
    
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining; //the number of pixels the timebar needs to shrink during each second of the game
    
    
    //is the game running?
    bool paused = true;
    
    //Draw some Text
    int score = 0;
    
    Text messageText;
    Text scoreText;
    Text fpsText;
    
    //Choose a font
    Font font;
    font.loadFromFile(resourcePath() + "KOMIKAP_.ttf");
    
    //Set the font to our message
    messageText.setFont(font);
    scoreText.setFont(font);
    fpsText.setFont(font);
    
    // Set up the fps text
    fpsText.setFillColor(Color::White);
    fpsText.setCharacterSize(100);
    fpsText.setPosition(1200, 20);
    
    //Assign the actual message
    messageText.setString(" Press Enter to start!\n Use LEFT and RIGHT arrows to chop.\n Don't get squished by a branch.");
    scoreText.setString("Score = 0");
    
    //Make text big
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    
    //Choose text colour
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);
    
    //Position the text
    //FloatRect object holds a rectangle with floating point coords.
    //initialise textRect with the coordinates of the rectangle that wraps messageText
    FloatRect textRect = messageText.getLocalBounds();
    //set the origin of messageText to the centre of the rectangle that wraps it
    messageText.setOrigin(
                          textRect.left + textRect.width/2.0f, //set x value of origin to middle of the rectangle
                          textRect.top + textRect.height/2.0f); //set y value of origin to middle of the rectangle
    messageText.setPosition(1920/2.0f, 1080/2.0f); //magic numbers are window resolution
    scoreText.setPosition(20, 20); //magic numbers are a small indent from edge of screen
    
    // Backgrounds for the text
    RectangleShape rect1;
    rect1.setFillColor(sf::Color(0, 0, 0, 150));
    rect1.setSize(Vector2f(600,105));
    rect1.setPosition(0,30);
    
    RectangleShape rect2;
    rect2.setFillColor(sf::Color(0, 0, 0, 150));
    rect2.setSize(Vector2f(1000, 105));
    rect2.setPosition(1150, 30);
    
    //Prepare 6 branches
    Texture textureBranch;
    textureBranch.loadFromFile(resourcePath() + "branch.png");
    for (int i=0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000,-2000); //maginc numbers place the branches well off screen initially
        branches[i].setOrigin(220,40); //branch png is 440 x 80. This allow us  to rotate the sprite without moving it out of position.
    }
    
    // Prepare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile(resourcePath() + "player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
    
    // The player starts on the left
    side playerSide = side::LEFT;
    
    // Prepare the gravestone
    Texture textureRIP;
    textureRIP.loadFromFile(resourcePath() + "rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);
    
    // Prepare the axe
    Texture textureAxe;
    textureAxe.loadFromFile(resourcePath() + "axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);
    
    // Line the axe up with the tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;
    
    // Prepare the flying log
    Texture textureLog;
    textureLog.loadFromFile(resourcePath() + "log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);
    
    // Some other useful log related variables
    bool logActive = false; //if it's currently moving or not.
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    
    //Control player input. When to wait for player input and when to ignore player input.
    bool acceptInput = false;
    
    //Prepare the sound
    SoundBuffer chopBuffer; //create an object to hold the audio data
    chopBuffer.loadFromFile(resourcePath() + "chop.wav");
    Sound chop; // the Sound type object has functions to play, stop the audio
    chop.setBuffer(chopBuffer); //assign the relevant audio data
    
    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile(resourcePath() + "death.wav");
    Sound death;
    death.setBuffer(deathBuffer);
    
    SoundBuffer ootBuffer; //out of time buffer
    ootBuffer.loadFromFile(resourcePath() + "out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);
    
    //control the drawing of the score
    int lastDrawn = 0;
    
    //MAIN GAME LOOP
    while (window.isOpen())
    {
        /*
         Process events. Handle the player's input.
        */
        
         Event event; //could be a mouse click, something to the window, key press. Events are cued.
        while (window.pollEvent(event))
        {
            if(event.type == Event::KeyReleased && !paused)
            {
                //listen for key presses again
                acceptInput = true;
                
                //hide the axe
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }
            
            //Close window: exit
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

            //Close window: exit
            //this type of input is immediate, responds immediately to key press.
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
            //Return pressed: start game
            if (Keyboard::isKeyPressed(Keyboard::Return))
            {
                paused = false;
                
                //Reset the time and score
                score = 0;
                timeRemaining = 6;
                
                // Make all the branches disappear
                for (int i = 1; i < NUM_BRANCHES; i++)
                {
                    branchPositions[i] = side::NONE;
                }
                
                // Make sure the gravestone is hidden
                spriteRIP.setPosition(675, 2000);
                
                // Move the player into position
                spritePlayer.setPosition(580, 720);
                
                acceptInput = true;
                
            }
            
            // Wrap the player controls to
            // Make sure we are accepting input
            if (acceptInput)
            {
                // More code here next...
                // First handle pressing the right cursor key
                //Check if player has chopped on right side of tree
                if (Keyboard::isKeyPressed(Keyboard::Right))
                {
                    // Make sure the player is on the right
                    playerSide = side::RIGHT;
                    
                    score++;
                    
                    // Add to the amount of time remaining
                    timeRemaining += (2 / score) + .15;  //the more score, the less time is added. Play with this formula for difficulty level
                    
                    //Move the axe to the right side, at same y height
                    spriteAxe.setPosition(AXE_POSITION_RIGHT,
                                          spriteAxe.getPosition().y);
                    
                    spritePlayer.setPosition(1200, 720);
                    
                    // update the branches. Move them all down one space and spawn a new branch using score as the seed
                    updateBranches(score);
                    
                    // set the log flying to the left
                    spriteLog.setPosition(810, 720);
                    logSpeedX = -5000;
                    logActive = true;
                    
                    acceptInput = false; //prevent player from making any more chops
                    
                    chop.play(); //play sound
                    
                }
                // Handle the left cursor key
                if (Keyboard::isKeyPressed(Keyboard::Left))
                {
                    // Make sure the player is on the left
                    playerSide = side::LEFT;
                    
                    score++;
                    
                    // Add to the amount of time remaining
                    timeRemaining += (2 / score) + .15;
                    
                    spriteAxe.setPosition(AXE_POSITION_LEFT,
                                          spriteAxe.getPosition().y);
                    
                    
                    spritePlayer.setPosition(580, 720);
                    
                    // update the branches
                    updateBranches(score);
                    
                    // set the log flying
                    spriteLog.setPosition(810, 720);
                    logSpeedX = 5000;
                    logActive = true;
                    
                    acceptInput = false;
                    
                    chop.play(); //play sound
                }
            }
        
        /*
         * Update the scene
        */
        
        if (!paused)
        {
                //Measure time
                Time dt = clock.restart();
            
                //Calculate time remaining
                timeRemaining -= dt.asSeconds();
                //Resize timebar
                timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
            
                if (timeRemaining <= 0.0f)
                {
                    paused = true;
                    
                    messageText.setString("Out of Time!!");
                    //Reposition the text based on its new size
                    FloatRect textRect = messageText.getLocalBounds();
                    messageText.setOrigin(
                                          textRect.left + textRect.width/2.0f,
                                          textRect.top + textRect.height/2.0f);
                    messageText.setPosition(1920/2.0f, 1080/2.0f);
                    
                    outOfTime.play(); //play sound
                }
            
                    //setup the bee
                    if (!beeActive)
                    {
                        //bee speed
                        // seed srand(), the random number generator, with current time.
                        //(int) = cast time to an int, which is required for the stand function
                        //rand() gets a random number. % gets remainder. % 100 divides the remainder by 100.
                        srand((int)time(0)*10);
                        beeSpeed = (rand() % 200) + 200;
                        
                        //bee height
                        srand((int)time(0) * 10);
                        float height = (rand() % 500) + 500;
                        spriteBee.setPosition(2000, height);
                        beeActive = true;
                    }
                    else //move the bee
                    {
                        spriteBee.setPosition(
                            spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                                              spriteBee.getPosition().y);
                    
                        //has the bee reached the righ edge of the screen?
                        if (spriteBee.getPosition().x < -100)
                        {
                            //set it up to be in a new height next frame
                            beeActive = false;
                        }
                    }
            
                //Manage the clouds with arrays
            for (int i=0; i <NUM_CLOUDS; i++)
            {
                if (!cloudsActive[i]) //if the cloud isn't active, make it active
                {
                   //how fast is the cloud?
                    srand((int)time(0) * i);
                    cloudSpeeds[i] = (rand() % 200);
                    
                    //How high is the cloud
                    srand((int)time(0) * i);
                    float height = (rand() % 150);
                    clouds[i].setPosition(-200, height);
                    cloudsActive[i] = true;
                }
                else //move the cloud
                {
                    clouds[i].setPosition(
                        clouds[i].getPosition().x + (cloudSpeeds[i] * dt.asSeconds()),
                        clouds[i].getPosition().y);
                    if (clouds[i].getPosition().x > 1920) //has cloud gone off screen?
                    {
                        cloudsActive[i] = false; //set it up to be a new cloud in the next loop
                    }

                }
            }
                    

            //Draw the score and the frame rate once every 100 frames
            lastDrawn++;
            if (lastDrawn == 100) {
                 //Update the score text
                std::stringstream ss; //define a variable of type stringstream (this type allows concatenation of strings with non-strings)
                ss << "Score = " << score;
                scoreText.setString(ss.str());
            
                //draw the fps
                std::stringstream ss2;
                ss2 << "FPS = " << 1/dt.asSeconds();
                fpsText.setString(ss2.str());
                lastDrawn = 0;
            }
                
            //Update branch sprites
            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                float height = i * 150; //means first branch will have height = 0, 6 branch at 750
                if (branchPositions[i] == side::LEFT)
                {
                    //move sprite to left side
                    branches[i].setPosition(610, height); //610 is appropriate position for left, based on branch origin we set previously
                    //flip sprite around
                    branches[i].setRotation(180);
                }
                else if (branchPositions[i] == side::RIGHT)
                {
                    //move sprite to right side
                    branches[i].setPosition(1330, height); //1330 is appropriate position for left
                    //flip sprite around
                    branches[i].setRotation(0);
                }
                else
                {
                        //hide the branch
                    branches[i].setPosition(3000, height); //well off screen
                }
            }
            
            ////handle flying log
            if (logActive)
            {
                spriteLog.setPosition(
                        spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                        spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
                
                // Has the log reached the right hand edge of the screen?
                if (spriteLog.getPosition().x < -100 ||
                    spriteLog.getPosition().x > 2000)
                {
                    // Set it up ready to be a whole new log next frame
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }
            
            // has the player been squished by a branch?
            if (branchPositions[5] == playerSide) //is the last branch on the player's side?
            {
                // death
                paused = true;
                acceptInput = false;
                
                // Draw the gravestone
                spriteRIP.setPosition(525, 760); //need to update this to be on player side
                
                // hide the player and axe
                spritePlayer.setPosition(2000, 660);
                spriteAxe.setPosition(2000, 660);
                
                // Change the text of the message
                messageText.setString("SQUISHED!!");
                
                // Center message on the screen
                FloatRect textRect = messageText.getLocalBounds();
                
                messageText.setOrigin(textRect.left +
                                      textRect.width / 2.0f,
                                      textRect.top + textRect.height / 2.0f);
                
                messageText.setPosition(1920 / 2.0f,
                                        1080 / 2.0f);
                
                death.play(); //play sound
    
            }
            
        } //END if(!paused)
        /*
        *  Draw the scene
        */
        
        //Clear everything from the last frame
        window.clear();
        
        // Draw our game scene here
        window.draw(spriteBackground);
        for (int i=0; i < NUM_CLOUDS; i++)
        {
        window.draw(clouds[i]);
        }
        
        // Enhanced version. Order matters. Draw the trees before the branches so branches are in front.
        window.draw(spriteTree2);
        window.draw(spriteTree3);
        window.draw(spriteTree4);
        window.draw(spriteTree5);
        window.draw(spriteTree6);
        
        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            window.draw(branches[i]);
        }
        
        
        window.draw(spriteTree);
        
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);   // Draw the flying log
        window.draw(spriteRIP); // Draw the gravestone
        
        // Draw backgrounds for the text
        window.draw(rect1);
        window.draw(rect2);
        
        window.draw(spriteBee);
        
        window.draw(scoreText);
        
        // Draw the FPS
        window.draw(fpsText);

        window.draw(timeBar);
        
        if (paused)
        {
            window.draw(messageText);
        }
        
        //Show everything we just drew
        window.display();
        
    }
    return 0;
}

//FUNCTION DECLARATIONS
void updateBranches(int seed)
{
    //move all branches down one place
    for(int j = NUM_BRANCHES - 1; j > 0; j--)
    {
        branchPositions[j] = branchPositions[j-1];
    }
    //We need to spawn a new branch at top of tree, cos we lost one off the bottom
    //LEFT, RIGHT or NONE position
    srand((int)time(0) + seed); //use seed to guarantee the seed is always different
    int r = (rand() % 5); //generate a random number between 0 and 4 (ie 5 possibilities)
    switch (r) //GAME BALANCE - 2/5ths of the time we'll get a branch.
    {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
    }
}


