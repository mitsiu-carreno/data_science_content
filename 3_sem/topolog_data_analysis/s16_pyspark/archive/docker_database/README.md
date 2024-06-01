
# Step 1 

docker-compose up -d


## Other way (update with envs)
podman run --rm -P -p 127.0.0.1:5432:5432 -e POSTGRES_PASSWORD="1234" --name pg postgres:14-alpine

podman run -d --name=pg -h pg --expose 5432 -p 5432:5432 -e POSTGRES_PASSWORD="1234" postgres:14-alpine



psql postgresql://postgres:1234@localhost:5432/postgres

psql -p 5432 -h localhost -d postgres -U postgres


