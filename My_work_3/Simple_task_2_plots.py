import numpy as np
import matplotlib.pyplot as plt

D = np.array([])
T, dt, k, R = 0, 0, 0, 0

#D = np.fromfile("Data.txt", 'float', )

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

D = np.array([])
with open("Energy.txt", "r") as file:
    data1 = []
    for line in file:
        data1 = list(map(float, line.split(';')))
        D = np.append(D, data1, axis = 0)
D = D.reshape(D.size//2, 2)
Dt = D[:, 0]
E = D[:, 1]

plt.plot(t, (k*a**2 + b**2)/2)
plt.title('Energy from t', fontsize = 12)
plt.show()
plt.plot(t, a)
plt.title('x from t', fontsize = 12)
plt.show()
plt.plot(t, b)
plt.title('v from t', fontsize = 12)
plt.show()
plt.plot(a, b)
plt.title('v from x', fontsize = 12)
plt.show()
plt.scatter(np.log10(Dt), np.log10(E))
#plt.scatter(Dt, E)
plt.title('E from dt, t0 = ' + str(T), fontsize = 12)
plt.show()
