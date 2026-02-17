#pragma once
#include "utilities/vector2D.hpp"

struct InputState {
    Vector2D movement; 
};

struct InputEvent{
    bool quit = false;
    bool reset = false;
};

InputState getInputState();

InputEvent pollInputEvent();