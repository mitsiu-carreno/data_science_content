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

def execQuery(query, params):
    try:
        cursor.execute(query, params)
        records = cursor.fetchall()
        return records
    except Exception as e:
        print(e)
        conn.rollback()

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

    cursor.execute("""
        CREATE TABLE alerts(
            date DATE NOT NULL,
            time TIME,
            expected_traffic INT,
            found_traffic INT
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

def insertLog(row):
    try:
        cursor.execute(
            """
                INSERT INTO logs(
                    remote_addr,
                    remote_usr,
                    date,
                    time,
                    weekday,
                    request,
                    req_method,
                    req_uri,
                    http_ver,
                    status,
                    body_bytes_sent,
                    http_referer,
                    user_agent,
                    dec_req_uri,
                    clean_path,
                    clean_query_list,
                    domain,
                    fabstime
                )VALUES(
                     %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s,%s
                )
            """,
            (
                    row["remote_addr"],
                    row["remote_usr"],
                    row["date"],
                    row["time"],
                    row["weekday"],
                    row["request"],
                    row["req_method"],
                    row["req_uri"],
                    row["http_ver"],
                    row["status"],
                    row["body_bytes_sent"],
                    row["http_referer"],
                    row["user_agent"],
                    row["dec_req_uri"],
                    row["clean_path"],
                    row["clean_query_list"],
                    row["domain"],
                    row["fabstime"]
            )
        )
        conn.commit()
    except Exception as e:
        print(e)
        conn.rollback()


def insertAlert(row):
    try:
        cursor.execute(
            """
                INSERT INTO alerts(
                    date,
                    time,
                    expected_traffic,
                    found_traffic
                )VALUES(
                     %s, %s, %s, %s
                )
            """,
            (
                    row["date"],
                    row["time"],
                    row["expected_traffic"],
                    row["found_traffic"]
            )
        )
        conn.commit()
    except Exception as e:
        print(e)
        conn.rollback()

def query():
    try:
        cursor.execute("""SELECT COUNT(*) FROM logs""")
        records = cursor.fetchall()
        return records
    except Exception as e:
        print(e)
        conn.rollback()
