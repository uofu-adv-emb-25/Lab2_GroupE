#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "helpers.h"

void setUp(void) {}

void tearDown(void) {}

void test_convert_lower(void)
{
    TEST_ASSERT_EQUAL('A', convert_char('a'));
    TEST_ASSERT_EQUAL('Z', convert_char('z'));
}

void test_convert_upper(void)
{
    TEST_ASSERT_EQUAL('a', convert_char('A'));
    TEST_ASSERT_EQUAL('z', convert_char('Z'));
}

void test_bounds(void)
{

}

void test_convert_non_letter(void)
{
    
}

void test_one_blink(void)
{

}

void test_two_blinks(void)
{

}

void test_many_blinks(void)
{
    
}

int main (void)
{
    while (1) {
        stdio_init_all();
        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();
        RUN_TEST(test_variable_assignment);
        RUN_TEST(test_multiplication);
        sleep_ms(5000);
        UNITY_END();
    }
}
