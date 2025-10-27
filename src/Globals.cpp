#include "Globals.h"

float EXTERNS::deltaT;

int EXTERNS::screenWidth = 1024;
int EXTERNS::screenHeight = 768;

std::string EXTERNS::spaceshipTexture = "res/img/spaceship.png";;
int EXTERNS::spaceshipTextureID = 0;

std::string EXTERNS::bigAsteroidTexture = "res/img/big_asteroid.png";;
int EXTERNS::bigAsteroidTextureID = 0;

std::string EXTERNS::mediumAsteroidTexture = "res/img/medium_asteroid.png";;
int EXTERNS::mediumAsteroidTextureID = 0;

std::string EXTERNS::smallAsteroidTexture = "res/img/small_asteroid.png";;
int EXTERNS::smallAsteroidTextureID = 0;

std::string EXTERNS::firstFrameLaserTexture = "res/img/laser_1.png";;
int EXTERNS::firstFrameLaserTextureID = 0;

 std::string EXTERNS::fontText = "res/fonts/Conthrax-SemiBold.otf";
 int EXTERNS::font = 0;

 TEXT::Text EXTERNS::defaultText;

 std::string  EXTERNS::shootEffect = "res/sound/spaceship_shot.wav";
 Sound EXTERNS::shootEffectSound;