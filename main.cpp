#include <iostream>
#include <vector>
#include <cmath>

std::vector<float> func(
        float t,
        std::vector<float>* y
    ) {

    float G = 9.81;
    float k = 0.0003;
    return std::vector<float> {
        y->at(1),
        static_cast<float>(-k * pow(y->at(1), 3)),
        y->at(3),
        static_cast<float>(-k * pow(y->at(3), 3) - G)
    };
}


std::vector<float> func2(
        float t,
        std::vector<float>* y
) {

    return std::vector<float> {
            y->at(1),
            exp(-t * y->at(0))
    };
}


std::vector<float> calc(std::vector<float>* y, std::vector<float>* k, float h) {
    std::vector<float> res;

    size_t len = y->size();
    res.reserve(len);
    for (int i = 0; i < len; i++) {
        res.push_back(y->at(i) + k->at(i) * h);
    }

    return res;
}


std::vector<std::vector<float>> rk4(
        std::vector<float> (*func) (float, std::vector<float>*),
        float x0,
        float xf,
        std::vector<float>* y0,
        float h
        ) {

    int count = (int)((xf - x0)/h) + 1;
    std::vector<std::vector<float>> res {*y0};
    size_t len = y0->size();
    float x = x0;

    std::vector<float> k1, k2, k3, k4, curr, iter;

    for (int i = 1; i < count; i++) {
        curr = {}, iter = {};

        k1 = func(x, &res.at(i - 1));

        iter = calc(&res.at(i - 1), &k1, h/2);
        k2 = func(x + h/2, &iter);

        iter = calc(&res.at(i - 1), &k2, h/2);
        k3 = func(x + h/2, &iter);

        iter = calc(&res.at(i - 1), &k3, h);
        k4 = func(x + h, &iter);

        for (int j = 0; j < len; j++) {
            curr.push_back(res[i-1][j] + h/6 * (k1[j] + 2*k2[j] + 2*k3[j] + k4[j]));
        }

        res.push_back(curr);
        x += h;
    }

    return res;
}

int main() {
    std::vector<float> y0 {0, 0};
    std::vector<std::vector<float>> ans = rk4(&func2, 0, 1, &y0, 0.1);
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            std::cout << ans[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}

//
// Created by Nik  on 17.10.23.
//

//#include <iostream>
//#include <vector>
//#include <cmath>
//
//
//std::vector<float> func2(
//        float t,
//        std::vector<float>* y
//) {
//
//    return std::vector<float> {
//            y->at(0),
//            exp(-t * y->at(0))
//    };
//}
//
//
//std::vector<std::vector<float>> euler(
//        std::vector<float> (*func) (float, std::vector<float>*),
//        float x0,
//        float xf,
//        std::vector<float>* y0,
//        float h
//) {
//
//    int count = (int) ((xf - x0) / h) + 1;
//    std::vector<std::vector<float>> y {*y0};
//    int len = y0->size();
//    float x = x0;
//
//    for (int i = 1; i < count; i++) {
//        std::vector<float> right_parts, curr;
//        right_parts = func2(x, &y[i-1]);
//
//        for (int j = 0; j < len; j++) {
//            curr.push_back(y[i-1][j] + h * right_parts[j]);
//        }
//
//        y.push_back(curr);
//        x += h;
//    }
//
//    return y;
//}
//
//
//int main() {
//    std::vector<float> y0 {0, 0};
//    std::vector<std::vector<float>> ans = euler(&func2, 0, 1, &y0, 0.1);
//    for (auto & an : ans) {
//        for (float j : an) {
//            std::cout << j << " ";
//        }
//        std::cout << "\n";
//    }
//    return 0;
//}