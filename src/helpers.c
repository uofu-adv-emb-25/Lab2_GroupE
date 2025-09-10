#include "helpers.h"

char convert_char(char c) {
    if (c <= 'z' && c >= 'a') return (c - 32);
    else if (c >= 'A' && c <= 'Z') return(c + 32);
    else return (c);
}