#include "randomizer.h"
#include <random>

int Randomizer::getRandomInt(int from, int to)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(from,to);
    return dist(rng);
}
