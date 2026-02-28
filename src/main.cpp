#include "core/input.hpp"
#include "core/project_path.hpp"
#include "core/time.hpp"
#include "core/ui.hpp"
#include "entities/player.hpp"
#include "entities/projectile.hpp"
#include "platform/sdl/graphics.hpp"
#include "platform/sdl/init.hpp"
#include "game/game.hpp"
#include "systems/collisions.hpp"
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

    #ifdef DEBUG_MODE
    cout << "Debug mode activo\n";
    #endif

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

    #ifdef DEBUG_MODE
    Uint32 lastPrint= 0;
    Uint32 appTime = 0;
    const Uint32 intervalPrint= 1000;
    #endif

    float finalScore= 0.0f;

    auto& player = game.player;
    auto& projectiles = game.projectiles;
    auto& deltaTime = game.gameClock.deltaTime;

    while (game.running){
        InputEvent events= pollInputEvent();

        if (events.quit) game.running = false;

        if (events.reset && game.gameState == GameState::GameOver) {
            resetGame(game);
        }

        //Limpio la pantalla con color de fondo (Sistema RGB)
        SDL_SetRenderDrawColor(graphics.renderer, 91, 91, 91, 255);
        SDL_RenderClear(graphics.renderer);

        if (game.gameState == GameState::Playing){
            game.gameClock.update();

            #ifdef DEBUG_MODE
            appTime= SDL_GetTicks();
            if (appTime - lastPrint >= intervalPrint){
                cout << "Tiempo global: " << appTime / 1000 << "s" << endl;
                lastPrint += intervalPrint;
            }
            #endif

            InputState state= getInputState();

            updatePlayer(player, deltaTime, state);

            renderPlayer(player, graphics.renderer);
            
            projectileSpawnSystem(projectiles, game.spawnType.projectileSpawner, deltaTime);

            updateProjectile(projectiles, player, deltaTime);
            
            renderProjectile(projectiles, graphics.renderer);

            updateScore(game.score, deltaTime);

            renderScore(graphics, game.score);
        }

        if(!game.player.alive) game.gameState=GameState::GameOver;

        if (game.gameState == GameState::GameOver){
            finalScore= game.score;
            renderGameOver(graphics, finalScore);
        }

        //Muestro el contenido en pantalla
        SDL_RenderPresent(graphics.renderer);
    }
    destroyGraphics(graphics);
    quitPlatform();

    return 0;
}