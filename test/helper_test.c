#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
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

void test_convert_bounds(void)
{
    TEST_ASSERT_EQUAL('a' - 1, convert_char('a' - 1));
    TEST_ASSERT_EQUAL('z' + 1, convert_char('z' + 1));
    TEST_ASSERT_EQUAL('A' - 1, convert_char('A' - 1));
    TEST_ASSERT_EQUAL('Z' + 1, convert_char('Z' + 1));
}

void test_convert_non_letter(void)
{
    TEST_ASSERT_EQUAL('1', convert_char('1'));
    TEST_ASSERT_EQUAL('?', convert_char('?'));
}

void test_one_blink(void)
{
    int count = 1;
    bool on = 0;
    on = update_state(on, &count);
    TEST_ASSERT_EQUAL_MESSAGE(1, on, "Wrong return value");
    TEST_ASSERT_EQUAL_MESSAGE(2, count, "Count not updated");
    on = update_state(on, &count);
    TEST_ASSERT_EQUAL_MESSAGE(0, on, "Wrong return value");
    int gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
    TEST_ASSERT_EQUAL_MESSAGE(1, gpio, "Wrong GPIO");
}

void test_eleven_no_toggle(void)
{
    int count = 11;
    bool on = 1;
    on = update_state(on, &count);
    TEST_ASSERT_EQUAL_MESSAGE(1, on, "Wrong return value");
    int gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
    TEST_ASSERT_EQUAL_MESSAGE(1, gpio, "Wrong GPIO");
}

void test_multiple_eleven_no_blink(void)
{
    int count;
    bool on = 0;

    for (int i = 11; i <= 121; i += 11) {
        count = i;
        on = update_state(on, &count);
        TEST_ASSERT_EQUAL_MESSAGE(0, on, "Wrong return value");
        int gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
        TEST_ASSERT_EQUAL_MESSAGE(0, gpio, "Wrong GPIO");
    }
}

void test_many_blinks(void)
{
    int count = 0;
    bool on = 0;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    for (int i = 0; i < 50; i++) {
        int old_count = count;
        bool updated_on = update_state(on, &count);

        // update_state writes the old on value
        int gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
        TEST_ASSERT_EQUAL_MESSAGE(on, gpio, "Wrong GPIO");

        // multiple of 11 no toggle
        if (!(i % 11))
            TEST_ASSERT_EQUAL_MESSAGE(on, updated_on, "On toggled for multiple of 11");
        else // Non multiple of 11 toggle
            TEST_ASSERT_NOT_EQUAL_MESSAGE(on, updated_on, "On didn't toggle for non multiple of 11");

        TEST_ASSERT_EQUAL_MESSAGE(old_count + 1, count, "Count didn't increment");
        on = updated_on;
    }
}

int main (void)
{
    while (1) {
        stdio_init_all();
        hard_assert(cyw43_arch_init() == PICO_OK);
        while (1) {
            sleep_ms(5000); // Give time for TTY to attach.
            printf("Start tests\n");
            UNITY_BEGIN();
            RUN_TEST(test_convert_lower);
            RUN_TEST(test_convert_upper);
            RUN_TEST(test_convert_bounds);
            RUN_TEST(test_convert_non_letter);

            RUN_TEST(test_one_blink);
            RUN_TEST(test_eleven_no_toggle);
            RUN_TEST(test_multiple_eleven_no_blink);
            RUN_TEST(test_many_blinks);

            UNITY_END();
        }
    }
}
