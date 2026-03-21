#pragma once
#include "core/layout.hpp"
#include "debug/debug_state.hpp"
#include <SDL_ttf.h>
#include <string>

struct Graphics;

struct TextProperties {
    TTF_Font* font;
    SDL_Color color;
    LayoutAxis x;
    LayoutAxis y;
};

void renderScore(const Graphics& graphics, float score);

void updateScore(float& score, float deltaTime);

void renderText(const Graphics& graphics, const std::string& text, TextProperties properties);

void renderGOBackground(const Graphics& graphics);

void renderGameOver(const Graphics& graphics, float finalScore);

#ifdef DEBUG_MODE
void renderDebugUi(const Graphics& graphics, DebugData data);

void renderDebugHeader(const Graphics& graphics);

void renderDebugModeInfo(const Graphics& graphics, DebugData data);

void renderLayoutInfo(const Graphics& graphics);

void renderSpawnRateInfo(const Graphics& graphics, DebugData data);

std::string toString(DebugMode mode);

std::string toString(LayoutMode mode);

std::string toString(Align align);
#endif