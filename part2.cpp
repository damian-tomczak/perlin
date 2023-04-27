#include "tasks.h"

namespace part2
{
[[nodiscard]] std::vector<double>
permutacje_podw_wygeneruj_v1(const uint32_t n, const std::initializer_list<uint32_t>&& seed)
{
    std::vector<double> result(n);
    std::iota(result.begin(), result.end(), 0);

    std::seed_seq seq(seed);
    std::mt19937 mt(seq);
    std::uniform_int_distribution<> dist(0.0, n);
    for (auto i{result.begin()}; i != result.end(); ++i)
    {
        auto random{dist(mt)};
        result.at(random) = *i;
        (*i) = random;
    }
    result.reserve(result.size() + n);
    for (uint32_t i{}; i < n; ++i)
    {
        result.push_back(result.at(i));
    }

    return result;
}

uint32_t skoki_perm(const std::vector<double> tab_perm, uint32_t wynik_pocz, const std::initializer_list<uint32_t>&& skl)
{
    for (auto it{skl.begin()}; it != skl.end(); ++it)
    {
        wynik_pocz = tab_perm.at(wynik_pocz + *it);
    }
    return wynik_pocz;
}

void task1()
{
    for (const auto& v : permutacje_podw_wygeneruj_v1(3, {666}))
    {
        std::cout << v;
    }
    std::cout << "\n";
}

void task2()
{
    std::cout << skoki_perm(permutacje_podw_wygeneruj_v1(3, {666}), 0, {1, 0}) << "\n";
}

int32_t funkcja_skrotu_1d_perm_v3(int32_t x_c, const std::vector<int32_t>& tab_perm)
{
    bool isNegative{};
    auto dtw{tab_perm.size() / 2};
    if (x_c < 0)
    {
        isNegative = true;
        x_c = abs(x_c);
    }
    else
    {
        isNegative = false;
    }
    auto result{tab_perm.at(x_c % dtw)};
    x_c = floor(x_c / dtw);
    while (x_c > 0)
    {
        result = tab_perm.at(result + (x_c % dtw));
        x_c = floor(x_c / dtw);
    }
    if (isNegative)
    {
        result = tab_perm.at(result);
    }
    return result;
}

void task3()
{
    std::vector<int32_t> tab_perm{1, 2, 0, 1, 2, 0};
    std::vector<double> tab_x{0, 0.7, 1};
    std::vector<double> x(40);
    std::iota(x.begin(), x.end(), -20);
    std::vector<double> y(x.size());
    for (size_t i{}; i < y.size(); ++i)
    {
        y.at(i) = funkcja_skrotu_1d_perm_v3(x.at(i), tab_perm);
    }
    plt::bar(x, y);
    plt::show();
}

double szum_1d_pseudoperlin_vperm3(double x, const std::vector<double>& tab_wart, const std::vector<int32_t>& tab_perm)
{
    auto x_l{floor(x)};
    auto x_p{x_l + 1};
    auto i_x_l{funkcja_skrotu_1d_perm_v3(x_l, tab_perm)};
    auto i_x_p{funkcja_skrotu_1d_perm_v3(x_p, tab_perm)};
    auto w_l{tab_wart.at(i_x_l)};
    auto w_p{tab_wart.at(i_x_p)};
    auto delta_x{x - x_l};
    auto result{part1::interpolacja_1d_rdzen_vnlin(w_l, w_p, delta_x)};
    return result;
}

double szum_1d_pseudoperlin_oktawy(
    double x,
    const std::vector<double>& tab_wart,
    const std::vector<int32_t>& tab_perm,
    int32_t oktawa_liczba,
    double oktawa_mnoznik,
    int32_t oktawa_zageszczenie
    )
{
    double ampl_suma{};
    double result{};
    for (int i{}; i < oktawa_liczba; ++i)
    {
        auto wys_mnoznik{pow(oktawa_mnoznik, i)};
        auto zageszczenie_mnoznik{pow(oktawa_zageszczenie, i)};
        ampl_suma += wys_mnoznik;
        result += wys_mnoznik * szum_1d_pseudoperlin_vperm3(x * zageszczenie_mnoznik, tab_wart, tab_perm);
    }
    result = result / ampl_suma;
    return result;
}

void task4()
{
    std::vector<int32_t> tab_perm{1, 2, 0, 1, 2, 0};
    std::vector<double> tab_x{0, 0.7, 1};
    auto x{linspace(-20, 20, 1501)};
    std::vector<double> y(x.size());
    for (auto itx{x.begin()}, ity{y.begin()}; ity != y.end(); ++ity, ++itx)
    {
        *ity = szum_1d_pseudoperlin_oktawy(*itx, tab_x, tab_perm, 6, 0.5, 2);
    }
    plt::plot(x, y);
    plt::show();
}

void task5()
{
    std::vector<int32_t> tab_perm{1, 2, 0, 1, 2, 0};
    std::vector<double> tab_x{0, 0.7, 1, 0.3};
    auto x{linspace(-20, 20, 1501)};
    std::vector<double> y(x.size());
    for (auto itx{x.begin()}, ity{y.begin()}; ity != y.end(); ++ity, ++itx)
    {
        *ity = szum_1d_pseudoperlin_oktawy(*itx, tab_x, tab_perm, 6, 0.5, 2.1);
    }
    plt::plot(x, y);
    plt::show();
}
}