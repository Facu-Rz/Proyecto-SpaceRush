#include "game/game.hpp"

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