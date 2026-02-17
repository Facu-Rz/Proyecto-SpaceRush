#pragma once
#include "entities/projectile.hpp"
#include "game/game.hpp"
#include <SDL.h>
#include <vector>

ProjectileType randomType();

void projectileSpawnSystem(Uint32 appTime, std::vector<Projectile>& projectiles, const Uint32 intervalSpawn);

void spawnProjectile(std::vector<Projectile>& projectiles);