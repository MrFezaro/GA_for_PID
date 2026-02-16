#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <cmath>
using namespace std;

// Updates population in place; last element of each individual stores the score
inline void simulateSystem(vector<vector<float>> &population) {
    for (auto& ind : population) {
        float dt = 0.01f;
        float simTime = 5.0f;
        float Kp = ind[0];
        float Ki = ind[1];
        float Kd = ind[2];

        float y = 0.0f;
        float integral = 0.0f;
        float prevError = 0.0f;
        float errorIntegral = 0.0f;

        for (float t = 0.0f; t < simTime; t += dt) {
            float setpoint = 1.0f;
            float error = setpoint - y;
            integral += error * dt;
            float derivative = (error - prevError) / dt;
            float u = Kp * error + Ki * integral + Kd * derivative;

            y += (-y + u) * dt;

            errorIntegral += fabs(error) * dt;
            prevError = error;
        }

        ind[3] = errorIntegral; // store score in last element
    }
}

#endif
