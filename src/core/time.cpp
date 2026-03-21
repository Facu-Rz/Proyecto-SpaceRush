#include "core/time.hpp"
#include "game/game.hpp"
#include "debug/debug_state.hpp"
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
    #ifdef DEBUG_MODE
    if (debug.pause) deltaTime = 0;
    #endif
    globalTime += deltaTime;
    lastTime = currentTime; 
}