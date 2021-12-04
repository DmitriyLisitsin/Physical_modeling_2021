import numpy as np

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
        return (x0+(v0+x0*b/2)*T)*np.exp(-b/2*T)

def amplitude(w0, b, W, F0):
    return w0**2 * F0/np.sqrt((w0**2-W**2)**2 + b**2 * W**2)

def phase(w0, b, W):
    return np.arctan2(b*W, w0**2-W**2)

def force_oscillation(T, W, F0, w0, b, x0, v0):
    B = amplitude(w0, b, W, F0)
    psi0 = phase(w0, b, W)
    return B*np.cos(W*T-psi0) + friction_oscillation(T, w0, b, x0-B*np.cos(psi0), v0-B*W*np.sin(psi0))
    #return B*np.cos(W*T-psi0)

def sinus_response(T, W, F0, w0, b):
    B = amplitude(w0, b, W, F0)
    psi0 = phase(w0, b, W)
    return B*np.cos(W*T-psi0)

def impulses_response(T, W, tau, F0, w0, b, x0, v0, n_harmonics):
    Xt = np.zeros(len(T))
    I = np.arange(1, n_harmonics+1)
    Wi = I*W
    F = 2*F0/I/np.pi*np.sin(Wi*tau*0.5)
    B = amplitude(w0, b, Wi, F)
    psi0 = phase(w0, b, Wi)
    Xt += W*0.5/np.pi*tau*F0
    x0 -= W*0.5/np.pi*tau*F0
    for i in range(0, n_harmonics):
        Xt += B[i]*np.cos(Wi[i]*T-psi0[i])
        x0 -= B[i]*np.cos(psi0[i])
        v0 -= B[i]*Wi[i]*np.sin(psi0[i])
    return Xt + friction_oscillation(T, w0, b, x0, v0)


def cut_cos_response(T, W, F0, w0, b, x0, v0, n_harmonics):
    Xt = np.zeros(len(T))
    I = np.arange(1, n_harmonics+1)
    Wi = 2*I*W
    F = 2 * F0 / np.pi * (-1)**I / (1-(2*I)**2)
    B = amplitude(w0, b, W, F0)
    psi0 = phase(w0, b, W)
    Xt += F0/np.pi + 0.5*B*np.cos(W*T-psi0)
    x0 -= F0/np.pi + 0.5*B*np.cos(psi0)
    v0 -= 0.5*B*W*np.sin(psi0)
    B = amplitude(w0, b, Wi, F)
    psi0 = phase(w0, b, Wi)
    for i in range(0, n_harmonics):
        Xt += B[i]*np.cos(Wi[i]*T-psi0[i])
        x0 -= B[i]*np.cos(psi0[i])
        v0 -= B[i]*Wi[i]*np.sin(psi0[i])
    return Xt + friction_oscillation(T, w0, b, x0, v0)

def count_fft_frequency(t, Y):
    f = np.fft.fftfreq(len(t), t[1]-t[0])
    Yf = np.abs(np.fft.fft(Y))
    return np.abs(f[np.argmax(Yf[1:])+1])

def ang_frequency(b, w0):
    return np.sqrt(w0**2-(b/2)**2)

def q_factor(b, w0):
    return np.sqrt(w0**2-(b/2)**2)/b

def count_q_factor(T, V, X, b = None, e = None):
    s = 0
    periods = 0
    T0 = 0
    T1 = 0
    beg = b or np.size(T)//4
    end = e or np.size(T)//2
    for i in range(beg, end-1):
        if V[i] >= 0 and V[i+1] < 0:
            periods += 1
            if s == 0:
                s = 1
                T0 = i
                periods -= 1
            elif s == 1:
                T1 = i
    d = np.log(X[T0]/X[T1])/periods
    return np.pi/d

def count_frequency(T, V, b = None, e = None):
    s = 0
    periods = 0
    T0 = 0
    T1 = 0
    beg = b or np.size(T)//4
    end = e or np.size(T)//2
    for i in range(beg, end-1):
        if V[i] >= 0 and V[i+1] < 0:
            periods += 1
            if s == 0:
                s = 1
                T0 = i
                periods -= 1
            elif s == 1:
                T1 = i
    return 1 / ((T1 - T0) * (T[2] - T[1])) * periods

def count_amplitude(X, b = None, e = None):
    beg = b or 2*np.size(X)//3
    end = e or np.size(X)
    #return np.mean(-np.partition(-np.abs(X[::-1]), end-beg)[:end-beg])
    return np.max(X[beg:end])

def count_amplitude2(X, b = None, e = None):
    beg = b or 9*np.size(X)//3
    end = e or np.size(X)
    Amax = np.max(X[beg:end])
    Amin = np.min(X[beg:end])
    return( Amax - Amin)/2

if __name__ == "__main__":
    print("This module is not for direct call!")

