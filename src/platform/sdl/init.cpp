#include "platform/sdl/init.hpp"
#include <SDL.h>
#include <SDL_ttf.h>


bool initPlatform(){
    if (SDL_Init(SDL_INIT_VIDEO) !=0){
        SDL_Log("Error al inicializar SDL: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1){
        SDL_Log("Error al inicializar TTF: %s", TTF_GetError());
        return false;
    }

    return true;
}

void quitPlatform(){
    SDL_Quit();
    TTF_Quit();
}