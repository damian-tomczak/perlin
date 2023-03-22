#include "matplotlibcpp.h"

#include <iostream>
#include <random>
#include <array>
#include <initializer_list>

namespace plt = matplotlibcpp;

std::array<double, 8> array;

void task1(std::initializer_list<uint32_t> seed)
{
    std::seed_seq seq(seed.begin(), seed.end());
    std::mt19937 mt(seq);
    std::uniform_real_distribution<double> dist(0., 1.);
    for (auto i{array.begin()}; i != array.end(); i++)
    {
        (*i) = dist(mt);
    }
}

int main()
{
    task1({666});
    std::vector<uint32_t> vector(array.begin(), array.end());
    plt::plot(vector);
    plt::show();
}