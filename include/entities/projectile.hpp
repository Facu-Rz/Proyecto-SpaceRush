#pragma once
#include "utilities/vector2D.hpp"
#include "entities/player.hpp"
#include <SDL.h>
#include <vector>

enum class ProjectileType {
    Small,
    Medium,
    Big
};

struct Projectile {
    SDL_Rect rectProjectile;

    Vector2D position;
    Vector2D direction;
    float speed;

    Uint32 firstTimeSpawn;
    Uint32 liveTime;
    bool alive;
    ProjectileType type;
};

Projectile createProjectile(ProjectileType type);

void updateProjectile(std::vector<Projectile>& projectiles, Player& player, float deltaTime);

void renderProjectile(std::vector<Projectile>& projectiles, SDL_Renderer* renderer);