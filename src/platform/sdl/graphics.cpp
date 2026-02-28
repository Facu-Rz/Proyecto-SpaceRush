#include "platform/sdl/graphics.hpp"
#include "core/project_path.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

namespace {
    std::filesystem::path getFont(const std::filesystem::path& relativePath){
        return ProjectPaths::getAsset("fonts") / relativePath;
    }
}

bool initGraphics(Graphics& graphics){
    graphics.window = SDL_CreateWindow("Space Rush",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, graphics.WINDOW_WIDTH, graphics.WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if(!graphics.window){
        SDL_Log("Error al crear ventana: %s", SDL_GetError());
        return false;
    }

    graphics.renderer = SDL_CreateRenderer(graphics.window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    if (!graphics.renderer){
        SDL_Log("Error creando renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawBlendMode(graphics.renderer, SDL_BLENDMODE_BLEND);

    auto scorePath = getFont("Pacifico.ttf");
    auto gameOverPath = getFont("Spectral/Spectral-Bold.ttf");
    auto hintPath = getFont("Spectral/Spectral-Medium.ttf"); 

    graphics.fonts.score = TTF_OpenFont(scorePath.string().c_str(), 24);
    graphics.fonts.gameOver = TTF_OpenFont(gameOverPath.string().c_str(), 72);
    graphics.fonts.hint = TTF_OpenFont(hintPath.string().c_str(), 28);

    if (!graphics.fonts.score || !graphics.fonts.gameOver || !graphics.fonts.hint) {
        SDL_Log("Error al cargar la fuente: %s", TTF_GetError());
        return false;
    }

    return true;
}

void destroyGraphics(Graphics& graphics){
    if(graphics.window) SDL_DestroyWindow(graphics.window);
    if(graphics.renderer) SDL_DestroyRenderer(graphics.renderer);
    if(graphics.fonts.score) TTF_CloseFont(graphics.fonts.score);
    if(graphics.fonts.gameOver) TTF_CloseFont(graphics.fonts.gameOver);
    if(graphics.fonts.hint) TTF_CloseFont(graphics.fonts.hint);
}