#!/bin/bash -l
#SBATCH --job-name="hostname"
#SBATCH --account="uzh8"
#SBATCH --mail-type=ALL
#SBATCH --mail-user=daniel.zeitz@uzh.ch
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-core=2
#SBATCH --ntasks-per-node=24
#SBATCH --cpus-per-task=1
#SBATCH --partition=debug
#SBATCH --constraint=gpu
#SBATCH --hint=nomultithread




export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
export CRAY_CUDA_MPS=1

srun cpi_omp 
