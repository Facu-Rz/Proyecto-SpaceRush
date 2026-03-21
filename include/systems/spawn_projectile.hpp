#pragma once
#include "entities/projectile.hpp"
#include <SDL.h>
#include <vector>

struct Game;

struct Spawner {
    float timer=0.0f;
    float spawnRate;
    
    Spawner(int rate)
        : spawnRate(rate) {}
};

struct SpawnType {
    Spawner projectileSpawner;

    SpawnType()
        : projectileSpawner(4.0f) {}
};

ProjectileType randomType();

void projectileSpawnSystem(std::vector<Projectile>& projectiles, Spawner& projectileSpawner, float deltaTime);

Projectile spawnProjectile();

bool isPositionFree(const SDL_Rect& candidate, const std::vector<Projectile>& projectiles);