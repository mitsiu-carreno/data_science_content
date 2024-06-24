Mitsiu Alejandro Carreño Sarabia - E23S-18014

# Descripción:
El siguiente código permite levantar dos contenedores, uno con el gestor de bases de datos postgres y el otro con una API Rest para consumir y crear datos alojados en el gestor de base de datos.
# Procedimiento:
1. Se deberán descargar los datos para llenar la base de datos, se puede descargar cualquiera de los dos archivos (el sql ocupa más disco pero se carga más rápido, el archivo parquet ocupa menos espacio pero es más lento en cargar) contenidos en [drive](https://drive.google.com/drive/folders/1udL7Kr08BGNz_TQNnWH0qwG1C8zQWW0X?usp=sharing) y se deben guardar en la carpeta **data**:

2. Una vez que los archivos sql o parquet estén en **data** se puede usar el siguiente comando para levantar la api del proyecto:
```bash
# Para docker
docker compose up
```
ó 
```bash
# Para podman
podman-compose -f podman-compose.yml up
```
Se preparan los contenedores y configuraciones necesarias para levantar los contenedores, cuando estén listos deberá aparecer un mensaje como el siguiente:
```bash
[api]  	| INFO 	Using path main.py                                                	 
[api]  	| INFO 	Resolved absolute path /usr/src/api/main.py                       	 
[api]  	| INFO 	Searching for package file structure from directories with __init__.py
[api]  	|      	files                                                             	 
[api]  	| INFO 	Importing from /usr/src/api                                       	 
[api]  	|                                                                            	 
[api]  	|  ╭─ Python module file ─╮                                                  	 
[api]  	|  │                  	│                                                  	 
[api]  	|  │  🐍 main.py      	│                                                  	 
[api]  	|  │                  	│                                                  	 
[api]  	|  ╰──────────────────────╯                                                  	 
[api]  	|                                                                            	 
[api]  	| INFO 	Importing module main                                             	 
[api]  	| Trying to connect to database
[api]  	| Database connected successfully
[api]  	| INFO 	Found importable FastAPI app                                      	 
[api]  	|                                                                            	 
[api]  	|  ╭─ Importable FastAPI app ─╮                                              	 
[api]  	|  │                      	│                                              	 
[api]  	|  │  from main import app	│                                              	 
[api]  	|  │                      	│                                              	 
[api]  	|  ╰──────────────────────────╯                                              	 
[api]  	|                                                                            	 
[api]  	| INFO 	Using import string main:app                                      	 
[api]  	|                                                                            	 
[api]  	|  ╭─────────── FastAPI CLI - Production mode ───────────╮                   	 
[api]  	|  │                                                 	│                   	 
[api]  	|  │  Serving at: http://0.0.0.0:8000                	│                   	 
[api]  	|  │                                                 	│                   	 
[api]  	|  │  API docs: http://0.0.0.0:8000/docs             	│                   	 
[api]  	|  │                                                 	│                   	 
[api]  	|  │  Running in production mode, for development use:   │                   	 
[api]  	|  │                                                 	│                   	 
[api]  	|  │  fastapi dev                                    	│                   	 
[api]  	|  │                                                 	│                   	 
[api]  	|  ╰─────────────────────────────────────────────────────╯                   	 
[api]  	|                                                                            	 
[api]  	| INFO: 	Started server process [1]
[api]  	| INFO: 	Waiting for application startup.
[api]  	| INFO: 	Application startup complete.
[api]  	| INFO: 	Uvicorn running on http://0.0.0.0:8000 (Press CTRL+C to quit)
```
Una vez que obtenga este mensaje puede acceder desde _localhost:8000_
3. Al ingresar a _localhost:8000/docs_ podrá navegar una serie de endpoints para interactuar con la base de datos.

# Troubleshooting
1. En caso de que durante la instalación de requirements.txt (pip install X) ocurra un error, intente cambiando la primera línea del archivo api/Dockerfile a
```bash
FROM python:3.9.19
``` 

2. En caso de que el mensaje que vea sea 
```bash
[api]  	| Trying to connect to database
[api]  	| Database not connected
[api]  	| connection to server at "127.0.0.1", port 5432 failed: Connection refused
[api]  	|     Is the server running on that host and accepting TCP/IP connections?
[api]  	|
```
Se debe a un error en la comunicación entre contenedores, revise el archivo **docker-compose.yml** o **podman-compose.yml**

