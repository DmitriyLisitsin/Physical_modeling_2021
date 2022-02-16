import numpy as np
import matplotlib.pyplot as plt
#%%
def g1(X):
    return np.where(X < 0.5, np.sqrt(2*X), 2-np.sqrt(2-2*X))

#%%
X = np.random.sample(10000)
Y = g1(X)

n_bins = 50
plt.hist(Y, bins = n_bins)
plt.show()
