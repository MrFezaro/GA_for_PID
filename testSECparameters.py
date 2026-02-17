import numpy as np
import matplotlib.pyplot as plt

def simulate_system(population):
    dt = 0.01
    sim_time = 5.0
    steps = int(sim_time / dt)

    # Second order system parameters
    wn = 2.0
    zeta = 0.5
    wn2 = wn ** 2
    two_zeta_wn = 2 * zeta * wn

    setpoint = 1.0

    weight_error = 1.0
    weight_os = 0.5

    results = []

    for ind in population:
        Ks, Ke, Kc, Ts, Tc = ind[:5]
        Ts2 = Ts ** 2
        Tc2 = Tc ** 2

        error_integral = 0.0
        y = 0.0
        y_dot = 0.0
        y_max = y
        y_history = []

        for _ in range(steps):
            error = setpoint - y
            error2 = error ** 2

            u = (error / np.sqrt(Ts2 + error2)) * Ks + \
                (np.exp(error2) - 1.0) * Ke + \
                (Tc / np.sqrt(Tc2 + error2)) * Kc

            y_ddot = wn2 * (u - y) - two_zeta_wn * y_dot
            y_dot += y_ddot * dt
            y += y_dot * dt
            y_history.append(y)

            error_integral += abs(error) * dt
            if y > y_max:
                y_max = y

        percent_os = (y_max - setpoint) / setpoint if y_max > setpoint else 0.0
        combined_cost = weight_error * error_integral + weight_os * percent_os
        ind.append(combined_cost)
        results.append(y_history)

    return results

# Example population [Ks, Ke, Kc, Ts, Tc]
population = [
    [1.0, 0.5, 0.2, 0.1, 0.05],
    [1.5, 0.3, 0.1, 0.2, 0.1]
]

responses = simulate_system(population)
time = np.arange(0, 5.0, 0.01)

# Plot the results
for i, y_history in enumerate(responses):
    plt.plot(time, y_history, label=f'Individual {i+1}')
plt.axhline(1.0, color='k', linestyle='--', label='Setpoint')
plt.xlabel('Time [s]')
plt.ylabel('Output y')
plt.title('Second-Order System Response')
plt.legend()
plt.grid(True)
plt.show()
