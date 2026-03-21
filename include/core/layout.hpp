#pragma once

enum class Align {
    None,
    Start,
    Center,
    End
};

struct LayoutAxis {
    int section;
    int divisions;
    Align align;
    int margin = 0;
};

inline float alignValue(Align align){
    switch(align){
        case Align::None: return 1.0f;
        case Align::Start: return 1.0f;
        case Align::Center: return 0.5f;
        case Align::End: return 0.0f;
    }

    return 1.0f;
}

inline int layoutAxisValue(int total, int size, const LayoutAxis& axis) {
    float alignNumber= alignValue(axis.align);
    return (int)((total - size) * (axis.section - alignNumber) / axis.divisions) + axis.margin;
}