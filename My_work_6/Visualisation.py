#%%
import numpy as np
import matplotlib.pyplot as plt

#%%
folder = 'My_work_7'
file = "/Data.txt"
Data = np.loadtxt('C:/Олег/Github/Physical_modeling_2021/' + folder + file)
T = Data[:, 0]
X = Data[:, 1]
V = Data[:, 2]
E = V**2/2 - np.cos(X)
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
ax.plot(T, (E-E[0]), 'r')
plt.title('E from t', fontsize = 12)
plt.show()