#include "matplotlibcpp.h"

#include <iostream>
#include <random>
#include <vector>
#include <numbers>
#include <cmath>
#include <initializer_list>

namespace plt = matplotlibcpp;

[[nodiscard]] std::vector<double>
wartosci_losowe_wygeneruj_v0(const uint32_t n, const std::initializer_list<uint32_t>&& seed)
{
    std::vector<double> result(n);
    std::seed_seq seq(seed);
    std::mt19937 mt(seq);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    for (auto i{result.begin()}; i != result.end(); ++i)
    {
        (*i) = dist(mt);
    }
    return result;
}

[[nodiscard]] std::vector<double>
wartosci_losowe_wygeneruj_v1(const uint32_t n, const std::initializer_list<uint32_t>&& seed)
{
    assert(n >= 2);
    std::vector<double> result(n);
    std::seed_seq seq(seed);
    std::mt19937 mt(seq);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    result.at(0) = 0.0;
    result.at(1) = 1.0;
    for (auto i{result.begin() + 2}; i != result.end(); ++i)
    {
        (*i) = dist(mt);
    }
    return result;
}

uint32_t
funkcja_skrotu_1d_v0(const uint32_t x, const size_t DTW)
{
    return ((x % DTW) + DTW) % DTW;
}

double
interpolacja_1d_rdzen_vlin(const double w_l, const double w_p, const double delta_x)
{
    if (std::floor(delta_x) == delta_x)
    {
        return w_l;
    }
    else if (std::ceil(delta_x) == delta_x)
    {
        return w_p;
    }

    return w_p * delta_x +
        w_l * (1 - delta_x);
}

// double
// task1_2(const double x, const std::vector<double>& array)
// {
//     assert((x >= 0.0) && (x <= array.size()-1));
//     auto slot{x - std::floor(x)};
//     if (std::floor(x) == x)
//     {
//         return array.at(static_cast<int>(x));
//     }
//     return array.at(static_cast<int>(std::ceil(x))) * slot +
//         array.at(static_cast<int>(std::floor(x))) * (1 - slot);
// }

// double
// task1_3(
//     double x,
//     const std::vector<double>& array)
// {
//     assert((x >= 0.0) && (x <= array.size()));
//     auto xLoop{(static_cast<int>(x) % (arraySize - 1)) + (x - std::floor(x))};
//     auto slot{xLoop - std::floor(xLoop)};
//     if (std::floor(slot) == slot)
//     {
//         return array.at(static_cast<int>(slot));
//     }
//     return array.at(static_cast<int>(std::ceil(xLoop))) * slot +
//         array.at(static_cast<int>(std::floor(xLoop))) * (1 - slot);
// }

// double
// task1_4(
//     double x,
//     const std::vector<double>& array)
// {
//     auto xLoop{abs(((arraySize - 1) - (static_cast<int>(x) % (arraySize - 1)))) + (x - std::floor(x))};
//     auto slot{xLoop - std::floor(xLoop)};
//     if (std::floor(slot) == slot)
//     {
//         return array.at(static_cast<int>(slot));
//     }
//     return array.at(static_cast<int>(std::ceil(xLoop))) * slot +
//         array.at(static_cast<int>(std::floor(xLoop))) * (1 - slot);
// }

// double
// task1_5(
//     double x,
//     const std::vector<double>& array)
// {
//     auto slot{abs((static_cast<int>(x) % (arraySize - 1)) + (x - std::floor(x)))};
//     if (std::floor(slot) == slot)
//     {
//         return array.at(static_cast<int>(slot));
//     }
//     auto slotSmoothed{std::cos(std::numbers::pi + (slot - std::floor(slot)) * std::numbers::pi)/2 + 0.5};
//     return array.at(static_cast<int>(std::ceil(slot))) * slotSmoothed +
//         array.at(static_cast<int>(std::floor(slot))) * (1 - slotSmoothed);
// }

// double
// task1_6(
//     double x,
//     const std::vector<double>& array)
// {
//     auto slot{abs((static_cast<int>(x) % (arraySize - 1)) + (x - std::floor(x)))};
//     if (std::floor(slot) == slot)
//     {
//         return array.at(static_cast<int>(slot));
//     }
//     auto slotSmoothed{std::cos(std::numbers::pi + (slot - std::floor(slot)) * std::numbers::pi)/2 + 0.5};
//     return array.at(static_cast<int>(std::ceil(slot))) * slotSmoothed +
//         array.at(static_cast<int>(std::floor(slot))) * (1 - slotSmoothed);
// }

int main()
{
    // {
    //     plt::figure_size(1280, 720);
    //     plt::title("Zadanie 1");
    //     plt::subplot2grid(1, 2, 0, 0);
    //     const auto wartosci_losowe_wygeneruj_v0_result{wartosci_losowe_wygeneruj_v0(8, {666})};
    //     plt::plot(wartosci_losowe_wygeneruj_v0_result);
    //     plt::subplot2grid(1, 2, 0, 1);
    //     const auto wartosci_losowe_wygeneruj_v1_result{wartosci_losowe_wygeneruj_v1(8, {997})};
    //     plt::plot(wartosci_losowe_wygeneruj_v1_result);
    //     plt::show();
    // }

    // {
    //     plt::figure_size(1280, 720);
    //     plt::title("Zadanie 2");
    //     auto DTL{8};
    //     std::vector<int32_t> funkcja_skrotu_1d_v0_result;
    //     funkcja_skrotu_1d_v0_result.reserve(DTL);
    //     for (auto i{10}; i < 16; ++i)
    //     {
    //         auto tmp(funkcja_skrotu_1d_v0(i, DTL));
    //         funkcja_skrotu_1d_v0_result.emplace_back(tmp);
    //     }
    //     plt::plot(funkcja_skrotu_1d_v0_result);
    //     plt::show();
    // }

    // {
    //     plt::figure_size(1280, 720);
    //     plt::title("Zadanie 3");
    //     std::vector<double> x, y;
    //     for (double delta_x{}; delta_x <= 1.0; delta_x += 0.1)
    //     {
    //         x.push_back(delta_x);
    //         y.push_back(interpolacja_1d_rdzen_vlin(0.9, 0.2, delta_x));
    //     }
    //     plt::plot(x, y);
    //     plt::show();
    // }

    // plt::figure_size(1900, 1000);
    // plt::subplot2grid(3, 2, 0, 0);
    // plt::plot(t1_1);

    // {
    //     std::vector<double> x, y;
    //     for (double i{}; i <= static_cast<double>(t1_1.size()-1); i += 0.1)
    //     {
    //         x.push_back(i);
    //         y.push_back(task1_2(i, t1_1));
    //     }
    //     plt::subplot2grid(3, 2, 0, 1);
    //     plt::plot(x, y);
    // }

    // {
    //     std::vector<double> x, y;
    //     for (double i{}; i <= static_cast<double>(t1_1.size()); i += 0.1)
    //     {
    //         x.push_back(i);
    //         y.push_back(task1_3(i, t1_1));
    //     }
    //     plt::subplot2grid(3, 2, 1, 0);
    //     plt::plot(x, y);
    // }

    // {
    //     std::vector<double> x, y;
    //     for (double i{-20.0}; i <= 20.0; i += 0.1)
    //     {
    //         x.push_back(i);
    //         y.push_back(task1_4(i, t1_1));
    //     }
    //     plt::subplot2grid(3, 2, 1, 1);
    //     plt::plot(x, y);
    // }

    // {
    //     std::vector<double> x, y;
    //     for (double i{}; i <= static_cast<double>(t1_1.size()-1); i += 0.1)
    //     {
    //         x.push_back(i);
    //         y.push_back(task1_5(i, t1_1));
    //     }
    //     plt::subplot2grid(3, 2, 2, 0);
    //     plt::plot(x, y);
    // }

    // {
    //     std::vector<double> x, y;
    //     for (double i{-20.0}; i <= 20.0; i += 0.1)
    //     {
    //         x.push_back(i);
    //         y.push_back(task1_6(i, t1_1));
    //     }
    //     plt::subplot2grid(3, 2, 2, 1);
    //     plt::plot(x, y);
    // }

    // plt::show();
}