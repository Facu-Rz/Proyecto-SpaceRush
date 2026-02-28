#pragma once
#include "core/time.hpp"
#include "entities/player.hpp"
#include "entities/projectile.hpp"
#include "systems/spawn_projectile.hpp"
#include <vector>

enum class GameState {
    Playing,
    GameOver,
};

struct Game {
    bool running = true;

    GameState gameState;
    GameClock gameClock;
    SpawnType spawnType;

    float score;
    static constexpr float SCORE_RATE = 10.0f;

    Player player;
    std::vector<Projectile> projectiles;


    Game():
        gameState(GameState::Playing),
        score(0.0f),
        player(createPlayer())
    {
        gameClock.reset();
    }
};

void resetGame(Game& game);

void gameOverEvents(SDL_Event& event, Game& game);