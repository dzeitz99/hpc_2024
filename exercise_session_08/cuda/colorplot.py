import numpy as np
import matplotlib.pyplot as plt

# Initialize empty lists to store the block, thread, and elapsed time values
blocks = []
threads = []
elapsed_times = []

# Read the file line by line
with open("cuda_time_dependance.txt", "r") as file:
    next(file)  # Skip header
    for line in file:
        # Strip newline characters and split by comma
        block, thread, elapsed_time = line.strip().split(',')
        
        # Convert strings to integers and float
        block = int(block)
        thread = int(thread)
        elapsed_time = float(elapsed_time)
        
        # Append values to lists
        blocks.append(block)
        threads.append(thread)
        elapsed_times.append(elapsed_time)

# Convert lists to unique sorted arrays for meshgrid creation
unique_blocks = np.unique(blocks)
unique_threads = np.unique(threads)

# Create a meshgrid for block and thread values
X, Y = np.meshgrid(unique_blocks, unique_threads)

# Initialize a 2D array for elapsed times based on the meshgrid shape
Z = np.zeros(X.shape)

# Fill in the Z array with elapsed time values
for i, (block, thread, elapsed_time) in enumerate(zip(blocks, threads, elapsed_times)):
    # Find indices of the block and thread in unique values
    block_index = np.where(unique_blocks == block)[0][0]
    thread_index = np.where(unique_threads == thread)[0][0]
    Z[thread_index, block_index] = elapsed_time

# Plot the 2D grid using a heatmap
plt.figure(figsize=(10, 6))
plt.contourf(X, Y, Z, cmap='jet')
plt.colorbar(label='Elapsed Time (s)')
plt.xlabel('Blocks')
plt.ylabel('Threads')
plt.title('Elapsed time vs blocks and threads')
plt.savefig('time_dependance.png',dpi=300)
