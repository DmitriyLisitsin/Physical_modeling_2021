#%%
import numpy as np
import matplotlib.pyplot as plt
import oscillation_functions as of
#%%
a = 5
folder = 'Force_pend_data/'
solver = ['Heun/', 'Euler/'][0]
prefix  = 'Data' + '_'
name = solver + prefix + str(a) + '.txt'
Data = np.loadtxt(folder + name, skiprows=1)
T = Data[:, 0]
X = Data[:, 1]
V = Data[:, 2]

x0, v0, w0, b, W, F0 = np.loadtxt(folder + name, max_rows=1)
#E = V**2/2 + (w0**2 - (b/2)**2) * X**2/2
E = V**2/2 + w0**2 * X**2/2

#%%
if_second = 0
if(if_second):
    folder2 = 'Force_pend_data/'
    solver2 = ['Heun/', 'Euler/'][1]
    prefix2  = 'Data' + '_'
    name2 = solver2 + prefix + str(a) + ".txt"
    Data2 = np.loadtxt(folder2 + name2,  skiprows=1)
    T2 = Data2[:, 0]
    X2 = Data2[:, 1]
    V2 = Data2[:, 2]
    
    x02, v02, w02, b2, W2, F02 = np.loadtxt(folder2 + name2, max_rows=1)
    E2 = V2**2/2 + (w02**2 - (b2/2)**2) * X2**2/2

#%%
print('Частота: ', W)

Q = np.round((w0**2 - (b/2)**2)/b, 4)
print('Добротность: ', Q)

w_exp1 = np.round(2*np.pi * of.count_frequency(T, V), 3)
print('Эксп.частота 1: ', w_exp1)

w_exp2 = np.round(2*np.pi*of.count_fft_frequency(T, X), 3)
print('Эксп.частота 2: ', w_exp2)
#%%
fig, ax = plt.subplots()
ax.plot(T, X, label=solver)
Xt = of.force_oscillation(T, W, F0, w0, b, x0, v0)
ax.plot(T, Xt, label='analitic')
if(if_second):
    ax.plot(T2, X2, label=solver2)
ax.legend(loc='lower right', fontsize=12)
plt.title('x from t', fontsize = 12)
plt.show()
#%%
fig, ax = plt.subplots()
ax.plot(T, V, label=solver)
if(if_second):
    ax.plot(T2, V2, label=solver2)
ax.legend(loc='lower right', fontsize=12)
plt.title('v from t', fontsize = 12)
plt.show()
#%%
fig, ax = plt.subplots()
ax.plot(T, (E), label=solver)
if(if_second):
    ax.plot(T2, E2, label=solver2)
ax.legend(loc='lower right', fontsize=12)
#ax.set_ylim([np.min(E), np.max(E)])
#ax.set_ylim([0, 0.1])
plt.title('E from t', fontsize = 12)
plt.show()

#%%
fig, ax = plt.subplots()
ax.plot(X, V, label=solver)
if(if_second):
    ax.plot(X2, V2, label=solver2)
ax.legend(loc='lower right', fontsize=12)
plt.title('V from X', fontsize = 12)
plt.show()

