#include "core/input.hpp"
#include "core/project_path.hpp"
#include "core/time.hpp"
#include "core/ui/ui.hpp"
#include "entities/player.hpp"
#include "entities/projectile.hpp"
#include "platform/sdl/graphics.hpp"
#include "platform/sdl/init.hpp"
#include "game/game.hpp"
#include "debug/debug_visual.hpp"
#include "systems/collisions.hpp"
#include "systems/colission_rules.hpp"
#include "systems/spawn_projectile.hpp"
#include "utilities/vector2D.hpp"
#include "utilities/random.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <random>
using namespace std;


int main(int argc, char* argv[]){
    (void)argc;
    (void)argv;

    ProjectPaths::initialize();
    
    if (!initPlatform()){
        return 1;
    }

    Graphics graphics;

    if(!initGraphics(graphics)){
        destroyGraphics(graphics);
        quitPlatform();
        return 1;
    }

    Game game;
    game.player = createPlayer();
    ColissionSystem colissionSystem;
    
    colissionSystem.registerRule(ColissionLayer::Player, ColissionLayer::Projectile, playerVsProjectile);
    colissionSystem.registerRule(ColissionLayer::Projectile, ColissionLayer::Projectile, projectileVsProjectile);

    float finalScore= 0.0f;

    #ifdef DEBUG_MODE
    cout << "Debug mode activo" << endl;
    #endif

    auto& player = game.player;
    auto& projectiles = game.projectiles;
    auto& deltaTime = game.gameClock.deltaTime;

    while (game.running){
        game.gameClock.update();
        
        InputEvent events= pollInputEvent();

        if (events.quit) game.running = false;

        if (events.reset && game.gameState == GameState::GameOver) {
            resetGame(game);
        }

        //Limpio la pantalla con color de fondo (Sistema RGB)
        SDL_SetRenderDrawColor(graphics.renderer, 91, 91, 91, 255);
        SDL_RenderClear(graphics.renderer);

        #ifdef DEBUG_MODE
        DebugData data = game.getDebugData();
        #endif

        if (game.gameState == GameState::Playing){
            game.gameClock.playingTime += deltaTime;

            InputState state= getInputState();

            projectileSpawnSystem(projectiles, game.spawnType.projectileSpawner, deltaTime);

            updatePlayer(player, deltaTime, state);

            updateProjectile(projectiles, deltaTime);

            std::vector<Entity*> collidable;

            collidable.push_back(&player);

            for (auto& projectile:projectiles) collidable.push_back(&projectile);

            colissionSystem.detectColissions(collidable);

            cleanUpProjectiles(projectiles);
            
            renderPlayer(player, graphics.renderer);
            
            renderProjectile(projectiles, graphics.renderer);

            updateScore(game.score, deltaTime);

            renderScore(graphics, game.score);
        }

        if(!game.player.alive) game.gameState=GameState::GameOver;

        if (game.gameState == GameState::GameOver){
            finalScore= game.score;
            renderGameOver(graphics, finalScore);
        }

        #ifdef DEBUG_MODE
        renderDebugVisual(graphics.renderer);
        renderDebugUi(graphics, data);
        #endif
        SDL_RenderPresent(graphics.renderer);
    }
    destroyGraphics(graphics);
    quitPlatform();

    return 0;
}