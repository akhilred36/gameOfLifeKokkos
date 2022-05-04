all: clean
	cmake -S . -B build/ -DCMAKE_CXX_COMPILER="nvcc_wrapper" -DCMAKE_CXX_FLAGS="--expt-extended-lambda -g -DDEBUG" -DKokkos_ENABLE_CUDA=On
	cd build && make

#glider:
#	./gameOfLife.o 32 100 10 10 9 10 8 10 8 9 9 8 1

cleandata:
	cd data && rm -f *

clean:
	cd build && rm -rf *
