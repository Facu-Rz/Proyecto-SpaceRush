#include "systems/collisions.hpp"
#include "entities/player.hpp"
#include "entities/projectile.hpp"

void checkProjectileDeath(Projectile& projectile, Player& player){
    if (projectile.rectProjectile.y > 600){
        projectile.alive= false;
    }

    if (SDL_HasIntersection(&projectile.rectProjectile, &player.rectPlayer)){
        projectile.alive= false;
        player.alive= false;
    }
}