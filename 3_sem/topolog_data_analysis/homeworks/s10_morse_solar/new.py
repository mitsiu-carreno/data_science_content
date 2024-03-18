# Mitsiu Alejandro Carreño Sarabia E23S-18014

# data sets from https://github.com/Bob05757/Renewable-energy-generation-input-feature-variables-analysis/blob/main/README.md
import csv
import math
from datetime import datetime
import numpy as np
import matplotlib.pyplot as plt

with open("wind_farm.csv", "r") as file:
    csv_reader = csv.DictReader(file)
    wind_farm_data = [row for row in csv_reader]


with open("solar_energy.csv", "r") as file:
    csv_reader = csv.DictReader(file)
    solar_energy_data = [row for row in csv_reader]

def morse_function(x, y):
    return x**2 + y**2  

def analisis_medias(x_values, y_values):
    print(f"X max: {max(x_values)}")
    print(f"X min: {min(x_values)}")
    print(f"X mean: {np.mean(x_values)}")
    print(f"X std: {np.std(x_values)}")
    print(f"X var: {np.var(x_values)}")
    print(f"X quartiles: {np.quantile(x_values,[0.25, 0.5, 0.75])}")
    print("-"*12)
    print(f"Y max: {max(y_values)}")
    print(f"Y min: {min(y_values)}")
    print(f"Y mean: {np.mean(y_values)}")
    print(f"Y std: {np.std(y_values)}")
    print(f"Y var: {np.var(y_values)}")
    print(f"Y quariles: {np.quantile(y_values,[0.25, 0.5, 0.75])}")

    return np.quantile(x_values, 0.95) + np.quantile(y_values, 0.95);

def critical_points(x_range,y_range, threshold):
    critical_points = []
    for x in x_range:
        for y in y_range:
            if (x + y) > threshold:  # Condición para puntos críticos
                critical_points.append([x, y])
    return np.array(critical_points)


def process_wind_farm_data(wind_farm_data):
    raw_values = {}

    for element in wind_farm_data:
        raw_date = element["date"]

        # Convertir a objeto datetime
        date_object = datetime.strptime(raw_date, "%Y-%m-%d %H:%M:%S")

        # Convertir a formato yyyy-mm-dd
        formatted_date = date_object.strftime("%Y-%m-%d")
        if formatted_date in raw_values:
            raw_values[formatted_date] = round(
                float(raw_values[formatted_date]) + float(element["power"]), 2
            )
        else:
            raw_values[formatted_date] = element["power"]

    return raw_values


x_raw_values = process_wind_farm_data(wind_farm_data)

y_raw_values = process_wind_farm_data(solar_energy_data)

# en este punto los valores en raw de ambos elementos son diferentes hay que emparejarlos 

x_values = []
y_values = []

for date,power in y_raw_values.items():
    if date in x_raw_values:
        x_values.append(int(x_raw_values[date]))
        y_values.append(int(power))


threshold = analisis_medias(x_values, y_values)

crit_points = critical_points(x_values,y_values, threshold)
X, Y = np.meshgrid(x_values, y_values)
z = morse_function(X, Y)

#z.tofile("./output", ",");
#print(z.shape)
#print(z.max())
#print(z.min())
#print(np.mean(z))
#print(np.std(z))
#print(np.var(z))
#print(np.quantile(z, [0.25, 0.5, 0.75, 0.8]))
#print(math.sqrt(np.quantile(z, 0.8)))


fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")
ax.plot_surface(x_values, y_values, z, cmap="viridis", alpha=0.8)
ax.scatter(
    crit_points[:, 0],
    crit_points[:, 1],
    morse_function(crit_points[:, 0], crit_points[:, 1]),
    color="red",
    s=50,
)
ax.set_xlabel("x_values")
ax.set_ylabel("y_values")
ax.set_zlabel("z")
plt.title("Función de Morse y Puntos Críticos")
plt.show()

print("Número de puntos críticos encontrados:", len(crit_points))

