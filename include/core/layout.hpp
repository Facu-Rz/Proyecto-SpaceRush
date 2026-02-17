#pragma once

enum class Aling {
    Start,
    Center,
    End
};

struct layoutAxis {
    int section;
    int divisions;
    Aling aling;
    int margin = 0;
};

inline float alingValue(Aling aling){
    switch(aling){
        case Aling::Start: return 1.0f;
        case Aling::Center: return 0.5f;
        case Aling::End: return 0.0f;
    }

    return 1.0f;
}

inline int layoutAxisValue(int total, int size, const layoutAxis& axis) {
    float alingNumber= alingValue(axis.aling);
    return (int)((total - size) * (axis.section - alingNumber) / axis.divisions) + axis.margin;
}