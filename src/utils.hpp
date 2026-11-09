//
// Created by x3r1x on 11/10/26.
//

#include <random>

static int GenerateRandomNumber(const int start, const int finish)
{
    const int actualFinish = finish - 1;

    static std::random_device randomDevice;
    static std::mt19937 gen(randomDevice());
    static std::uniform_int_distribution<> distribution(start, actualFinish);

    return distribution(gen);
}