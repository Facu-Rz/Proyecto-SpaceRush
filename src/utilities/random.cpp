#include "utilities/random.hpp"
#include <random>

static std::mt19937& getGenerator(){
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

int randomInt(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    return dist(getGenerator());
}

float randomFloat(float min, float max){
    std::uniform_real_distribution<float> dist(min, max);
    return dist(getGenerator());
}
