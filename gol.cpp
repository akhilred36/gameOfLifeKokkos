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

const int MAXDIMS = 2;
const int NNEIGHBORS = pow(3, MAXDIMS) - 1;
//const int NREQUESTS = 2 * NNEIGHBORS;
const int NREQUESTS = 2 * (pow(3, 2) - 1);

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
void setActive(Kokkos::View<int **, Kokkos::LayoutRight, Kokkos::HostSpace> view, int argc, char ** argv){
    int len = (argc - 2);
    for(int i=3; i < len; i+=2){
        view(atoi(argv[i]), atoi(argv[i + 1])) = 1;
    }
}

//void printState(int *m, int N){
//    using namespace std;
//    for(int j=0; j<N; j++){
//        for(int i=N-1; i>=0; i--){
//            std::cout << m[N*j + i] << " ";
//        }
//        std::cout << "\n";
//    }
//}

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

void stitchPrint(std::string path){
    
}

void printState(Kokkos::View<int **, Kokkos::LayoutRight, Kokkos::HostSpace> view, int N){
    std::cout <<"N is: " << N << std::endl;
    for(int row=0; row<N; row++){
        for(int col=0; col<N; col++){
            std::cout << view(row, col) << " ";
        }
        std::cout << "\n";
    }
}


void exchangeGhosts(MPI_Comm comm, Kokkos::View<int**, Kokkos::LayoutRight, Kokkos::HostSpace> current,
                        int nrow, int ncol, int* neighbors, int* sendL, int* recvL, int* sendR, int* recvR,
                        MPI_Request *requests) {
    //Starts at bottom left, goes right, then moves up and goes right...
    //Top Left to Bottom Right
    MPI_Irecv(&(current(nrow + 1, ncol + 1)), 1, MPI_INT, neighbors[0], 0, comm, &(requests[0]));
    MPI_Isend(&(current(1, 1)), 1, MPI_INT, neighbors[0], 0, comm, &(requests[1]));
    // int temp = 5;
    // MPI_Isend(&temp, 1, MPI_INT, neighbors[0], 0, comm, &(requests[1]));

    // Top to Bottom
    MPI_Irecv(&(current(nrow + 1, 1)), nrow, MPI_INT, neighbors[1], 0, comm, &(requests[2]));
    MPI_Isend(&(current(1, 1)), nrow, MPI_INT, neighbors[1], 0, comm, &(requests[3]));

    //Top Right to Bottom left
    MPI_Irecv(&(current(nrow + 1, 0)), 1, MPI_INT, neighbors[2], 0, comm, &(requests[4]));
    MPI_Isend(&(current(1, ncol)), 1, MPI_INT, neighbors[2], 0, comm, &(requests[5]));
    // int temp1 = 4;
    // MPI_Isend(&temp1, 1, MPI_INT, neighbors[2], 0, comm, &(requests[5]));

    //Right to Left
    MPI_Irecv(recvL, nrow, MPI_INT, neighbors[3], 0, comm, &(requests[6]));
    //TODO Add Kokkos parallel for 
    //pack left and right edges
    for(int i=1; i<=nrow; i++){
        sendL[i-1] = current(i, 1);
        sendR[i-1] = current(i, ncol);
    }
    MPI_Isend(sendR, nrow, MPI_INT, neighbors[3], 0, comm, &(requests[7]));

    //Left to Right
    MPI_Irecv(recvR, nrow, MPI_INT, neighbors[4], 0, comm, &(requests[8]));
    MPI_Isend(sendL, nrow, MPI_INT, neighbors[4], 0, comm, &(requests[9]));

    //Bottom Left to Top Right
    MPI_Irecv(&(current(0, ncol + 1)), 1, MPI_INT, neighbors[5], 0, comm, &(requests[10]));
    MPI_Isend(&(current(nrow, 1)),     1, MPI_INT, neighbors[5], 0, comm, &(requests[11]));
    // int temp2 = 3;
    // MPI_Isend(&temp2,     1, MPI_INT, neighbors[5], 0, comm, &(requests[11]));

    //Bottom to Top
    MPI_Irecv(&(current(0, 1)), ncol, MPI_INT, neighbors[6], 0, comm, &(requests[12]));
    MPI_Isend(&(current(nrow, 1)), ncol, MPI_INT, neighbors[6], 0, comm, &(requests[13]));

    // cout << "Top Buffer: " << endl;
    // for(int i=0; i<ncol; i++){
    //     cout << viewData[0] + 
    // }

    //Bottom Right to Top Left
    MPI_Irecv(&(current(0, 0)), 1, MPI_INT, neighbors[7], 0, comm, &(requests[14]));
    MPI_Isend(&(current(nrow, ncol)), 1, MPI_INT, neighbors[7], 0, comm, &(requests[15]));
    // int temp3 = 2;
    // MPI_Isend(&temp3, 1, MPI_INT, neighbors[7], 0, comm, &(requests[15]));

    MPI_Waitall(NREQUESTS, requests, MPI_STATUSES_IGNORE);

    //TODO Add Kokkos parallel for 
    //unpack Right to Left
    for(int i=1; i<=nrow; i++){
        current(i, 0)        = recvL[i-1]; // Left
        current(i, nrow + 1) = recvR[i-1]; // Right 
    }
}

void exchangeGhostsGPU(MPI_Comm comm, Kokkos::View<int**, Kokkos::LayoutRight, Kokkos::CudaSpace> current,
                        int nrow, int ncol, int* neighbors,
                        Kokkos::View<int*, Kokkos::CudaSpace> sendL,
                        Kokkos::View<int*, Kokkos::CudaSpace> recvL, 
                        Kokkos::View<int*, Kokkos::CudaSpace> sendR, 
                        Kokkos::View<int*, Kokkos::CudaSpace> recvR,
                        Kokkos::View<int*, Kokkos::CudaSpace> sendT,
                        Kokkos::View<int*, Kokkos::CudaSpace> recvT, 
                        Kokkos::View<int*, Kokkos::CudaSpace> sendB, 
                        Kokkos::View<int*, Kokkos::CudaSpace> recvB,
                        MPI_Request *requests) {
    // packing (length of edge without ghost cells) 
    Kokkos::parallel_for("packing Top/Bottom", ((unsigned int) ncol) + 1, 
        KOKKOS_LAMBDA(const int i){
            sendT(i) = current(1,    i+1);
            sendB(i) = current(ncol, i+1);
        }
    );
    Kokkos::parallel_for("packing L/R", ((unsigned int) nrow) + 1,
        KOKKOS_LAMBDA(const int i){
            sendL(i) = current(i+1, 1);
            sendR(i) = current(i+1, ncol);
        }
    );

    // neighbor top-left
    MPI_Irecv(recvT.data(), 1, MPI_INT, neighbors[0], 0, comm, &(requests[0]));
    MPI_Isend(sendT.data(), 1, MPI_INT, neighbors[0], 0, comm, &(requests[1]));

    // neighbor top
    MPI_Irecv(recvT.data() + 1, ncol, MPI_INT, neighbors[1], 0, comm, &(requests[2]));
    MPI_Isend(sendT.data(),     ncol, MPI_INT, neighbors[1], 0, comm, &(requests[3]));

    // neighbor top-right
    MPI_Irecv(recvT.data() + ncol + 1, 1, MPI_INT, neighbors[2], 0, comm, &(requests[4]));
    MPI_Isend(sendT.data() + ncol - 1, 1, MPI_INT, neighbors[2], 0, comm, &(requests[5]));

    // neighbor left
    MPI_Irecv(recvL.data(), nrow, MPI_INT, neighbors[3], 0, comm, &(requests[6]));
    MPI_Isend(sendL.data(), nrow, MPI_INT, neighbors[3], 0, comm, &(requests[7]));

    // neigbhor right
    MPI_Irecv(recvR.data(), nrow, MPI_INT, neighbors[4], 0, comm, &(requests[8]));
    MPI_Isend(sendR.data(), nrow, MPI_INT, neighbors[4], 0, comm, &(requests[9]));

    // neighbor bottom-left
    MPI_Irecv(recvB.data(), 1, MPI_INT, neighbors[5], 0, comm, &(requests[10]));
    MPI_Isend(sendB.data(), 1, MPI_INT, neighbors[5], 0, comm, &(requests[11]));

    // neighbor below
    MPI_Irecv(recvB.data() + 1, ncol, MPI_INT, neighbors[6], 0, comm, &(requests[12]));
    MPI_Isend(sendB.data(),     ncol, MPI_INT, neighbors[6], 0, comm, &(requests[13]));

    // neighbor bottom-right
    MPI_Irecv(recvB.data() + ncol + 1, 1, MPI_INT, neighbors[7], 0, comm, &(requests[14]));
    MPI_Isend(sendB.data() + ncol - 1, 1, MPI_INT, neighbors[7], 0, comm, &(requests[15]));

    MPI_Waitall(NREQUESTS, requests, MPI_STATUSES_IGNORE);

    // unpack t/b buffers
    //Kokkos::RangePolicy<Kokkos::CudaSpace> tempPolicy = Kokkos::RangePolicy<Kokkos::CudaSpace>(1, ((unsigned int) nrow) + 1);
    Kokkos::parallel_for("unpacking top/bottom", ((unsigned int) ncol) + 3, 
        KOKKOS_LAMBDA(const int i){
            // TODO flip?
            current(0, i)        = recvB(i); // Top
            current(nrow + 1, i) = recvT(i); // Bottom
        }
    );
    // unpack l/r buffers
    Kokkos::parallel_for("unpacking L/R", ((unsigned int) nrow) + 1, 
        KOKKOS_LAMBDA(const int i){
            // TODO flip?
            current(i + 1, 0)        = recvR(i); // Left
            current(i + 1, ncol + 1) = recvL(i); // Right 
        }
    );
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::cout << "Rank is: " << rank << std::endl;
    int nProc;
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    if(!(sqrt(nProc) * sqrt(nProc) == nProc)){
        if(rank == 0){
            std::cerr << "N processes must be a square value" << std::endl;
        }
        MPI_Abort(MPI_COMM_WORLD, -1);
    }
    Kokkos::initialize(argc, argv); {
        Kokkos::DefaultExecutionSpace::print_configuration(std::cout);

        std::cout << argv[0] << std::endl;

        // N = dimension of 2D game of life state
        int N = atoi(argv[1]);
        int iter = atoi(argv[2]);

        if(N%nProc !=0){
            std::cerr << "The processes don't divide N evenly" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, -1);
        }

        // get neighbor ranks
        int M = sqrt(nProc);
        int dims[MAXDIMS] = {M, M};
        int periodic[MAXDIMS] = {1,1};
        MPI_Comm comm;
        MPI_Cart_create(MPI_COMM_WORLD, MAXDIMS, dims, periodic, 0, &comm);
        int coords[MAXDIMS];
        MPI_Cart_coords(comm, rank, MAXDIMS, coords);
        int neighbors[NNEIGHBORS];
        int counter = 0;
        int tempR, tempC; 
        for(int i=-1; i<2; i++){
            for(int j=-1; j<2; j++){
                if(!(i==0 && j==0)){
                    tempR = coords[0] + i;
                    tempC = coords[1] + j;
                    if(tempR < 0){
                        tempR = tempR + dims[0];
                    }
                    else{
                        tempR = tempR % dims[0];
                    }
                    if(tempC < 0){
                        tempC = tempC + dims[0];
                    }
                    else{
                        tempC = tempC % dims[0];
                    }
                    int tempCoords[2] = {tempR, tempC};
                    MPI_Cart_rank(comm, tempCoords, &(neighbors[counter]));
                    // TODO: fix 
                    if (rank == 0) {
                        std::cout << "n: " << counter << ", coords: " << tempCoords[0] << ", " << tempCoords[1] << std::endl;
                    }
                    counter++;
                }            
            }
        }

        int localN = N/M;

        //Device Views
        Kokkos::View<int**, Kokkos::LayoutRight, Kokkos::CudaSpace> current("current", localN+2, localN+2);
        Kokkos::View<int**, Kokkos::LayoutRight, Kokkos::CudaSpace> next("next", localN+2, localN+2);

        //Host Views
        Kokkos::View<int**, Kokkos::LayoutRight, Kokkos::HostSpace> currentMirror("currentMirror", localN+2, localN+2);

        MPI_Request requests[2 * NNEIGHBORS];
        // packing buffers
        // int* sendL = (int* ) malloc(localN * sizeof(int));
        // int* recvL = (int* ) malloc(localN * sizeof(int));
        // int* sendR = (int* ) malloc(localN * sizeof(int));
        // int* recvR = (int* ) malloc(localN * sizeof(int));

        //packing views
        Kokkos::View<int*, Kokkos::CudaSpace> sendLView("sendL", localN);
        Kokkos::View<int*, Kokkos::CudaSpace> sendRView("sendR", localN);
        Kokkos::View<int*, Kokkos::CudaSpace> sendTView("sendT", localN);
        Kokkos::View<int*, Kokkos::CudaSpace> sendBView("sendB", localN);
        Kokkos::View<int*, Kokkos::CudaSpace> recvLView("recvL", localN);
        Kokkos::View<int*, Kokkos::CudaSpace> recvRView("recvR", localN);
        Kokkos::View<int*, Kokkos::CudaSpace> recvTView("recvT", localN+2);
        Kokkos::View<int*, Kokkos::CudaSpace> recvBView("recvB", localN+2);
        
        // std::cout << "Rank is: " << rank << std::endl;

        if (rank == 0) {
            setActive(currentMirror, argc, argv);
            int * p = &currentMirror(1, 1);
            // std::cout << "Current at 1, 1: " << *p << std::endl;
            // std::cout << "Current at 2, 1: " << *(p+1) << std::endl;
            // std::cout << "Current at 1, 2: " << *(10*(localN+2)+p+10) << std::endl;
            Kokkos::deep_copy(current, currentMirror);
        }
        
        bool print = atoi(argv[argc - 1]);
        if(print && rank == 0){
            std::cout << "Current: " << std::endl;
            printState(currentMirror, localN+2);
        }

        // exchangeGhosts(comm, currentMirror, localN, localN, neighbors, sendL, recvL, sendR, recvR, requests);

        // if(print && rank == 0){
        //     std::cout << "Current: " << std::endl;
        //     printState(currentMirror, localN+2);
        // }


        for(int i=0; i<iter; i++){
            // Kokkos::deep_copy(currentMirror, current);
            exchangeGhostsGPU(comm, current, localN, localN, neighbors, sendLView, recvLView, sendRView, recvRView,
                    sendTView, recvTView, sendBView, recvBView, requests);
            // Kokkos::deep_copy(current, currentMirror);
            Kokkos::parallel_for(Kokkos::MDRangePolicy<Kokkos::Rank<2>>({1,1}, {localN+1,localN+1}), 
            KOKKOS_LAMBDA(const int row, const int col){
                int neighbors = 0;
                for(int i=-1; i<=1; i++){ //Calculate total neighbors
                    for(int j=-1; j<=1; j++){
                        if(!(i == 0 && j == 0)){ //Avoid checking self
                            int tempR, tempC;
                            tempR = row + i;
                            tempC = col + j;
                            
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
                } else {
                    if(neighbors == 3){
                        next(row, col) = 1;//Cell is born
                    } else{
                        next(row, col) = 0;//No cell is born
                    }
                }
            });

            if(print){
                Kokkos::deep_copy(currentMirror, current);
                int rank;
                MPI_Comm_rank(MPI_COMM_WORLD, &rank);
                std::string path = "../data/";
                writeState(currentMirror.data(), i, path, rank, localN+2);
            }

            Kokkos::View<int**, Kokkos::LayoutRight, Kokkos::CudaSpace> temp("tempView", localN+2, localN+2);
            temp = current;
            current = next;
            next = temp;
        }
        //Stitch and print
        if(rank == 0){
            if(print){
                std::string path = "../data/";
                stitchPrint(path);
            }
        }

        MPI_Comm_free(&comm);
        // free(sendL);
        // free(sendR);
        // free(recvL);
        // free(recvR);
    }
    Kokkos::finalize();
    MPI_Finalize();
}
