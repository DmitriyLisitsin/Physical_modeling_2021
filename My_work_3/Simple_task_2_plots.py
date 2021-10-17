import numpy as np
import matplotlib.pyplot as plt

def read_data(path):
    D = np.array([])
    with open(path, "r") as file:
        data1 = []
        i = 0
        for line in file:
            if i:
                data1 = list(map(float, line.split(';')))
                D = np.append(D, data1, axis = 0)
            else:
                T, dt, k, R, v0 = list(map(float, line.split(';')))
            i += 1
    D = D.reshape(D.size//3, 3)
    t = D[:, 0]
    a = D[:, 1]
    b = D[:, 2]
    return t, a, b, T, dt, k, R, v0

def read_energy(path):
    D = np.array([])
    with open(file2, "r") as file:
        data1 = []
        for line in file:
            data1 = list(map(float, line.split(';')))
            D = np.append(D, data1, axis = 0)
    D = D.reshape(D.size//2, 2)
    Dt = D[:, 0]
    E = D[:, 1]
    return Dt, E


#D = np.fromfile("Data.txt", 'float', )
file1 = "Data.txt"
file2 = "Energy.txt"
file3 = "Data(Kohen).txt"
file4 = "Energy(Kohen).txt"

t1, a1, b1, T1, dt1, k1, R1, v01 = read_data(file1)
t2, a2, b2, T2, dt2, k2, R2, v02 = read_data(file3)
Dt1, E1 = read_energy(file2)
Dt2, E2 = read_energy(file4)
#%%
fig, ax = plt.subplots()
ax.plot(t1, R1*np.cos(np.sqrt(k1) * t1), 'b')
ax.plot(t2, R2*np.cos(np.sqrt(k2) * t2), 'r')
plt.show()
#%%
fig, ax = plt.subplots()
ax.plot(t1, (k1*a1**2 + b1**2)/2, 'b')
ax.plot(t2, (k2*a2**2 + b2**2)/2, 'r')
plt.title('Energy from t', fontsize = 12)
plt.show()
#%%
fig, ax = plt.subplots()
ax.plot(t1, a1, 'b')
ax.plot(t2, a2, 'r')
ax.plot(t1, R1*np.cos(np.sqrt(k1) * t1), 'b')
plt.title('x from t', fontsize = 12)
plt.show()
#%%
fig, ax = plt.subplots()
ax.plot(t1, b1, 'b')
ax.plot(t2, b2, 'r')
plt.title('v from t', fontsize = 12)
plt.show()
#%%
fig, ax = plt.subplots()
ax.plot(a1, b1, 'b')
ax.plot(a2, b2, 'r')
plt.title('v from x', fontsize = 12)
plt.show()
#%%
# =============================================================================
fig, ax = plt.subplots()
# plt.scatter(np.log10(Dt1), np.log10(E1), 'b')
# plt.scatter(np.log10(Dt2), np.log10(E2), 'r')
# #plt.scatter(Dt1, E1)
# plt.title('E from dt, t0 = ' + str(T), fontsize = 12)
# plt.show()
# =============================================================================
