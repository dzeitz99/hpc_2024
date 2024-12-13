#!/bin/bash

NUM_BLOCKS=(60 120 180 240 300 360 420 600)

NUM_THREADS=(16 32 48 64 80 96 112 128 144 160)

echo "#!/bin/bash" > pi_cuda_setups.slurm
echo "#SBATCH --account=uzg2" >> pi_cuda_setups.slurm
echo "#SBATCH --job-name=calc_pi" >> pi_cuda_setups.slurm
echo "#SBATCH --output=cuda.out" >> pi_cuda_setups.slurm
echo "#SBATCH --error=cuda.err" >> pi_cuda_setups.slurm
echo "#SBATCH --time=00:30:00" >> pi_cuda_setups.slurm
echo "#SBATCH --nodes=128" >> pi_cuda_setups.slurm
echo "#SBATCH --ntasks-per-core=1" >> pi_cuda_setups.slurm
echo "#SBATCH --ntasks-per-node=4" >> pi_cuda_setups.slurm
echo "#SBATCH --cpus-per-task=2" >> pi_cuda_setups.slurm
echo "#SBATCH --partition=normal" >> pi_cuda_setups.slurm
echo "#SBATCH --constraint=gpu" >> pi_cuda_setups.slurm

output_file="cuda_time_dependance.txt"
echo "NUM_BLOCK NUM_THREAD ELAPSED_TIME" > $output_file

for BLOCK in "${NUM_BLOCKS[@]}"; do
  for THREAD in "${NUM_THREADS[@]}"; do
    echo "
      start_time=\$(date +%s.%N)
      srun ./your_cuda_program --block $BLOCK --thread $THREAD
      end_time=\$(date +%s.%N)
      elapsed_time=\$(echo "\$end_time - \$start_time" | bc)
      echo "$BLOCK,$THREAD,\${elapsed_time}" >> $output_file
		  " >> pi_cuda_setups.slurm  
  done
done

sbatch pi_cuda_setups.slurm
