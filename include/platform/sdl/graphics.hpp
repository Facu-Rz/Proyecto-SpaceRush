#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

struct Fonts {
    TTF_Font* score = nullptr;
    TTF_Font* gameOver = nullptr;
    TTF_Font* hint = nullptr;
};

struct Graphics {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Fonts fonts;

    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;
};

bool initGraphics(Graphics& graphics);

void destroyGraphics(Graphics& graphics);