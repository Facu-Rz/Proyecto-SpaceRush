#pragma once
#include "entities/entity.hpp"
#include <vector>

enum class ColissionLayer {
    Player,
    Projectile
};

struct ColissionResult {
    bool destroyA;
    bool destroyB;
};

struct ColissionRule {
    ColissionLayer layerA;
    ColissionLayer layerB;
    ColissionResult (*ruleFunc)(Entity&, Entity&);
};

class ColissionSystem {
    public: 
        void registerRule(ColissionLayer a, ColissionLayer b, ColissionResult(*ruleFunc)(Entity&, Entity&));

        void detectColissions(std::vector<Entity*>& entities);

    private:
        std::vector<ColissionRule> rules;

        void resolveColission(Entity& a, Entity& b);
};