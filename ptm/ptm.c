#include <stdio.h>
#include <time.h>
#include <errno.h>

#include "ptm.h"
#include "../tmp125/tmp125.h"

/* Local Defines */
#define NUM_SENSORS 4
#define READ_TIME   500

/* Local Variables */
static struct timespec remaining;
static struct timespec request = {0, READ_TIME*1000000L};


void start_check_temp(pthread_t *th, pthread_mutex_t* mxq)
{
    // Init and lock mutex before creating thread.
    // As long a mutex is closed, thread will run.
    pthread_mutex_init(mxq, NULL);
    pthread_mutex_lock(mxq);
    pthread_create(th, NULL, &check_temp_limits, mxq);
}

void stop_check_temp(pthread_t *th, pthread_mutex_t* mxq)
{
    pthread_mutex_unlock(mxq); 
    pthread_join(*th, NULL);

}

int exit_thread(pthread_mutex_t* mtx)
{
    switch(pthread_mutex_trylock(mtx)) {
        // if locked, unlock and return true
        case 0:
            pthread_mutex_unlock(mtx);
            return 1;
        // return false if mutex was locked
        case EBUSY:
            return 0;
  }

    return 1;
}

void* check_temp_limits(void* mtx)
{
    float tempVal[NUM_SENSORS];
    pthread_mutex_t* mx = (pthread_mutex_t*) mtx;

    while (!exit_thread(mtx)) {
        for (uint8_t i=1; i<=NUM_SENSORS; i++) {
            int32_t status = tmp125_read_temp(i, &tempVal[i]);

            if (!status) {
                if (tempVal[i] < -40.0f || tempVal[i] > 85.0f) {
                    time_t t = time(NULL);
                    struct tm currTime = *localtime(&t);

                    printf("Warning! Temperature limit was reached.\n");
                    printf("Date: %d-%02d-%02d\n", currTime.tm_year + 1900, currTime.tm_mon + 1, currTime.tm_mday);
                    printf("Time: %02d:%02d:%02d\n", currTime.tm_hour, currTime.tm_min, currTime.tm_sec);
                    printf("Sensor %d: %.2fC\n\n", i, tempVal[i]);
                }
            }
            else
                printf("Invalid temperature reading.\n");

        }

        nanosleep(&request, &remaining);
    }

    return NULL;
}

