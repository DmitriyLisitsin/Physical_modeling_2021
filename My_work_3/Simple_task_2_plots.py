import numpy as np
import matplotlib.pyplot as plt

D = np.array([])
with open("Data.txt", "r") as file:
    data1 = []
    for line in file:
        data1 = list(map(float, line.split(';')))
        D = np.append(D, data1, axis = 0)
D = D.reshape(D.size//3, 3)

t = D[:, 0]
a = D[:, 1]
b = D[:, 2]

plt.plot(a, b)
plt.show()

#plt.plot(t, a**2 + b**2/2)
plt.plot(t, a)
#plt.plot(t, b)
plt.show()