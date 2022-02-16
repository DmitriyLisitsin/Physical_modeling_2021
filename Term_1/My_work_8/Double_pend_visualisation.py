#%%
import numpy as np
import matplotlib.pyplot as plt
import pygame as py
#%%
a = 10
folder = 'Double_pend_data/'
solver = ['Heun/', 'Euler/', 'RK4/'][2]
prefix  = 'Data' + '_'
name = solver + prefix + str(a) + '.txt'
Data = np.loadtxt(folder + name, skiprows=1)
T = Data[:, 0]
X1 = Data[:, 1]
X2 = Data[:, 2]
V1 = Data[:, 3]
V2 = Data[:, 4]
F = Data[:, 5]
E = Data[:, 6]
x10, x20, v10, v20, m1, m2, L1, L2, F0, W = np.loadtxt(folder + name, max_rows=1)

#%%
fig, [[ax1, ax2], [ax3, ax4]] = plt.subplots(2, 2)
ax1.plot(T, X1, label='1')
ax1.plot(T, X2, label='2')
ax1.plot(T, F)
ax1.legend(loc='lower left', fontsize=12)
ax1.set_title('x from t', fontsize = 12)

ax2.plot(T, V1, label='1')
ax2.plot(T, V2, label='2')
ax2.legend(loc='lower right', fontsize=12)
ax2.set_title('v from t', fontsize = 12)

ax3.plot(T, E)
ax3.set_title('E from t', fontsize = 12)

ax4.plot(X1, V1, label='1')
ax4.plot(X2, V2, label='2')
ax4.legend(loc='lower right', fontsize=12)
ax4.set_title('v from x', fontsize = 12)
#%%
screen_X = 1000
screen_Y = 550
FPS = 30
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

k = min(screen_X/(L1 + L2)/2, screen_Y/(L1 + L2)/2)*0.9
l1 = k*L1
l2 = k*L2
x0, y0 = int(screen_X/2), int(screen_Y/2.6)
r1 = np.round(m1*10/(m1+m2))
r2 = np.round(m2*10/(m1+m2))
f = 100*F
py.display.update()
finished = False
i = 0
while not finished:
    clock.tick(FPS)
    for event in py.event.get():
        if event.type == py.QUIT:
            finished = True
    if i < len(T):
        py.draw.line(screen, BLACK, [x0, y0], [x0+l1*np.sin(X1[i]),y0+l1*np.cos(X1[i])], 5)
        py.draw.line(screen, BLACK, [x0+l1*np.sin(X1[i]), y0+l1*np.cos(X1[i])],
                    [x0+l1*np.sin(X1[i])+l2*np.sin(X2[i]),y0+l1*np.cos(X1[i])+l2*np.cos(X2[i])], 5)
        py.draw.line(screen, BLACK, [x0+l1*np.sin(X1[i])+l2*np.sin(X2[i]),y0+l1*np.cos(X1[i])+l2*np.cos(X2[i])],
                     [x0+l1*np.sin(X1[i])+l2*np.sin(X2[i]) + f[i]*np.cos(X2[i]),y0+l1*np.cos(X1[i])+l2*np.cos(X2[i]) - f[i]*np.sin(X2[i])], 3)
        py.draw.circle(screen, BLACK, [x0,y0], 5)
        py.draw.circle(screen, BLACK, [x0+l1*np.sin(X1[i]),y0+l1*np.cos(X1[i])], r1)
        py.draw.circle(screen, BLACK, [x0+l1*np.sin(X1[i])+l2*np.sin(X2[i]),y0+l1*np.cos(X1[i])+l2*np.cos(X2[i])], r2)
        
        py.display.update()
        screen.fill(WHITE)
    i += 1

py.quit()
