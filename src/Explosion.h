#pragma once
#include "raylib.h"
#include "Globals.h" 

namespace EXPLOSION
{
    struct Explosion
    {
        Vector2 position; 
        Texture texture;

        float frameWidth; 
        float frameHeight;
        int totalFrames;  

        float currentFrame; 
        float frameRate;   

        bool isActive;    
    };

    void InitExplosion(Explosion& explosion, Vector2 position, Texture texture, float frameWidth, float frameHeight, int totalFrames, float frameRate);

    void UpdateExplosion(Explosion& explosion);

    void DrawExplosion(Explosion explosion);
}