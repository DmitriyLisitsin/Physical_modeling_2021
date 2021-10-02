import numpy as np
import matplotlib.pyplot as plt

T = 100
dt = 0.1
k = 1
R = 6370000

iter = int(T / dt)
print(iter)
a = np.zeros(iter)
b = np.zeros(iter)
a[0] = R
b[0] = 0
for i in range(iter-1):
    a[i+1] = a[i] + b[i]*dt
    b[i+1] = b[i] - a[i]*k*dt

print(a)
t = np.arange(iter)
#plt.plot(t, a)
plt.plot(a, b)
plt.show()