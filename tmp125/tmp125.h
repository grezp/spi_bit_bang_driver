#pragma once

#include "../gpio/gpio_lib.h"

int32_t tmp125_init();
int32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c);
uint16_t bit_bang_spi_read(uint8_t temp_sensor_id);
float ten_bit_2_float(uint16_t bits);
