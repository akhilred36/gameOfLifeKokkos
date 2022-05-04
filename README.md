# gameOfLifeKokkos
Game of Life implementation in Kokkos with MPI.

## Prerequisites
- GCC>=7.5.0
- CUDA>=11.2.0
- Kokkos>=3.5.00 with cuda and nvcc_wrapper
- OpenMPI>=4.1.2 with cuda
- CMake>=3.10

## Install prerequisites into a spack environment:
Note: GCC@10.2.0 is required for the spack environment installation
```bash
spack env create <name> spack.yaml
```
```bash
spack env activate <name>
```
```bash
spack install
```

## Building
### Initial setup:
```bash
mkdir build && mkdir data
```
### Compile:
```bash
make clean && make
```
### Clean generated log files:
```bash
make cleandata
```

## Running
Run the following in the build directory:
### Format:
```bash
mpirun -n <numTasks> ./gol <meshSize> <numIterations> <coord1X coord1Y> <coord2X coord2Y> .... <coordNX coordNY> <print>
```
### Example runs:
4 tasks, mesh size 32, 100 iterations, (10, 10) (10, 11) (10, 13) as active cells, and log enabled: 
```bash
mpirun -n 4 ./gol 32 100 10 10 10 11 10 13 1
```
4 tasks, mesh size 32, 100 iterations, (10, 10) (10, 11) (10, 13) as active cells, and log disabled: 
```bash
mpirun -n 4 ./gol 32 100 10 10 10 11 10 13 0
```

## Interpreting logs:
The logs are written into the directory data/. The naming convention used is <rank>_<iter>. For example, to view the state of a mesh of rank 0 and iteration 12, run:
  ```bash
  cat 0_12
  ```
