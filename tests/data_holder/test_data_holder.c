#include "unity.h"
#include "fff.h"

#include "common.h"
#include "data_holder.h"
#include "data_source.h"

DEFINE_FFF_GLOBALS

/** Constants ****************************************************************/
#define TEST_VALID_TEMPERATURE   (30U)
#define TEST_INVALID_TEMPERATURE (DATA_HOLDER_TEMPERATURE_MAX + 1U)
#define TEST_VALID_TIME          (120000LL) /* 12:00:00 */
#define TEST_INVALID_TIME_NEG    (-1LL)
#define TEST_INVALID_TIME_OVER   (DATA_HOLDER_TIME_MAX + 1LL)
#define TEST_VALID_TRAFFIC       (50U)
#define TEST_INVALID_TRAFFIC     (DATA_HOLDER_TRAFFIC_MAX + 1U)

/** Fakes ********************************************************************/
FAKE_VALUE_FUNC2(enum status_e, OBSERVER_init, struct Observer_s *, observer_update_fn_t)

/** Functions ****************************************************************/
void setUp(void)
{
    RESET_FAKE(OBSERVER_init);

    OBSERVER_init_fake.return_val = SC_STATUS_SUCCESS;

    FFF_RESET_HISTORY();
}

void tearDown(void)
{
}

/** DATA_HOLDER_temperature_init *********************************************/
void test_temperature_init_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = DATA_HOLDER_temperature_init(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, OBSERVER_init_fake.call_count);
}

void test_temperature_init_should_initialize_observer_and_reset_state(void)
{
    struct TemperatureDataHolder_s dh = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    dh.is_valid = true;

    status = DATA_HOLDER_temperature_init(&dh);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_FALSE(dh.is_valid);
    TEST_ASSERT_EQUAL_UINT(1U, OBSERVER_init_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&dh.observer, OBSERVER_init_fake.arg0_val);
    TEST_ASSERT_NOT_NULL(OBSERVER_init_fake.arg1_val);
}

/** DATA_HOLDER_time_init ****************************************************/
void test_time_init_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = DATA_HOLDER_time_init(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, OBSERVER_init_fake.call_count);
}

void test_time_init_should_initialize_observer_and_reset_state(void)
{
    struct TimeDataHolder_s dh = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    dh.is_valid = true;

    status = DATA_HOLDER_time_init(&dh);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_FALSE(dh.is_valid);
    TEST_ASSERT_EQUAL_UINT(1U, OBSERVER_init_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&dh.observer, OBSERVER_init_fake.arg0_val);
    TEST_ASSERT_NOT_NULL(OBSERVER_init_fake.arg1_val);
}

/** DATA_HOLDER_traffic_init *************************************************/
void test_traffic_init_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = DATA_HOLDER_traffic_init(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, OBSERVER_init_fake.call_count);
}

void test_traffic_init_should_initialize_observer_and_reset_state(void)
{
    struct TrafficDataHolder_s dh = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    dh.is_valid = true;

    status = DATA_HOLDER_traffic_init(&dh);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_FALSE(dh.is_valid);
    TEST_ASSERT_EQUAL_UINT(1U, OBSERVER_init_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&dh.observer, OBSERVER_init_fake.arg0_val);
    TEST_ASSERT_NOT_NULL(OBSERVER_init_fake.arg1_val);
}

/** Temperature update callback **********************************************/
void test_temperature_update_should_reject_null_self(void)
{
    struct TemperatureDataHolder_s dh = {0};
    struct TemperatureRawData_s reading = {.value = TEST_VALID_TEMPERATURE};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_temperature_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    dh.is_valid = true;

    captured_callback(NULL, &reading);

    TEST_ASSERT_TRUE(dh.is_valid);
}

void test_temperature_update_should_reject_null_context(void)
{
    struct TemperatureDataHolder_s dh = {0};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_temperature_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    dh.is_valid = true;

    captured_callback(&dh, NULL);

    TEST_ASSERT_FALSE(dh.is_valid);
}

void test_temperature_update_should_reject_invalid_reading(void)
{
    struct TemperatureDataHolder_s dh = {0};
    struct TemperatureRawData_s reading = {.value = TEST_INVALID_TEMPERATURE};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_temperature_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    captured_callback(&dh, &reading);

    TEST_ASSERT_FALSE(dh.is_valid);
}

void test_temperature_update_should_accept_valid_reading(void)
{
    struct TemperatureDataHolder_s dh = {0};
    struct TemperatureRawData_s reading = {.value = TEST_VALID_TEMPERATURE};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_temperature_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    captured_callback(&dh, &reading);

    TEST_ASSERT_TRUE(dh.is_valid);
    TEST_ASSERT_EQUAL_UINT32(TEST_VALID_TEMPERATURE, dh.data.celsius);
}

void test_temperature_update_should_accept_max_boundary(void)
{
    struct TemperatureDataHolder_s dh = {0};
    struct TemperatureRawData_s reading = {.value = DATA_HOLDER_TEMPERATURE_MAX};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_temperature_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    captured_callback(&dh, &reading);

    TEST_ASSERT_TRUE(dh.is_valid);
    TEST_ASSERT_EQUAL_UINT32(DATA_HOLDER_TEMPERATURE_MAX, dh.data.celsius);
}

/** Time update callback *****************************************************/
void test_time_update_should_reject_null_context(void)
{
    struct TimeDataHolder_s dh = {0};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_time_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    dh.is_valid = true;

    captured_callback(&dh, NULL);

    TEST_ASSERT_FALSE(dh.is_valid);
}

void test_time_update_should_reject_negative_reading(void)
{
    struct TimeDataHolder_s dh = {0};
    struct TimeRawData_s reading = {.value = TEST_INVALID_TIME_NEG};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_time_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    captured_callback(&dh, &reading);

    TEST_ASSERT_FALSE(dh.is_valid);
}

void test_time_update_should_reject_reading_exceeding_max(void)
{
    struct TimeDataHolder_s dh = {0};
    struct TimeRawData_s reading = {.value = TEST_INVALID_TIME_OVER};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_time_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    captured_callback(&dh, &reading);

    TEST_ASSERT_FALSE(dh.is_valid);
}

void test_time_update_should_accept_valid_reading(void)
{
    struct TimeDataHolder_s dh = {0};
    struct TimeRawData_s reading = {.value = TEST_VALID_TIME};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_time_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    captured_callback(&dh, &reading);

    TEST_ASSERT_TRUE(dh.is_valid);
    TEST_ASSERT_EQUAL_INT64(TEST_VALID_TIME, dh.data.hhmmss);
}

void test_time_update_should_accept_zero(void)
{
    struct TimeDataHolder_s dh = {0};
    struct TimeRawData_s reading = {.value = 0LL};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_time_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    captured_callback(&dh, &reading);

    TEST_ASSERT_TRUE(dh.is_valid);
    TEST_ASSERT_EQUAL_INT64(0LL, dh.data.hhmmss);
}

void test_time_update_should_accept_max_boundary(void)
{
    struct TimeDataHolder_s dh = {0};
    struct TimeRawData_s reading = {.value = DATA_HOLDER_TIME_MAX};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_time_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    captured_callback(&dh, &reading);

    TEST_ASSERT_TRUE(dh.is_valid);
    TEST_ASSERT_EQUAL_INT64(DATA_HOLDER_TIME_MAX, dh.data.hhmmss);
}

/** Traffic update callback **************************************************/
void test_traffic_update_should_reject_null_context(void)
{
    struct TrafficDataHolder_s dh = {0};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_traffic_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    dh.is_valid = true;

    captured_callback(&dh, NULL);

    TEST_ASSERT_FALSE(dh.is_valid);
}

void test_traffic_update_should_reject_invalid_reading(void)
{
    struct TrafficDataHolder_s dh = {0};
    struct TrafficRawData_s reading = {.value = TEST_INVALID_TRAFFIC};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_traffic_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    captured_callback(&dh, &reading);

    TEST_ASSERT_FALSE(dh.is_valid);
}

void test_traffic_update_should_accept_valid_reading(void)
{
    struct TrafficDataHolder_s dh = {0};
    struct TrafficRawData_s reading = {.value = TEST_VALID_TRAFFIC};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_traffic_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    captured_callback(&dh, &reading);

    TEST_ASSERT_TRUE(dh.is_valid);
    TEST_ASSERT_EQUAL_UINT16(TEST_VALID_TRAFFIC, dh.data.congestion_percent);
}

void test_traffic_update_should_accept_max_boundary(void)
{
    struct TrafficDataHolder_s dh = {0};
    struct TrafficRawData_s reading = {.value = DATA_HOLDER_TRAFFIC_MAX};
    observer_update_fn_t captured_callback = NULL;

    DATA_HOLDER_traffic_init(&dh);
    captured_callback = OBSERVER_init_fake.arg1_val;

    captured_callback(&dh, &reading);

    TEST_ASSERT_TRUE(dh.is_valid);
    TEST_ASSERT_EQUAL_UINT16(DATA_HOLDER_TRAFFIC_MAX, dh.data.congestion_percent);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_temperature_init_should_fail_when_self_is_null);
    RUN_TEST(test_temperature_init_should_initialize_observer_and_reset_state);

    RUN_TEST(test_time_init_should_fail_when_self_is_null);
    RUN_TEST(test_time_init_should_initialize_observer_and_reset_state);

    RUN_TEST(test_traffic_init_should_fail_when_self_is_null);
    RUN_TEST(test_traffic_init_should_initialize_observer_and_reset_state);

    RUN_TEST(test_temperature_update_should_reject_null_self);
    RUN_TEST(test_temperature_update_should_reject_null_context);
    RUN_TEST(test_temperature_update_should_reject_invalid_reading);
    RUN_TEST(test_temperature_update_should_accept_valid_reading);
    RUN_TEST(test_temperature_update_should_accept_max_boundary);

    RUN_TEST(test_time_update_should_reject_null_context);
    RUN_TEST(test_time_update_should_reject_negative_reading);
    RUN_TEST(test_time_update_should_reject_reading_exceeding_max);
    RUN_TEST(test_time_update_should_accept_valid_reading);
    RUN_TEST(test_time_update_should_accept_zero);
    RUN_TEST(test_time_update_should_accept_max_boundary);

    RUN_TEST(test_traffic_update_should_reject_null_context);
    RUN_TEST(test_traffic_update_should_reject_invalid_reading);
    RUN_TEST(test_traffic_update_should_accept_valid_reading);
    RUN_TEST(test_traffic_update_should_accept_max_boundary);

    return UNITY_END();
}
