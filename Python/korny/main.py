import numpy as np
import matplotlib.pyplot as plt

def meth_poldelenya(f, a, b, epsilon):
    while b - a > epsilon:
        midpoint = (a + b) / 2.0
        if f(midpoint) == 0.0:
            return midpoint
        elif f(a) * f(midpoint) < 0.0:
            b = midpoint
        else:
            a = midpoint

    return (a + b) / 2.0

def newton_meth(f, x0, epsilon):
    x = x0
    while abs(f(x)) > epsilon:

        
        derivative = (f(x + epsilon) - f(x)) / epsilon
        x = x - f(x) / derivative
    return x


f = lambda x: x**3 - 6*np.sin(x)**2 + 11*x - 6


a, b = -10.0, 10.0
epsilon = 1e-6


root_bisection = meth_poldelenya(f, a, b, epsilon)
root_newton = newton_meth(f, 0.0, epsilon)

x_values = np.linspace(a, b, 100)
y_values = f(x_values)

plt.plot(x_values, y_values, label='f(x)')
plt.axhline(0, color='black', linewidth=0.8, linestyle='--', label='y=0')
plt.scatter([root_bisection, root_newton], [0, 0], color='red', label='Roots')
plt.title('Function and Roots')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.legend()
plt.grid(True)
plt.show()

print(f"poldeleniya method: {root_bisection}")
print(f"Newton's method: {root_newton}")
