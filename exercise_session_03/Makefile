cpi_omp: cpi_omp.c
	cc -O3 -o cpi_omp -fopenmp cpi_omp.c 

cpi_mpi: cpi_mpi.c
	cc -O3 -o cpi_mpi cpi_mpi.c 

cpi: cpi.o gettime.o
	gcc -O3 -o cpi cpi.o gettime.o
cpi.o: cpi.c gettime.h
	gcc -O3 -ffast-math -mavx2 -c -o cpi.o cpi.c
gettime.o: gettime.c gettime.h
	gcc -O3 -ffast-math -mavx2 -c -o gettime.o gettime.c

all: cpi_omp cpi_mpi cpi

clean:
	rm -f cpi cpi.o gettime.o
