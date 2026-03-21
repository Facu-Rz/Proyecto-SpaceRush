#include "systems/spawn_projectile.hpp"
#include "entities/projectile.hpp"
#include "utilities/random.hpp"
#include "game/game.hpp"
#include "debug/debug_tools.hpp"
#include "game/game_config.hpp"
#include <vector>

ProjectileType randomType(){
    std::vector<ProjectileType> types= {ProjectileType::Big, ProjectileType::Medium, ProjectileType::Small};
    return types[randomInt(0, types.size() - 1)];
}

void projectileSpawnSystem(std::vector<Projectile>& projectiles, Spawner& projectileSpawner, float deltaTime){
    #ifdef DEBUG_MODE
    if (debug.disableProjectileSpawn) return;
    modSpawnRate(debug, projectileSpawner);
    #endif

    float interval = 1.0f / projectileSpawner.spawnRate;
    projectileSpawner.timer += deltaTime;

    while (projectileSpawner.timer >= interval) {
        Projectile candidate= spawnProjectile();

        if (isPositionFree(candidate.collider, projectiles)) projectiles.push_back(std::move(candidate));
        projectileSpawner.timer -= interval;
    }
}

Projectile spawnProjectile(){
    ProjectileType type= randomType();

    Projectile projectile= createProjectile(type);

    projectile.position.x= randomFloat(0, GameConfig::WorldWidth - projectile.collider.w);
    projectile.position.y= - projectile.collider.h;

    projectile.collider.x= (int)projectile.position.x;
    projectile.collider.y= (int)projectile.position.y;

    static int nextId= 0;
    projectile.spawnId= nextId++;

    return projectile;
}

bool isPositionFree(const SDL_Rect& candidate, const std::vector<Projectile>& projectiles){
    for (const auto& projectile : projectiles) {
        if (SDL_HasIntersection(&candidate, &projectile.collider)) return false;
    }

    return true;
}