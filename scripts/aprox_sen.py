import numpy as np

x1 = np.linspace(-np.pi, np.pi,100)
x2 = x1*x1
x3 = x2*x1
x4 = x3*x1
x5 = x4*x1
x0 = 0*x1+1

s = np.concat(
    [
        #x0[:, np.newaxis],
        x1[:, np.newaxis],
        #x2[:, np.newaxis],
        x3[:, np.newaxis],
        #x4[:, np.newaxis],
        x5[:, np.newaxis]
    ],
    axis=1
) # [100, 4]

sinx = np.sin(x1)

aprox, _, _, _ = np.linalg.lstsq(s, sinx[:,np.newaxis])

print(aprox, aprox.shape)

from matplotlib import pyplot as plt

plt.plot(x1, sinx, c='k')
plt.plot(x1, s@aprox, c='k', linestyle=':')
plt.show()