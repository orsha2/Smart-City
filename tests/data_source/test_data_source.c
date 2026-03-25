#include "unity.h"
#include "fff.h"

#include "common.h"
#include "data_source.h"

DEFINE_FFF_GLOBALS

/** Constants ****************************************************************/
#define TEST_TEMPERATURE_VALUE (42U)
#define TEST_TIME_VALUE        (153000LL) /* 15:30:00 */
#define TEST_TRAFFIC_VALUE     (75U)

/** Fakes ********************************************************************/
FAKE_VALUE_FUNC0(uint32_t, HAL_read_temperature_sensor)
FAKE_VALUE_FUNC0(int64_t, HAL_read_time_sensor)
FAKE_VALUE_FUNC0(uint16_t, HAL_read_traffic_sensor)

FAKE_VALUE_FUNC2(enum status_e, OBSERVER_init, struct Observer_s *, observer_update_fn_t)
FAKE_VALUE_FUNC1(enum status_e, SUBJECT_init, struct Subject_s *)
FAKE_VALUE_FUNC2(enum status_e, SUBJECT_notify_all, struct Subject_s *, void *)
FAKE_VALUE_FUNC2(bool, SUBJECT_attach, struct Subject_s *, struct Observer_s *)

/** Functions ****************************************************************/
void setUp(void)
{
    RESET_FAKE(HAL_read_temperature_sensor);
    RESET_FAKE(HAL_read_time_sensor);
    RESET_FAKE(HAL_read_traffic_sensor);
    RESET_FAKE(OBSERVER_init);
    RESET_FAKE(SUBJECT_init);
    RESET_FAKE(SUBJECT_notify_all);
    RESET_FAKE(SUBJECT_attach);

    OBSERVER_init_fake.return_val = SC_STATUS_SUCCESS;
    SUBJECT_init_fake.return_val = SC_STATUS_SUCCESS;

    FFF_RESET_HISTORY();
}

void tearDown(void)
{
}

/** DATA_SOURCE_temperature_init *********************************************/
void test_temperature_init_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = DATA_SOURCE_temperature_init(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, OBSERVER_init_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_init_fake.call_count);
}

void test_temperature_init_should_initialize_observer_and_subject(void)
{
    struct TemperatureDataSource_s ds = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = DATA_SOURCE_temperature_init(&ds);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, OBSERVER_init_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&ds.observer, OBSERVER_init_fake.arg0_val);
    TEST_ASSERT_NOT_NULL(OBSERVER_init_fake.arg1_val);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_init_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&ds.subject, SUBJECT_init_fake.arg0_val);
}

void test_temperature_init_should_propagate_observer_init_failure(void)
{
    struct TemperatureDataSource_s ds = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    OBSERVER_init_fake.return_val = SC_STATUS_FAILURE;

    status = DATA_SOURCE_temperature_init(&ds);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_init_fake.call_count);
}

/** DATA_SOURCE_time_init ****************************************************/
void test_time_init_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = DATA_SOURCE_time_init(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, OBSERVER_init_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_init_fake.call_count);
}

void test_time_init_should_initialize_observer_and_subject(void)
{
    struct TimeDataSource_s ds = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = DATA_SOURCE_time_init(&ds);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, OBSERVER_init_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&ds.observer, OBSERVER_init_fake.arg0_val);
    TEST_ASSERT_NOT_NULL(OBSERVER_init_fake.arg1_val);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_init_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&ds.subject, SUBJECT_init_fake.arg0_val);
}

void test_time_init_should_propagate_observer_init_failure(void)
{
    struct TimeDataSource_s ds = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    OBSERVER_init_fake.return_val = SC_STATUS_FAILURE;

    status = DATA_SOURCE_time_init(&ds);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_init_fake.call_count);
}

/** DATA_SOURCE_traffic_init *************************************************/
void test_traffic_init_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = DATA_SOURCE_traffic_init(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, OBSERVER_init_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_init_fake.call_count);
}

void test_traffic_init_should_initialize_observer_and_subject(void)
{
    struct TrafficDataSource_s ds = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = DATA_SOURCE_traffic_init(&ds);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, OBSERVER_init_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&ds.observer, OBSERVER_init_fake.arg0_val);
    TEST_ASSERT_NOT_NULL(OBSERVER_init_fake.arg1_val);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_init_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&ds.subject, SUBJECT_init_fake.arg0_val);
}

void test_traffic_init_should_propagate_observer_init_failure(void)
{
    struct TrafficDataSource_s ds = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    OBSERVER_init_fake.return_val = SC_STATUS_FAILURE;

    status = DATA_SOURCE_traffic_init(&ds);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_init_fake.call_count);
}

/** Observer callbacks *******************************************************/
void test_temperature_update_should_read_hal_and_notify_subject(void)
{
    struct TemperatureDataSource_s ds = {0};
    observer_update_fn_t captured_callback = NULL;

    /* Init to capture the callback registered with the observer */
    DATA_SOURCE_temperature_init(&ds);
    captured_callback = OBSERVER_init_fake.arg1_val;

    RESET_FAKE(HAL_read_temperature_sensor);
    RESET_FAKE(SUBJECT_notify_all);
    HAL_read_temperature_sensor_fake.return_val = TEST_TEMPERATURE_VALUE;

    captured_callback(&ds, NULL);

    TEST_ASSERT_EQUAL_UINT(1U, HAL_read_temperature_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_notify_all_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&ds.subject, SUBJECT_notify_all_fake.arg0_val);
    TEST_ASSERT_NOT_NULL(SUBJECT_notify_all_fake.arg1_val);
}

void test_temperature_update_should_not_notify_when_self_is_null(void)
{
    struct TemperatureDataSource_s ds = {0};
    observer_update_fn_t captured_callback = NULL;

    DATA_SOURCE_temperature_init(&ds);
    captured_callback = OBSERVER_init_fake.arg1_val;

    RESET_FAKE(HAL_read_temperature_sensor);
    RESET_FAKE(SUBJECT_notify_all);

    captured_callback(NULL, NULL);

    TEST_ASSERT_EQUAL_UINT(0U, HAL_read_temperature_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_notify_all_fake.call_count);
}

void test_time_update_should_read_hal_and_notify_subject(void)
{
    struct TimeDataSource_s ds = {0};
    observer_update_fn_t captured_callback = NULL;

    DATA_SOURCE_time_init(&ds);
    captured_callback = OBSERVER_init_fake.arg1_val;

    RESET_FAKE(HAL_read_time_sensor);
    RESET_FAKE(SUBJECT_notify_all);
    HAL_read_time_sensor_fake.return_val = TEST_TIME_VALUE;

    captured_callback(&ds, NULL);

    TEST_ASSERT_EQUAL_UINT(1U, HAL_read_time_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_notify_all_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&ds.subject, SUBJECT_notify_all_fake.arg0_val);
    TEST_ASSERT_NOT_NULL(SUBJECT_notify_all_fake.arg1_val);
}

void test_time_update_should_not_notify_when_self_is_null(void)
{
    struct TimeDataSource_s ds = {0};
    observer_update_fn_t captured_callback = NULL;

    DATA_SOURCE_time_init(&ds);
    captured_callback = OBSERVER_init_fake.arg1_val;

    RESET_FAKE(HAL_read_time_sensor);
    RESET_FAKE(SUBJECT_notify_all);

    captured_callback(NULL, NULL);

    TEST_ASSERT_EQUAL_UINT(0U, HAL_read_time_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_notify_all_fake.call_count);
}

void test_traffic_update_should_read_hal_and_notify_subject(void)
{
    struct TrafficDataSource_s ds = {0};
    observer_update_fn_t captured_callback = NULL;

    DATA_SOURCE_traffic_init(&ds);
    captured_callback = OBSERVER_init_fake.arg1_val;

    RESET_FAKE(HAL_read_traffic_sensor);
    RESET_FAKE(SUBJECT_notify_all);
    HAL_read_traffic_sensor_fake.return_val = TEST_TRAFFIC_VALUE;

    captured_callback(&ds, NULL);

    TEST_ASSERT_EQUAL_UINT(1U, HAL_read_traffic_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_notify_all_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&ds.subject, SUBJECT_notify_all_fake.arg0_val);
    TEST_ASSERT_NOT_NULL(SUBJECT_notify_all_fake.arg1_val);
}

void test_traffic_update_should_not_notify_when_self_is_null(void)
{
    struct TrafficDataSource_s ds = {0};
    observer_update_fn_t captured_callback = NULL;

    DATA_SOURCE_traffic_init(&ds);
    captured_callback = OBSERVER_init_fake.arg1_val;

    RESET_FAKE(HAL_read_traffic_sensor);
    RESET_FAKE(SUBJECT_notify_all);

    captured_callback(NULL, NULL);

    TEST_ASSERT_EQUAL_UINT(0U, HAL_read_traffic_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_notify_all_fake.call_count);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_temperature_init_should_fail_when_self_is_null);
    RUN_TEST(test_temperature_init_should_initialize_observer_and_subject);
    RUN_TEST(test_temperature_init_should_propagate_observer_init_failure);

    RUN_TEST(test_time_init_should_fail_when_self_is_null);
    RUN_TEST(test_time_init_should_initialize_observer_and_subject);
    RUN_TEST(test_time_init_should_propagate_observer_init_failure);

    RUN_TEST(test_traffic_init_should_fail_when_self_is_null);
    RUN_TEST(test_traffic_init_should_initialize_observer_and_subject);
    RUN_TEST(test_traffic_init_should_propagate_observer_init_failure);

    RUN_TEST(test_temperature_update_should_read_hal_and_notify_subject);
    RUN_TEST(test_temperature_update_should_not_notify_when_self_is_null);

    RUN_TEST(test_time_update_should_read_hal_and_notify_subject);
    RUN_TEST(test_time_update_should_not_notify_when_self_is_null);

    RUN_TEST(test_traffic_update_should_read_hal_and_notify_subject);
    RUN_TEST(test_traffic_update_should_not_notify_when_self_is_null);

    return UNITY_END();
}
