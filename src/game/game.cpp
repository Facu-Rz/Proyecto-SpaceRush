#include "game/game.hpp"

void resetGame(Game& game){
    game.gameState= GameState::Playing;
    game.gameClock.reset();

    game.score= 0.0f;

    game.player= createPlayer();
    game.projectiles.clear();
}