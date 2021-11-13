import numpy as np
import matplotlib.pyplot as plt
#from scipy.fft import fft, fftfreq
#%%
def count_amplitude(w0, b, W, F0):
    return w0**2*F0/np.sqrt((w0**2-W**2)**2 + b**2*W**2)

def count_phase(w0, b, W):
    return np.arctan2(b*W, w0**2-W**2)
#%%
A = np.arange(1, 12)
folder = 'Force_pend_data/'
solver = ['Heun/', 'Euler/'][0]
prefix  = 'Data' + '_'
B = np.zeros(len(A))
Psi = np.zeros(len(A))
Freq = np.zeros(len(A))
for i in range(len(A)):
    name = solver + prefix + str(A[i]) + '.txt'
    x0, v0, w0, b, W, F0 = np.loadtxt(folder + name, max_rows=1)
    Freq[i] = W
    B[i] = count_amplitude(w0, b, W, F0)
    Psi[i] = count_phase(w0, b, W)
#%%
fig, ax = plt.subplots()
ax.scatter(Freq[:], B[:])
ax.grid()
plt.show()
