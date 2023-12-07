import math

def f(x):
    return math.sin(math.pow(x, 2) + 6 * x + 4)



def get_s_rectangle(a, b, n):
    delta = (b - a) / n
    res = 0.0
    for i in range(n):
        res += f(a + i * delta)
    return res * delta

def rectangle_method(a, b):
    n = 2
    s = get_s_rectangle(a, b, n)
    n *= 2
    s_next = get_s_rectangle(a, b, n)
    while abs(s_next - s) >= 0.000001:
        n *= 2
        s = get_s_rectangle(a, b, n)
        n *= 2
        s_next = get_s_rectangle(a, b, n)
    return s_next


def simpson_method(a, b):
    n = 1000
    delta = (b - a) / n
    res = 0.0
    for i in range(1, n, 2):
        res += delta * (f(a + (i - 1) * delta) + 4 * f(a + i * delta) + f(a + (i + 1) * delta)) / 3
    return res

a = 1.0
b = 15.0
value1 = rectangle_method(a, b)
value2 = simpson_method(a, b)
print("Метод прямоугольников:", value1)
print("Метод Симпсона:", value2)



