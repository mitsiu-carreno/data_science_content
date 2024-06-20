from typing import Union
from fastapi import FastAPI, HTTPException
from enum import Enum
import time
import sys

from config.conn import testConn
from controller.importData import importSQL, importParquet

app = FastAPI()

conn_ready = False
for i in range(5):
    try:
        time.sleep(1)
        print("Trying to connect to database")
        testConn()
        conn_ready = True
        break
    except Exception as e:
        print("Database not connected")
        print(e)

if conn_ready == False:
    sys.exit()

@app.get("/")
def read_root():
    return {"Hi": "visit /docs"}

class Sources(str, Enum):
    sql = "sql"
    parquet = "parquet"
@app.get("/loadData/")
def load_data(source: Sources):
    if source is Sources.sql:
        try:
            importSQL()
        except Exception as e:
            raise HTTPException(status_code=500, detail="Error while importing sql")
        return { "status":"SQL file loaded" } 
    if source is Sources.parquet:
        try:
            importParquet()
        except Exception as e:
            print(e)
            raise HTTPException(status_code=500, detail="Error while importing parquet")
        return { "status":"Parquet file loaded" } 
    raise HTTPException(status_code=404, detail="Source not recognized")

@app.get("/items/{item_id}")
def read_item(item_id: int, q: Union[str, None] = None  ):
    return {"item_id": item_id, "q": q}
