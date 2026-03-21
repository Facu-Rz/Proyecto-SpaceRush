#include "debug/debug_state.hpp"
#include "debug/debug_visual.hpp"
#include "game/game_config.hpp"
#include <iostream>
#include <SDL.h>

#ifdef DEBUG_MODE
void renderDebugVisual(SDL_Renderer* renderer){
    if (debug.showGrid) showGrid(renderer, debug.gridDivX, debug.gridDivY);
    if (debug.showSection) showSection(renderer);
}

void showGrid(SDL_Renderer* renderer, int xDiv, int yDiv){
    float stepX = GameConfig::WorldWidth / xDiv;
    float stepY = GameConfig::WorldHeight / yDiv;

    int thickness = 3;

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 175);

    for (int i = 1; i < xDiv; i++){
        int x = (int)(stepX * i);
        SDL_Rect line = {x - thickness/2, 0, thickness, (int)GameConfig::WorldHeight};
        SDL_RenderFillRect(renderer, &line);
    }

    for (int i = 1; i < yDiv; i++){
        int y = (int)(stepY * i);
        SDL_Rect line = {0, y - thickness/2, (int)GameConfig::WorldWidth, thickness};
        SDL_RenderFillRect(renderer, &line);
    }
}

void showObjectsBounds(SDL_Renderer* renderer, SDL_Rect& objectRect){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &objectRect);
}

SDL_Rect getSectionRect(){
    int startX = (GameConfig::WorldWidth * debug.navigator.sectionX) / debug.gridDivX;
    int endX = (GameConfig::WorldWidth * (debug.navigator.sectionX + 1)) / debug.gridDivX;

    int startY = (GameConfig::WorldHeight * debug.navigator.sectionY) / debug.gridDivY;
    int endY = (GameConfig::WorldHeight * (debug.navigator.sectionY + 1)) / debug.gridDivY;

    auto& section = debug.navigator.section;

    section.x = startX;
    section.y = startY;
    section.w = endX - startX;
    section.h = endY - startY;

    applyAlign(section);
    applyMargin(section);

    return section;
}

void applyAlign(SDL_Rect& section){
    int subW = section.w / 3;
    int subH = section.h / 3;

    if (debug.navigator.alignX != Align::None) {
        int index = alignToIndex(debug.navigator.alignX);
        section.x += index * subW;
        section.w = subW;
    }

    if (debug.navigator.alignY != Align::None) {
        int index = alignToIndex(debug.navigator.alignY);
        section.y += index * subH;
        section.h = subH;
    }
}

void applyMargin(SDL_Rect& section){
    section.x += debug.navigator.marginX;
    section.y += debug.navigator.marginY;
}

void showSection(SDL_Renderer* renderer){
    SDL_Rect section = getSectionRect();

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 80);
    SDL_RenderFillRect(renderer, &section);

    if (debug.ghost.active) {
        SDL_SetRenderDrawColor(renderer, 44, 59, 145, 80);
        SDL_RenderFillRect(renderer, &debug.ghost.rect);
    }
}

int alignToIndex(Align align){
    switch (align) {
        case Align::Start: return 0;
        case Align::Center: return 1;
        case Align::End: return 2;
        default: return -1;
    }
}
#endif