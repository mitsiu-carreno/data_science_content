from typing import Union
from fastapi import FastAPI, HTTPException
import time
import sys

from controller import  ( estimate, importData, alerts )

from config.conn import testConn, query

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



app.include_router(importData.router, prefix='/import')
app.include_router(estimate.router, prefix='/estim')
app.include_router(alerts.router, prefix='/alert')



#-----------------------------------
'''
@app.get("/items/{item_id}")
def read_item(item_id: int, q: Union[str, None] = None  ):
    return {"item_id": item_id, "q": q}

@app.get("/test1")
def read_item():
    res = query()
    return {"res":res}
    
@app.get("/test2")
def read_item():
    res = query()
    return {"res":res}
'''
