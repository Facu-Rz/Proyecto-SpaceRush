#include "systems/collisions.hpp"
#include "entities/entity.hpp"
#include <vector>

/*void checkProjectileDeath(Projectile& projectile, Player& player){
    if (projectile.rectProjectile.y > 600){
        projectile.alive= false;
    }

    if (SDL_HasIntersection(&projectile.rectProjectile, &player.rectPlayer)){
        projectile.alive= false;
        player.alive= false;
    }
}*/

void ColissionSystem::registerRule(ColissionLayer a, ColissionLayer b, ColissionResult(*ruleFunc)(Entity&, Entity&)){
    rules.push_back({a, b, ruleFunc});
}

void ColissionSystem::detectColissions(std::vector<Entity*>& entities){
    for (size_t i = 0; i < entities.size(); ++i){
        for (size_t j = i + 1; j < entities.size(); j++){
            if (!entities[i]->alive || !entities[j]->alive) continue;

            if (SDL_HasIntersection(&entities[i]->collider, &entities[j]->collider)){
                resolveColission(*entities[i], *entities[j]);
            }
        }
    }
}

void ColissionSystem::resolveColission(Entity& a, Entity& b){
    for (auto& rule:rules){
        if ((rule.layerA == a.layer && rule.layerB == b.layer) ||
         (rule.layerA == b.layer && rule.layerB == a.layer)){
            ColissionResult result = rule.ruleFunc(a, b);

            if (result.destroyA) a.markForDestroy();
            if (result.destroyB) b.markForDestroy();

            return;
         }
    }
}