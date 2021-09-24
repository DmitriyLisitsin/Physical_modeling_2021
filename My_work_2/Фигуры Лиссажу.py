#%%


import numpy as np
import matplotlib.pyplot as plt


#%%

Ax = 2
Ay = 2
wx = 2
wy = 3
fix = 0
fiy = 0

t = np.arange(-3.14, 3.15, 0.01)
X = Ax * np.sin(wx*t + fix)
Y = Ay * np.sin(wy*t + fiy)
plt.plot(X, Y)
plt.show()


plt.hist(X)
plt.show()
plt.hist(Y)
plt.show()

