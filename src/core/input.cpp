#include "core/input.hpp"
#include "debug/debug_state.hpp"
#include "debug/debug_tools.hpp"
#include "utilities/vector2D.hpp"
#include <SDL.h>

InputState getInputState(){
    InputState state{};

    SDL_PumpEvents();
    const Uint8* playerKeys= SDL_GetKeyboardState(NULL);

    state.movement= {0.0f, 0.0f};

    state.movement.x= (playerKeys[SDL_SCANCODE_RIGHT] ? 1.0f : 0.0f) -
    (playerKeys[SDL_SCANCODE_LEFT] ? 1.0f : 0.0f);

    state.movement.y= (playerKeys[SDL_SCANCODE_DOWN] ? 1.0f : 0.0f) -
    (playerKeys[SDL_SCANCODE_UP] ? 1.0f : 0.0f);

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

        #ifdef DEBUG_MODE
            handleDebugInput(event);
            #endif
    }

    return events;
}