import numpy as np
import matplotlib.pyplot as plt
#%%
file = "Array.txt"
Data  = np.loadtxt(file)

n_bins = 15
plt.hist(Data, bins = n_bins)
plt.show()