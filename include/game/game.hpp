#pragma once
#include "core/time.hpp"
#include "entities/player.hpp"
#include "entities/projectile.hpp"
#include <vector>

enum class GameState {
    Playing,
    GameOver,
};

struct Game {
    GameState gameState;
    GameClock gameClock;

    float score;
    const float SCORE_RATE;

    Player player;
    std::vector<Projectile> projectiles;


    Game():
        gameState(GameState::Playing),
        SCORE_RATE(10.0f),
        score(0.0f)
    {
        gameClock.reset();
    }
};

void resetGame(Game& game);