#include "systems/spawn_projectile.hpp"
#include "entities/projectile.hpp"
#include "utilities/random.hpp"
#include "game/game.hpp"
#include "game/game_config.hpp"
#include <iostream>
#include <vector>

ProjectileType randomType(){
    std::vector<ProjectileType> types= {ProjectileType::Big, ProjectileType::Medium, ProjectileType::Small};
    return types[randomInt(0, types.size() - 1)];
}

void projectileSpawnSystem(std::vector<Projectile>& projectiles, Spawner& projectileSpawner, float deltaTime){
    projectileSpawner.timer += deltaTime;

    while (projectileSpawner.timer >= projectileSpawner.interval) {
        projectiles.push_back(spawnProjectile());
        projectileSpawner.timer -= projectileSpawner.interval;
    }
}

Projectile spawnProjectile(){
    ProjectileType type= randomType();

    Projectile projectile= createProjectile(type);

    projectile.position.x= randomFloat(0, GameConfig::WorldWidth - projectile.rectProjectile.w);
    projectile.position.y= - projectile.rectProjectile.h;

    projectile.rectProjectile.x= (int)projectile.position.x;
    projectile.rectProjectile.y= (int)projectile.position.y;

    return projectile;
}