#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <cmath>
using namespace std;

// Updates population in place; last element of each individual stores the score
inline void simulateSystemPID(std::vector<std::vector<float>> &population) {
    for (auto& ind : population) {

        double dt = 0.01;
        double simTime = 5.0;

        double Kp = ind[0];
        double Ki = ind[1];
        double Kd = ind[2];

        // Second-order system parameters
        double wn = 2.0;   // natural frequency
        double zeta = 0.5; // damping ratio

        // System state
        double y = 0.0;
        double y_dot = 0.0;

        // PID state
        double integral = 0.0;
        double prevError = 0.0;
        double prevDerivative = 0.0;
        double errorIntegral = 0.0;

        double alpha = 0.9;
        double maxU = 1e6;
        double maxIntegral = 1e3;

        double setpoint = 0.5;
        double y_max = y;  // Track maximum y for overshoot

        for (double t = 0.0; t < simTime; t += dt) {

            double error = setpoint - y;

            // Integral with anti-windup
            integral += error * dt;
            if (integral > maxIntegral) integral = maxIntegral;
            if (integral < -maxIntegral) integral = -maxIntegral;

            // Derivative with low-pass filter
            double derivativeRaw = (error - prevError) / dt;
            double derivative = alpha * prevDerivative + (1.0 - alpha) * derivativeRaw;

            // PID controller
            double u = Kp * error + Ki * integral + Kd * derivative;
            if (u > maxU) u = maxU;
            if (u < -maxU) u = -maxU;

            // Second-order system update
            double y_ddot = wn*wn * (u - y) - 2.0 * zeta * wn * y_dot;
            y_dot += y_ddot * dt;
            y += y_dot * dt;

            // Track error integral
            errorIntegral += fabs(error) * dt;

            // Track max output for overshoot
            if (y > y_max) y_max = y;

            prevError = error;
            prevDerivative = derivative;
        }

        // Compute % overshoot relative to setpoint
        double percentOS = 0.0;
        if (y_max > setpoint) {
            percentOS = (y_max - setpoint) / setpoint;
        }

        // Combine costs: weighted sum (you can tune the weights)
        double weightError = 1;
        double weightOS = 0.5;
        double combinedCost = weightError * errorIntegral + weightOS * percentOS;

        // Store results in last element
        ind.back() = combinedCost;
    }
}

inline void simulateSystemSEC(std::vector<std::vector<float>> &population) {
    for (auto& ind : population) {

        double dt = 0.01;
        double simTime = 5.0;

        double Ks = ind[0];
        double Ke = ind[1];
        double Kc = ind[2];

        // Second-order system parameters
        double wn = 2.0;   // natural frequency
        double zeta = 0.5; // damping ratio

        // System state
        double errorIntegral = 0.0;
        double y = 0.0;
        double y_dot = 0.0;

        double setpoint = 0.5;
        double y_max = y;  // Track maximum y for overshoot

        for (double t = 0.0; t < simTime; t += dt) {

            double error = setpoint - y;

            // SEC controller
            double u = 10;

            // Second-order system update
            double y_ddot = wn*wn * (u - y) - 2.0 * zeta * wn * y_dot;
            y_dot += y_ddot * dt;
            y += y_dot * dt;

            // Track error integral
            errorIntegral += fabs(error) * dt;
        }

        // Compute % overshoot relative to setpoint
        double percentOS = 0.0;
        if (y_max > setpoint) {
            percentOS = (y_max - setpoint) / setpoint;
        }

        // Combine costs: weighted sum (you can tune the weights)
        double weightError = 0.5;
        double weightOS = 0.25;
        double combinedCost = weightError * errorIntegral + weightOS * percentOS;

        // Store results in last element
        ind.back() = combinedCost;
    }
}


#endif
