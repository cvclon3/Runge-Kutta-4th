#include <iostream>
#include <vector>
#include "rk4.h"


struct params {
    float k = 0.0003;
} params;


std::vector<float> func(
        float t,
        std::vector<float> y,
        struct params *p
) {

    float G = 9.81;
    float k = p->k;

    return std::vector<float> {
            y[1],
            static_cast<float>(-k * pow(y[1], 3)),
            y[3],
            static_cast<float>(-k * pow(y[3], 3) - G)
    };
}


int main() {

    std::vector<float> y0 {0, 100, 0, 100};
    std::vector<std::vector<float>> ans = rk4(&func, &params, 0, 5, &y0, 0.01);

    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            std::cout << ans[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}