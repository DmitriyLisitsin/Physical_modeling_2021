import numpy as np
import matplotlib.pyplot as plt

beg = 0
end = 100
a = 2.5
b = -2

if_b = 1

x = np.arange(beg, end)
y = a*x + b + np.random.uniform(-1, 1, np.size(x))

A = np.vstack([x, np.full(len(x), if_b)]).T
print(A)
m, c = np.linalg.lstsq(A, y, rcond=None)[0]
print(m, c)
print(np.linalg.lstsq(A, y, rcond=None))

_ = plt.plot(x, y, 'o', label='Original data', markersize=5)
_ = plt.plot(x, m*x + c, 'r', label='Fitted line')
_ = plt.legend()
plt.show()