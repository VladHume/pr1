#include <stdio.h>
#include <omp.h>
#include <aio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "module1.h"
#include "module2.h"

void async_print(const char *message) {
    struct aiocb cb;
    memset(&cb, 0, sizeof(struct aiocb));
    cb.aio_fildes = STDOUT_FILENO;
    cb.aio_buf = message;
    cb.aio_nbytes = strlen(message);
    aio_write(&cb);
    while (aio_error(&cb) == EINPROGRESS);
}

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int thread_num = omp_get_thread_num();
            char buffer[100];
            snprintf(buffer, sizeof(buffer), "Thread %d executing module1_function.\n", thread_num);
            async_print(buffer);
            module1_function();
        }
        
        #pragma omp section
        {
            int thread_num = omp_get_thread_num();
            char buffer[100];
            snprintf(buffer, sizeof(buffer), "Thread %d executing module2_function.\n", thread_num);
            async_print(buffer);
            module2_function();
        }
    }
    
    async_print("All tasks finished execution.\n");
    return 0;
}
