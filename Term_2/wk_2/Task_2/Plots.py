import numpy as np
import matplotlib.pyplot as plt
#%%

Data = np.loadtxt("boxes_data.txt")
X = Data[:, 0]
Y = Data[:, 1]

plt.plot(X, Y)
plt.grid()
plt.show()