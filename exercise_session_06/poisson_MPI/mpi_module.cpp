#include "mpi.h"
#include <stdio.h>
#include "init.h"

int start_MPI(int* my_rank, int* size){
	printf("Setting MPI environment\n");
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,size);
	MPI_Comm_rank(MPI_COMM_WORLD,my_rank);

	return 0;
}

int close_MPI(){
	MPI_Finalize();
	return 0;
}

int mpi_get_domain(int nx, int ny, int my_rank, int size, int* min_x, int* max_x, int* min_y, int* max_y){
	/*
	define corners or local domains
	*/
	int base_size_x = nx / size;
	int remainder_x = nx % size;

	if (my_rank < remainder_x) {
		*min_x = my_rank * (base_size_x + 1);
		*max_x = *min_x + base_size_x - 1;
	} else {
		*min_x = my_rank * base_size_x + remainder_x;
		*max_x = *min_x + base_size_x -1;
	}

	int base_size_y = ny / size;
	int remainder_y = ny % size;

	if ( my_rank < remainder_y){
		*min_y = my_rank * (base_size_y + 1);
		*max_y = *min_y + base_size_y;
	} else {
		*min_y = my_rank * base_size_y + remainder_y;
		*max_y = *min_y + base_size_y -1;
	}
    printf("in mpi_get_domain() in mpi_module.cpp,  define corners of the local domains\n");

	printf("I am rank %d and my domain is: xmin, xmax, ymin, ymax: %d %d %d %d\n",my_rank,*min_x,*max_x,*min_y,*max_y);
	return 0;
}
/*
typedef struct {
	int xmin, xmax, ymin, ymax;
} params;
*/

int halo_comm(params p, int my_rank, int size, double** u, double* fromLeft, double* fromRight){
	
	/*this function, vectors fromLeft and fromRight should be received from the neighbours of my_rank process*/
	/*if you want to implement also cartesian topology, you need fromTop and fromBottom in addition to fromLeft a
	nd fromRight*/





	for (int j=0;j<(p.ymax - p.ymin);j++) {fromLeft[j] = 0; fromRight[j] = 0;} //initialize fromLeft and fromRight

    /* define columns to be sent to right neighbour and to the left neighbour, 
    also receive one both form left and right neighbour*/

    /* choose either to define MPIcolumn_type (lines 43-45) or define 
    the columns to be sent manually (lines 53-56)*/

    MPI_Datatype column_type;
    MPI_Type_vector(p.ymax - p.ymin, 1, p.xmax - p.xmin, MPI_DOUBLE, &column_type);
    MPI_Type_commit(&column_type);
    
    int left_rank = (my_rank % size == 0) ? MPI_PROC_NULL : my_rank - 1;
    int right_rank = ((my_rank + 1) % size == 0) ? MPI_PROC_NULL : my_rank + 1;

    MPI_Sendrecv(&(u[0][0]), 1, column_type, left_rank, 0, fromRight, p.ymax-p.ymin, MPI_DOUBLE, right_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Sendrecv(&(u[0][p.xmax-p.xmin]), 1, column_type, right_rank, 1, fromLeft, p.ymax-p.ymin, MPI_DOUBLE, left_rank, 1, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    // ...some code goes here and then do not forget to free the column_type

    MPI_Type_free(&column_type);

	//or alternative approach below

	// double* column_to_right = new double [p.ymax - p.ymin];
	// for (int j=0;j<(p.ymax - p.ymin);j++) column_to_right[j] = u[p.xmax - p.xmin - 1][j]; 
	// double* column_to_left = new double [p.ymax - p.ymin];
	// for (int j=0;j<(p.ymax - p.ymin);j++) column_to_left[j] = u[0][j]; 


	printf("mpi_module.cpp, define halo comm:  \n");
	return 0;
}


int ALLREDUCE(double* loc_diff, double* loc_sumdiff){

	MPI_Allreduce(loc_diff, loc_sumdiff, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	return 0;

	}

