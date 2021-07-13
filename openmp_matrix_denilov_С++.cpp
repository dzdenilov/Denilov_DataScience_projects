//g++  7.4.0
#include <stdio.h>
#include <omp.h>
#include <random>


const int N = 1000;
int main() {

    std::mt19937 generator;
    generator.seed(123);
    std::uniform_int_distribution<int> distribution(-10,10);
    int A[N][N] = {0};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = distribution(generator);
        }
    }
    
    for (int t = 0; t < 8; t++) {
        
//  Тут счетчик для reduction и atomic локальной
//        int count = 0;
        int count_s = 0;
        
        omp_set_num_threads(t);
        double start = omp_get_wtime();

        
//Вариант с reductuion
//       #pragma omp parallel for reduction(+:count)

        
//Вариант с атомарной синхронизацеий с локальным счетчиком
//       #pragma omp parallel for

//Вариант с атомарной синхронизаций с глобальным счетчиком
       #pragma omp parallel
        {
            int count = 0;
       #pragma omp for
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (A[i][j]<0){
                    
                        //Локальный вариант
                       // #pragma omp atomic
                            count+=1;
                    }
                }
            }
            #pragma omp atomic
            count_s += count;
        }
    printf("Time = %f\n", omp_get_wtime() - start);
    }
    //printf("Counter = %d", count);
}
