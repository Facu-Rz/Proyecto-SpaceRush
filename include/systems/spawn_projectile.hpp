#pragma once
#include "entities/projectile.hpp"
#include <SDL.h>
#include <vector>

struct Game;

struct Spawner {
    float timer=0.0f;
    float interval;

    Spawner(float interval)
        : interval(interval) {}
};

struct SpawnType {
    Spawner projectileSpawner;

    SpawnType()
        : projectileSpawner(0.25f) {}
};

ProjectileType randomType();

void projectileSpawnSystem(std::vector<Projectile>& projectiles, Spawner& projectileSpawner, float deltaTime);

Projectile spawnProjectile();