#include "Explosion.h"

#include "Utils.h"

void EXPLOSION::InitExplosion(Explosion& explosion, Vector2 position, Texture texture, float frameWidth, float frameHeight, int totalFrames, float frameRate)
{
    explosion.position = position;
    explosion.texture = texture;
    explosion.frameWidth = frameWidth;
    explosion.frameHeight = frameHeight;
    explosion.totalFrames = totalFrames;
    explosion.frameRate = frameRate;
    explosion.currentFrame = 0.0f; 
    explosion.isActive = true;
}

void EXPLOSION::UpdateExplosion(Explosion& explosion)
{
    if (!explosion.isActive)
    {
        return;
    }

    explosion.currentFrame += explosion.frameRate * EXTERNS::deltaT;

    if (explosion.currentFrame >= explosion.totalFrames)
    {
        explosion.isActive = false;
    }
}

void EXPLOSION::DrawExplosion(Explosion explosion)
{  
    int framesPerRow = 4; 

    int frameNum = static_cast<int>(explosion.currentFrame);

    int frameCol = frameNum % framesPerRow;  
    int frameRow = frameNum / framesPerRow;  

    float frameX = (float)frameCol * explosion.frameWidth;
    float frameY = (float)frameRow * explosion.frameHeight;

    Rectangle sourceRec = { frameX, frameY, explosion.frameWidth, explosion.frameHeight };

    float drawX = UTILS::PercentToPixelsX(explosion.position.x);
    float drawY = UTILS::PercentToPixelsY(explosion.position.y);

    float drawWidth = explosion.frameWidth * 4.0f;
    float drawHeight = explosion.frameHeight * 4.0f;

    Rectangle destRec = { drawX, drawY, drawWidth, drawHeight };

    Vector2 origin = { drawWidth / 2.0f, drawHeight / 2.0f };

    DrawTexturePro(explosion.texture, sourceRec, destRec, origin, 0.0f, WHITE);
}
