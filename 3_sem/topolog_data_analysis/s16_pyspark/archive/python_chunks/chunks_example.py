import pandas as pd 

chunksize = 10 ** 6
path = '/Users/alan/Documents/UniversidadCiudadAguascalientes/python/dask/benchmarking_data.csv'
with pd.read_csv(path, chunksize=chunksize) as reader:
    for chunk in reader:
        print(chunk)