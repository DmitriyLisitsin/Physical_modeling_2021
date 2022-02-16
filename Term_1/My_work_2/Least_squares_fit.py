
#%%
import numpy as np

#%%
def Dij(x, y, dig = 14):
    return np.round(np.mean(x*y) - np.mean(x) * np.mean(y), dig)

def mnk_coef(x, y, if_b = True, dig = 6):
    n = np.shape(x)[0]
    if if_b:
        k = Dij(x, y) / Dij(x, x)
        b = np.mean(y) - k * np.mean(x)
        si_k = np.sqrt(np.abs((Dij(y, y) / Dij(x, x) - k ** 2) / (n-2)))
        si_b = si_k * np.sqrt(Dij(x, x))
        return np.round([k, b, si_k, si_b], dig)
    else:
        k = np.mean(x * y) / np.mean(x * x)
        si_k = np.sqrt(np.abs((np.mean(y * y) / np.mean(x * x) - k ** 2) / (n-2)))
        return np.round([k, si_k], dig)