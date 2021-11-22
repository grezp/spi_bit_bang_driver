#include <stdio.h>
#include <unistd.h>


#include "ptm/ptm.h"
#include "tmp125/tmp125.h"

int main()
{
    // initialize SPI pins
    printf("\nINITIALIZING SPI PINS:\n\n");
    int32_t init_status = tmp125_init();

    pthread_t th1;
    // mutex used as quit flag
    pthread_mutex_t mx;
    
    // create thread, lock mutex, and begin checking temp ranges
    printf("\nREADING TEMPERATURE:\n\n");
    start_check_temp(&th1, &mx);
     
    sleep(2);
    // do stuff
        
    // unlock mutex, then join thread
    stop_check_temp(&th1, &mx);

    return 0;
}
