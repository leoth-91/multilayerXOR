import numpy as np
from matplotlib import pyplot as plt 

from matplotlib import rcParams
rcParams['font.family'] = 'serif'
rcParams.update({'text.usetex': True})
rcParams.update({'figure.autolayout': True})

path = 'error.txt'
plot_path = 'weight.png'

print('Creating Loss Plot:')
dpi = 300
fsize = 12

loss = np.transpose(np.genfromtxt(path, dtype=np.float32))

plt.plot(loss[0], loss[1], '.-', color='dodgerblue')
plt.ylabel('Recent Average Error',fontsize=fsize)
plt.xlabel('Epoch',fontsize=fsize)

# plt.ylim((np.min(loss[1]),np.max(loss[1])*1.05))
plt.ylim((0,np.max(loss[1])*1.05))

plt.xlim((np.min(loss[0]), np.max(loss[0])*1.01))
# plt.grid()
plt.savefig('error.png', dpi=dpi)
plt.close()

print('Done.')
