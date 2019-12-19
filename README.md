# K-means-parallel-and-sequential

### Problem Statement
Implement a parallel K-means clustering algorithm. The assignment is to be submitted as three versions of the code – one sequential, one with Pthreads, and one using OpenMP. Lab1_suite was provided by the TAs. 

The code that adheres to the format provided in the suite is present in Omp.cpp, pthread.cpp and Seq.cpp. Codes Omp_global_centroid_sum, Seq_global_array.cpp and Seq_global_vectors adhere to more generic formats and maybe suitable depending on the data size.
The input format can be seen from dataset_10000_4.txt
Use Lab1_suite/dataset.py to generate datasets.

### Running the code
1. To compile
```
g++ main_omp.c lab1_io.h lab1_omp.h lab1_io.c Omp.cpp -lm -fopenmp
g++ main_sequential.c lab1_io.h lab1_sequential.h lab1_io.c Seq.cpp -lm
g++ main_pthread.c lab1_io.h lab1_pthread.h lab1_io.c pthread.cpp -lm -pthread -fopenmp

```

2. To run
arg1: K (no of clusters)
arg2: no of threads
arg3: input filename (data points)
arg4: output filename (data points & cluster)
arg5: output filename (centroids of each iteration)

```
./a.out 150 4 test.txt o1.txt o2.txt
```

3. To visualise the output given by k-means and the dataset points
```
python3 visualise.py o1.txt
```
