#include "entities/projectile.hpp"
#include "entities/player.hpp"
#include "utilities/vector2D.hpp"
#include "systems/collisions.hpp"
#include <SDL.h>
#include <vector>

Projectile createProjectile(ProjectileType type){
    Projectile projectile{};

    projectile.type = type;

    switch (type){
        case ProjectileType::Small:
            projectile.collider.h=16;
            projectile.collider.w=16;
            projectile.speed= 375.0f;
            projectile.alive= true;
            projectile.layer= ColissionLayer::Projectile;
            break;

        case ProjectileType::Medium:
            projectile.collider.h=40;
            projectile.collider.w=40;
            projectile.speed= 275.0f;
            projectile.alive=true;
            projectile.layer= ColissionLayer::Projectile;
            break;

        case ProjectileType::Big:
            projectile.collider.h=100;
            projectile.collider.w=100;
            projectile.speed= 175.0f;
            projectile.alive=true;
            projectile.layer= ColissionLayer::Projectile;
            break;
    }

    return projectile;
}

void updateProjectile(std::vector<Projectile>& projectiles, float deltaTime){
    for (auto& projectile : projectiles){
        if (!projectile.alive) continue;

        projectile.position.y += projectile.speed * deltaTime;
        projectile.collider.y= (int)projectile.position.y;
    }
}

void renderProjectile(std::vector<Projectile>& projectiles, SDL_Renderer* renderer){
    for (auto& projectile : projectiles){
        if(!projectile.alive) continue;

        switch (projectile.type){
            
            case ProjectileType::Small:
                SDL_SetRenderDrawColor(renderer, 76, 0, 153, 255);
                break;

            case ProjectileType::Medium:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                break;

            case ProjectileType::Big:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                break;
        }

        SDL_RenderFillRect(renderer, &projectile.collider);
    }
}

int Projectile::getRank() const {
    switch (type){
        case ProjectileType::Small: return 1;
        case ProjectileType::Medium: return 2;
        case ProjectileType::Big: return 3;
    }

    return 0;
}