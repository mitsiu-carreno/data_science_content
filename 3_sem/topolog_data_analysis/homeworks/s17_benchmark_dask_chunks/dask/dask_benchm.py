import dask.dataframe as dd
import time
import os
from shared_scripts.postgres_handler import testConn, insertRow

path = "./data/benchmarking_data.csv"
if "FILE_PATH" in os.environ:
    path = os.environ["FILE_PATH"]

conn_ready = False

for i in range(5):
    try:
        time.sleep(1);
        print("Trying to connect to database")
        testConn()
        conn_ready = True
        break
    except:
        print("Database not connected")

def processThread(row):
    insertRow(row)

def startBenchm():
    print("---------start------------")
    start = time.perf_counter()
    ddf = dd.read_csv(path)
    
    t = ddf.apply(processThread, axis=1)
    t.compute()

    print(f"Completed execution in {time.perf_counter() - start} seconds")

if conn_ready:
    startBenchm()

"""
ddf = dd.read_csv(path)

print(ddf)

def do_something_with_side_effects(row):
    print("----------")
    print(row)
    print(row["Age"])

t = ddf.apply(do_something_with_side_effects, axis=1)
t.compute()
"""
