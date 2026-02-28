#pragma once
#include "core/layout.hpp"
#include <SDL_ttf.h>
#include <string>

struct Graphics;

struct TextProperties {
    TTF_Font* font;
    SDL_Color color;
    layoutAxis x;
    layoutAxis y;
};

void renderScore(const Graphics& graphics, float score);

void updateScore(float& score, float deltaTime);

void renderText(const Graphics& graphics, const std::string& text, TextProperties properties);

void renderGOBackground(const Graphics& graphics);

void renderGameOver(const Graphics& graphics, float finalScore);

