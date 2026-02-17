#include "core/input.hpp"
#include "utilities/vector2D.hpp"
#include <SDL.h>

InputState getInputState(){
    InputState state{};

    SDL_PumpEvents();
    const Uint8* playerKeys= SDL_GetKeyboardState(NULL);

    state.movement= {0.0f, 0.0f};

    if (playerKeys[SDL_SCANCODE_LEFT]) state.movement.x -= 1.0f;
    if (playerKeys[SDL_SCANCODE_RIGHT]) state.movement.x += 1.0f;
    if (playerKeys[SDL_SCANCODE_UP]) state.movement.y -= 1.0f;
    if (playerKeys[SDL_SCANCODE_DOWN]) state.movement.y += 1.0f;

    state.movement= normalize(state.movement);

    return state;
}

InputEvent pollInputEvent(){
    SDL_Event event;
    InputEvent events{};

    while(SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT) events.quit = true;

        if (event.type != SDL_KEYDOWN || event.key.repeat) continue;

        switch (event.key.keysym.sym) {
            case SDLK_r: events.reset = true; break;
        }
    }

    return events;
}