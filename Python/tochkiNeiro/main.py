import numpy as np
import matplotlib.pyplot as plt
#нужно сделать так чтобы нейросеть определяла куда ставить точку а не цвет поставленных точек

def activation(x):
    return 1 if x > 0 else 0

def forward_in(xs,weights):
    s = np.dot(weights,xs)
    out =[]
    for value in s:
        loc_ar = []
        for var in value:
            loc_ar.append(activation(var))
        out.append(loc_ar)
    return out

def forward_out(xs,weights):
    s=np.dot(weights,xs)
    return [activation(value) for value in s]

def Lhidden():
    weights=np.array([[0,1,-0.2],[0,1,-0.8],[-1.5,-1,0.65],[-1.5,1,-0.35],[1.3,-1,-0.65],[-1.5,-1,0.65],[-1.5,1,-0.35],[-1.5,-1,0.65]])
    x_in=np.array([x1,x2,x3])
    return forward_in(x_in,weights)

def Layers(results):
    weights = np.array([1,-1,-1,-1,-1,-1,-1,-1])
    return forward_out(results,weights)



W = np.array([1, 1, -1])

N = 500
x1 = np.random.random(N)
x2 = np.random.random(N)
x3 = [1] * N
X = np.array([x1, x2, x3])
result = Lhidden()
result=Layers(result)


for i in range(N):
    if result[i] == 1:
        plt.scatter(x1[i], x2[i], c='green')
    else:
        plt.scatter(x1[i], x2[i], c='red')


x = [0.1,0.3,0.9,1.0,1.0,0.6,0.3,0.1]
y = [0.5,0.8,0.8,0.8,0.6,0.2,0.2,0.5]
plt.plot(x, y, color='blue')


plt.xlabel('x')
plt.ylabel('y')
plt.show()