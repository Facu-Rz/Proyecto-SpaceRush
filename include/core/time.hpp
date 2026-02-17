#pragma once

struct GameClock {
    float deltaTime = 0.0f;
    float playingTime = 0.0f;

    void reset();
    void update();
};