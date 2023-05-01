import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['figure.figsize'] = [12, 8]
plt.rcParams.update({'font.size': 18})

dt = 0.001
t = np.arange(0, 2, dt)
f0 = 50
f1 = 250
t1 = 2
x = np.cos(2*np.pi*t*(f0 + (f1-f0)*np.power(t, 2)/(3*t1**2)))

result = plt.specgram(x, NFFT=128, Fs=1/dt, noverlap=0, cmap='jet')
magnitude = result[0]
times = result[2]
freqs = result[1]

with open("spectral.dat", "w") as file:
    for point in range(times.size):
        for bin in range(freqs.size):
            file.write(str(times[point]) + " " +
                       str(freqs[bin]) + " " +
                       str(magnitude[bin][point]) + "\n")
        file.write("\n")

# plt.colorbar()
# plt.show()
