import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Generar datos ficticios
np.random.seed(0)
n = 100
edad = np.random.randint(20, 65, size=n)
salario = np.random.randint(20000, 100000, size=n)
ubicacion = np.random.randint(1, 4, size=n)  # Simulando ubicaciones geográficas: 1, 2 o 3

# Definir una función de Morse simple en 2D basada en salario y edad
def morse_function(salario, edad):
    return salario**2 + edad**2  # Función de Morse trivial para este ejemplo

# Definir los puntos críticos
def critical_points(salario, edad, delta=1000):
    crit_points = []
    for i in range(len(salario)):
        sal = salario[i]
        ed = edad[i]
        neighbors = [(sal + delta, ed), (sal - delta, ed), (sal, ed + delta), (sal, ed - delta)]
        for neighbor in neighbors:
            if neighbor[0] not in salario or neighbor[1] not in edad:
                crit_points.append((sal, ed))
                break
    return crit_points

# Encontrar los puntos críticos
crit_points = critical_points(salario, edad)

# Visualizar los datos y los puntos críticos
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(salario, edad, ubicacion, c='b', marker='o', label='Datos')
ax.scatter([x[0] for x in crit_points], [x[1] for x in crit_points], [1]*len(crit_points), c='r', marker='o', s=50, label='Puntos Críticos')
ax.set_xlabel('Salario')
ax.set_ylabel('Edad')
ax.set_zlabel('Ubicación')
plt.title('Datos y Puntos Críticos')
plt.legend()
plt.show()

print("Número de puntos críticos encontrados:", len(crit_points))