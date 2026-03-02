#pragma once
#include "utilities/vector2D.hpp"
#include <SDL.h>

enum class ColissionLayer;

struct Entity {
    SDL_Rect collider;
    Vector2D position;
    Vector2D direction;
    float speed;
    bool alive = true;
    ColissionLayer layer;

    void markForDestroy(){
        alive = false;
    }

    virtual ~Entity() = default;
};
