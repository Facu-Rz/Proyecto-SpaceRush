#pragma once
#include "systems/collisions.hpp"

ColissionResult playerVsProjectile(Entity& player, Entity& projectile);

ColissionResult projectileVsProjectile(Entity& projectileA, Entity& projectileB);