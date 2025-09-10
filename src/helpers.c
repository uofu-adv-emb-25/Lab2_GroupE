#include "helpers.h"
#include "stdbool.h"

char convert_char(char c) {
    if (c <= 'z' && c >= 'a') return (c - 32);
    else if (c >= 'A' && c <= 'Z') return(c + 32);
    else return (c);
}

bool update_state(bool on, int count) {
    // Each on/off is 2 counts, so 11 makes the system pause every 5th blink 
    if (count % 11) on = !on;
    return on;
}
