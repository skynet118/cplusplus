#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h> 

struct User {
    int id;
    int role_id;
};

int READERS_COUNT = 10;
int WRITERS_COUNT = 5;
int ATTEMPTS = 10000;
struct User shared;

pthread_mutex_t lock;
sem_t sem; 

void *reader() {
    int local_id;
    int local_role;

    // READER
    for(int j=0; j<ATTEMPTS; j++) {  
        // down_sem(sem_id, 1);
        // pthread_mutex_lock(&lock); 
        sem_wait(&sem); 

        local_id = shared.id; 
        local_role = shared.role_id;

        // up_sem(sem_id, 1);
        // pthread_mutex_unlock(&lock); 
        sem_post(&sem); 

        if (local_id != local_role) {
            printf("Read current user: %d, %d\n", local_id, local_role);             
        }                
    }
}

void *writer() {
    int id = 0;

    for(int j=0; j<ATTEMPTS; j++) {
        id = rand() % 10;

        // Allow only one writer at a time
        pthread_mutex_lock(&lock); 

        // Wait for all readers
        for(int k=0; k<READERS_COUNT; k++) {
            sem_wait(&sem);
        }

        shared.id = id;
        shared.role_id = id;

        for(int k=0; k<READERS_COUNT; k++) {
            sem_post(&sem);
        }

        pthread_mutex_unlock(&lock); 
    }
}

int main() {
	pid_t pid;
    pthread_t reader_tids[READERS_COUNT];
    pthread_t writer_tids[WRITERS_COUNT];
    struct timeval  tv1, tv2;

    pthread_mutex_init(&lock, NULL);
    sem_init(&sem, 0, READERS_COUNT); 
    
    gettimeofday(&tv1, NULL); // Wall clock time

    for(int i=0; i<READERS_COUNT; i++) {
        pthread_create (&reader_tids[i], NULL, reader, NULL);  
    }

    for(int i=0; i<WRITERS_COUNT; i++) {
        pthread_create (&writer_tids[i], NULL, writer, NULL);  
    }

    // Waiting

    for(int i=0; i<READERS_COUNT; i++) {
        pthread_join(reader_tids[i], NULL);
    }

    for(int i=0; i<WRITERS_COUNT; i++) {
        pthread_join(writer_tids[i], NULL);
    }

    gettimeofday(&tv2, NULL);

    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));
}