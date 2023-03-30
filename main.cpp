#include "matplotlibcpp.h"

#include <iostream>
#include <random>
#include <vector>
#include <numbers>
#include <cmath>
#include <initializer_list>

namespace plt = matplotlibcpp;

constexpr auto arraySize{10};

[[nodiscard]] std::vector<double>
task1_1(const std::initializer_list<uint32_t>&& seed)
{
    std::vector<double> result(arraySize);
    std::seed_seq seq(seed);
    std::mt19937 mt(seq);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    for (auto i{result.begin()}; i != result.end(); i++)
    {
        (*i) = dist(mt);
    }
    return result;
}

double
task1_2(
    double x,
    const std::vector<double>& array)
{
    assert((x >= 0.0) && (x <= array.size()-1));
    auto slot{x - std::floor(x)};
    if (std::floor(x) == x)
    {
        return array.at(static_cast<int>(x));
    }
    return array.at(static_cast<int>(std::ceil(x))) * slot +
        array.at(static_cast<int>(std::floor(x))) * (1 - slot);
}

double
task1_3(
    double x,
    const std::vector<double>& array)
{
    assert((x >= 0.0) && (x <= array.size()));
    auto xLoop{(static_cast<int>(x) % (arraySize - 1)) + (x - std::floor(x))};
    auto slot{xLoop - std::floor(xLoop)};
    if (std::floor(slot) == slot)
    {
        return array.at(static_cast<int>(slot));
    }
    return array.at(static_cast<int>(std::ceil(xLoop))) * slot +
        array.at(static_cast<int>(std::floor(xLoop))) * (1 - slot);
}

double
task1_4(
    double x,
    const std::vector<double>& array)
{
    auto xLoop{abs(((arraySize - 1) - (static_cast<int>(x) % (arraySize - 1)))) + (x - std::floor(x))};
    auto slot{xLoop - std::floor(xLoop)};
    if (std::floor(slot) == slot)
    {
        return array.at(static_cast<int>(slot));
    }
    return array.at(static_cast<int>(std::ceil(xLoop))) * slot +
        array.at(static_cast<int>(std::floor(xLoop))) * (1 - slot);
}

double
task1_5(
    double x,
    const std::vector<double>& array)
{
    auto slot{abs((static_cast<int>(x) % (arraySize - 1)) + (x - std::floor(x)))};
    if (std::floor(slot) == slot)
    {
        return array.at(static_cast<int>(slot));
    }
    auto slotSmoothed{std::cos(std::numbers::pi + (slot - std::floor(slot)) * std::numbers::pi)/2 + 0.5};
    return array.at(static_cast<int>(std::ceil(slot))) * slotSmoothed +
        array.at(static_cast<int>(std::floor(slot))) * (1 - slotSmoothed);
}

double
task1_6(
    double x,
    const std::vector<double>& array)
{
    auto slot{abs((static_cast<int>(x) % (arraySize - 1)) + (x - std::floor(x)))};
    if (std::floor(slot) == slot)
    {
        return array.at(static_cast<int>(slot));
    }
    auto slotSmoothed{std::cos(std::numbers::pi + (slot - std::floor(slot)) * std::numbers::pi)/2 + 0.5};
    return array.at(static_cast<int>(std::ceil(slot))) * slotSmoothed +
        array.at(static_cast<int>(std::floor(slot))) * (1 - slotSmoothed);
}

int main()
{
    const auto t1_1{task1_1({666})};
    for (const auto& v : t1_1)
    {
        std::cout << v << " ";
    }
    std::cout << "\n";

    plt::figure_size(1900, 1000);
    plt::subplot2grid(3, 2, 0, 0);
    plt::plot(t1_1);

    {
        std::vector<double> x, y;
        for (double i{}; i <= static_cast<double>(t1_1.size()-1); i += 0.1)
        {
            x.push_back(i);
            y.push_back(task1_2(i, t1_1));
        }
        plt::subplot2grid(3, 2, 0, 1);
        plt::plot(x, y);
    }

    {
        std::vector<double> x, y;
        for (double i{}; i <= static_cast<double>(t1_1.size()); i += 0.1)
        {
            x.push_back(i);
            y.push_back(task1_3(i, t1_1));
        }
        plt::subplot2grid(3, 2, 1, 0);
        plt::plot(x, y);
    }

    {
        std::vector<double> x, y;
        for (double i{-20.0}; i <= 20.0; i += 0.1)
        {
            x.push_back(i);
            y.push_back(task1_4(i, t1_1));
        }
        plt::subplot2grid(3, 2, 1, 1);
        plt::plot(x, y);
    }

    {
        std::vector<double> x, y;
        for (double i{}; i <= static_cast<double>(t1_1.size()-1); i += 0.1)
        {
            x.push_back(i);
            y.push_back(task1_5(i, t1_1));
        }
        plt::subplot2grid(3, 2, 2, 0);
        plt::plot(x, y);
    }

    {
        std::vector<double> x, y;
        for (double i{-20.0}; i <= 20.0; i += 0.1)
        {
            x.push_back(i);
            y.push_back(task1_6(i, t1_1));
        }
        plt::subplot2grid(3, 2, 2, 1);
        plt::plot(x, y);
    }

    plt::show();
}