import pandas as pd
import psycopg2
import dask.dataframe as dd
 
DB_NAME = "citizix_db"
DB_USER = "citizix_user"
DB_PASS = "S3cret"
DB_HOST = "127.0.0.1"
DB_PORT = "5432"

conn = psycopg2.connect(database=DB_NAME,
                        user=DB_USER,
                        password=DB_PASS,
                        host=DB_HOST,
                        port=DB_PORT)
print("Database connected successfully")
 
cur = conn.cursor()  # creating a cursor
 
# executing queries to insert into  table
'''
cur.execute("""
INSERT INTO CsvData
(
    ID ,
    Pregnancies,
    Glucose,
    BloodPressure
)
VALUES (
    value1, 
    value2,
    value3,
    value4
)
""")
 
# commit the changes
conn.commit()
print("Table Created successfully")'''

