#include "unity.h"

#include "math.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_add_should_return_sum_of_two_positive_numbers(void)
{
    TEST_ASSERT_EQUAL_INT(5, MATH_add(2, 3));
}

void test_add_should_return_sum_of_two_negative_numbers(void)
{
    TEST_ASSERT_EQUAL_INT(-5,MATH_add(-2, -3));
}

void test_add_should_return_sum_of_negative_and_positive_number(void)
{
    TEST_ASSERT_EQUAL_INT(1, MATH_add(-2, 3));
}

void test_add_should_return_zero_for_opposite_numbers(void)
{
    TEST_ASSERT_EQUAL_INT(0, MATH_add(-7, 7));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_add_should_return_sum_of_two_positive_numbers);
    RUN_TEST(test_add_should_return_sum_of_two_negative_numbers);
    RUN_TEST(test_add_should_return_sum_of_negative_and_positive_number);
    RUN_TEST(test_add_should_return_zero_for_opposite_numbers);

    return UNITY_END();
}