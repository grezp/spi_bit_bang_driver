#include <stdio.h>
#include <unistd.h>
// #include <pthread.h>

#include "ptm/ptm.h"

int main()
{
    pthread_t th1;
    // mutex used as quit flag
    pthread_mutex_t mx;

    // create thread, lock mutex, and begin checking temp ranges
    start_check_temp(&th1, &mx);
     
    for (int i=0; i<5; i++) {
        sleep(1);
        // do stuff
    }

    // unlock mutex, then join thread
    stop_check_temp(&th1, &mx);

    return 0;
}
