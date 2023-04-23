FROM gcc:latest
WORKDIR /app
COPY . .
RUN gcc -o unixipc main.c
ENTRYPOINT ["./unixipc"]