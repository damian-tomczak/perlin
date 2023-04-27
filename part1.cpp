#include "tasks.h"

namespace part1
{
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

void task1()
{
    plt::subplot2grid(1, 2, 0, 0);
    plt::title("Zadanie 1");
    const auto values0{wartosci_losowe_wygeneruj_v0(8, {666})};
    plt::plot(values0);
    plt::subplot2grid(1, 2, 0, 1);
    const auto values1{wartosci_losowe_wygeneruj_v1(8, {997})};
    plt::plot(values1);
    plt::show();
}

uint32_t
funkcja_skrotu_1d_v0(const uint32_t x, const size_t DTW)
{
    return ((x % DTW) + DTW) % DTW;
}

void task2()
{
    plt::title("Zadanie 2");
    auto DTL{8};
    std::vector<int32_t> funkcja_skrotu_1d_v0_result;
    funkcja_skrotu_1d_v0_result.reserve(DTL);
    for (auto i{10}; i < 16; ++i)
    {
        auto tmp(funkcja_skrotu_1d_v0(i, DTL));
        funkcja_skrotu_1d_v0_result.emplace_back(tmp);
    }
    plt::plot(funkcja_skrotu_1d_v0_result);
    plt::show();
}

double interpolacja_1d_rdzen_vlin(const double w_l, const double w_p, const double delta_x)
{
    return w_p * delta_x + w_l * (1 - delta_x);
}

void task3()
{
    plt::subplot2grid(1, 2, 0, 0);
    plt::title("Zadanie 3");
    std::vector<double> x, y;
    for (double delta_x{}; delta_x <= 1.0; delta_x += 0.1)
    {
        x.push_back(delta_x);
        y.push_back(interpolacja_1d_rdzen_vlin(0.3, 0.7, delta_x));
    }
    plt::plot(x, y);
    plt::subplot2grid(1, 2, 0, 1);
    y.clear();
    for (double delta_x{}; delta_x <= 1.0; delta_x += 0.1)
    {
        y.push_back(interpolacja_1d_rdzen_vlin(0.9, 0.2, delta_x));
    }
    plt::plot(x, y);
    plt::show();
}

double interpolacja_1d_rdzen_vkos(const double w_l, const double w_p, const double delta_x)
{
    auto k = cos(std::numbers::pi + delta_x * std::numbers::pi) / 2 + 0.5f;
    auto result = w_p * k + w_l * (1 - k);
    return result;
}

double interpolacja_1d_rdzen_wmian(const double w_l, const double w_p, const double delta_x)
{
    auto k = 6 * pow(delta_x, 5) - 15 * pow(delta_x, 4) + 10 * pow(delta_x, 3);
    auto result = w_p * k + w_l * (1 - k);
    return result;
}

void task4()
{
    plt::subplot2grid(2, 2, 0, 0);
    plt::title("Zadanie 4");
    std::vector<double> x, y;
    for (double delta_x{}; delta_x <= 1.0; delta_x += 0.1)
    {
        x.push_back(delta_x);
        y.push_back(interpolacja_1d_rdzen_vkos(0.3, 0.7, delta_x));
    }
    plt::plot(x, y);

    plt::subplot2grid(2, 2, 0, 1);
    y.clear();
    for (double delta_x{}; delta_x <= 1.0; delta_x += 0.1)
    {
        y.push_back(interpolacja_1d_rdzen_vkos(0.9, 0.2, delta_x));
    }
    plt::plot(x, y);

    plt::subplot2grid(2, 2, 1, 0);
    y.clear();
    for (double delta_x{}; delta_x <= 1.0; delta_x += 0.1)
    {
        y.push_back(interpolacja_1d_rdzen_wmian(0.3, 0.7, delta_x));
    }
    plt::plot(x, y);

    plt::subplot2grid(2, 2, 1, 1);
    y.clear();
    for (double delta_x{}; delta_x <= 1.0; delta_x += 0.1)
    {
        y.push_back(interpolacja_1d_rdzen_wmian(0.9, 0.2, delta_x));
    }
    plt::plot(x, y);

    plt::show();
}

double interpolacja_1d_cala_vlin(const double x, const std::vector<double> tab_wart)
{
    auto x_l = std::floor(x);
    auto x_p = x_l + 1;
    auto i_x_l = funkcja_skrotu_1d_v0(x_l, tab_wart.size());
    auto i_x_p = funkcja_skrotu_1d_v0(x_p, tab_wart.size());
    auto w_l = tab_wart.at(i_x_l);
    auto w_p = tab_wart.at(i_x_p);
    auto delta_x = fabs(x - x_l);
    return interpolacja_1d_rdzen_vlin(w_l, w_p, delta_x);
}

double interpolacja_1d_rdzen_vnlin(const double w_l, const double w_p, const double delta_x)
{
    return interpolacja_1d_rdzen_wmian(w_l, w_p, delta_x);
}

double interpolacja_1d_cala_vnlin(const double x, const std::vector<double> tab_wart)
{
    auto x_l = floor(x);
    auto x_p = x_l + 1;
    auto i_x_l = funkcja_skrotu_1d_v0(x_l, tab_wart.size());
    auto i_x_p = funkcja_skrotu_1d_v0(x_p, tab_wart.size());
    auto w_l = tab_wart.at(i_x_l);
    auto w_p = tab_wart.at(i_x_p);
    auto delta_x = fabs(x - x_l);
    return interpolacja_1d_rdzen_vnlin(w_l, w_p, delta_x);
}

void task5()
{
    auto randoms{wartosci_losowe_wygeneruj_v0(4, {666})};
    plt::subplot2grid(1, 2, 0, 0);
    plt::title("Zadanie 5");
    std::vector<double> x, y;
    for (auto delta_x{-4.f}; delta_x < 8.f; delta_x += 0.1)
    {
        x.push_back(delta_x);
        y.push_back(interpolacja_1d_cala_vlin(delta_x, randoms));
    }
    plt::plot(x, y);
    plt::subplot2grid(1, 2, 0, 1);
    y.clear();
    for (auto delta_x{-4.f}; delta_x < 8.f; delta_x += 0.1)
    {
        y.push_back(interpolacja_1d_cala_vnlin(delta_x, randoms));
    }
    plt::plot(x, y);
    plt::show();
}
}