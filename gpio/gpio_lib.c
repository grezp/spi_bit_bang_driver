/*

File: gpio_lib.c
Description: Provides a mock up of an API to control GPIO pins from Linux userspace for
the TPM coding challenge
Author: John Doe, Epiq Solutions

*/
/*Includes */
#include <stdio.h>
#include <stdint.h>
#include "gpio_lib.h"

/*Local Defines */ 
#define NUM_PORTS 1 /*we have a single 8-bit GPIO port available */ 
#define NUM_PINS_PER_PORT 8 /*each GPIO port has 8-bits, represented as 0-7 */ 
#define DIR_OUTPUT 0
/*set dir to 0 for output */
#define DIR_INPUT 1
/*set dir to 1 for input */
/*Local Variables */
/*For this mock up library, the pin values and direction are stored in simple arrays static to this
file */
static uint8_t gpio_port_pins[NUM_PORTS];
static uint8_t gpio_port_dirs[NUM_PORTS];
/*Global Functions */
/*Description: set the GPIO direction for the specified GPIO pin pin_id on GPIO port port_id.
Parameters: dir=0 indicates output, dir=1 indicates input,
Returns: int32_t indicating status (0=success, otherwise an error code) */
int32_t gpio_set_direction(uint8_t port_id, uint8_t pin_id, uint8_t dir)
{
    int32_t status = 0;
    if (port_id >= NUM_PORTS)
    {
        printf("Error: invalid port_id %d;\r\n", port_id);
        status = -1;
        goto out;
    }
    if (pin_id >= NUM_PINS_PER_PORT)
    {
        printf("Error: invalid pin_id %d; valid pin_id values are between 0 and %d\r\n", pin_id,
            (NUM_PINS_PER_PORT - 1));
        status = -2;
        goto out;
    }
    if (dir == DIR_OUTPUT)
    {
        gpio_port_dirs[port_id] &= ~(1 << pin_id);
    }
    else if (dir == DIR_INPUT)
    {
        gpio_port_dirs[port_id] |= (1 << pin_id);
    }
    else
    {
        printf("Error: invalid dir %d (0=output, 1=input)\r\n", dir);
        status = -3;

        goto out;
    }
    printf("Info: successfully set pin %d of port %d to a direction of %d\r\n", pin_id, port_id,
        dir);
    out:
        return (status);
}
/*Description: reads the pin value for the specified GPIO pin pin_id on GPIO port port_id.
Parameters: port_id is the ID of the GPIO port, pin_id is a value from 0-7, and pin_state=0 for a
logic level low, pin_state=1 for logic level high
Returns: int32_t indicating status (0=success, otherwise an error code)
*/
int32_t gpio_read_pin(uint8_t port_id, uint8_t pin_id, uint8_t *p_pin_state)
{
    int32_t status = 0;
    if (port_id >= NUM_PORTS)
    {
        printf("Error: invalid port_id %d\r\n", port_id);
        status = -1;
        goto out;
    }
    if (pin_id >= NUM_PINS_PER_PORT)
    {
        printf("Error: invalid pin_id %d; valid pin_id values are between 0 and %d\r\n",
            pin_id, (NUM_PINS_PER_PORT - 1));
        status = -2;
        goto out;
    }
    if ((gpio_port_pins[port_id] &(1 << pin_id)))
    {
        *p_pin_state = 1;
    }
    else
    {
        *p_pin_state = 0;
    }
    printf("Info: successfully read pin %d of port %d with a value of %d\r\n", pin_id, port_id,
        *p_pin_state);
    out:
        return (status);
}

/*Description: writes the pin value for the specified GPIO pin pin_id on GPIO port port_id.
Parameters: port_id is the id of the GPIO port, pin_id is a value from 0-7, and pin_state=0 for a
logic level low, pin_state=1 for logic level high
Returns: int32_t indicating status (0=success, otherwise an error code)
*/
int32_t gpio_write_pin(uint8_t port_id, uint8_t pin_id, uint8_t pin_state)
{
    int32_t status = 0;

    if (port_id >= NUM_PORTS)
    {
        printf("Error: invalid port_id %d\r\n", port_id);
        status = -1;
        goto out;
    }
    if (pin_id >= NUM_PINS_PER_PORT)
    {
        printf("Error: invalid pin_id %d; valid pin_id values are between 0 and %d\r\n",
            pin_id, (NUM_PINS_PER_PORT - 1));
        status = -2;
        goto out;
    }
    if (pin_state == 0)
    {
        gpio_port_pins[port_id] &= ~(1 << pin_id);
    }
    else if (pin_state == 1)
    {
        gpio_port_pins[port_id] |= (1 << pin_id);
    }
    else
    {
        printf("Error: invalid pin state %d requested\r\n", pin_state);
        status = -3;
        goto out;
    }
    printf("Info: successfully wrote pin %d of port %d with a value of %d\r\n", pin_id, port_id,
        pin_state);
    out:
        return (status);
}
