//

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <omp.h>

using namespace std::chrono;

int a = 0;
int b = 10;
int N = 10000;
int i = 2;



int main()
{
    std::vector<std::vector<double>> matr(i, std::vector<double>(N));
    
    for (int z=0; z < i; z++)
    {
        for (int j=0; j < N; j++)
        {
            matr[z][j] = a + j*(b-a)/N;
        }
    }
    
    std::vector<double> result;
        
    std::vector<duration<double>> timekeeper;
        
    int maxthreads = 8;
    
    #pragma parallel for num_threads(th)
        for(int th = 1; th <= maxthreads; th++)
        {
            system_clock::time_point start = system_clock::now();
            
                for(int j=0; j < N; j++)
                    {
                        result.push_back((matr[0][j] - 1.0)*(matr[0][j] - 1.0)+(matr[1][j] - 2.5)*(matr[1][j] - 2.5));
                    }
                
            
            
            system_clock::time_point end = system_clock::now();
            duration<double> time = end - start;
            printf("Number of threads: %d\n", th);
            std::cout << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << std::endl;
            timekeeper.push_back(time);
        }
        double min = std::min_element(result.begin(),result.end()) - result.begin();
        std::cout << "MIN ELEMENT" << std::endl;
        std::cout << min << std::endl;

}
