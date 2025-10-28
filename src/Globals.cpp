#include "Globals.h"

float EXTERNS::deltaT;

int EXTERNS::screenWidth = 1024;
int EXTERNS::screenHeight = 768;

std::string EXTERNS::spaceshipTexture = "res/img/spaceship.png";
int EXTERNS::spaceshipTextureID = 0;

std::string EXTERNS::bigAsteroidTexture = "res/img/big_asteroid.png";
int EXTERNS::bigAsteroidTextureID = 0;

std::string EXTERNS::mediumAsteroidTexture = "res/img/medium_asteroid.png";
int EXTERNS::mediumAsteroidTextureID = 0;

std::string EXTERNS::smallAsteroidTexture = "res/img/small_asteroid.png";
int EXTERNS::smallAsteroidTextureID = 0;

std::string EXTERNS::firstFrameLaserTexture = "res/img/laser_1.png";
int EXTERNS::firstFrameLaserTextureID = 0;

std::string EXTERNS::bombTexture = "res/img/bomb.png";
int EXTERNS::bombTextureID = 0;

std::string EXTERNS::backgroundTexture = "res/img/background_space.png";
int EXTERNS::backgroundTextureID = 0;

std::string EXTERNS::gameHUD = "res/img/game_HUD.png";;
int EXTERNS::gameHudID = 0;

std::string EXTERNS::powerUpTexture = "res/img/powerup_img.png";;
int EXTERNS::powerUpTextureID = 0;

std::string EXTERNS::explosionTexture = "res/img/explosion.png";;

 std::string EXTERNS::fontText = "res/fonts/Conthrax-SemiBold.otf";
 int EXTERNS::font = 0;

 TEXT::Text EXTERNS::defaultText;

 std::string EXTERNS::shootEffect = "res/sound/spaceship_shot.wav";
 Sound EXTERNS::shootEffectSound;

 std::string EXTERNS::asteroidExplosion = "res/sound/asteroid_explosion.wav";
 Sound EXTERNS::asteroidExplosionSound;

 std::string EXTERNS::shotgunShot = "res/sound/gunshot_sound.wav";
 Sound EXTERNS::shotgunShotSound;

 std::string EXTERNS::powerUpShotgun = "res/sound/pu_active_shotgun.wav";
 Sound EXTERNS::powerUpShotgunSound;

 std::string EXTERNS::powerUpSlow = "res/sound/pu_active_slow.wav";
 Sound EXTERNS::powerUpSlowSound;

 std::string EXTERNS::powerUpInvencible = "res/sound/pu_active_invincible.wav";
 Sound EXTERNS::powerUpInvencibleSound;

 extern double EXTERNS::timer = 0;

 extern int EXTERNS::initialMaxAsteroidsOnScreen = 10;
 extern int EXTERNS::maxAsteroidsOnScreen = 30;
 extern float EXTERNS::spawnTime = 10.0f;
 extern float EXTERNS::timerSpawn = spawnTime;
 extern float EXTERNS::timerToIncreaseDifficulty = 30.0f;
 extern float EXTERNS::difficultyTimer = timerToIncreaseDifficulty;