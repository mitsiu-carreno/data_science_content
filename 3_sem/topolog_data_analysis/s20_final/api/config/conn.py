import psycopg2
import os

cursor = None
conn = None

def testConn():
    global conn
    global cursor

    conn = psycopg2.connect(
        database=os.environ['POSTGRES_DB'],
        user=os.environ['POSTGRES_USER'],
        password=os.environ['POSTGRES_PASSWORD'],
        host=os.environ['POSTGRES_HOST'],
        port=os.environ['POSTGRES_PORT'])
    print("Database connected successfully")
    
    cursor = conn.cursor()
    return conn

def getConn():
    return conn

def setup():
    cursor.execute("""
        DROP SCHEMA public CASCADE
    """)

    cursor.execute("""
        CREATE SCHEMA public
    """)

    conn.commit()

    cursor.execute("""
        CREATE TYPE http_method AS ENUM('GET', 'POST', 'HEAD', 'PUT', 'OPTIONS', 'PATCH', 'DELETE', 'CONNECT', 'TRACE')
    """)
    

    cursor.execute("""
        CREATE TABLE logs(
            remote_addr INET,
            remote_usr TEXT,
            date DATE,
            time TIME,
            weekday SMALLINT,
            request TEXT,
            req_method http_method,
            req_uri TEXT,
            http_ver TEXT,
            status SMALLINT,
            body_bytes_sent NUMERIC,
            http_referer TEXT,
            user_agent TEXT,
            dec_req_uri TEXT,
            clean_path TEXT,
            clean_query_list TEXT,
            domain TEXT,
            fabstime NUMERIC
        )
    """)

    conn.commit()

    print("Table created sucessfully")

def createIndex():
    cursor.execute("""
        CREATE INDEX idx_logs_domain ON logs(domain)
    """)

    cursor.execute("""
        CREATE INDEX idx_logs_datetime ON logs(date, time)
    """)

    cursor.execute("""
        CREATE INDEX idx_logs_fabstime ON logs(fabstime)
    """)
    
    cursor.execute("""
        CREATE INDEX idx_logs_weekday ON logs(weekday)
    """)

    conn.commit()

    print("Index created sucessfully")


def query():
    try:
        cursor.execute("""SELECT COUNT(*) FROM logs""")
        records = cursor.fetchall()
        return records
    except Exception as e:
        print(e)
        conn.rollback()
