#%%
import numpy as np
import matplotlib.pyplot as plt
from scipy.fft import fft, fftfreq

#%%
folder = 'My_work_7'
file = "/Data.txt"
Data = np.loadtxt('C:/Олег/Github/Physical_modeling_2021/' + folder + file)
T = Data[:, 0]
X = Data[:, 1]
V = Data[:, 2]
E = V**2/2 - np.cos(X)

#%%
s = 0
T0 = 0
T1 = 0
Xmax = np.max(X)
Xmin = np.min(X)
e = 0.01
for i in range(1, np.size(T)):
    if Xmax < X[i] + e and (s == 0 or s == 2):
        if s == 0:
            T0 = i
            s = 1
        elif s == 2:
            T1 = i
            break
    elif Xmax > X[i] + e and s == 1:
        s = 2
w = 2*np.pi / ((T1 - T0) * (T[2] - T[1]))
print(w)

#%%

Xf = fft(X)
Wf = fftfreq(np.size(T), T[2]-T[1])
plt.plot(Wf, Xf)
plt.show()

#%%
i, = np.where(Xf == np.max(Xf))
print(i)
print(Wf[i]*2*np.pi)
#%%
fig, ax = plt.subplots()
ax.plot(T, X, 'b')
plt.title('x from t', fontsize = 12)
plt.show()
#%%
fig, ax = plt.subplots()
ax.plot(T, V, 'r')
plt.title('v from t', fontsize = 12)
plt.show()
#%%
fig, ax = plt.subplots()
ax.plot(T, (E), 'r')
#ax.set_ylim([-1.1, -0.5])
plt.title('E from t', fontsize = 12)
plt.show()

#%%
fig, ax = plt.subplots()
ax.plot(X, V, 'r')
plt.title('V from X', fontsize = 12)
plt.show()