#%%
import numpy as np
import matplotlib.pyplot as plt
from scipy.fft import fft, fftfreq

#%%
a = 1
folder = 'Force_pend_data/'
solver = ['Heun_', 'Euler_'][0]
name = solver + str(a) + ".txt"
Data = np.loadtxt(folder + name, skiprows=1)
T = Data[:, 0]
X = Data[:, 1]
V = Data[:, 2]

x0, v0, w0, b = np.loadtxt(folder + name, max_rows=1)
E = V**2/2 + (w0**2 - (b/2)**2) * X**2/2

#%%
w = np.round(np.sqrt(w0**2 - (b/2)**2), 5)
print('Частота: ', w)

Q = np.round(w/b, 5)
print('Добротность: ', Q)

#%%
s = 0
periods = 0
T0 = 0
T1 = 0
beg = np.size(T)//4
end = np.size(T)//2
for i in range(beg, end-1):
    if V[i] >= 0 and V[i+1] < 0:
        periods += 1
        if s == 0:
            s = 1
            T0 = i
            periods -= 1
        elif s == 1:
            T1 = i
w_exp = np.round(2*np.pi / ((T1 - T0) * (T[2] - T[1]))*periods, 5)
print('Эксп.частота: ', w_exp)

d_exp = np.log(X[T0]/X[T1])/periods

Q_exp = np.round(np.pi/d_exp, 5)
print('Эксп.добротность: ', Q_exp)
#%%

Xf = fft(X)
Wf = fftfreq(np.size(T), T[2]-T[1])
plt.plot(Wf, Xf)
plt.show()

#%%
i, = np.where(Xf == np.max(Xf))
print(i)
print(Wf[i]*2*np.pi)

