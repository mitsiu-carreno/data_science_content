import pandas as pd
import time
import os
from shared_scripts.postgres_handler import testConn, insertRow

chunksize = 10 ** 6

path = './data/benchmarking_data.csv'
if "FILE_PATH" in os.environ:
    path = os.environ["FILE_PATH"]

conn_ready = False
total = 0

for i in range(5):
    try:
        time.sleep(1);
        print("Trying to connect to database")
        testConn()
        conn_ready = True
        break
    except:
        print("Database not connected")

def processChunk(chunk):
    global total
    for index, row in chunk.iterrows():
        # V1
        insertRow(row)
        # V2
        #total = total + 1

def startBenchm():
    global total
    print("------------start-----------")
    start = time.perf_counter()
    with pd.read_csv(path, chunksize=chunksize) as reader:
        for chunk in reader:
            processChunk(chunk)

    print(f"Total {total}")
    print(f"Completed Execution in {time.perf_counter() - start} seconds")

if conn_ready:
    startBenchm()

