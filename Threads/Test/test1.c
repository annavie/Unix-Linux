#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* mythread(void* arg){
    
    printf("hello from thread \n");

    return NULL;

}

//protype for creating thread
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//     void *(*start_routine)(void *), void *arg);

int main() {
    pthread_t thread;
    pthread_create(&thread,NULL,mythread,NULL);

    pthread_join(thread, NULL);
    pthread_join(thread, NULL);

    // sleep(1);
    // pthread_detach(thread);
    // pthread_detach(thread);


}