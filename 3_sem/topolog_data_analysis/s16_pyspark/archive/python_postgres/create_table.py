import psycopg2
 
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
 
# executing queries to create table
cur.execute("""
CREATE TABLE CsvData
(
    ID INT   PRIMARY KEY NOT NULL,
    Pregnancies TEXT NOT NULL,
    Glucose TEXT NOT NULL,
    BloodPressure TEXT NOT NULL
)
""")
 
# commit the changes
conn.commit()
print("Table Created successfully")