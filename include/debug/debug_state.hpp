#pragma once
#include "core/layout.hpp"
#include <SDL.h>

#ifdef DEBUG_MODE
enum class DebugMode {
    None,
    SpawnRate,
    LayoutTools
};

enum class LayoutMode {
    None,
    Grid,
    Navigator
};

enum class Axis {
    X,
    Y
};

struct DebugData {
    float spawnRate;
    float time;
    int activeProjectile;
    int projectileCapacity;
};

struct SectionNavigator {
    SDL_Rect section;
    
    int sectionX = 0;
    int sectionY = 0;

    Align alignX = Align::None;
    Align alignY = Align::None;

    int marginX = 0;
    int marginY = 0;
    int magnitude = 5;
};

struct RectGhost {
    SDL_Rect rect;
    bool active = false;
};

struct DebugState {
    bool disablePlayerColission = false;
    bool disableProjectileSpawn = false;
    bool disableBounds = false;
    bool pause = false;

    bool showObjectsBounds = false;
    bool showGrid = false;
    bool showSection = false;

    bool increment = false;
    bool decrement = false;
    float rate = 0.5f;

    DebugMode mode = DebugMode::None;
    LayoutMode layoutMode = LayoutMode::None;
    Axis axis = Axis::X;

    SectionNavigator navigator;
    RectGhost ghost;

    int gridDivX = 3;
    int gridDivY = 3;
};

extern DebugState debug;
#endif