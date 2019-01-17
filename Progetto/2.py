from mpl_toolkits.mplot3d.art3d import Poly3DCollection
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure(figsize=plt.figaspect(0.5))

poliVTX = np.array([[np.cos(t), np.sin(t), 0] for t in np.linspace(0, 2*np.pi,11,endpoint=False)])

#First Figure (2D)
ax = fig.add_subplot(1, 2, 1)
ax.set_aspect('equal')
ax.fill(poliVTX[:,0],poliVTX[:,1])


#Second Figure (3D)
ax = fig.add_subplot(1, 2, 2, projection='3d')
poli = Poly3DCollection([poliVTX])
poli.set_edgecolor('k')
ax.add_collection3d(poli)
ax.set_xlim(-1, 1)
ax.set_ylim(-1, 1)
ax.set_zlim(-1, 1)
ax.set_xlabel('X axis')
ax.set_ylabel('Y axis')
ax.set_zlabel('Z axis')



plt.show()
