#include "entities/player.hpp"
#include "systems/collisions.hpp"
#include "core/input.hpp"
#include <SDL.h>

Player createPlayer(){
    Player player{};

    player.collider={300, 300, 50, 50};
    player.position={300.0f, 300.0f};
    player.direction={0.0f, 0.0f};
    player.speed= 312.0f;
    player.alive= true;
    player.layer= ColissionLayer::Player;

    return player;
}

void updatePlayer(Player& player, float deltaTime, InputState state){
    player.direction = state.movement;

    player.position.x += player.direction.x * player.speed * deltaTime;
    player.position.y += player.direction.y * player.speed * deltaTime;

    player.collider.x=(int)player.position.x;
    player.collider.y=(int)player.position.y;
}

void renderPlayer(Player& player, SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    if(!player.alive){
        player.speed=0.0f;
        return;
    }
    SDL_RenderFillRect(renderer, &player.collider);
}