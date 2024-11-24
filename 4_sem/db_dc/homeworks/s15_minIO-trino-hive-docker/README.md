# Credit
This code is based off the following repo:
https://github.com/sanogotech/minIO-trino-hive-docker


# trino-hive-docker
trino + hive + minio with postgres in docker compose



## DOCS

- How to Build a Modern Data Lake with MinIO:
  * https://medium.com/codex/how-to-build-a-modern-data-lake-with-minio-db0455eec053

"
In this article, the focus is to build a modern data lake using only open source technologies. I will walk-through a step-by-step process to demonstrate how we can leverage an S3-Compatible Object Storage (MinIO) and a Distributed SQL query engine (Trino) to achieve this.
"

## Getting started with the Hive Connector on Trino #
To drive this point home, I created a tutorial that showcases using Trino and looking at the metadata it produces. In the following scenario, the docker environment contains four docker containers:

* trino - the runtime in this scenario that replaces Hive.
* minio - the storage is an open-source cloud object storage.
* hive-metastore - the metastore service instance.
* mariadb - the database that the metastore uses to store the metadata.

You can play around with the system and optionally view the configurations. The scenario asks you to run a query to populate data in MinIO and then see the resulting metadata populated in MariaDB by the HMS. The next step asks you to run queries over the mariadb database which holds the generated metadata from the metastore.
# Trino-Hive-Postgres-Minio Exercise

This is a personal exercise for me to understand Trino and its architecture, especially with 
Hive Metastore/ Postgres/ Minio. The idea of the exercise is originated from 
https://trino.io/blog/2020/10/20/intro-to-hive-connector.html. The only difference is that I 
changed the DB of Hive Metastore from MariaDB to PostgresDB and tried to implement it 
with k8s with the help of https://github.com/alexcpn/presto_in_kubernetes.

## Architechure Diagram
![Exercise 1 (Trino Hive Postgres Minio on k8s)](https://user-images.githubusercontent.com/84711996/186559791-1b974247-dd1d-4ba1-bada-fe0759f5c8d4.jpeg)


## Run Locally with Docker-compose
The implementation with docker-compose is referred to https://github.com/bitsondatadev/trino-getting-started/tree/main/hive/trino-minio 
with the help of https://github.com/bitsondatadev/hive-metastore/pull/2/commits to build a Hive Metastore image to
support PostgresDB.

Step 0 - Go to the docker-compose directory
```bash
cd docker-compose
```
Step 1 - Build a Hive Metastore image with the Dockerfile to support PostgresDB
```bash
docker build -t my-hive-metastore .
```
Step 2 - Implement with docker-compose
```bash
docker-compose up -d
```
Step 3 - Create Bucket in MinIO
- account: minio
- password: minio123

Step 4 - Into the runnung trino container
```bash
docker container exec -it docker-compose_trino-coordinator_1 trino
```
Step 5 -  Create schema and table and play around with trino, you can see the trino dashboard from localhost:8080.
```sql
CREATE SCHEMA minio.test
WITH (location = 's3a://test/');

CREATE TABLE minio.test.customer
WITH (
    format = 'ORC',
    external_location = 's3a://test/customer/'
) 
AS SELECT * FROM tpch.tiny.customer;
```

			
### (Optional: see the metadata store in Postgres)
Step 6 - Into the running postgres container
```bash 
docker exec -it "docker-compose_postgres_1" psql -U admin -d "hive_db"
```
Step 7 - Run SQL commands on postgresDB to see where the metadata is stored. 
```sql
SELECT
 "DB_ID",
 "DB_LOCATION_URI",
 "NAME", 
 "OWNER_NAME",
 "OWNER_TYPE",
 "CTLG_NAME"
FROM "DBS";
```

For more metadata detail, kindly check: 
https://github.com/bitsondatadev/trino-getting-started/tree/main/hive/trino-minio

Step 8 - Close down the running containers
```bash
docker-compose down
```



```bash
podman build -t hive-poc .
```

```bash
podman-compose up minio
podman-compose up postgres
podman-compose up hive-metastore
podman-compose up trino-coordinator
```

```bash
localhost:9001
Bucket iris
```

```bash
localhost:8080
podman exec -it trino-coordinator trino
```

```bash
SHOW CATALOGS;
```

etc/catalog/minio.properties

```bash
SHOW SCHEMAS IN minio;
```

```bash
CREATE SCHEMA IF NOT EXISTS minio.iris
WITH (location = 's3a://iris/');
```

```bash
CREATE TABLE IF NOT EXISTS minio.iris.iris_parquet (
  sepal_length DOUBLE,
  sepal_width  DOUBLE,
  petal_length DOUBLE,
  petal_width  DOUBLE,
  class        VARCHAR
)
WITH (
  external_location = 's3a://iris/',
  format = 'PARQUET'
);
```

```bash
SHOW TABLES IN minio.iris;
```

```bash
SELECT * FROM minio.iris.iris_parquet LIMIT 5;
```

```bash
podman exec -it postgres psql -U admin -d hive_db
```

```bash
\dt
```

SELECT * FROM "DBS";

SELECT 
 t."TBL_ID", 
 t."DB_ID", 
 t."OWNER", 
 t."TBL_NAME", 
 t."TBL_TYPE",
 t."SD_ID"
FROM "TBLS" t 
 JOIN "DBS" d 
  ON t."DB_ID"= d."DB_ID" 
WHERE d."NAME" = 'iris';

SELECT 
 s."SD_ID",
 s."INPUT_FORMAT",
 s."LOCATION",
 s."SERDE_ID" 
FROM "TBLS" t 
 JOIN "DBS" d
  ON t."DB_ID" = d."DB_ID"
 JOIN "SDS" s 
  ON t."SD_ID" = s."SD_ID"
WHERE t."TBL_NAME" = 'iris_parquet'
 AND d."NAME"='iris';


SELECT c.* 
FROM "TBLS" t
 JOIN "DBS" d
  ON t."DB_ID" = d."DB_ID"
 JOIN "SDS" s
  ON t."SD_ID" = s."SD_ID"
 JOIN "COLUMNS_V2" c
  ON s."CD_ID" = c."CD_ID"
WHERE t."TBL_NAME" = 'iris_parquet'
 AND d."NAME"='iris'
ORDER by "CD_ID", "INTEGER_IDX";

Further research:
https://medium.com/@ahmetfurkandemir/kubernetes-with-data-engineering-approach-2-querying-to-object-storage-minio-with-trino-using-ae68ffbde9f9
