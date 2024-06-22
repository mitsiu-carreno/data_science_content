# Endpoints
from fastapi import APIRouter
from enum import Enum
from typing import Union

# New log
import re
import urllib.parse
from datetime import datetime, date
import time

# Import from file
import subprocess
import os
import pandas as pd
from sqlalchemy import create_engine
from sqlalchemy.dialects.postgresql import INET, TEXT, DATE, TIME, ENUM, SMALLINT, NUMERIC



from config.conn import setup, createIndex

router = APIRouter()

class Sources(str, Enum):
    sql = "sql"
    parquet = "parquet"
@router.put("/file")
def load_file(source: Sources):
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


class TestLogs(str, Enum):
    t1 = '37.187.215.255 - - [27/Jun/2023:05:07:33 -0600] "GET / HTTP/1.1" 502 173 "-" "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:58.0) Gecko/20100101 Firefox/58.0"'
    t2 = '177.249.162.144 - - [27/Jun/2023:06:01:19 -0600] "GET / HTTP/1.1" 200 91 "https://sii.upa.edu.mx/alumnos/index.php" "Mozilla/5.0 (iPhone; CPU iPhone OS 16_5_1 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/16.5.1 Mobile/15E148 Safari/604.1"'
    t3 = '177.249.162.144 - - [27/Jun/2023:06:01:21 -0600] "GET /image/icono/logo_upp.png HTTP/1.1" 200 67272 "https://sii.upa.edu.mx/index.php" "Mozilla/5.0 (iPhone; CPU iPhone OS 16_5_1 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/16.5.1 Mobile/15E148 Safari/604.1"'
    t4 = '201.182.23.7 - - [27/Jun/2023:06:12:27 -0600] "GET /auth/oauth2/login.php?id=2&wantsurl=https%3A%2F%2Fmoodle.ucags.edu.mx%2Fpluginfile.php%2F125947%2Fmod_assign%2Fintroattachment%2F0%2FTAREA%25205.pdf%3Fforcedownload%3D1&sesskey=ca1fiT9UKV HTTP/1.1" 404 16683 "https://moodle.ucags.edu.mx/login/index.php" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36"'
@router.put('/batch')
def new_log(log: TestLogs, repeat: Union[int, None] = None ):
    pattern = re.compile(r"(?P<remote_addr>(?:^|\b(?<!\.))(?:1?\d\d?|2[0-4]\d|25[0-5])(?:\.(?:1?\d\d?|2[0-4]\d|25[0-5])){3}(?=$|[^\w.]))\s-\s(?P<remote_usr>-|[A-z_][A-z0-9_]{0,30})\s(?P<date_time>\[(?P<date>[0-2][0-9]\/\w{3}\/[12]\d{3}):(?P<time>\d\d:\d\d:\d\d).*\])\s(?P<request>\"(?P<req_method>GET|POST|HEAD|PUT|DELETE|CONNECT|OPTIONS|TRACE|PATCH)\s(?P<req_uri>\/[^\s]*)\s(?P<http_ver>HTTP/\d\.\d)\")\s(?P<status>\d{3})\s(?P<body_byte_sent>\d+)\s\"(?P<http_referer>[^\s]+)\"\s\"(?P<user_agent>[^\"]+)\"")
    
    match = pattern.match(log)

    new_log = match.groupdict()

    if len(str(new_log["remote_addr"])) > 17 :
        raise HTTPException(status_code=500, detail="Error while importing parquet")

    # Substitute real date with current date for testing purposes
    new_log["date"] = date.today().strftime('%d/%b/%Y')

    new_log["dec_req_uri"] = urllib.parse.unquote(new_log["req_uri"])

    new_log["clean_path"] = urllib.parse.urlparse(new_log["dec_req_uri"]).path

    new_log["clean_query_list"] = urllib.parse.parse_qsl(urllib.parse.urlparse(new_log["dec_req_uri"]).query)

    new_log["domain"] = urllib.parse.urlparse(new_log["http_referer"]).netloc

    new_log["fdate"] = datetime.strptime(new_log["date"], '%d/%b/%Y')

    new_log["ftime"] = datetime.strptime(new_log["time"], '%H:%M:%S').time()
    
    new_log["fabstime"] = new_log["ftime"].hour + new_log["ftime"].minute/60.0

    new_log["weekday"] =  new_log["fdate"].weekday() +1 

    print(new_log)
    
    return {"ok":True}




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
            "weekday",
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
            "weekday": SMALLINT,
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
