# Ulises unzip

import os
import zipfile


def extraer_archivos_zip(directorio):
    # Recorrer todos los archivos en el directorio
    for archivo in os.listdir(directorio):
        # Verificar si es un archivo .zip
        if archivo.endswith(".zip"):
            # Construir la ruta completa del archivo zip
            ruta_zip = os.path.join(directorio, archivo)

            # Extraer el archivo zip en el mismo directorio
            with zipfile.ZipFile(ruta_zip, "r") as zip_ref:
                zip_ref.extractall(directorio)

            # Mensaje de retroalimentación
            print(f"Archivos extraídos con éxito: {ruta_zip}")


# Obtener el directorio del archivo .py actual
directorio_actual = os.path.dirname(os.path.abspath(__file__))

# Llamar a la función para extraer los archivos zip en el directorio actual
extraer_archivos_zip(directorio_actual)
