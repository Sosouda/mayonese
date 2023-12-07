import numpy as np
from scipy import interpolate
import matplotlib.pyplot as plt

def spline():
    x_dots = np.linspace(0, 30, 52)
    y_dots = np.cos( (x_dots ** 2) / 3 + 10)

    func_spline = interpolate.interp1d(x_dots, y_dots, kind="cubic")

    plt.plot(x_dots, y_dots, "o")
    plt.plot(x_dots, func_spline(x_dots), "--")
    plt.show()

if __name__ == "__main__":
    spline()


