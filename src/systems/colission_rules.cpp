#include "systems/colission_rules.hpp"
#include "entities/entity.hpp"
#include "entities/projectile.hpp"

ColissionResult playerVsProjectile(Entity& player, Entity& projectile){
    (void)player;
    (void)projectile;

    return {true, true};
}

ColissionResult projectileVsProjectile(Entity& projectileA, Entity& projectileB){
    Projectile& p1 = static_cast<Projectile&>(projectileA);
    Projectile& p2 = static_cast<Projectile&>(projectileB);

    if (p1.getRank() > p2.getRank()) return {false, true};
    else if (p1.getRank() < p2.getRank()) return {true, false};
    else {
        if (p1.spawnId < p2.spawnId) return {false, true};
        else return {true, false};
    }
}