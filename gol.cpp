/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 3.0
//       Copyright (2020) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY NTESS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NTESS OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#include "Kokkos_Core.hpp"
#include <iostream>
#include <cstdio>
#include <vector>
#include <mpi.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>


struct CountFunctor {
  KOKKOS_FUNCTION void operator()(const long i, long& lcount) const {
    lcount += (i % 2) == 0;
  }
};

void init_matrix(int * m, int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            m[size*i + j] = 0;
        }
    }
}

// void setActive(int *m, int argc, char ** argv, int localN){
//     int len = (argc - 2);
//     for(int i=3; i < len; i+=2){
//         m[atoi(argv[i]) + localN*atoi(argv[i + 1])] = 1;
//     }
// }
void setActive(Kokkos::View<int **, Kokkos::HostSpace> view, int argc, char ** argv){
    int len = (argc - 2);
    for(int i=3; i < len; i+=2){
        view(atoi(argv[i]), atoi(argv[i + 1])) = 1;
    }
}

void printState(int *m, int N){
    using namespace std;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            std::cout << m[N*i + j] << " ";
        }
        std::cout << "\n";
    }
}

void writeState(int *m, int iter, std::string path, int rank, int size){
    using namespace std;
    string fName = path;
    fName.append(to_string(rank));
    fName.append("_");
    fName.append(to_string(iter));
    
    ofstream file;
    file.open(fName.c_str());
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(j == size - 1){
                file << m[i*size + j] << "\n";
            }
            else file << m[i*size + j] << " ";
        }
    }
    file.close();
}

// void printState(Kokkos::View<int **, Kokkos::CudaSpace> view, int size){
//     for(int i=0; i<size; i++){
//         for(int j=0; j<size; j++){
//             std::cout << i << ", " << j << "\n";
//             std::cout << view(i, j) << " ";
//         }
//         std::cout << "\n";
//     }
// }

void exchangeGhosts(MPI_Comm comm, Kokkos::View<int**, Kokkos::CudaSpace> current, int nrow, int ncol){
    int rank; 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int coordinates[2];
    MPI_Cart_coords(comm, rank, 2, coordinates);
    int dim[2];
    MPI_Cart_get(comm, 2, dim, NULL, NULL);
    int ranks[8];
    int counter = 0;
    for(int i=-1; i<2; i++){
        for(int j=-1; j<2; j++){
            if(!(i==0 && j==0)){
                int tempR = coordinates[0] + i;
                int tempC = coordinates[1] + j;
                if(tempR < 0){
                    tempR = tempR + dim[0];
                }
                else{
                    tempR = tempR % dim[0];
                }
                if(tempC < 0){
                    tempC = tempC + dim[0];
                }
                else{
                    tempC = tempC % dim[0];
                }
                int tempRank;
                int tempCoords[2] = {tempR, tempC};
                MPI_Cart_rank(comm, tempCoords, &tempRank);
                ranks[counter] = tempRank;
                counter++;
            }            
        }
    }
    //Starts at bottom left, goes right, then moves up and goes right...
    int * viewData;
    MPI_Request requests[16];
    viewData = current.data();
    //Bottom Left
    MPI_Irecv(viewData, 1, MPI_INT, ranks[0], 0, comm, &requests[0]);
    MPI_Isend(viewData + dim[0] + 1, 1, MPI_INT, ranks[0], 0, comm, &requests[1]);

    //Bottom
    MPI_Irecv(viewData + 1, dim[0] - 2, MPI_INT, ranks[1], 0, comm, &requests[2]);
    MPI_Isend(viewData + dim[0] + 1, dim[0] - 2, MPI_INT, ranks[1], 0, comm, &requests[3]);

    //Bottom Right
    MPI_Irecv(viewData + dim[0] - 1, 1, MPI_INT, ranks[2], 0, comm, &requests[4]);
    MPI_Isend(viewData + 2*dim[0] - 2, 1, MPI_INT, ranks[2], 0, comm, &requests[5]);

    //Left
    int * sendLeftBuffer = (int *) malloc(sizeof(int) * dim[0] - 2);
    int * recvLeftBuffer = (int *) malloc(sizeof(int) * dim[0] - 2);
    MPI_Irecv(recvLeftBuffer, dim[0] - 2, MPI_INT, ranks[3], 0, comm, &requests[6]);
    for(int i=1; i<(dim[0] - 2); i++){
        current(i, 0) = recvLeftBuffer[i];
    }
    for(int i=1; i<(dim[0] - 2); i++){
        sendLeftBuffer[i] = current(i, 1);
    }
    MPI_Isend(sendLeftBuffer, dim[0] - 2, MPI_INT, ranks[3], 0, comm, &requests[7]);
    

    //Right
    int * sendRightBuffer = (int *) malloc(sizeof(int) * dim[0] - 2);
    int * recvRightBuffer = (int *) malloc(sizeof(int) * dim[0] - 2);
    MPI_Irecv(recvRightBuffer, dim[0] - 2, MPI_INT, ranks[4], 0, comm, &requests[8]);
    for(int i=1; i<(dim[0] - 2); i++){
        current(i, dim[0] - 1) = recvRightBuffer[i];
    }
    for(int i=1; i<(dim[0] - 2); i++){
        sendRightBuffer[i] = current(i , dim[0] - 2);
    }
    MPI_Isend(sendRightBuffer, dim[0] - 2, MPI_INT, ranks[4], 0, comm, &requests[9]);

    //Top Left
    MPI_Irecv(viewData + (dim[0]*(dim[0] - 1)), 1, MPI_INT, ranks[5], 0, comm, &requests[10]);
    MPI_Isend(viewData + (dim[0]*(dim[0] - 2)) + 1, 1, MPI_INT, ranks[5], 0, comm, &requests[11]);
    //Top
    MPI_Irecv(viewData + (dim[0]*(dim[0] - 1)) + 1, dim[0] - 2, MPI_INT, ranks[6], 0, comm, &requests[12]);
    MPI_Isend(viewData + (dim[0]*(dim[0] - 2)) + 1, dim[0] - 2, MPI_INT, ranks[6], 0, comm, &requests[13]);
    //Top Right
    MPI_Irecv(viewData + dim[0]*dim[0] - 1, 1, MPI_INT, ranks[7], 0, comm, &requests[14]);
    MPI_Isend(viewData + (dim[0]*(dim[0] - 1)) - 1, 1, MPI_INT, ranks[7], 0, comm, &requests[15]);

    MPI_Waitall(16, requests, MPI_STATUSES_IGNORE);
    free(sendLeftBuffer);
    free(sendRightBuffer);
    free(recvLeftBuffer);
    free(recvRightBuffer);
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int nProc;
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    if(!(sqrt(nProc) * sqrt(nProc) == nProc)){
        if(rank == 0){
            std::cerr << "N processes must be a square value" << std::endl;
        }
        MPI_Abort(MPI_COMM_WORLD, -1);
    }
    Kokkos::initialize(argc, argv);
    {
    Kokkos::DefaultExecutionSpace::print_configuration(std::cout);

    std::cout << argv[0] << std::endl;

  // N = dims for matrices
    int N = atoi(argv[1]);
    int iter = atoi(argv[2]);

    if(N%nProc !=0){
        std::cerr << "The processes don't divide N evenly" << std::endl;
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    int M = sqrt(nProc);
    int dims[2] = {M, M};
    int periodic[2] = {1,1};
    MPI_Comm comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periodic, 0, &comm);

    int localN = N/sqrt(nProc);

    //Device Views
    Kokkos::View<int**, Kokkos::CudaUVMSpace> current("current", localN+2, localN+2);
    Kokkos::View<int**, Kokkos::CudaUVMSpace> next("next", localN+2, localN+2);

    //Host Views
    Kokkos::View<int**, Kokkos::HostSpace> currentMirror("currentMirror", localN+2, localN+2);
    
    setActive(currentMirror, argc, argv);
    Kokkos::deep_copy(current, currentMirror);

    std::cout << "Passed!" << std::endl;

    bool print = atoi(argv[argc - 1]);
    if(print){
        std::cout << "Current: " << std::endl;
        printState(current.data(), localN+2);
    }
    for(int i=0; i<iter; i++){

        Kokkos::parallel_for(Kokkos::MDRangePolicy<Kokkos::Rank<2>>({1,1}, {localN+1,localN+1}), 
        KOKKOS_LAMBDA(const int row, const int col){
            int neighbors = 0;
            for(int i=-1; i<=1; i++){ //Calculate total neighbors
                for(int j=-1; j<=1; j++){
                    if(!(i == 0 && j == 0)){ //Avoid checking self
                        int tempR, tempC;
                        tempR = row + i;
                        tempC = col + j;
                        // if(tempR < 0){
                        //     tempR = tempR + N;
                        // }
                        // else{
                        //     tempR = tempR % N;
                        // }
                        // if(tempC < 0){
                        //     tempC = tempC + N;
                        // }
                        // else{
                        //     tempC = tempC % N;
                        // }
                        neighbors += current(tempR, tempC);
                    }
                }
            }
            if(current(row, col) == 1){ //If cell is alive
                if(neighbors < 2){
                    next(row, col) = 0; //Cell dies because of solitude
                }
                else if(neighbors < 4){
                    next(row, col) = 1; //Cell survives
                }
                else if(neighbors >= 4){
                    next(row, col) = 0; //Cell dies because of overpopulation
                }
            }
            else{
                if(neighbors == 3){
                    next(row, col) = 1;//Cell is born
                }
                else{
                    next(row, col) = 0;//No cell is born
                }
            }
        });
        //Kokkos::deep_copy(current, next);
        Kokkos::View<int**, Kokkos::CudaUVMSpace> temp("tempView", localN+2, localN+2);
        temp = current;
        current = next;
        next = temp;

        //Write views to storage
        if(print){
            int rank;
            MPI_Comm_rank(MPI_COMM_WORLD, &rank);
            std::string path = "../data/";
            writeState(current.data(), i, path, rank, localN+2);
        }
    }

  MPI_Comm_free(&comm);
  }
  Kokkos::finalize();
  MPI_Finalize();
}
