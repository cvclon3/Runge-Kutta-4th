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
    float km = k/m;
} params;


/*
 * IMPORTANT
 *
 * Any function on the right side of the odu must be defined using
 * the following prototype:
 *
 * float* %FUNC_NAME% (float t, float* y, struct params *p)
 *
 * in which:
 * :float t: - default argument, define as time, [s].
 * :float*: y - integration variables.
 * :struct params *p: - structure with additional parameters for the
 * function of the right parts of the odu system
 *
 */
float* func3(
        float t,
        float* y,
        struct params *p
) {

    float G = 9.81;
    float k = p->k;
    float m = p->m;

    return new float[4] {
            y[1],
            static_cast<float>(-k / m * pow(y[1], 3)),
            y[3],
            static_cast<float>(-k / m * pow(y[3], 3) - G)
    };
}


float* func2(
        float t,
        float *y,
        struct params *p
) {

    float G = 9.81;

    return new float[4]{
            y[1],
            static_cast<float>(-p->km * y[1] * sqrt(pow(y[1], 2) + pow(y[3], 2))),
            y[3],
            static_cast<float>(-p->km * y[3] * sqrt(pow(y[1], 2) + pow(y[3], 2)) - G)
    };
}


int main() {

    // Initialization of initial values
    // Number of equations of the given ODE system
    int NUM = 4;

    // Starting speed
    float v0 = 950;

    // Y-axis angle
    float beta = 30;

    // Initial conditional
    float *y0;
    y0 = new float[4]{
            0,  // x0
            static_cast<float>(v0 * cos(beta * M_PI / 180)),  // Vx
            0,  // y0
            static_cast<float>(v0 * sin(beta * M_PI / 180))   // Vy
    };


    // Initialize necessary variables
    std::vector<float*> ans_iter = {y0};
    float* y;
    float FlightTime, Distance, Height, y4_old = 0;

    // Solving a given system of ODE using (std::vector<float>) rk_iteration()
    // with some conditional
    for (float t = 0; t < UINT16_MAX; t += 0.01) {
        y = rk4_iteration(NUM, &func2, &params, t, ans_iter.back(), 0.01);

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
        for (int j = 0; j < NUM; j++) {
            std::cout << ans_iter[i][j] << " ";
        }
        std::cout << "\n";
    }


    // Some statistics about the shot
    std::cout << "\n\n";
    std::cout << "Flight Time = " << FlightTime << "\n";
    std::cout << "Distance = " << Distance << "\n";
    std::cout << "Max Height = " << Height << "\n";

    delete y0;
    return 0;
}