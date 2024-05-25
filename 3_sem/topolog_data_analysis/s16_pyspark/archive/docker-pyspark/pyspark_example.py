# Python code snippet
from pyspark.sql import SparkSession
spark = SparkSession.builder \
    .master('local[*]') \
    .config("spark.driver.memory", "5g") \
    .appName('my-cool-app') \
    .getOrCreate()

csv_file_path = 'benchmarking_data.csv'
df = spark.read \
    .format("csv") \
    .option("header", "true") \
    .load(csv_file_path)

data_collect = df.collect()
 
df.show()