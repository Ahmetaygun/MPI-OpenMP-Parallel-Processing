FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    openmpi-bin \
    libopenmpi-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY parallel_compute.c /app/

RUN mpicc -fopenmp -o parallel_compute parallel_compute.c

CMD ["mpirun", "--allow-run-as-root", "--oversubscribe", "-np", "4", "./parallel_compute"]

