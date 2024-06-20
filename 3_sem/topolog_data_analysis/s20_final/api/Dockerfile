FROM python:3.9.19-alpine3.20

WORKDIR /usr/src/api

COPY ./requirements.txt ./
 
RUN pip install --no-cache-dir --upgrade -r requirements.txt

RUN apk add postgresql

CMD ["fastapi", "run", "main.py", "--port", "8000"]
