#include "core/ui.hpp"
#include "core/layout.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

void renderScore(const Graphics& graphics, float score){
    int screenScore= (int)score;

    TextProperties scoreText = {
        graphics.fonts.score,
        {255, 255, 255, 255},
        {1, 1, Aling::End, -20},
        {1, 1, Aling::Start, 5}
    };
    
    renderText(graphics, "Score: " + std::to_string(screenScore), scoreText);
}

void updateScore(float& score, float deltaTime){
    score += 10.0f * deltaTime;
}

void renderGameOver(const Graphics& graphics, float finalScore){
    renderGOBackground(graphics.renderer);

    int score= (int)finalScore;

    TextProperties gameOver = {
        graphics.fonts.gameOver,
        {255, 215, 0, 255},
        {1, 1, Aling::Center, 0},
        {1, 3, Aling::End, 0}
    };

    renderText(graphics, "GAME OVER", gameOver);

    TextProperties scoreText {
        graphics.fonts.hint,
        {255, 255, 255, 255},
        {1, 1, Aling::Center, 0},
        {3, 3, Aling::Start, 31}
    };

    renderText(graphics, "Puntuacion final: " + std::to_string(score), scoreText);

    TextProperties reset {
        graphics.fonts.hint,
        {255, 255, 255, 255},
        {1, 1, Aling::Center, 0},
        {3, 3, Aling::Center, -20}
    };

    renderText(graphics, "Presione R para volver a jugar", reset);
}

void renderText(const Graphics& graphics, const std::string& text, TextProperties properties){
    int w, h;
    TTF_SizeText(properties.font, text.c_str(), &w, &h);

    SDL_Rect rect;
    rect.w= w;
    rect.h= h;

    int ascent= TTF_FontAscent(properties.font);

    rect.x= layoutAxisValue(graphics.SCREEN_WIDTH, w, properties.x);
    rect.y= layoutAxisValue(graphics.SCREEN_HEIGHT, h, properties.y);

    SDL_Surface* surface= TTF_RenderText_Blended(properties.font, text.c_str(), properties.color);
    SDL_Texture* texture= SDL_CreateTextureFromSurface(graphics.renderer, surface);

    SDL_FreeSurface(surface);
    SDL_RenderCopy(graphics.renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}

void renderGOBackground(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    SDL_Rect backGround= {0, 0, 800, 600};
    SDL_RenderFillRect(renderer, &backGround);
}