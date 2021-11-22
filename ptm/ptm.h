#pragma once

#include <pthread.h>
#include <stdint.h>


/*
 * Description: Creates thread, locks mutex, then executes check_temp_limits(). 
 * Parameters:  th - Thread ID used to create new thread.
 *              mxq - Mutex used to init and lock thread from using shared resource.
 * Return:      None.
 * 
 */
void start_check_temp(pthread_t* th, pthread_mutex_t* mxq);

/*
 * Description: Unlocks previously created mutex, safely exits check_temp_limits(),
 *              then joins thread into the main thread.
 * Parameters:  th - Previously created thread ID to join.
 *              mxq - Previously create mutex to unlock and stop check_temp_limits().
 * Return:      None.
 */
void stop_check_temp(pthread_t* th, pthread_mutex_t* mxq);

/*
 * Description: Checks whether mutex is locked/unlocked.
 * Parameters:  mtx - mutex to lock/unlock thread
 * Return:      true (1) = mutex is unlocked, false (0) = mutex is locked
 */
static int exit_thread(pthread_mutex_t* mtx);

/*
 * Description: Calls tmp125_read_temp every 500ms and determines whether temp is out of range.
 *              Prints a warning message if alarm is set.
 *              Will run infinitely until mutex is unlocked.
 * Parameters:  mtx - of type pthread_mutex_t* is used to determine if mutex is locked/unlocked
 * Return:      None.
 */
static void* check_temp_limits(void* mtx);

