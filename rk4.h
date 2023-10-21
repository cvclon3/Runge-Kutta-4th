#pragma once
#include <vector>


std::vector<float> calc(
        std::vector<float>* y,
        std::vector<float>* k,
        float h
        ) {

    std::vector<float> res;
    size_t len = y->size();
    res.reserve(len);

    for (int i = 0; i < len; i++) {
        res.push_back(y->at(i) + k->at(i) * h);
    }

    return res;
}


std::vector<float> rk4_iteration(
        std::vector<float> (*func) (float, std::vector<float>, struct params*),
        struct params* p,
        float x,
        std::vector<float>* y,
        float h
        ) {

    size_t len = y->size();
    std::vector<float> k1, k2, k3, k4, curr;

    curr = {};

    k1 = func(x, *y, p);
    k2 = func(x + h/2, calc(y, &k1, h/2), p);
    k3 = func(x + h/2, calc(y, &k2, h/2), p);
    k4 = func(x + h, calc(y, &k3, h), p);

    for (int j = 0; j < len; j++) {
        curr.push_back(y->at(j) + h/6 * (k1[j] + 2*k2[j] + 2*k3[j] + k4[j]));
    }

    return curr;
}


std::vector<std::vector<float>> rk4(
        std::vector<float> (*func) (float, std::vector<float>, struct params*),
        struct params* p,
        float x0,
        float xf,
        std::vector<float>* y0,
        float h
        ) {

    int count = (int)((xf - x0)/h) + 1;
    std::vector<std::vector<float>> res {*y0};
    size_t len = y0->size();
    float x = x0;

    std::vector<float> k1, k2, k3, k4, curr;

    for (int i = 1; i < count; i++) {
        curr = {};

        k1 = func(x, res.at(i - 1), p);
        k2 = func(x + h/2, calc(&res.at(i - 1), &k1, h/2), p);
        k3 = func(x + h/2, calc(&res.at(i - 1), &k2, h/2), p);
        k4 = func(x + h, calc(&res.at(i - 1), &k3, h), p);

        for (int j = 0; j < len; j++) {
            curr.push_back(res[i-1][j] + h/6 * (k1[j] + 2*k2[j] + 2*k3[j] + k4[j]));
        }

        res.push_back(curr);
        x += h;
    }

    return res;
}