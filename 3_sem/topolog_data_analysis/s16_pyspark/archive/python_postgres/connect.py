
import psycopg2
 
DB_NAME = "citizix_db"
DB_USER = "citizix_user"
DB_PASS = "S3cret"
DB_HOST = "127.0.0.1"
DB_PORT = "5432"
 
try:
    conn = psycopg2.connect(database=DB_NAME,
                            user=DB_USER,
                            password=DB_PASS,
                            host=DB_HOST,
                            port=DB_PORT)
    print("Database connected successfully")
except:
    print("Database not connected successfully")

