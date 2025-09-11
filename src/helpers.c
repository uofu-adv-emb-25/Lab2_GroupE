#include "helpers.h"
#include "stdbool.h"

/**
 * Swaps upper and lower case letters. Other characters are not changed
 * @param c character to convert
 * @return converted character
 */
char convert_char(char c) {
    if (c <= 'z' && c >= 'a') return (c - 32);
    else if (c >= 'A' && c <= 'Z') return(c + 32);
    else return (c);
}

/**
 * Determines the next state of the light
 * @param on the current state of the light
 * @param count the number of times the light has been toggled
 * @return the new state of the light
 */
bool update_state(bool on, int count) {
    // Each on/off is 2 counts, so 11 makes the system pause every 5th blink 
    if (count % 11) on = !on;
    return on;
}
