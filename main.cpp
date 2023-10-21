#include <iostream>
#include <vector>
#include "rk4.h"


/*
 * IMPORTANT
 *
 * If you want to use additional parameters in a function containing
 * the right parts of the ode system, you need to create a structure
 * of type "params" and initialize it BEFORE defining the ode function.
 *
 */
struct params {
    float k = 0.0003;
} params;


/*
 * IMPORTANT
 *
 * Any function on the right side of the odu must be defined using
 * the following prototype:
 *
 * std::vector<float> %FUNC_NAME% (float t, std::vector<float> y, struct params *p)
 *
 * in which:
 * :float t: - default argument, define as time, [s].
 * :std::vector<float>: y - integration variables.
 * :struct params *p: - structure with additional parameters for the
 * function of the right parts of the odu system
 *
 */
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

    // Initialization of initial values
    std::vector<float> y0 {0, 100, 0, 100};

    // Solving a given ODE system on a given time interval with
    // given initial values and a given initial step
    std::vector<std::vector<float>> ans = rk4(&func, &params, 0, 5, &y0, 0.01);

    // Output of the obtained values
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            std::cout << ans[i][j] << " ";
        }
        std::cout << "\n";
    }


    // Solving a given system of oda at a certain moment with
    // given values and a given step
    std::vector<float> ans_iter = rk4_iteration(&func, &params, 0, &y0, 0.01);

    // Output of the obtained values
    for (auto & i : ans_iter) {
        std::cout << i << " ";
    }

    return 0;
}