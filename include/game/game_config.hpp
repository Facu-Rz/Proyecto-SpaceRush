#pragma once

namespace GameConfig {
    constexpr float WorldWidth = 800.0f;
    constexpr float WorldHeight = 600.0f;

    constexpr float PlayableMargin = 3.0f;

    constexpr float LeftBound = PlayableMargin;
    constexpr float RightBound = WorldWidth - PlayableMargin;
    constexpr float TopBound = PlayableMargin;
    constexpr float BottomBound = WorldHeight - PlayableMargin;
}

inline bool isInsideBounds(float x, float y){
    return x >= GameConfig::LeftBound && x <= GameConfig::RightBound
    &&
    y >= GameConfig::TopBound && y <= GameConfig::BottomBound;
}
