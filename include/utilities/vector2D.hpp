#pragma once

struct Vector2D {
    float x;
    float y;
};

Vector2D normalize(const Vector2D& vector);

Vector2D sumVector(const Vector2D& a, const Vector2D& b);

Vector2D subVector(const Vector2D& a, const Vector2D& b);

Vector2D multScalar(const Vector2D& vector, float scalar);