# Gen data
Este script genera varios archivos de distintas longitudes para usar en los benchmarks de dask y chunks

## Uso
Dentro del directorio de `gen_data.py` 
```bash
podman run -v .:/usr/src/app:Z -w /usr/src/app python:3.9.19-alpine3.20 sh -c "pip install pandas && python gen_data.py"
```

## Salida
Se espera que se generen los siguientes archivos:
- full_benchmarking_data.csv - 307,200,001 renglones
- 10k_benchmarking_data.csv - 10,000 renglones
- 100k_benchmarking_data.csv - 100,000 renglones
- 1M_benchmarking_data.csv - 1,000,000 renglones
- 50M_benchmarking_data.csv - 50,000,000 renglones
