#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <cmath>
using namespace std;

// Updates population in place; last element of each individual stores the score
#include <vector>
#include <cmath>
#include <algorithm> // for std::clamp

inline void simulateSystemPID(std::vector<std::vector<float>> &population) {
    for (auto& ind : population) {

        // Simulation parameters
        const float dt = 0.01f;
        const float simTime = 5.0f;
        const int steps = static_cast<int>(simTime / dt);

        // PID gains from individual
        const float Kp = ind[0];
        const float Ki = ind[1];
        const float Kd = ind[2];

        // Second-order system parameters
        const float wn = 2.0f;   // natural frequency
        const float zeta = 0.5f; // damping ratio
        const float wn2 = wn * wn;
        const float twoZetaWn = 2.0f * zeta * wn;

        // System state
        float y = 0.0f;
        float y_dot = 0.0f;

        // PID state
        float integral = 0.0f;
        float prevError = 0.0f;
        float prevDerivative = 0.0f;
        float errorIntegral = 0.0f;

        const float alpha = 0.9f;
        const float maxU = 1e6f;
        const float maxIntegral = 1e3f;

        const float setpoint = 0.5f;
        float y_max = y;  // Track maximum y for overshoot

        for (int i = 0; i < steps; ++i) {
            float error = setpoint - y;

            // Integral with anti-windup
            integral = std::clamp(integral + error * dt, -maxIntegral, maxIntegral);

            // Derivative with low-pass filter
            float derivativeRaw = (error - prevError) / dt;
            float derivative = alpha * prevDerivative + (1.0f - alpha) * derivativeRaw;

            // PID controller with saturation
            float u = Kp * error + Ki * integral + Kd * derivative;
            u = std::clamp(u, -maxU, maxU);

            // Second-order system update
            float y_ddot = wn2 * (u - y) - twoZetaWn * y_dot;
            y_dot += y_ddot * dt;
            y += y_dot * dt;

            // Track error integral
            errorIntegral += std::fabs(error) * dt;

            // Track max output for overshoot
            y_max = std::max(y_max, y);

            prevError = error;
            prevDerivative = derivative;
        }

        // Compute % overshoot relative to setpoint
        float percentOS = 0.0f;
        if (y_max > setpoint) {
            percentOS = (y_max - setpoint) / setpoint;
        }

        // Combine costs: weighted sum (you can tune the weights)
        const float weightError = 1.0f;
        const float weightOS = 0.5f;
        float combinedCost = weightError * errorIntegral + weightOS * percentOS;

        // Check for NaN
        if (std::isnan(combinedCost)) {
            ind.back() = 100000.0f;
        } else {
            ind.back() = combinedCost;
        }
    }
}


inline void simulateSystemSEC(std::vector<std::vector<float>> &population)
{
    const float dt = 0.01f;
    const float simTime = 5.0f;
    const int steps = static_cast<int>(simTime / dt);

    // Second order system parameters
    const float wn = 2.0f;
    const float zeta = 0.5f;
    const float wn2 = wn * wn;
    const float twoZetaWn = 2.0f * zeta * wn;

    const float setpoint = 1.0f;

    const float weightError = 1.0f;
    const float weightOS = 0.5f;

    for (auto &ind : population)
    {
        const float Ks = ind[0];
        const float Ke = ind[1];
        const float Kc = ind[2];
        const float Ts = ind[3];
        const float Tc = ind[4];

        const float Ts2 = Ts * Ts;
        const float Tc2 = Tc * Tc;

        float errorIntegral = 0.0f;
        float y = 0.0f;
        float y_dot = 0.0f;
        float y_max = y;

        for (int i = 0; i < steps; ++i)
        {
            float error = setpoint - y;
            float error2 = error * error;

            float u =
                (error / std::sqrt(Ts2 + error2)) * Ks +
                (std::exp(error2) - 1.0f) * Ke +
                (Tc / std::sqrt(Tc2 + error2)) * Kc;

            float y_ddot = wn2 * (u - y) - twoZetaWn * y_dot;

            y_dot += y_ddot * dt;
            y += y_dot * dt;

            errorIntegral += std::fabs(error) * dt;

            if (y > y_max)
                y_max = y;
        }

        float percentOS = 0.0f;
        if (y_max > setpoint)
            percentOS = (y_max - setpoint) / setpoint;

        float combinedCost =
            weightError * errorIntegral +
            weightOS * percentOS;

        if (std::isnan(combinedCost))
            ind.back() = 100000.0f;
        else
            ind.back() = combinedCost;
    }
}



#endif
