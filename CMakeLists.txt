# Kokkos minimally requires 3.10 right now,
# but your project can set it higher
cmake_minimum_required(VERSION 3.10)

project(Kokkos-mpi)
# Projects can safely mix languages - must have C++ support
# Kokkos flags will only apply to C++ files
# You need this for using Kokkos_ROOT variable
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.12.0")
  message(STATUS "Setting policy CMP0074 to use <Package>_ROOT variables")
  cmake_policy(SET CMP0074 NEW)
endif()

# Look for an installed Kokkos
find_package(Kokkos REQUIRED)
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

add_executable(gol gol.cpp)

set_target_properties(gol PROPERTIES CUDA_ARCHITECTURES "35")
set(CMAKE_CUDA_FLAGS "-ccbin=mpicxx -arch=sm_35")

# This is the only thing required to set up compiler/linker flags
target_link_libraries(gol Kokkos::kokkos ${MPI_LIBRARIES})

enable_testing()
add_test(NAME KokkosInTree_Verify COMMAND example 10)