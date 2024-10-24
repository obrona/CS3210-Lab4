#!/bin/bash

## You can use sbatch instead of salloc to run batch jobs, as usual.

#SBATCH --job-name=lab4-mpi
#SBATCH --nodes=2
#SBATCH --ntasks=8
#SBATCH --partition=i7-7700
#SBATCH --time=00:00:30
#SBATCH --output=logs/lab4_mpi_%j.slurmlog
#SBATCH --error=logs/lab4_mpi_%j.slurmlog

echo "Received mpirun arguments: $@"

# Display commands being run in stdout
set -x

# Run mpirun with debugging options to display mapping and binding
mpirun --report-bindings --display-map --display-allocation $@
