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
            projectile.rectProjectile.h=16;
            projectile.rectProjectile.w=16;
            projectile.speed= 375.0f;
            projectile.alive= true;
            break;

        case ProjectileType::Medium:
            projectile.rectProjectile.h=40;
            projectile.rectProjectile.w=40;
            projectile.speed= 275.0f;
            projectile.alive=true;
            break;

        case ProjectileType::Big:
            projectile.rectProjectile.h=100;
            projectile.rectProjectile.w=100;
            projectile.speed= 175.0f;
            projectile.alive=true;
            break;
    }

    return projectile;
}

void updateProjectile(std::vector<Projectile>& projectiles, Player& player, float deltaTime){
    for (auto& projectile : projectiles){
        if (!projectile.alive) continue;

        projectile.position.y += projectile.speed * deltaTime;
        projectile.rectProjectile.y= (int)projectile.position.y;

        checkProjectileDeath(projectile, player);
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

        SDL_RenderFillRect(renderer, &projectile.rectProjectile);
    }
}