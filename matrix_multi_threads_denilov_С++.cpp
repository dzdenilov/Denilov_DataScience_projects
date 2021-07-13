//
#include <iostream>
#include <thread>
#include <vector>
#include <future>



int m = 100;
int n = 6;
int mn = m/n;

std::vector<std::vector<int>> matA(m, std::vector<int>(m));
std::vector<std::vector<int>> matB(m, std::vector<int>(m));
std::vector<std::vector<int>> matC(m, std::vector<int>(m));
int step = 0;
  
void* multi(void*)
{
    int thread = step++;
    
    //for (int core=0; core < n; core++) {
        for (int i = thread * mn; i < (thread+1)*mn; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < m; k++)
                {
                    matC[i][j] += matA[i][k] * matB[k][j];
                }
            }
        }
    //}
    return 0;
}
  

int main()
{

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            matA[i][j] = rand()%10+1;
            matB[i][j] = rand()%10+1;
        }
    }
  
  
    
    pthread_t threads[n];
  
    
    for (int i = 0; i < n; i++) {
        int* p = nullptr;
        pthread_create(&threads[i], NULL, multi, (void*)(p));
    }
  
    
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << matC[i][j] << " " << std::endl;
                            
        }
    }
    
    
    return 0;
}
