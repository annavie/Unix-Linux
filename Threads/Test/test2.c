#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  


pthread_mutex_t lock;
int counter = 0;

void* mythread(void* arg){
    
    printf("hello from mythread \n");

    if (pthread_mutex_lock(&lock) != 0) {
        perror("pthread_mutex_lock");
        return NULL;
    }
    counter++;
    printf("Thread %ld incremented counter to %d\n", (long)arg,counter);

    if (pthread_mutex_unlock(&lock) != 0) {
        perror("pthread_mutex_unlock");
        return NULL;
    }
    return NULL;

}



int main() {

    pthread_t threads[5];
    
    pthread_mutex_init(&lock, NULL);

    for(int i = 0; i < 5; ++i){
        pthread_create(&threads[i], NULL, mythread, (void*)(int)i);
    }
   
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);

    return 0;

}