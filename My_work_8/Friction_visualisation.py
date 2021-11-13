#%%
import numpy as np
import matplotlib.pyplot as plt
#%%
def friction_oscillation(T, w0, b, x0, v0):
    if w0 > b/2:
        w = np.sqrt(w0**2-(b/2)**2)
        if x0 == 0.0:
            fi0 = np.pi/2
            A = v0/w
        else:
            fi0 = np.arctan((v0+x0*b/2)/x0/w)
            A = x0/np.cos(fi0)
        return A*np.cos(w*T-fi0)*np.exp(-b/2*T)
    elif w0 < b/2:
        u = np.sqrt((b/2)**2-w0**2)
        C1 = (x0*(u+b/2)+v0)/2/u
        C2 = x0-C1
        return (C1*np.exp(u*T) + C2*np.exp(-u*T))*np.exp(-b/2*T)
    else:
        print('here')
        return (x0+(v0+x0*b/2)*T)*np.exp(-b/2*T)

#%%
def get_frequency(t, Y):
    f = np.fft.fftfreq(len(t), t[1]-t[0])
    Yf = np.abs(np.fft.fft(Y))
    return np.abs(f[np.argmax(Yf[1:])+1])

#%%
a = 3
folder = 'Friction_pend_data/'
solver = ['Heun/', 'Euler/'][0]
prefix  = 'Data' + '_'
name = solver + prefix + str(a) + '.txt'
Data = np.loadtxt(folder + name, skiprows=1)
T = Data[:, 0]
X = Data[:, 1]
V = Data[:, 2]

x0, v0, w0, b = np.loadtxt(folder + name, max_rows=1)
E = V**2/2 + (w0**2 - (b/2)**2) * X**2/2

#%%
if_second = 1
if(if_second):
    folder2 = 'Friction_pend_data/'
    solver2 = ['Heun/', 'Euler/'][1]
    prefix2  = 'Data' + '_'
    name2 = solver2 + prefix + str(a) + ".txt"
    Data2 = np.loadtxt(folder2 + name2, skiprows=1)
    T2 = Data2[:, 0]
    X2 = Data2[:, 1]
    V2 = Data2[:, 2]
    
    x02, v02, w02, b2= np.loadtxt(folder2 + name2, max_rows=1)
    E2 = V2**2/2 + (w02**2 - (b2/2)**2) * X2**2/2

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
w_exp1 = np.round(2*np.pi / ((T1 - T0) * (T[2] - T[1]))*periods, 5)
print('Эксп.частота 1: ', w_exp1)

d_exp = np.log(X[T0]/X[T1])/periods

Q_exp = np.round(np.pi/d_exp, 5)
print('Эксп.добротность: ', Q_exp)
#%%
w_exp2 = np.round(2*np.pi*get_frequency(T, X), 3)
print('Эксп.частота 2: ', w_exp2)
#%%
# =============================================================================
# Xf = fft(X)
# Wf = fftfreq(np.size(T), T[2]-T[1])
# plt.plot(Wf, Xf)
# plt.show()
# 
# #%%
# i, = np.where(Xf == np.max(Xf))
# print(i)
# print(Wf[i]*2*np.pi)
# =============================================================================
#%%
fig, ax = plt.subplots()
ax.plot(T, X, label=solver)
Xt = friction_oscillation(T, w0, b, x0, v0)
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
ax.legend(loc='upper right', fontsize=12)
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