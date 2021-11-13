import numpy as np
import matplotlib.pyplot as plt
import oscillation_functions as of
#from scipy.fft import fft, fftfreq
#%%
A = np.arange(1, 56)
folder = 'Force_pend_data/FR/'
solver = ['Heun/', 'Euler/'][0]
prefix  = '/Data' + '_'
B = np.zeros(len(A))
B2 = np.zeros(len(A))
Psi = np.zeros(len(A))
Freq = np.zeros(len(A))
for i in range(len(A)):
    name = solver + prefix + str(A[i]) + '.txt'
    X = np.loadtxt(folder + name, skiprows=1)[:, 1]
    x0, v0, w0, b, W, F0 = np.loadtxt(folder + name, max_rows=1)
    Freq[i] = W
    B2[i] = of.amplitude(w0, b, W, F0)
    B[i] = of.count_amplitude(X)
    Psi[i] = of.phase(w0, b, W)
#%%
fig, ax = plt.subplots()
ax.scatter(Freq, B, label='Эксп. точки')
ax.scatter(Freq, B2, color='r', label='Точная АЧХ')
ax.legend(loc='upper right', fontsize=12)
ax.grid()
ax.set_ylabel('A')
ax.set_xlabel('w, рад/с')
ax.set_title('АЧХ', fontsize=12)
plt.show()
