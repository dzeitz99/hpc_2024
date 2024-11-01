#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long long N = 1000000000; // Total number of terms
    long long terms_per_proc = N / size; // Terms handled by each process

    // Calculate the partial sum for this process's assigned terms
    double partial_sum = 0.0;
    long long start = rank * terms_per_proc;
    long long end = (rank == size - 1) ? N : start + terms_per_proc;

    for (long long i = start; i < end; i++) {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
        partial_sum += term;
    }

    // Gather partial sums to the master process
    double global_sum = 0.0;
    MPI_Reduce(&partial_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // The master process computes the final approximation of pi
    if (rank == 0) {
        double pi_approx = global_sum * 4.0;
        printf("Approximation of Pi: %.15f\n", pi_approx);
    }

    MPI_Finalize();
    return 0;
}
