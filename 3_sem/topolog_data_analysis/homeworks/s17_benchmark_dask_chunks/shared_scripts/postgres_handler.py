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

    cursor.execute("""
        CREATE TABLE csvData(
            ID SERIAL PRIMARY KEY NOT NULL,
            Pregnancies SMALLINT NOT NULL,
            Glucose SMALLINT NOT NULL,
            BloodPressure SMALLINT NOT NULL,
            SkinThickness SMALLINT NOT NULL,
            Insulin SMALLINT NOT NULL,
            BMI FLOAT NOT NULL,
            DiabetesPedigreeFunction FLOAT NOT NULL,
            Age SMALLINT NOT NULL,
            Outcome SMALLINT NOT NULL
        )
    """)

    conn.commit()
    
    print("Table created successfully")
    return conn

def insertRow(row):
    cursor.execute(
        """
            INSERT INTO csvData(
                Pregnancies,
                Glucose,
                BloodPressure,
                SkinThickness,
                Insulin,
                BMI,
                DiabetesPedigreeFunction,
                Age,
                Outcome
            )VALUES(
                %s, %s, %s, %s, %s, %s, %s, %s, %s
            )
        """, 
        (
            row["Pregnancies"],
            row["Glucose"],
            row["BloodPressure"],
            row["SkinThickness"],
            row["Insulin"],
            row["BMI"],
            row["DiabetesPedigreeFunction"],
            row["Age"],
            row["Outcome"]
        )
    )
    conn.commit()
