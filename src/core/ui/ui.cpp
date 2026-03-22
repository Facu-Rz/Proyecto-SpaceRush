#include "core/ui/ui.hpp"
#include "core/layout.hpp"
#include "platform/sdl/graphics.hpp"
#include "debug/debug_state.hpp"
#include "debug/debug_visual.hpp"
#include "game/game_config.hpp"
#include "entities/projectile.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <format>
#include <vector>

void renderScore(const Graphics& graphics, float score){
    int screenScore= (int)score;

    TextProperties scoreText = {
        graphics.fonts.score,
        {255, 255, 255, 255},
        {1, 1, Align::End, -20},
        {1, 1, Align::Start, 5}
    };
    
    renderText(graphics, "Score: " + std::to_string(screenScore), scoreText);
}

void updateScore(float& score, float deltaTime){
    score += 10.0f * deltaTime;
}

void renderGameOver(const Graphics& graphics, float finalScore){
    renderGOBackground(graphics);

    int score= (int)finalScore;

    TextProperties gameOver = {
        graphics.fonts.gameOver,
        {255, 215, 0, 255},
        {1, 1, Align::Center, 0},
        {1, 3, Align::End, 0}
    };

    renderText(graphics, "GAME OVER", gameOver);

    TextProperties scoreText {
        graphics.fonts.hint,
        {255, 255, 255, 255},
        {1, 1, Align::Center, 0},
        {3, 3, Align::Start, 31}
    };

    renderText(graphics, "Puntuacion final: " + std::to_string(score), scoreText);

    TextProperties reset {
        graphics.fonts.hint,
        {255, 255, 255, 255},
        {1, 1, Align::Center, 0},
        {3, 3, Align::Center, -20}
    };

    renderText(graphics, "Presione R para volver a jugar", reset);
}

#ifdef DEBUG_MODE
void renderDebugUi(const Graphics& graphics, DebugData data) {
    renderDebugHeader(graphics);
    renderDebugModeInfo(graphics, data);

    if (debug.mode == DebugMode::LayoutTools) renderLayoutInfo(graphics);
    if (debug.mode == DebugMode::SpawnRate) renderSpawnRateInfo(graphics, data);
}

void renderDebugHeader(const Graphics& graphics) {
    TextProperties header {
        graphics.fonts.hint2,
        {0, 255, 140, 120},
        {1, 4, Align::Center, -10},
        {1, 1, Align::Start, 10}
    };

    renderText(graphics, "[DEBUG MODE]", header);
}

void renderDebugModeInfo(const Graphics& graphics, DebugData data) {
    TextProperties projectileInScreen {
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {2, 12, Align::Start, -5}
    };

    renderText(graphics, "Proyectiles activos: " + std::to_string(data.activeProjectile), projectileInScreen);

    TextProperties projectileCapacity {
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {2, 12, Align::Start, 15}
    };

    renderText(graphics, "Reserva en memoria de proyectiles: " 
    + std::to_string(data.projectileCapacity), projectileCapacity);

    TextProperties mode {
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {3, 12, Align::Start, 10}
    };

    renderText(graphics, "Mode: " + toString(debug.mode), mode);

    TextProperties globalTime {
        graphics.fonts.hint,
        {0, 255, 140, 140},
        {5, 9, Align::Center, 0},
        {1, 1, Align::Start, 5}
    };

    renderText(graphics, std::to_string((int)data.time), globalTime);
}

void renderLayoutInfo(const Graphics& graphics) {
    TextProperties tool{
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {3, 12, Align::Center, 5}
    };

    renderText(graphics, "Tool: " + toString(debug.layoutMode), tool);

    TextProperties section{
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {4, 12, Align::Start, 10}
    };

    renderText(graphics, "Section: (" + std::to_string(debug.navigator.sectionX)
    + ", " + std::to_string(debug.navigator.sectionY) + ")", section);

    TextProperties sectionRect{
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {4, 12, Align::Center, 5}
    };

    renderText(graphics, "Section Rect: {" 
    + std::to_string(debug.navigator.section.x) + ", " + std::to_string(debug.navigator.section.y) + ", " 
    + std::to_string(debug.navigator.section.w) + ", " + std::to_string(debug.navigator.section.h) + "}", sectionRect);

    TextProperties grid{
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {5, 12, Align::Start, 10}
    };

    renderText(graphics, "Grid: (" + std::to_string(debug.gridDivX) 
    + ", " + std::to_string(debug.gridDivY) + ")", grid);

    TextProperties margin{
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {5, 12, Align::End, -10}
    };

    renderText(graphics, "Margin: (" + std::to_string(debug.navigator.marginX) 
    + ", " + std::to_string(debug.navigator.marginY) + ")", margin);

    TextProperties magnitude{
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {6, 12, Align::Start, 10}
    };

    renderText(graphics, "Margin Magnitude: " + std::to_string(debug.navigator.magnitude), magnitude);

    TextProperties align{
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {6, 12, Align::Center, 5}
    };

    renderText(graphics, "Align: (" + toString(debug.navigator.alignX) 
    + ", " + toString(debug.navigator.alignY) + ")", align);

}

void renderSpawnRateInfo(const Graphics& graphics, DebugData data) {
    TextProperties rate{
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {3, 12, Align::Center, 5}
    };

    std::string r = std::format("{:.1f}", data.spawnRate);

    renderText(graphics, "Rate: " + r, rate);

    TextProperties magnitude{
        graphics.fonts.hint3,
        {0, 255, 140, 140},
        {1, 1, Align::Start, 10},
        {4, 12, Align::Start, 10}
    };

    std::string m = std::format("{:.1f}", debug.rate);

    renderText(graphics, "Rate Magnitude: " + m, magnitude);
}
#endif


void renderText(const Graphics& graphics, const std::string& text, TextProperties properties){
    int w, h;
    TTF_SizeText(properties.font, text.c_str(), &w, &h);

    SDL_Rect rect;
    rect.w= w;
    rect.h= h;

    rect.x= layoutAxisValue((int)GameConfig::WorldWidth, w, properties.x);
    rect.y= layoutAxisValue((int)GameConfig::WorldHeight, h, properties.y);

    SDL_Surface* surface= TTF_RenderText_Blended(properties.font, text.c_str(), properties.color);
    SDL_Texture* texture= SDL_CreateTextureFromSurface(graphics.renderer, surface);

    #ifdef DEBUG_MODE
    if (debug.showObjectsBounds) showObjectsBounds(graphics.renderer, rect);
    #endif

    SDL_FreeSurface(surface);
    SDL_RenderCopy(graphics.renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}

void renderGOBackground(const Graphics& graphics){
    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 180);
    SDL_Rect backGround= {0, 0, (int)GameConfig::WorldWidth, (int)GameConfig::WorldHeight};
    SDL_RenderFillRect(graphics.renderer, &backGround);
}

#ifdef DEBUG_MODE
std::string toString(DebugMode mode){
    switch (mode) {
        case DebugMode::None: return "None";
        case DebugMode::LayoutTools: return "LayoutTools";
        case DebugMode::SpawnRate: return "SpawnRate";

        default: return "Unknown";
    }
}

std::string toString(LayoutMode mode){
    switch (mode) {
        case LayoutMode::None: return "None";
        case LayoutMode::Grid: return "Grid";
        case LayoutMode::Navigator: return "Navigator";

        default: return "Unknown";
    }
}

std::string toString(Align align){
    switch (align) {
        case Align::None: return "None";
        case Align::Start: return "Start";
        case Align::Center: return "Center";
        case Align::End: return "End";

        default: return "Unknown";
    }
}
#endif