import numpy as np
import matplotlib.pyplot as plt
import oscillation_functions as of
#%%
A = np.arange(1, 56)
folder = 'Force_pend_data/FR/'
solver = ['Heun', 'Euler'][0]
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
    B[i] = of.count_amplitude2(X, int(4*len(A)/5))
    Psi[i] = of.phase(w0, b, W)

#%%
Wres = w0
print('Рез. частота: ', Wres)
Q = of.q_factor(b, w0)
print('Добротность: ', Q)
#%%
Wres_exp = Freq[np.argmax(B)]
print('Эксп. рез. частота: ', Wres_exp)

Bd = np.abs(B-np.max(B)/np.sqrt(2))
b1, b2 = np.partition(Bd, 2)[:2]
w1 = Freq[np.where(Bd == b1)]
w2 = Freq[np.where(Bd == b2)]
Q_exp = np.round(Wres_exp / np.abs(w1-w2), 1)[0]
print('Эксп.добротность: ', Q_exp)
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
