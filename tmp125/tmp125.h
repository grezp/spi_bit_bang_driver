#pragma once

#include "../gpio/gpio_lib.h"

int32_t tmp125_init();
/*
 * Description: Read the temperature of the requested temperature sensor_id
 * Parameters:  temp_sensor_id-the id of the temp sensor to read (1-4)
 *              p_temp_in_degrees_c-a pointer to a float where the temperature
 *              will be written
 * Returns:     int32_t indicating status (0=success, any other value indicates an
 *              error code)
 */
int32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c);
uint16_t bit_bang_spi_read(uint8_t temp_sensor_id);
float ten_bit_2_float(uint16_t bits);
