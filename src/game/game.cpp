#include "game/game.hpp"

#ifdef DEBUG_MODE
DebugData Game::getDebugData() const {
    DebugData data;

    data.spawnRate = spawnType.projectileSpawner.spawnRate;
    data.time = gameClock.globalTime;
    data.activeProjectile = projectiles.size();
    data.projectileCapacity = projectiles.capacity();

    return data;
}
#endif

void resetGame(Game& game){
    game.gameState= GameState::Playing;
    game.gameClock.reset();

    game.spawnType.projectileSpawner.timer= 0.0f;

    game.score= 0.0f;

    game.player= createPlayer();
    game.projectiles.clear();
}

void gameOverEvents(SDL_Event& event, Game& game){
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
                resetGame(game);
            }
}