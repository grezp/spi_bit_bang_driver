/*Includes */
#include "tmp125.h"
#include <stdio.h>

/* Local Defines */ 
#define GPIO_PORT   0
#define SI_PIN      0
#define SO_PIN      1
#define CLK_PIN     2
#define CS1_PIN     3
#define CS2_PIN     4
#define CS3_PIN     5
#define CS4_PIN     6
#define DIR_OUT     0
#define DIR_IN      1
#define PIN_LO      0
#define PIN_HI      1
#define REG_SIZE    16
#define DONT_CARE   5


int32_t tmp125_init()
{
    // set clock direction
    gpio_set_direction(GPIO_PORT, CLK_PIN, DIR_OUT);
    // set slave I/O direction
    gpio_set_direction(GPIO_PORT, SI_PIN, DIR_OUT);
    gpio_set_direction(GPIO_PORT, SO_PIN, DIR_IN);
    // set chip select direction
    gpio_set_direction(GPIO_PORT, CS1_PIN, DIR_OUT);
    gpio_set_direction(GPIO_PORT, CS2_PIN, DIR_OUT);
    gpio_set_direction(GPIO_PORT, CS3_PIN, DIR_OUT);
    gpio_set_direction(GPIO_PORT, CS4_PIN, DIR_OUT);

    // set chip select pins high
    gpio_write_pin(GPIO_PORT, CS1_PIN, PIN_HI);
    gpio_write_pin(GPIO_PORT, CS2_PIN, PIN_HI);
    gpio_write_pin(GPIO_PORT, CS3_PIN, PIN_HI);
    gpio_write_pin(GPIO_PORT, CS4_PIN, PIN_HI);

    // set slave in low
    // for simplicity - keep sensors powered on all the time
    gpio_write_pin(GPIO_PORT, SI_PIN, PIN_LO);

    return 0;
}

int32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c)
{
    // read sensor
    uint16_t bit_data = bit_bang_spi_read(temp_sensor_id);

    // convert 10-bit to float
    *p_temp_in_degrees_c = ten_bit_2_float(bit_data);

    return 0;
}

uint16_t bit_bang_spi_read(uint8_t temp_sensor_id)
{
    // prep CS to start collecting data
    gpio_write_pin(GPIO_PORT, temp_sensor_id, PIN_LO);
     
    uint16_t data = 0;

    for (int8_t i=REG_SIZE-1; i>=0; i--) {
        uint8_t pin_state;

        // set clock HI
        gpio_write_pin(GPIO_PORT, CLK_PIN, PIN_HI);
        // read sensor data
        gpio_read_pin(GPIO_PORT, SO_PIN, &pin_state);
        // set clock LO
        gpio_write_pin(GPIO_PORT, CLK_PIN, PIN_LO);

        // construct temp data
        data |= pin_state << i;
    }

    // set CS back to default state
    gpio_write_pin(GPIO_PORT, temp_sensor_id, PIN_HI);

    // return data by shifting by don't care (throw away) vals
    return data >> DONT_CARE;
}

float ten_bit_2_float(uint16_t bits)
{
    float data = 0;
    uint8_t sign = 0;

    // two's complememt
    if ((bits >> 9) & 1U) {
        bits = ~bits + 1;
        sign = 1;
    }

    // convert left side of decimal to float
    data = (float) ((bits>>2) & 0x7f);

    // convert right side of decimal to float
    data += 0.25f * (float) (bits & 0b11);

    return sign ? -data : data;
}
