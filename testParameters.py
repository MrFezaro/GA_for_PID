import numpy as np
import matplotlib.pyplot as plt

# Simulation parameters
dt = 0.01          # Smaller dt for stability
T = 5.0
time = np.arange(0, T, dt)

# PID parameters
Kp = 2.3
Ki = 6.5
Kd = 1.6

# Second-order system parameters
wn = 2.0        # natural frequency
zeta = 0.5      # damping ratio

# Initialize system state
y = 0.0
y_dot = 0.0

# PID state
integral = 0.0
prev_error = 0.0
prev_derivative = 0.0
alpha = 0.9       # derivative smoothing

# Reference signal
setpoint = 1

# Store results
y_values = []

# Simulation loop
for t in time:
    error = setpoint - y
    
    # Integral term with anti-windup
    integral += error * dt
    integral = np.clip(integral, -1e3, 1e3)
    
    # Derivative with low-pass filter
    derivative_raw = (error - prev_error) / dt
    derivative = alpha * prev_derivative + (1 - alpha) * derivative_raw
    
    # PID control signal
    u = Kp * error + Ki * integral + Kd * derivative
    u = np.clip(u, -1e6, 1e6)
    
    # Second-order system update
    y_ddot = wn**2 * (u - y) - 2 * zeta * wn * y_dot
    y_dot += y_ddot * dt
    y += y_dot * dt
    
    y_values.append(y)
    prev_error = error
    prev_derivative = derivative

# Plot results
plt.plot(time, y_values)
plt.xlabel('Time [s]')
plt.ylabel('Output y')
plt.title('Second-order system with PID control')
plt.grid(True)
plt.show()
