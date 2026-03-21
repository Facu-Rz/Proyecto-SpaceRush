#pragma once
#include "core/layout.hpp"
#include "systems/spawn_projectile.hpp"
#include <SDL.h>

#ifdef DEBUG_MODE
void handleDebugInput(const SDL_Event& event);

void handleEscape();

void handleGameplayInput(const SDL_Event& event);

void handleSpawnRateInput(const SDL_Event& event);

void modSpawnRate(DebugState& debug, Spawner& spawner);

float cycleRate(float rate);

void handleLayoutToolsInput(const SDL_Event& event);

void handleGridInput(const SDL_Event& event);

void handleNavigatorInput(const SDL_Event& event);

void handleSectionMovement(const SDL_Event& event);

Align cycleAlign(Align align);

void handleAlignInput(const SDL_Event& event);

void handleMarginInput(const SDL_Event& event);

int cycleMargin(int magnitude);

void resetLayoutDebugConfig(DebugState& debug);

void enableLayoutDebugRender();

void disableLayoutDebugRender();

void clampNavigatorSection();

void applyAxisStep(int step, int& valueX, int& valueY);

int getKeyStep(const SDL_Event& event, int magnitude);
#endif