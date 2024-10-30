#!/bin/bash 
#SBATCH --account=uzh8
#SBATCH --job-name=run_ring
#SBATCH --output=run_ring_output.out
#SBATCH --error=run_ring_error.err
#SBATCH --time=00:30:00
#SBATCH --nodes=4
#SBATCH --ntasks-per-core=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --partition=normal
#SBATCH --constraint=mc

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

srun ring_mpi
