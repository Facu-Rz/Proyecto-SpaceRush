#pragma once
#include "utilities/vector2D.hpp"
#include "entities/entity.hpp"
#include <SDL.h>
#include <vector>

enum class ProjectileType {
    Small,
    Medium,
    Big
};

struct Projectile : public Entity{
    ProjectileType type;
    int spawnId;

    int getRank() const;
};

Projectile createProjectile(ProjectileType type);

void updateProjectile(std::vector<Projectile>& projectiles, float deltaTime);

void renderProjectile(std::vector<Projectile>& projectiles, SDL_Renderer* renderer);