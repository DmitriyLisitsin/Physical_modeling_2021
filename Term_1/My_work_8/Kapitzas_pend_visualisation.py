#%%
import numpy as np
import matplotlib.pyplot as plt
import pygame as py
#%%
a = 16
folder = 'Kapitzas_pend_data/'
solver = ['Heun/', 'Euler/', 'RK4/'][2]
prefix  = 'Data' + '_'
name = solver + prefix + str(a) + '.txt'
Data = np.loadtxt(folder + name, skiprows=1)
T = Data[:, 0]
X = Data[:, 1]
V = Data[:, 2]
F = Data[:, 3]
E = Data[:, 4]
x0, v0, L, F0, W = np.loadtxt(folder + name, max_rows=1)

#%%
fig, [[ax1, ax2], [ax3, ax4]] = plt.subplots(2, 2)
ax1.plot(T, X, label='1')
ax1.plot(T, F)
ax1.legend(loc='lower left', fontsize=12)
ax1.set_title('x from t', fontsize = 12)

ax2.plot(T, V, label='1')
ax2.legend(loc='lower right', fontsize=12)
ax2.set_title('v from t', fontsize = 12)

ax3.plot(T, E)
ax3.set_title('E from t', fontsize = 12)

ax4.plot(X, V, label='1')
ax4.legend(loc='lower right', fontsize=12)
ax4.set_title('v from x', fontsize = 12)
#%%
screen_X = 1000
screen_Y = 550
FPS = min(int(1/(T[2]-T[1])), 300)

WHITE = (255, 255, 255)
RED = (225, 0, 50)
BLACK = (0 , 0 , 0)
lightBLACK = (3,3,3)
lightGreen = (0, 255, 0)
BLUE  = (0,0,255, 20)
GRAY = (125, 125, 125)
lightBlue = (64, 128, 255)
GREEN = (0, 200, 64, 20)
YELLOW = (225, 225, 0, 2)
PINK = (230, 50, 230, 0)
brown = (105, 82, 62, 255)
darkorange3 = (205, 102, 0, 255)
rosybrown5 = (159, 125, 125, 255)
sandybrown = (244, 164, 96, 255)
CLEAR = (0,0,0,0)

py.init()
screen = py.display.set_mode((screen_X , screen_Y))
clock = py.time.Clock()
screen.fill(WHITE)

k = min(screen_X, screen_Y)/(L+F0)/2*0.9
l1 = k*L
f = k*F
x0, y0 = int(screen_X/2), int(screen_Y/2)
r = 10
py.display.update()
finished = False
i = 190000
while not finished:
    clock.tick(FPS)
    for event in py.event.get():
        if event.type == py.QUIT:
            finished = True
    if i < len(T):
        py.draw.line(screen, BLACK, [x0, y0-f[i]], [x0+l1*np.sin(X[i]),y0-f[i]+l1*np.cos(X[i])], 5)
        
        py.draw.circle(screen, BLACK, [x0, y0-f[i]], 5)
        py.draw.circle(screen, BLACK, [x0+l1*np.sin(X[i]),y0-f[i]+l1*np.cos(X[i])], r)
        
        py.display.update()
        screen.fill(WHITE)
    i += 1

py.quit()

