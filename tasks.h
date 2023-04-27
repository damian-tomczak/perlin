#pragma once

#include "matplotlibcpp.h"

#include <iostream>
#include <random>
#include <vector>
#include <numbers>
#include <cmath>
#include <initializer_list>

namespace plt = matplotlibcpp;

[[nodiscard]]
inline std::vector<double> linspace(
    const double start,
    const double end,
    const int num_points)
{
    std::vector<double> points;
    double step{(end - start) / (num_points - 1)};

    for (int i{}; i < num_points; ++i)
    {
        points.push_back(start + step * i);
    }

    return points;
}

namespace part1
{
double interpolacja_1d_rdzen_vnlin(const double w_l, const double w_p, const double delta_x);

void task1();
void task2();
void task3();
void task4();
void task5();
}

namespace part2
{
void task1();
void task2();
void task3();
void task4();
void task5();
}

namespace part3
{
void task1();
void task2();
void task3();
void task4();
void task5();
}