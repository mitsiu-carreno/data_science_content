import os

from pyspark.sql import SparkSession

#minio_access_key = os.environ.get('MINIO_ACCESS_KEY')
#minio_secret_key = os.environ.get('MINIO_SECRET_KEY')

minio_access_key = "rootuser"
minio_secret_key = "rootpass123"

spark = SparkSession.builder \
    .appName("Default SparkSession") \
    .config("spark.jars.packages", "org.apache.hadoop:hadoop-aws:3.3.4,com.amazonaws:aws-java-sdk-bundle:1.11.1026") \
    .config("spark.hadoop.fs.s3a.endpoint", "http://minio.minio.svc.cluster.local:9000") \
    .config("spark.hadoop.fs.s3a.access.key", minio_access_key) \
    .config("spark.hadoop.fs.s3a.secret.key", minio_secret_key) \
    .config("spark.hadoop.fs.s3a.path.style.access", "true") \
    .config("spark.hadoop.fs.s3a.impl", "org.apache.hadoop.fs.s3a.S3AFileSystem") \
    .enableHiveSupport() \
    .getOrCreate()

__builtins__.spark = spark
