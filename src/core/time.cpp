#include "core/time.hpp"
#include <SDL.h>

static Uint32 lastTime = 0;

void GameClock::reset(){
    lastTime = SDL_GetTicks();
    deltaTime = 0.0f;
    playingTime = 0.0f;
}

void GameClock::update(){
    Uint32 currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f;
    playingTime += deltaTime;
    lastTime = currentTime; 
}