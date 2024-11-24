#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;       // To lock access to shared resource
pthread_mutex_t write_lock;  // To give exclusive access to writers
int read_count = 0;          // Count of active readers

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    
    while (1) {
        // Reader Entry Section
        pthread_mutex_lock(&mutex);
        read_count++;
        if (read_count == 1) {
            pthread_mutex_lock(&write_lock);  // First reader locks the writer
        }
        pthread_mutex_unlock(&mutex);

        // Reading section (critical section for readers)
        printf("Reader %d is reading\n", reader_id);
        sleep(rand() % 3);  // Simulating reading time

        // Reader Exit Section
        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0) {
            pthread_mutex_unlock(&write_lock);  // Last reader unlocks the writer
        }
        pthread_mutex_unlock(&mutex);

        sleep(1);  // Give time for other threads
    }
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);
    
    while (1) {
        // Writer Entry Section
        pthread_mutex_lock(&write_lock);

        // Writing section (critical section for writers)
        printf("Writer %d is writing\n", writer_id);
        sleep(rand() % 3);  // Simulating writing time

        // Writer Exit Section
        pthread_mutex_unlock(&write_lock);

        sleep(1);  // Give time for other threads
    }
}

int main() {
    pthread_t readers[5], writers[3];
    int reader_ids[5], writer_ids[3];
    
    // Initialize mutexes
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&write_lock, NULL);
    
    // Create reader threads
    for (int i = 0; i < 5; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 3; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join all threads (optional, since in this example the threads run indefinitely)
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy mutexes
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&write_lock);

    return 0;
}
