#include <iostream>
#include <vector>
#include <cmath>
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
    float k = 0.003;
    float m = 110;
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
    float m = p->m;

    return std::vector<float> {
            y[1],
            static_cast<float>(-k / m * pow(y[1], 3)),
            y[3],
            static_cast<float>(-k / m * pow(y[3], 3) - G)
    };
}


int main() {

    // Initialization of initial values

    // Starting speed
    float v0 = 150;

    // Y-axis angle
    float beta = 45;

    // Initial conditional
    std::vector<float> y0 {
        0,  // x0
        static_cast<float>(v0 * cos(beta*M_PI/180)),  // Vx
        0,  // y0
        static_cast<float>(v0 * sin(beta*M_PI/180))   // Vy
    };

    // Solving a given ODE system on a given time interval with
    // given initial values and a given initial step using rk4()
    std::vector<std::vector<float>> ans = rk4(&func, &params, 0, 5, &y0, 0.01);

    // Output of the obtained values
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            std::cout << ans[i][j] << " ";
        }
        std::cout << "\n";
    }


    // Initialize necessary variables
    std::vector<std::vector<float>> ans_iter = {y0};
    std::vector<float> y;
    float FlightTime, Distance, Height, y4_old = 0;

    // Solving a given system of ODE using rk_iteration()
    // with some conditional
    for (float t = 0; t < UINT16_MAX; t += 0.01) {
        y = rk4_iteration(&func, &params, t, &ans_iter.back(), 0.01);

        // Max height
        if (y[3] * y4_old < 0) Height = y[2];

        // Flight distance and flight time
        if (y[3] < 0 && y[2] <= 0) {
            FlightTime = t;
            Distance = y[0];
            break;
        }

        y4_old = y[3];
        ans_iter.push_back(y);
    }

    // Output of the obtained values
    for (int i = 0; i < ans_iter.size(); i++) {
        for (int j = 0; j < ans_iter[i].size(); j++) {
            std::cout << ans_iter[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Some statistics about the shot
    std::cout << "\n\n";
    std::cout << "Flight Time = " << FlightTime << "\n";
    std::cout << "Distance = " << Distance << "\n";
    std::cout << "Max Height = " << Height << "\n";

    return 0;
}