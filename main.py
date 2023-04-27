import numpy as np
import random
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

def funkcja_skrotu_uniw_perm_v3(tab_skl, tab_perm):
    dtw = len(tab_perm)//2
    wynik = 0
    for skl_c in tab_skl:
        if skl_c < 0:
            czy_ujemne = True
            skl_c = -skl_c
        else:
            czy_ujemne = False
        wynik = tab_perm[wynik + (skl_c % dtw)]
        skl_c = math.floor(skl_c/dtw)
        while skl_c > 0:
            wynik = tab_perm[wynik + (skl_c % dtw)]
            skl_c = math.floor(skl_c / dtw)
        if czy_ujemne:
            wynik = tab_perm[wynik]
    return wynik


def task3_1():
    tab_perm = [1, 3, 2, 0, 1, 3, 2, 0]
    xx, yy = np.meshgrid(np.arange(10), np.arange(10))
    zz = np.zeros_like(xx)
    print(xx)
    for y in range(len(yy)):
        for x in range(len(xx)):
            zz[y, x] = funkcja_skrotu_uniw_perm_v3([x, y], tab_perm)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    plt.show()


def interpolacja_2d_rdzen_vnlin(w_ld, w_lg, w_pd, w_pg, delta_x, delta_y):
    delta_x = 6 * delta_x ** 5 - 15 * delta_x ** 4 + 10 * delta_x ** 3
    delta_y = 6 * delta_y ** 5 - 15 * delta_y ** 4 + 10 * delta_y ** 3
    result = w_ld * (1 - delta_x) * (1 - delta_y) + w_lg * (1 - delta_x) * delta_y + w_pd * delta_x * (1 - delta_y) + w_pg * delta_x * delta_y
    return result


def task3_2():
    xx, yy = np.meshgrid(np.linspace(0, 1, 11), np.linspace(0, 1, 11))
    zz = np.zeros_like(xx)
    for y in range(len(yy)):
        for x in range(len(xx)):
            zz[y, x] = interpolacja_2d_rdzen_vnlin(0, 1, 3, 2, xx[y, x], yy[y, x])
    xx2, yy2 = np.meshgrid(np.linspace(1, 2, 11), np.linspace(0, 1, 11))
    zz2 = np.zeros_like(xx2)
    for y in range(len(yy)):
        for x in range(len(xx)):
            zz2[y, x] = interpolacja_2d_rdzen_vnlin(3, 2, 5, 4, xx2[y, x] - 1, yy2[y, x])
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    surf = ax.plot_surface(xx2, yy2, zz2)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    plt.show()


def szum_2d_pseudoperlin_vperm3(x, y, tab_wart, tab_perm):
    x_l = math.floor(x)
    x_p = x_l + 1
    x_delta = x - x_l
    y_d = math.floor(y)
    y_g = y_d + 1
    y_delta = y - y_d
    i_ld = funkcja_skrotu_uniw_perm_v3([x_l, y_d], tab_perm)
    i_lg = funkcja_skrotu_uniw_perm_v3([x_l, y_g], tab_perm)
    i_pd = funkcja_skrotu_uniw_perm_v3([x_p, y_d], tab_perm)
    i_pg = funkcja_skrotu_uniw_perm_v3([x_p, y_g], tab_perm)
    w_ld = tab_wart[i_ld]
    w_lg = tab_wart[i_lg]
    w_pd = tab_wart[i_pd]
    w_pg = tab_wart[i_pg]
    return interpolacja_2d_rdzen_vnlin(w_ld, w_lg, w_pd, w_pg, x_delta, y_delta)


def szum_2d_pseudoperlin_oktawy(x, y, tab_wart, tab_perm, oktawa_liczba, oktawa_mnoznik, oktawa_zageszczenie):
    ampl_suma = 0
    result = 0
    for okt_n in range(oktawa_liczba):
        wys_mnoznik = oktawa_mnoznik ** okt_n
        zageszczenie_mnoznik = oktawa_zageszczenie ** okt_n
        ampl_suma += wys_mnoznik
        result += wys_mnoznik * szum_2d_pseudoperlin_vperm3(x * zageszczenie_mnoznik, y * zageszczenie_mnoznik, tab_wart, tab_perm)
    result = result / ampl_suma
    return result


def task3_3():
    tab_wart = [0, 0.3333, 0.6667, 1.0]
    tab_perm = [1, 3, 2, 0, 1, 3, 2, 0]
    xx, yy = np.meshgrid(np.linspace(-1, 3, 41), np.linspace(2, 4, 21))
    zz = np.zeros_like(xx)
    zz = np.zeros_like(xx)
    for y in range(len(yy)):
        for x in range(len(xx[0])):
            zz[y, x] = szum_2d_pseudoperlin_vperm3(xx[y, x], yy[y, x], tab_wart, tab_perm)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    plt.show()
    for y in range(len(yy)):
        for x in range(len(xx)):
            zz[y, x] = szum_2d_pseudoperlin_oktawy(xx[y, x], yy[y, x], tab_wart, tab_perm, 2, 0.5, 2)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    plt.show()


def zwroc_prog(value):
    if value < 0.3:
        return 0
    elif value < 0.8:
        return 0.5
    return 1


def task3_4():
    tab_wart = [0, 0.3333, 0.6667, 1.0]
    tab_perm = [1, 3, 2, 0, 1, 3, 2, 0]
    xx = np.linspace(-5, 5, 201)
    yy = np.linspace(1, 6, 101)
    zz = np.zeros([len(yy), len(xx)])
    for y in range(len(yy)):
        for x in range(len(xx)):
            zz[y, x] = zwroc_prog(szum_2d_pseudoperlin_oktawy(xx[x], yy[y], tab_wart, tab_perm, 2, 0.5, 2))
    plt.imshow(zz, extent=[xx[0], xx[-1], yy[0], yy[-1]])
    plt.show()


def interpolacja_1d_rdzen_PerlinaPlus(grad_l, grad_p, w_l, w_p, delta_x):
    fade = 6 * delta_x ** 5 - 15 * delta_x ** 4 + 10 * delta_x ** 3
    wyjscie = (w_l + delta_x * grad_l) * (1 - fade) + (w_p + (delta_x - 1) * grad_p) * fade
    return wyjscie


def task4_1():
    xpoints = np.linspace(0, 1, 101)
    ypoints = interpolacja_1d_rdzen_PerlinaPlus(-1, -0.6, -0.5, 0.2, xpoints)
    xpoints2 = np.linspace(1, 2, 101)
    ypoints2 = interpolacja_1d_rdzen_PerlinaPlus(-0.6, -1, 0.2, -0.1, xpoints2 - 1)
    plt.plot(xpoints, ypoints)
    plt.plot(xpoints2, ypoints2)
    plt.show()


def funkcja_skrotu_1d_perm_v3(x_c, tab_perm):
    dtw = len(tab_perm)//2
    if x_c < 0:
        czy_ujemne = True
        x_c = -x_c
    else:
        czy_ujemne = False
    wynik = tab_perm[x_c % dtw]
    x_c = math.floor(x_c / dtw)
    while x_c > 0:
        wynik = tab_perm[wynik + (x_c % dtw)]
        x_c = math.floor(x_c / dtw)
    if czy_ujemne:
        wynik = tab_perm[wynik]
    return wynik


def szum_1d_PerlinaPlus_vperm3(x, tab_grad, tab_perm_grad, tab_wys, tab_perm_wys):
    x_l = math.floor(x)
    x_p = 1 + x_l
    delta_x = x - x_l
    i_wys_l = funkcja_skrotu_1d_perm_v3(x_l, tab_perm_wys)
    i_wys_p = funkcja_skrotu_1d_perm_v3(x_p, tab_perm_wys)
    wys_l = tab_wys[i_wys_l]
    wys_p = tab_wys[i_wys_p]
    i_grad_l = funkcja_skrotu_1d_perm_v3(x_l, tab_perm_grad)
    i_grad_p = funkcja_skrotu_1d_perm_v3(x_p, tab_perm_grad)
    grad_l = tab_grad[i_grad_l]
    grad_p = tab_grad[i_grad_p]
    wy = interpolacja_1d_rdzen_PerlinaPlus(grad_l, grad_p, wys_l, wys_p, delta_x)
    return wy


def task4_2():
    tab_wys = [0, 0.2500, 0.5000, 0.7500, 1.0000]
    tab_perm_wys = [2, 0, 4, 1, 3, 2, 0, 4, 1, 3]
    tab_grad = [-1.0000, -0.3333, 0.3333, 1.0000]
    tab_perm_grad = [3, 2, 0, 1, 3, 2, 0, 1]
    xpoints = np.linspace(-1, 3, 401)
    ypoints = np.zeros(len(xpoints))
    for i in range(len(xpoints)):
        ypoints[i] = szum_1d_PerlinaPlus_vperm3(xpoints[i], tab_grad, tab_perm_grad, tab_wys, tab_perm_wys)
    plt.plot(xpoints, ypoints)
    plt.show()


def szum_1d_PerlinaPlus_oktawy(x, tab_grad, tab_perm_grad, tab_wys, tab_perm_wys, oktawa_liczba, oktawa_mnoznik = 0.5, oktawa_zageszczenie = 2, oktawa_czy_zmn_ampl = True):
    ampl_suma = 0
    wy = 0
    for okt_n in range(oktawa_liczba):
        mnoznik_wy_akt = oktawa_mnoznik ** okt_n
        mnoznik_x_akt = oktawa_zageszczenie ** okt_n
        ampl_suma += mnoznik_wy_akt
        wy += mnoznik_wy_akt * szum_1d_PerlinaPlus_vperm3(x*mnoznik_x_akt, tab_grad, tab_perm_grad, tab_wys, tab_perm_wys)
    if oktawa_czy_zmn_ampl:
        wy = wy / ampl_suma
    return wy

def task4_3():
    tab_wys = [0, 0.2500, 0.5000, 0.7500, 1.0000]
    tab_perm_wys = [2, 0, 4, 1, 3, 2, 0, 4, 1, 3]
    tab_grad = [-1.0000, -0.3333, 0.3333, 1.0000]
    tab_perm_grad = [3, 2, 0, 1, 3, 2, 0, 1]
    xpoints = np.linspace(-1, 3, 4001)
    ypoints = np.zeros(len(xpoints))
    for i in range(len(xpoints)):
        ypoints[i] = szum_1d_PerlinaPlus_oktawy(xpoints[i], tab_grad, tab_perm_grad, tab_wys, tab_perm_wys, 1)
    plt.plot(xpoints, ypoints)
    for i in range(len(xpoints)):
        ypoints[i] = szum_1d_PerlinaPlus_oktawy(xpoints[i], tab_grad, tab_perm_grad, tab_wys, tab_perm_wys, 2)
    plt.plot(xpoints, ypoints)
    for i in range(len(xpoints)):
        ypoints[i] = szum_1d_PerlinaPlus_oktawy(xpoints[i], tab_grad, tab_perm_grad, tab_wys, tab_perm_wys, 4)
    plt.plot(xpoints, ypoints)
    plt.show()


def permutacje_podw_wygeneruj_v1(length, seed):
    tab = []
    for i in range(length):
        tab.append(i)
    random.seed(seed)
    for i in range(length):
        los = random.randint(0, length - 1)
        tab[i], tab[los] = tab[los], tab[i]
    for i in range(length):
        tab.append(tab[i])
    return tab


def szum_PerlinaPlus2d_przygotuj(DTW, wys_min, wys_max, DTG, grad_xy_min, grad_xy_max, start_maszyny_losowej):
    random.seed(start_maszyny_losowej)
    tab_wys = []
    for i in range(DTW):
        tab_wys.append(random.uniform(wys_min, wys_max))
    tab_wys = sorted(tab_wys)
    tab_perm_wys = permutacje_podw_wygeneruj_v1(DTW, start_maszyny_losowej)
    tab_grad = []
    for i in range(DTG):
        tab_tmp = [random.uniform(grad_xy_min, grad_xy_max), random.uniform(grad_xy_min, grad_xy_max)]
        tab_grad.append(tab_tmp)
    tab_grad = sorted(tab_grad)
    tab_perm_grad = permutacje_podw_wygeneruj_v1(DTG, start_maszyny_losowej)
    return [tab_wys, tab_perm_wys, tab_grad, tab_perm_grad]


def task5_1():
    tab_all = szum_PerlinaPlus2d_przygotuj(5, 0, 1, 4, -1, 1, 1234567)
    p_tab_wys = tab_all[0]
    p_tab_perm_wys = tab_all[1]
    p_tab_grad = tab_all[2]
    p_tab_perm_grad = tab_all[3]
    print(p_tab_wys)
    print(p_tab_perm_wys)
    print(p_tab_grad)
    print(p_tab_perm_grad)


def interpolacja_2d_rdzen_PerlinaPlus(grad_ld, grad_lg, grad_pd, grad_pg, wys_ld, wys_lg, wys_pd, wys_pg, delta_x, delta_y):
    fade_x = 6 * delta_x ** 5 - 15 * delta_x ** 4 + 10 * delta_x ** 3
    fade_y = 6 * delta_y ** 5 - 15 * delta_y ** 4 + 10 * delta_y ** 3
    wynik = (wys_ld + grad_ld[0] * delta_x + grad_ld[1] * delta_y) * (1 - fade_x) * (1 - fade_y) + (wys_lg + grad_lg[0] * delta_x + grad_lg[1] * (delta_y - 1)) * (1-fade_x) * fade_y + (wys_pd + grad_pd[0] * (delta_x - 1) + grad_pd[1] * delta_y) * fade_x * (1 - fade_y) + (wys_pg + grad_pg[0] * (delta_x - 1) + grad_pg[1] * (delta_y - 1)) * fade_x * fade_y
    return wynik


def task5_2():
    X = np.linspace(0, 1, 11)
    Y = np.linspace(0, 1, 11)
    xx, yy = np.meshgrid(X, Y)
    zz = np.zeros_like(xx)
    for i in range(len(X)):
        for j in range(len(Y)):
            zz[j, i] = interpolacja_2d_rdzen_PerlinaPlus([0, 0], [0, 0], [0, 0], [0, 0], 0, 1, 3, 2, X[i], Y[j])
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()
    xx, yy = np.meshgrid(X, Y)
    zz = np.zeros_like(xx)
    for i in range(len(X)):
        for j in range(len(Y)):
            zz[j, i] = interpolacja_2d_rdzen_PerlinaPlus([-1, 0], [-1, 0], [-1, 0], [-1, 0], 0, 1, 3, 2, X[i], Y[j])
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()
    xx, yy = np.meshgrid(X, Y)
    zz = np.zeros_like(xx)
    for i in range(len(X)):
        for j in range(len(Y)):
            zz[j, i] = interpolacja_2d_rdzen_PerlinaPlus([0, -1], [0, -1], [0, -1], [0, -1], 0, 1, 3, 2, X[i], Y[j])
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()
    xx, yy = np.meshgrid(X, Y)
    zz = np.zeros_like(xx)
    for i in range(len(X)):
        for j in range(len(Y)):
            zz[j, i] = interpolacja_2d_rdzen_PerlinaPlus([0, 0], [0, -2], [1, 1], [-2, 0], 0, 1, 3, 2, X[i], Y[j])
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()
    xx, yy = np.meshgrid(X, Y)
    zz = np.zeros_like(xx)
    for i in range(len(X)):
        for j in range(len(Y)):
            zz[j, i] = interpolacja_2d_rdzen_PerlinaPlus([-2, 0], [-2, 0], [0, 0], [2, 0], 0, 1, 3, 2, X[i], Y[j])
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()
    xx, yy = np.meshgrid(X, Y)
    zz = np.zeros_like(xx)
    for i in range(len(X)):
        for j in range(len(Y)):
            zz[j, i] = interpolacja_2d_rdzen_PerlinaPlus([0, -1], [0, -1], [0, -1], [0, -1], 0, 0, 0, 0, X[i], Y[j])
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()


def szum_2d_PerlinaPlus_vperm3(x, y, tab_grad, tab_perm_grad, tab_wys, tab_perm_wys):
    x_l = math.floor(x)
    x_p = x_l + 1
    y_d = math.floor(y)
    y_g = y_d + 1
    delta_x = x - x_l
    delta_y = y - y_d
    i_wys_ld = funkcja_skrotu_uniw_perm_v3([x_l, y_d], tab_perm_wys)
    i_wys_lg = funkcja_skrotu_uniw_perm_v3([x_l, y_g], tab_perm_wys)
    i_wys_pd = funkcja_skrotu_uniw_perm_v3([x_p, y_d], tab_perm_wys)
    i_wys_pg = funkcja_skrotu_uniw_perm_v3([x_p, y_g], tab_perm_wys)
    wys_ld = tab_wys[i_wys_ld]
    wys_lg = tab_wys[i_wys_lg]
    wys_pd = tab_wys[i_wys_pd]
    wys_pg = tab_wys[i_wys_pg]
    i_grad_ld = funkcja_skrotu_uniw_perm_v3([x_l, y_d], tab_perm_grad)
    i_grad_lg = funkcja_skrotu_uniw_perm_v3([x_l, y_g], tab_perm_grad)
    i_grad_pd = funkcja_skrotu_uniw_perm_v3([x_p, y_d], tab_perm_grad)
    i_grad_pg = funkcja_skrotu_uniw_perm_v3([x_p, y_g], tab_perm_grad)
    grad_ld = tab_grad[i_grad_ld]
    grad_lg = tab_grad[i_grad_lg]
    grad_pd = tab_grad[i_grad_pd]
    grad_pg = tab_grad[i_grad_pg]
    wy = interpolacja_2d_rdzen_PerlinaPlus(grad_ld, grad_lg, grad_pd, grad_pg, wys_ld, wys_lg, wys_pd, wys_pg, delta_x, delta_y)
    return wy


def task5_3():
    tab_wart = [0, 0.7, 1, 0.4]
    tab_wys = [0, 0.25, 0.5, 0.75, 1.0]
    tab_perm_wys = [2, 0, 4, 1, 3, 2, 0, 4, 1, 3]
    tab_perm_grad = [3, 2, 0, 1, 3, 2, 0, 1]
    tab_grad = [[-0.8, -0.33], [0, 0.4], [-0.45, 0.39], [0.64, 0.13]]
    X = np.linspace(-1, 3, 41)
    Y = np.linspace(2, 4, 21)
    xx, yy = np.meshgrid(X, Y)
    zz = np.zeros_like(xx)
    for i in range(len(X)):
        for j in range(len(Y)):
            zz[j, i] = szum_2d_PerlinaPlus_vperm3(X[i], Y[j], tab_grad, tab_perm_grad, tab_wys, tab_perm_wys)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()
    xx, yy = np.meshgrid(X, Y)
    zz = np.zeros_like(xx)
    for i in range(len(X)):
        for j in range(len(Y)):
            zz[j, i] = szum_2d_PerlinaPlus_vperm3(X[i], Y[j], [[0, 0], [0, 0], [0, 0], [0, 0]], tab_perm_grad, tab_wys, tab_perm_wys)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()
    xx, yy = np.meshgrid(X, Y)
    zz = np.zeros_like(xx)
    for i in range(len(X)):
        for j in range(len(Y)):
            zz[j, i] = szum_2d_PerlinaPlus_vperm3(X[i], Y[j], tab_grad, tab_perm_grad, [0, 0, 0, 0, 0], tab_perm_wys)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xx, yy, zz, cmap=cm.coolwarm)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()


def main():
    # task3_1()
    # task3_2()
    # task3_3()
    # task3_4()
    # task4_1()
    # task4_2()
    # task4_3()
    # task5_1()
    # task5_2()
    task5_3()


if __name__ == '__main__':
    main()