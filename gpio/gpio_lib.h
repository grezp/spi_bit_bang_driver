#include <stdint.h>

int32_t gpio_write_pin(uint8_t port_id, uint8_t pin_id, uint8_t pin_state);
int32_t gpio_read_pin(uint8_t port_id, uint8_t pin_id, uint8_t *p_pin_state);
int32_t gpio_set_direction(uint8_t port_id, uint8_t pin_id, uint8_t dir);
