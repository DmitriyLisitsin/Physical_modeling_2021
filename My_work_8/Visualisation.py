#%%
import numpy as np
import matplotlib.pyplot as plt
import oscillation_functions as of
#%%
a = 5
folder = 'Arbitrary_pend_data/'
solver = ['Heun/', 'Euler/', 'RK4/'][2]
prefix  = 'Data' + '_'
name = solver + prefix + str(a) + '.txt'
Data = np.loadtxt(folder + name, skiprows=1)
T = Data[:, 0]
X = Data[:, 1]
V = Data[:, 2]
F = Data[:, 3]
E = Data[:, 4]
x0, v0, w0, b, W, F0 = np.loadtxt(folder + name, max_rows=1)
#%%
if_second = 0
if(if_second):
    folder2 = 'Arbitrary_pend_data/'
    solver2 = ['Heun/', 'Euler/', 'RK4/'][2]
    prefix2  = 'Data' + '_'
    name2 = solver2 + prefix + str(a) + ".txt"
    Data2 = np.loadtxt(folder2 + name2,  skiprows=1)
    T2 = Data2[:, 0]
    X2 = Data2[:, 1]
    V2 = Data2[:, 2]
    F2 = Data2[:, 3]
    E2 = Data2[:, 3]
    x02, v02, w02, b2, W2, F02 = np.loadtxt(folder2 + name2, max_rows=1)

#%%
fig, [[ax1, ax2], [ax3, ax4]] = plt.subplots(2, 2)
ax1.plot(T, X, label=solver)
#ax1.plot(T, of.impulses_response(T, W, np.pi/W, F0, w0, b, x0, v0, 100))
ax1.plot(T, of.cut_cos_response(T, W, F0, w0, b, x0, v0, 100))
#ax1.plot(T, F)

if(if_second):
    ax1.plot(T2, X2, label=solver2)
ax1.legend(loc='lower right', fontsize=12)
ax1.set_title('x from t', fontsize = 12)
ax2.plot(T, V, label=solver)
ax2.plot(T, F)
if(if_second):
    ax2.plot(T2, V2, label=solver2)
ax2.legend(loc='lower right', fontsize=12)
ax2.set_title('v from t', fontsize = 12)
ax3.plot(T, E, label=solver)
ax3.plot(T, F)
if(if_second):
    ax3.plot(T2, E2, label=solver2)
ax3.legend(loc='lower right', fontsize=12)
ax3.set_title('E from t', fontsize = 12)
ax4.plot(X, V, label=solver)
if(if_second):
    ax4.plot(X2, V2, label=solver2)
ax4.legend(loc='lower right', fontsize=12)
ax4.set_title('V from X', fontsize = 12)
plt.tight_layout()
plt.show()