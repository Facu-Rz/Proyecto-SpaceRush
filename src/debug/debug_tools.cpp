#include "debug/debug_state.hpp"
#include "debug/debug_tools.hpp"
#include "debug/debug_visual.hpp"
#include "systems/spawn_projectile.hpp"
#include "core/layout.hpp"
#include <iostream>
#include <SDL.h>

#ifdef DEBUG_MODE
DebugState debug;

void handleDebugInput(const SDL_Event& event){
    if (event.type != SDL_KEYDOWN || event.key.repeat) return;

    switch (event.key.keysym.sym) {
        case SDLK_ESCAPE: handleEscape(); return;

        case SDLK_F4: debug.mode = DebugMode::SpawnRate; break;
        case SDLK_F5: 
        if (debug.mode != DebugMode::LayoutTools) enableLayoutDebugRender();
        debug.mode = DebugMode::LayoutTools; break;

        case SDLK_p: debug.pause = !debug.pause; break;
    }

    switch (debug.mode){
        case DebugMode::None: handleGameplayInput(event); break;
        case DebugMode::SpawnRate: handleSpawnRateInput(event); break;
        case DebugMode::LayoutTools: handleLayoutToolsInput(event); break;
    }
}

void handleEscape() {
    if (debug.mode == DebugMode::LayoutTools) {
        if (debug.layoutMode != LayoutMode::None) {
        debug.layoutMode = LayoutMode::None;
        return;
        }
    }

    if (debug.layoutMode == LayoutMode::None) {
        disableLayoutDebugRender();
        debug.mode = DebugMode::None;
        return;
    }

    if (debug.mode == DebugMode::SpawnRate) {
        debug.mode = DebugMode::None;
        return;
    }
}

void handleGameplayInput(const SDL_Event& event){
    switch (event.key.keysym.sym) {
        case SDLK_F1: debug.disablePlayerColission = !debug.disablePlayerColission; break;
        case SDLK_F2: debug.disableProjectileSpawn = !debug.disableProjectileSpawn; break;
        case SDLK_F3: debug.disableBounds = !debug.disableBounds; break;
    }
}

void handleSpawnRateInput(const SDL_Event& event){
    if (event.key.keysym.sym == SDLK_KP_PLUS) debug.increment = true;
    if (event.key.keysym.sym == SDLK_KP_MINUS) debug.decrement = true;
    if (event.key.keysym.sym == SDLK_TAB) debug.rate = cycleRate(debug.rate);
}

void modSpawnRate(DebugState& debug, Spawner& spawner){
    if (debug.increment) spawner.spawnRate += debug.rate;
    if (debug.decrement) spawner.spawnRate -= debug.rate;

    debug.increment = false;
    debug.decrement = false;

    spawner.spawnRate = std::clamp(spawner.spawnRate, 0.5f, 25.0f);
}

float cycleRate(float rate){
    if (rate == 0.5f) return 1.0f;
    if (rate == 1.0f) return 5.0f;
    return 0.5f;
}

void handleLayoutToolsInput(const SDL_Event& event){
    switch (event.key.keysym.sym) {
        case SDLK_F1: debug.showGrid = !debug.showGrid; break;
        case SDLK_F2: debug.showObjectsBounds = !debug.showObjectsBounds; break;
        case SDLK_F3: debug.showSection = !debug.showSection; break;

        case SDLK_g: debug.layoutMode = LayoutMode::Grid; break;
        case SDLK_n: debug.layoutMode = LayoutMode::Navigator; break;

        case SDLK_BACKSPACE: resetLayoutDebugConfig(debug); break;
    }

    switch (debug.layoutMode) {
        case LayoutMode::Grid: handleGridInput(event); break;
        case LayoutMode::Navigator: handleNavigatorInput(event); break;
        default: break;
    }

    clampNavigatorSection();
}

void handleGridInput(const SDL_Event& event){
    if (event.key.keysym.sym == SDLK_e) {
        debug.axis = (debug.axis == Axis::X) ? Axis::Y : Axis::X;
        return;
    }

    int step = getKeyStep(event, 1);
    if (step == 0) return;

    applyAxisStep(step, debug.gridDivX, debug.gridDivY);

    debug.gridDivX = std::clamp(debug.gridDivX, 1, 12);
    debug.gridDivY = std::clamp(debug.gridDivY, 1, 12);
}

void handleNavigatorInput(const SDL_Event& event){
    if (event.key.keysym.sym == SDLK_RETURN) {
        if (!debug.ghost.active) {
            debug.ghost.rect = getSectionRect();
            debug.ghost.active = true;
        } else {
            debug.ghost.active = false;
        }
    }

    handleSectionMovement(event);
    handleAlignInput(event);
    handleMarginInput(event);
}

void handleSectionMovement(const SDL_Event& event){
    switch (event.key.keysym.sym) {
        case SDLK_w: debug.navigator.sectionY--; break;
        case SDLK_s: debug.navigator.sectionY++; break;
        case SDLK_a: debug.navigator.sectionX--; break;
        case SDLK_d: debug.navigator.sectionX++; break;
    }
}

Align cycleAlign(Align align){
    switch (align) {
        case Align::None: return Align::Start; 
        case Align::Start: return Align::Center;
        case Align::Center: return Align::End;
        case Align::End: return Align::None;
    }

    return Align::None;
}

void handleAlignInput(const SDL_Event& event){
    if (event.key.keysym.sym != SDLK_q) return;

    if (debug.axis == Axis::X) debug.navigator.alignX = cycleAlign(debug.navigator.alignX);
    else debug.navigator.alignY = cycleAlign(debug.navigator.alignY);
}

void handleMarginInput(const SDL_Event& event){
    if (event.key.keysym.sym == SDLK_e) {
        debug.axis = (debug.axis == Axis::X) ? Axis::Y : Axis::X;
        return;
    }
    if (event.key.keysym.sym == SDLK_TAB) 
    debug.navigator.magnitude = cycleMargin(debug.navigator.magnitude);

    int step = getKeyStep(event, debug.navigator.magnitude);
    if (step == 0) return;

    if (debug.axis == Axis::Y) step = -step;

    applyAxisStep(step, debug.navigator.marginX, debug.navigator.marginY);
}

int cycleMargin(int magnitude){
    if (magnitude == 1) return 5;
    if (magnitude == 5) return 20;
    return 1;
}

void resetLayoutDebugConfig(DebugState& debug){
    debug.axis = Axis::X;

    debug.gridDivX = 3;
    debug.gridDivY = 3;

    debug.navigator.sectionX = 0;
    debug.navigator.sectionY = 0;

    debug.navigator.alignX = Align::None;
    debug.navigator.alignY = Align::None;

    debug.navigator.marginX = 0;
    debug.navigator.marginY = 0;
    debug.navigator.magnitude = 5;
}

void enableLayoutDebugRender(){
    debug.showGrid = true;
    debug.showObjectsBounds = true;
    debug.showSection = true;
}

void disableLayoutDebugRender(){
    debug.showGrid = false;
    debug.showObjectsBounds = false;
    debug.showSection = false;
}

void clampNavigatorSection(){
    debug.navigator.sectionX = std::clamp(debug.navigator.sectionX, 0, debug.gridDivX - 1);
    debug.navigator.sectionY = std::clamp(debug.navigator.sectionY, 0, debug.gridDivY - 1);
}

void applyAxisStep(int step, int& valueX, int& valueY){
    if (debug.axis == Axis::X) valueX += step;
    else valueY += step;
}

int getKeyStep(const SDL_Event& event, int magnitude){
    if (event.key.keysym.sym == SDLK_KP_PLUS) return magnitude;
    if (event.key.keysym.sym == SDLK_KP_MINUS) return -magnitude;
    return 0;
}
#endif



