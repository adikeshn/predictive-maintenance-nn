FROM python:3.12-slim

WORKDIR /app

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    && rm -rf /var/lib/apt/lists/*

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY api ./api
COPY models ./models

# compile the shared library inside the container (Linux ELF format)
RUN gcc -shared -fPIC -o /app/api/machine_failure.so \
    models/src/activations.c \
    models/src/cost.c \
    models/src/evaluate.c \
    models/src/free_struct.c \
    models/src/init.c \
    models/src/train.c \
    models/src/util.c \
    models/src/python_facing.c \
    -Imodels/src/headers -lm

ENV MODEL_DIR=/app/models

WORKDIR /app/api

CMD exec uvicorn main:api --host 0.0.0.0 --port ${PORT:-8080}