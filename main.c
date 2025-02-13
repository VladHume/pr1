#include <stdio.h>
#include <pthread.h>
#include "module1.h"
#include "module2.h"

void *thread_function1(void *arg) {
    module1_function();
    return NULL;
}

void *thread_function2(void *arg) {
    module2_function();
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_function1, NULL);
    pthread_create(&thread2, NULL, thread_function2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("All threads finished execution.\n");

    return 0;
}
