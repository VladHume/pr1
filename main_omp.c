#include <stdio.h>
#include <omp.h>
#include "module1.h"
#include "module2.h"

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int thread_num = omp_get_thread_num();
            printf("Thread %d executing module1_function.\n", thread_num);
            module1_function();
        }
        
        #pragma omp section
        {
            int thread_num = omp_get_thread_num();
            printf("Thread %d executing module2_function.\n", thread_num);
            module2_function();
        }
    }
    
    printf("All tasks finished execution.\n");
    return 0;
}
