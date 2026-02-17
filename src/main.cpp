// ====================================
//           Includes y Definiciones
// ====================================


#include "platform/sdl/init.hpp"
#include "platform/sdl/graphics.hpp"
#include "utilities/vector2D.hpp"
#include "utilities/random.hpp"
#include "core/time.hpp"
#include "core/input.hpp"
#include "entities/player.hpp"
#include "entities/projectile.hpp"
#include "systems/collisions.hpp"
#include "systems/spawn_projectile.hpp"
#include "core/ui.hpp"
#include "game/game.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <random>
using namespace std;


// ====================================
//  Estructuras, Enums y Tipos de datos
// ====================================


/*enum class GameState {
    Playing,
    GameOver,
};*/

/*enum class ProjectileType {
    Small,
    Medium,
    Big
};*/

/*struct GameClock {
    Uint32 lastTime = 0;
    float deltaTime = 0.0f;
    float playingTime = 0.0f;

    void reset(){
        lastTime = SDL_GetTicks();
        deltaTime = 0.0f;
        playingTime = 0.0f;
    }

    void update(){
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        playingTime += deltaTime;
        lastTime = currentTime; 
    }
};*/

/*struct Vector2D {
    float x;
    float y;
};*/

/*struct Player {
    SDL_Rect rectPlayer;

    Vector2D position;
    Vector2D direction;
    float speed;

    bool alive;
};*/

/*struct Projectile {
    SDL_Rect rectProjectile;

    Vector2D position;
    Vector2D direction;
    float speed;

    Uint32 firstTimeSpawn;
    Uint32 liveTime;
    bool alive;
    ProjectileType type;
};*/


// ====================================
//           Variables globales
// ====================================


//const int SCREEN_WIDTH = 800;
//const int SCREEN_HEIGHT = 600;
//const float SCORE_RATE = 10.0f;
Uint32 appTime = 0;

//GameState gameState = GameState::Playing;
//GameClock gameClock;


// ====================================
//          Funciones de utilidad
// ====================================


/*static mt19937& getGenerator();

int randomInt(int min, int max);*/

/*Vector2D normalize(const Vector2D& vector);

Vector2D sumVector(const Vector2D& a, const Vector2D& b);

Vector2D subVector(const Vector2D& a, const Vector2D& b);

Vector2D multScalar(const Vector2D& vector, float scalar);*/


// ====================================
//           Creacion de entidades
// ====================================


//ProjectileType randomType();

//Projectile createProjectile(ProjectileType type);

//Player createPlayer();


// ====================================
//           Renderizado
// ====================================


//void renderProjectile(vector<Projectile>& projectiles, SDL_Renderer* renderer);

//void renderPlayer(Player& player, SDL_Renderer* renderer);

//void renderScore(SDL_Renderer* renderer, TTF_Font* fontScore, float score);


// ====================================
//           GAME OVER
// ====================================


//void renderGameOver(SDL_Renderer* renderer, TTF_Font* fontGameOver, TTF_Font* fontHint, float finalScore);

//void resetGame(Game& game);

void gameOverEvents(SDL_Event& event, Game& game);


// ====================================
//     Funciones a ordenar
// ====================================


//void projectileSpawnSystem(vector<Projectile>& projectiles, Uint32 currentTime, const Uint32 intervalSpawn);

//void spawnProjectile(vector<Projectile>& projectiles);

//void updateProjectile(vector<Projectile>& projectiles, Player& player, float deltaTime);

//void playerInputs(Player& player);

//void updatePlayer(Player& player, float deltaTime);

//void checkProjectileDeath(Projectile& projectile, Player& player);

//void updateScore(float& score, float deltaTime);


int main(int argc, char* argv[]){
    // ====================================
    //    Inicializacion de herramientas
    // ====================================

    
    if (!initPlatform()){
        return 1;
    }


    // ====================================
    //    Implementacion de herramientas
    // ====================================


    Graphics graphics;

    if(!initGraphics(graphics)){
        destroyGraphics(graphics);
        quitPlatform();
        return 1;
    }

    /*SDL_Window* window = SDL_CreateWindow("Space Rush",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    if(!window){
        cout << "Error al crear ventana: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    //Cargo fuentes de texto
    TTF_Font* fontScore = TTF_OpenFont("../assets/fonts/Pacifico.ttf", 24);
    TTF_Font* fontGameOver = TTF_OpenFont("../assets/fonts/Spectral/Spectral-Bold.ttf", 72);
    TTF_Font* fontHint = TTF_OpenFont("../assets/fonts/Spectral/Spectral-Medium.ttf", 28);

    if (!fontScore || !fontGameOver || !fontHint) {
        cout << "Error al cargar fuente: " << TTF_GetError() << endl;
    }

    //Inicializo render 
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (!renderer){
        SDL_Log("Error creando renderer: %s", SDL_GetError());
    }

    //Activo modo mezcla para interaccion de colores
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);*/


    // ====================================
    //           Variables locales
    // ====================================


    //vector<Projectile> projectiles;
    //Player player= createPlayer();
    Game game;
    game.player = createPlayer();

    //Implementacion del Loop principal (mostrar ventana)
    bool running = true;
    SDL_Event event;

    //Lapso de tiempo al imprimir el reloj
    Uint32 lastPrint= 0;
    const Uint32 intervalPrint= 1000;
    const float intervalSpawn= 250;   

    //Propiedades de puntuacion
    //float score= 0.0f;
    float finalScore= 0.0f;


    // ====================================
    //          Loop Principal
    // ====================================


    auto& player = game.player;
    auto& projectiles = game.projectiles;
    auto& deltaTime = game.gameClock.deltaTime;

    while (running){
        /*while (SDL_PollEvent(&event)){
            if (gameState == GameState::GameOver){
                gameOverEvents(event, projectiles, player, score);
            } 

            //if (event.type == SDL_QUIT) running = false;

            if (events.reset && gameState == GameState::GameOver) resetGame();
        }*/

        InputEvent events= pollInputEvent();

        if (events.quit) running = false;

        if (events.reset && game.gameState == GameState::GameOver) resetGame(game);

        //Limpio la pantalla con color de fondo (Sistema RGB)
        SDL_SetRenderDrawColor(graphics.renderer, 91, 91, 91, 255);
        SDL_RenderClear(graphics.renderer);

        if (game.gameState == GameState::Playing){
            appTime= SDL_GetTicks();
            game.gameClock.update();

            if (appTime - lastPrint >= intervalPrint){
                cout << "Tiempo global: " << appTime / 1000 << "s" << endl;
                lastPrint += intervalPrint;
            }

            InputState state= getInputState();

            //playerInputs(player);

            updatePlayer(player, deltaTime, state);

            renderPlayer(player, graphics.renderer);

            projectileSpawnSystem(appTime, projectiles, intervalSpawn);

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


    // ====================================
    //        Liberacion de recursos
    // ====================================

    
    destroyGraphics(graphics);
    quitPlatform();

    return 0;
}


// ====================================
//           Funciones de utilidad
// ====================================


/*static mt19937& getGenerator(){
    static mt19937 gen(random_device{}());
    return gen;
}

int randomInt(int min, int max){
    uniform_int_distribution<int> dist(min, max);
    return dist(getGenerator());
}*/

/*Vector2D normalize(const Vector2D& vector){
        float length= SDL_sqrt(vector.x*vector.x + vector.y*vector.y);
        if (length == 0.0f) {
            return {0.0f, 0.0f};
        } else return {vector.x / length, vector.y / length}; 
    }

Vector2D sumVector(const Vector2D& a, const Vector2D& b){
    return {a.x + b.x, a.y + b.y};
}

Vector2D subVector(const Vector2D& a, const Vector2D& b){
    return {a.x - b.x, a.y - b.y};
}

Vector2D multScalar(const Vector2D& vector, const float scalar){
    return {vector.x * scalar, vector.y * scalar};
}*/


// ====================================
//           Creacion de entidades
// ====================================


/*ProjectileType randomType(){
    vector<ProjectileType> types= {ProjectileType::Big, ProjectileType::Medium, ProjectileType::Small};
    return types[randomInt(0, types.size() - 1)];
}*/

/*Projectile createProjectile(ProjectileType type){
    Projectile projectile{};

    projectile.type = type;

    switch (type){
        case ProjectileType::Small:
            projectile.rectProjectile.h=16;
            projectile.rectProjectile.w=16;
            projectile.speed= 375.0f;
            projectile.alive= true;
            break;

        case ProjectileType::Medium:
            projectile.rectProjectile.h=40;
            projectile.rectProjectile.w=40;
            projectile.speed= 250.0f;
            projectile.alive=true;
            break;

        case ProjectileType::Big:
            projectile.rectProjectile.h=100;
            projectile.rectProjectile.w=100;
            projectile.speed= 125.0f;
            projectile.alive=true;
            break;
    }

    return projectile;
}*/

/*Player createPlayer(){
    Player player{};

    player.rectPlayer={300, 300, 50, 50};
    player.position={300.0f, 300.0f};
    player.direction={0.0f, 0.0f};
    player.speed= 312.0f;
    player.alive= true;

    return player;
}*/


// ====================================
//           Renderizado
// ====================================    


/*void renderPlayer(Player& player, SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    if(!player.alive){
        player.speed=0.0f;
        return;
    }
    SDL_RenderFillRect(renderer, &player.rectPlayer);
}*/

/*void renderProjectile(vector<Projectile>& projectiles, SDL_Renderer* renderer){
    for (auto& projectile : projectiles){
        if(!projectile.alive) continue;

        switch (projectile.type){
        case ProjectileType::Big:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            break;
        
        case ProjectileType::Medium:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            break;

        case ProjectileType::Small:
            SDL_SetRenderDrawColor(renderer, 76, 0, 153, 255);
            break;
        }

        SDL_RenderFillRect(renderer, &projectile.rectProjectile);
    }
}*/

/*void renderScore(SDL_Renderer* renderer, TTF_Font* font, float score){
    SDL_Color white= {255, 255, 255, 255};
    int screenScore= (int)score;
    string scoreText= "Score: " + to_string(screenScore);
    
    SDL_Surface* textSurface= TTF_RenderText_Blended(font, scoreText.c_str(), white);
    SDL_Texture* textTexture= SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
    
    textRect.x= SCREEN_WIDTH - textRect.w - 20;
    textRect.y= 20;


    SDL_FreeSurface(textSurface);

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
}*/


// ====================================
//           GAME OVER
// ====================================     


/*void renderGameOver(SDL_Renderer* renderer, TTF_Font* fontGameOver, TTF_Font* fontHint, float finalScore){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    SDL_Rect backGround= {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &backGround);

    SDL_Color gold= {255, 215, 0, 255};
    SDL_Color white= {255, 255, 255, 255};
    int screenFinalScore= (int)finalScore;

    string gameOverText= "GAME OVER";
    string finalScoreText= "Puntuacion final: " + to_string(screenFinalScore);
    string resetText= "Presione R para volver a jugar";

    SDL_Surface* gameOverSurface= TTF_RenderText_Blended(fontGameOver, gameOverText.c_str(), gold);
    SDL_Surface* finalScoreSurface= TTF_RenderText_Blended(fontHint, finalScoreText.c_str(), white);
    SDL_Surface* resetSurface= TTF_RenderText_Blended(fontHint, resetText.c_str(), white);

    SDL_Texture* gameOverTexture= SDL_CreateTextureFromSurface(renderer, gameOverSurface);
    SDL_Texture* finalScoreTexture= SDL_CreateTextureFromSurface(renderer, finalScoreSurface);
    SDL_Texture* resetTexture= SDL_CreateTextureFromSurface(renderer, resetSurface);

    SDL_Rect gameOverRect;
    SDL_QueryTexture(gameOverTexture, nullptr, nullptr, &gameOverRect.w, &gameOverRect.h);

    SDL_Rect finalScoreRect;
    SDL_QueryTexture(finalScoreTexture, nullptr, nullptr, &finalScoreRect.w, &finalScoreRect.h);

    SDL_Rect resetRect;
    SDL_QueryTexture(resetTexture, nullptr, nullptr, &resetRect.w, &resetRect.h);

    gameOverRect.x= (SCREEN_WIDTH - gameOverRect.w) / 2;
    gameOverRect.y= (SCREEN_HEIGHT - gameOverRect.h) / 3 - gameOverRect.h / 2; //Primer tercio

    finalScoreRect.x= (SCREEN_WIDTH - finalScoreRect.w) / 2;
    finalScoreRect.y = (SCREEN_HEIGHT * 2) / 3 - finalScoreRect.h / 2; //Tercer tercio

    resetRect.x= (SCREEN_WIDTH - resetRect.w) / 2;
    resetRect.y = (SCREEN_HEIGHT * 2) / 3 + resetRect.h / 2; //Tercer tercio

    SDL_FreeSurface(gameOverSurface);
    SDL_FreeSurface(finalScoreSurface);
    SDL_FreeSurface(resetSurface);

    SDL_RenderCopy(renderer, gameOverTexture, nullptr, &gameOverRect);
    SDL_RenderCopy(renderer, finalScoreTexture, nullptr, &finalScoreRect);
    SDL_RenderCopy(renderer, resetTexture, nullptr, &resetRect);
    SDL_DestroyTexture(gameOverTexture);
    SDL_DestroyTexture(finalScoreTexture);
    SDL_DestroyTexture(resetTexture);
}*/

/*void resetGame(Game& game){
    game.gameState= GameState::Playing;
    game.gameClock.reset();

    game.score= 0.0f;

    game.player= createPlayer();
    game.projectiles.clear();
}*/

void gameOverEvents(SDL_Event& event, Game& game){
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
                resetGame(game);
            }
}


// ====================================
//          Funciones a ordenar
// ====================================


/*void projectileSpawnSystem(vector<Projectile>& projectiles, Uint32 appTime, const Uint32 intervalSpawn){
    static float firstSpawn= true;
    static Uint32 lastSpawn= 0;

    if (firstSpawn || appTime - lastSpawn >= intervalSpawn){
                spawnProjectile(projectiles);
                lastSpawn= appTime;
                firstSpawn= false;
            }
}

void spawnProjectile(vector<Projectile>& projectiles){
    ProjectileType type= randomType();

    Projectile projectile= createProjectile(type);

    projectile.rectProjectile.x= randomInt(0, SCREEN_WIDTH - projectile.rectProjectile.w);
    projectile.rectProjectile.y= -10;

    projectiles.push_back(projectile);
}*/

/*void updateProjectile(vector<Projectile>& projectiles, Player& player, float deltaTime){
    for (auto& projectile : projectiles){
        if (!projectile.alive) continue;

        projectile.position.y += projectile.speed * deltaTime;
        projectile.rectProjectile.y= (int)projectile.position.y;

        checkProjectileDeath(projectile, player);
    }
}*/

/*void playerInputs(Player& player){
    SDL_PumpEvents();
    const Uint8* playerKeys= SDL_GetKeyboardState(NULL);

    player.direction= {0.0f, 0.0f};

    if (playerKeys[SDL_SCANCODE_LEFT]) player.direction.x -= 1.0f;
    if (playerKeys[SDL_SCANCODE_RIGHT]) player.direction.x += 1.0f;
    if (playerKeys[SDL_SCANCODE_UP]) player.direction.y -= 1.0f;
    if (playerKeys[SDL_SCANCODE_DOWN]) player.direction.y += 1.0f;

    player.direction= normalize(player.direction);
}*/

/*void updatePlayer(Player& player, float deltaTime){
    player.position.x += player.direction.x * player.speed * deltaTime;
    player.position.y += player.direction.y * player.speed * deltaTime;

    player.rectPlayer.x=(int)player.position.x;
    player.rectPlayer.y=(int)player.position.y;
}*/

/*void checkProjectileDeath(Projectile& projectile, Player& player){
    if (projectile.rectProjectile.y > SCREEN_HEIGHT){
        projectile.alive= false;
    }

    if (SDL_HasIntersection(&projectile.rectProjectile, &player.rectPlayer)){
        projectile.alive= false;
        player.alive= false;

        gameState= GameState::GameOver;
    }
}*/

/*void updateScore(float& score, float deltaTime){
    score += SCORE_RATE * deltaTime;
}*/