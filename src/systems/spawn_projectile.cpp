#include "systems/spawn_projectile.hpp"
#include "entities/projectile.hpp"
#include "utilities/random.hpp"
#include  "game/game.hpp"
#include <iostream>
#include <vector>

ProjectileType randomType(){
    std::vector<ProjectileType> types= {ProjectileType::Big, ProjectileType::Medium, ProjectileType::Small};
    return types[randomInt(0, types.size() - 1)];
}

void projectileSpawnSystem(Uint32 appTime ,std::vector<Projectile>& projectiles, const Uint32 intervalSpawn){
    static float firstSpawn= true;
    static Uint32 lastSpawn= 0;

    if (firstSpawn || appTime - lastSpawn >= intervalSpawn){
        spawnProjectile(projectiles);
        lastSpawn= appTime;
        firstSpawn= false;
    }
    
    /*game.projectileSpawnTimer += game.gameClock.deltaTime;

    if (game.projectileSpawnTimer >= intervalSpawn) {
        spawnProjectile(projectiles);
        game.projectileSpawnTimer -= intervalSpawn;
    }*/
}

void spawnProjectile(std::vector<Projectile>& projectiles){
    ProjectileType type= randomType();

    Projectile projectile= createProjectile(type);

    projectile.rectProjectile.x= randomInt(0, 800 - projectile.rectProjectile.w);
    projectile.rectProjectile.y= -10;

    projectiles.push_back(projectile);
}