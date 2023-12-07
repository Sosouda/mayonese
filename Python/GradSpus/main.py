import numpy as np
import matplotlib.pyplot as plt



def target_function(x, y):
    return x**2 + y**2 + np.sin(5 * x) + np.sin(5 * y)

def derivative_x(x, y):
    return 2 * x + 5 * np.cos(5 * x)

def derivative_y(x, y):
    return 2 * y + 5 * np.cos(5 * y)


learning_rate = 0.04
num_iterations = 100
start_point = (10.0, 100.0)

x_values = [start_point[0]]
y_values = [start_point[1]]
z_values = [target_function(start_point[0], start_point[1])]


for _ in range(num_iterations):
    x, y = start_point
    gradient_x = derivative_x(x, y)
    gradient_y = derivative_y(x, y)
    start_point = (x - learning_rate * gradient_x, y - learning_rate * gradient_y)
    x_values.append(start_point[0])
    y_values.append(start_point[1])
    z_values.append(target_function(start_point[0], start_point[1]))

x_min, x_max = min(x_values), max(x_values)
y_min, y_max = min(y_values), max(y_values)
z_min, z_max = min(z_values), max(z_values)
x = np.linspace(x_min, x_max, 100)
y = np.linspace(y_min, y_max, 100)
X, Y = np.meshgrid(x, y)
Z = target_function(X, Y)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.8, label="Целевая функция")
ax.scatter(x_values, y_values, z_values, c='red', marker='o', label="Точки спуска")
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_xlim(x_min, x_max)
ax.set_ylim(y_min, y_max)
ax.set_zlim(z_min, z_max)
ax.legend()
plt.title("Градиентный спуск")

plt.show()
