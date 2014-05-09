
# In[10]:

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


# In[11]:

#importando datos
data = np.loadtxt("resultados_schro.txt", dtype = type(0.0))



# In[12]:

#metodo para animacion
fig = plt.figure()
ax = plt.axes(xlim=(-60,60), ylim=(-0.01,0.01))
line, = ax.plot([], [], lw=2)

def init():
    line.set_data([],[])
    return line,

def animate(i):
    x = np.linspace(-75,75,len(data[0]))
    y = data[i]
    line.set_data(x,y)
    return line,

anim = animation.FuncAnimation(fig, animate, init_func = init, frames = len(data), interval = 1.5/100.0, blit = True)
plt.show() 
