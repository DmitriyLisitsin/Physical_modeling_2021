import numpy as np
import matplotlib.pyplot as plt
#%%

Data = np.loadtxt("5_boxes_data_1.txt")
X = Data[:, 0]
Y = Data[:, 1]

def point(S, K):
    p = 0
    for i in range(1, K+1):
        p += (-1)**(i+K) * i**S / np.math.factorial(i) / np.math.factorial(K-i)
    p *= np.math.factorial(K)/K**S
    return p
    

K = 5
Yp = np.zeros(len(X))
for i in range(len(X)):
    Yp[i] = point(X[i], K)
        
fig, ax = plt.subplots()
ax.plot(X, Y, 'o', label='K='+str(K))
ax.plot(X, Yp)
ax.legend(loc='lower right')
ax.set_ylabel('Вероятность')
ax.set_xlabel('N')
plt.grid()
plt.show()