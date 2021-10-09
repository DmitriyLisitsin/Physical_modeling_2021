import numpy as np
import matplotlib.pyplot as plt

D = np.array([])
T, dt, k, R = 0, 0, 0, 0
with open("Data.txt", "r") as file:
    data1 = []
    i = 0
    for line in file:
        if i:
            data1 = list(map(float, line.split(';')))
            D = np.append(D, data1, axis = 0)
        else:
            T, dt, k, R, v0 = list(map(float, line.split(';')))
        i += 1
D = D.reshape(D.size//3, 3)

t = D[:, 0]
a = D[:, 1]
b = D[:, 2]

plt.plot(a, b)
plt.show()

plt.plot(t, a**2 + b**2/k)
#plt.plot(t, a)
#plt.plot(t, b)
plt.show()