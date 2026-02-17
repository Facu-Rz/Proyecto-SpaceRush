#pragma once
#include "platform/sdl/graphics.hpp"
#include "core/layout.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

struct TextProperties {
    TTF_Font* font;
    SDL_Color color;
    layoutAxis x;
    layoutAxis y;
};

void renderScore(const Graphics& graphics, float score);

void updateScore(float& score, float deltaTime);

void renderText(const Graphics& graphics, const std::string& text, TextProperties properties);

void renderGOBackground(SDL_Renderer* renderer);

void renderGameOver(const Graphics& graphics, float finalScore);

