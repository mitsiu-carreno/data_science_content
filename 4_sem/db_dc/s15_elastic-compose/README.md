podman build -t cluster-apache-spark:3.5.3 .

podman exec -it spark ./bin/spark-shell  --packages org.apache.hadoop:hadoop-aws:3.3.4,com.amazonaws:aws-java-sdk-bundle:1.12.526,org.elasticsearch:elasticsearch-spark-30_2.12:8.6.2 --conf spark.hadoop.fs.s3a.endpoint=http://minio:9000 --conf spark.hadoop.fs.s3a.access.key=minio --conf spark.hadoop.fs.s3a.secret.key=minio123 --conf spark.hadoop.fs.s3a.path.style.access=true --conf spark.hadoop.fs.s3a.impl=org.apache.hadoop.fs.s3a.S3AFileSystem --conf spark.es.nodes="es01" --conf spark.es.port="9200" --conf spark.es.nodes.wan.only="true"

val df = spark.read.format("csv").option("header", "true").load("s3a://demo/demo.csv")
val df = spark.read.parquet("s3a://demo/iris.parq")

df.write.format("es").save("nombre_indice")


http://localhost:9200/nombre_indice/

http://localhost:9200/nombre_indice/_search?q=%22hola%22
http://localhost:9200/iris/_search?q=%22setosa%22

Generar dashboard en
http://localhost:5601

Dashboards
Index = iris
Create a dashboard
Create a visualization

Class keyword in donut
Slice by class keyword
Slice by petal_length

Line
Horizontal date_test
Vertical petal_length 


============================================================================

val df = spark.read.parquet("s3a://demo/iris.parq")

Fechas en timestamp

#String con fecha a date_format
val df_unused = df.withColumn("es_time", date_format(to_timestamp(col("date_test"), "yyyy-MM-dd"), "yyyy-MM-dd'T'HH:mm:ss.SSSZ"))

#Date a date_format
val df_time = df.withColumn("es_time", date_format(to_timestamp(col("date_test"), "yyyy-MM-dd"), "yyyy-MM-dd'T'HH:mm:ss.SSSZ"))


df_time.select("date_test", "es_time").show(truncate=false)


df_time.write.format("es").save("iris")
