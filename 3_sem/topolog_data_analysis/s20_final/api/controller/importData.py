import subprocess
import os
import pandas as pd
from sqlalchemy import create_engine
from sqlalchemy.dialects.postgresql import INET, TEXT, DATE, TIME, ENUM, SMALLINT, NUMERIC

from config.conn import setup, createIndex

def importSQL():
    subprocess.run(
        [
            "psql", 
            "-h", 
            os.environ['POSTGRES_HOST'], 
            "-U", 
            os.environ['POSTGRES_USER'],
            "-d", 
            os.environ['POSTGRES_DB'],
            "-c", 
            "DROP SCHEMA public CASCADE; CREATE SCHEMA public;", 
            "-f",
            "./data/full2.sql"
        ]
    ) 



def importParquet():
    setup()
    
    df = pd.read_parquet("./data/full2.parquet", columns=[
            "remote_addr",
            "remote_usr",
            "date",
            "time",
            "request",
            "req_method",
            "req_uri",
            "http_ver",
            "status",
            "body_bytes_sent",
            "http_referer",
            "user_agent",
            "dec_req_uri",
            "clean_path",
            "clean_query_list",
            "domain",
            "fabstime"
    ])


    engine = create_engine('postgresql+psycopg2://'+ os.environ['POSTGRES_USER'] +':'+ os.environ['POSTGRES_PASSWORD'] +'@'+ os.environ['POSTGRES_HOST'] +':'+ os.environ["POSTGRES_PORT"] +'/' + os.environ['POSTGRES_DB'])
    
    http_method = ENUM('GET', 'POST', 'HEAD', 'PUT', 'OPTIONS', 'PATCH', 'DELETE', 'CONNECT', 'TRACE', name='http_method')
    
    df.to_sql(
        'logs', 
        engine, 
        chunksize=1000, 
        index=False, 
        if_exists="replace",
        dtype={
            "remote_addr": INET,
            "remote_usr": TEXT,
            "date": DATE,
            "time": TIME,
            "request": TEXT,
            "req_method": http_method,
            "req_uri": TEXT,
            "http_ver": TEXT,
            "status": SMALLINT,
            "body_bytes_sent": NUMERIC,
            "http_referer": TEXT,
            "user_agent": TEXT,
            "dec_req_uri": TEXT,
            "clean_path": TEXT,
            "clean_query_list": TEXT,
            "domain": TEXT,
            "fabstime": NUMERIC
        }
    )

    createIndex()
