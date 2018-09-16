//
//  MtnProjectiles.h
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 8/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef MtnProjectiles_h
#define MtnProjectiles_h

#include <SFML/Graphics.hpp>

using namespace sf;

class MtnProjectiles
{
private:
    Sprite m_Sprite;
    Texture m_Texture;
    Vector2f m_SpritePosition;
    Vector2f m_TriggerPosition; //position of corresponding canon projectile where it hits base of mountain. When the canon projectile arrives at base of moutain we will turn on the MtnProjectile.
    Vector2f m_PeakPosition; //top of mountain (where enemy is)
  
    //handle display of the projectile
    bool m_MtnProjectileOn;
    double m_TimeMtnProjHasBeenOn;
    double m_OnDuration = 0.3;
    
    //for handling damage inflicted on enemies
    bool m_IsDamaging;
    
public:
    bool getOn();
    void stop();
    void turnOn();
    
    bool isDamaging();
    void stopDamaging();
    
    Sprite getSprite();
    Vector2f getSpritePosition();
    Vector2f getTriggerPosition(); 
    Vector2f getPeakPosition();
    
    void spawn(Vector2f spritePosition, int i, Vector2f triggerPosition, Vector2f peakPosition);
    void update (double dt);
};

#endif /* MtnProjectiles_h */
