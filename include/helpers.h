#include "FreeRTOS.h"
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>

char convert_char(char c);

bool update_state(bool on, int* count);