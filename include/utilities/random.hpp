#pragma once
#include <random>

static std::mt19937& getGenerator();

int randomInt(int min, int max);

float randomFloat(float min, float max);