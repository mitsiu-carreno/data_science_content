import pandas as pd
from pingouin import cronbach_alpha

# Cargar los datos del cuestionario (archivo CSV o Excel)
# Por ejemplo, si tienes un archivo CSV:
data = pd.read_csv('ruta_al_archivo.csv')

# Calcular el Alfa de Cronbach
alpha, _ = cronbach_alpha(data)
print(f'Alfa de Cronbach: {alpha}')
