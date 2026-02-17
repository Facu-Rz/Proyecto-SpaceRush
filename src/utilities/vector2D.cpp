#include "utilities/vector2D.hpp"
#include <SDL.h>

Vector2D normalize(const Vector2D& vector){
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
}