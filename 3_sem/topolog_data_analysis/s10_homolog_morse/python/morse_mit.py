import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Definir una función de Morse simple en 2D
def morse_function(x, y):
    return x**2 + y**2  # Esta es una función de Morse trivial para un plano

# Definir los puntos críticos
def critical_points(x_range, y_range, delta=0.01):
    #x_range = np.arange(-5, 5, delta)
    #y_range = np.arange(-5, 5, delta)
    critical_points = []
    for x in x_range:
        for y in y_range:
            gradient = np.array([2*x, 2*y])  # Gradiente de la función de Morse
            if np.all(np.abs(gradient) < 0.1):  # Condición para puntos críticos
                critical_points.append([x, y])
    return np.array(critical_points)

# Generar datos para visualizar la función y los puntos críticos
XX = np.arange(-5, 5, 0.1)
YY = np.arange(-5, 5, 0.1)
X, Y = np.meshgrid(XX, YY)
Z = morse_function(X, Y)

# Encontrar los puntos críticos
crit_points = critical_points(XX, YY)

# Visualizar la función de Morse y los puntos críticos
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.8)
ax.scatter(crit_points[:,0], crit_points[:,1], morse_function(crit_points[:,0], crit_points[:,1]), color='red', s=50)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.title('Función de Morse y Puntos Críticos')
plt.show()

print("Número de puntos críticos encontrados:", len(crit_points))
print(crit_points)
