#%%
import numpy as np

#%%

n = 10
Arr = np.diag(np.full(n, 2))
c = np.diag(np.full(n-1, -1), 1)
Arr += c + c.T
print(Arr)