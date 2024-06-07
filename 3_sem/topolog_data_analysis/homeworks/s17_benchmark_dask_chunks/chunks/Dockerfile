FROM python:3.9.19-alpine3.20

WORKDIR /usr/src/app

COPY requirements.txt ./

RUN pip install --no-cache-dir -r requirements.txt

COPY . .

CMD [ "python", "./chunks_benchm.py" ]
