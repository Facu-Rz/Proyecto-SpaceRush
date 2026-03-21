#pragma once
#include <SDL.h>

#ifdef DEBUG_MODE
void renderDebugVisual(SDL_Renderer* renderer);

void showGrid(SDL_Renderer* renderer, int xDiv, int yDiv);

void showObjectsBounds(SDL_Renderer* renderer, SDL_Rect& objectRect);

SDL_Rect getSectionRect();

void applyAlign(SDL_Rect& section);

void applyMargin(SDL_Rect& section);

void showSection(SDL_Renderer* renderer);

int alignToIndex(Align align);
#endif