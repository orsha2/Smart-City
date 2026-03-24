/** Headers ******************************************************************/

#include "unity.h"

#include "entry_points.h"
#include "entry_points_fakes.h"

/** Constants ****************************************************************/

#define TEST_TEMPERATURE_VALUE      (31U)
#define TEST_TIME_VALUE             (152311LL)
#define TEST_TRAFFIC_VALUE          (77U)
#define TEST_RED_LIGHT_DURATION     (45U)
#define TEST_GREEN_LIGHT_DURATION   (20U)

/** Functions ****************************************************************/

void setUp(void)
{
    ENTRY_POINTS_FAKES_reset();
}

void tearDown(void)
{
}

void test_temperature_entry_point_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = temperature_entry_point(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, HAL_read_temperature_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_notify_all_fake.call_count);
}

void test_time_entry_point_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = time_entry_point(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, HAL_read_time_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_notify_all_fake.call_count);
}

void test_traffic_entry_point_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = traffic_entry_point(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, HAL_read_traffic_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_notify_all_fake.call_count);
}

void test_temperature_entry_point_should_read_temperature_from_hal_and_notify_subject(void)
{
    struct Subject_s subject;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    HAL_read_temperature_sensor_fake.return_val = TEST_TEMPERATURE_VALUE;
    SUBJECT_notify_all_fake.custom_fake = naive_temperature_notify_all_fake;

    status = temperature_entry_point(&subject);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, HAL_read_temperature_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_notify_all_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&subject, g_subject_seen);
    TEST_ASSERT_EQUAL_UINT(TEST_TEMPERATURE_VALUE, g_temperature_raw_data.value);
}

void test_time_entry_point_should_read_time_from_hal_and_notify_subject(void)
{
    struct Subject_s subject;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    HAL_read_time_sensor_fake.return_val = TEST_TIME_VALUE;
    SUBJECT_notify_all_fake.custom_fake = naive_time_notify_all_fake;

    status = time_entry_point(&subject);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, HAL_read_time_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_notify_all_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&subject, g_subject_seen);
    TEST_ASSERT_EQUAL_INT64(TEST_TIME_VALUE, g_time_raw_data.value);
}

void test_traffic_entry_point_should_read_traffic_from_hal_and_notify_subject(void)
{
    struct Subject_s subject;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    HAL_read_traffic_sensor_fake.return_val = TEST_TRAFFIC_VALUE;
    SUBJECT_notify_all_fake.custom_fake = naive_traffic_notify_all_fake;

    status = traffic_entry_point(&subject);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, HAL_read_traffic_sensor_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_notify_all_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&subject, g_subject_seen);
    TEST_ASSERT_EQUAL_UINT(TEST_TRAFFIC_VALUE, g_traffic_raw_data.value);
}

void test_city_api_cooling_entry_point_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = city_api_cooling_entry_point(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, HAL_update_air_conditioner_state_fake.call_count);
}

void test_city_api_lighting_entry_point_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = city_api_lighting_entry_point(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, HAL_turn_on_streetlights_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, HAL_turn_off_streetlights_fake.call_count);
}

void test_city_api_traffic_entry_point_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = city_api_traffic_entry_point(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, HAL_set_traffic_light_fake.call_count);
}

void test_city_api_cooling_entry_point_should_call_hal_update_air_conditioner_state(void)
{
    struct CoolingCommand_s command;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    command.state = HAL_AIR_CONDITIONER_STATE_ON;
    command.mode = HAL_AIR_CONDITIONER_MODE_COOL;
    command.fan_level = HAL_AIR_CONDITIONER_FAN_LEVEL_3;

    status = city_api_cooling_entry_point(&command);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, HAL_update_air_conditioner_state_fake.call_count);
    TEST_ASSERT_EQUAL_INT(command.state,
                          HAL_update_air_conditioner_state_fake.arg0_val);
    TEST_ASSERT_EQUAL_INT(command.mode,
                          HAL_update_air_conditioner_state_fake.arg1_val);
    TEST_ASSERT_EQUAL_INT(command.fan_level,
                          HAL_update_air_conditioner_state_fake.arg2_val);
}

void test_city_api_lighting_entry_point_should_turn_on_streetlights_when_requested(void)
{
    struct LightingCommand_s command;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    command.should_turn_on = true;

    status = city_api_lighting_entry_point(&command);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, HAL_turn_on_streetlights_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, HAL_turn_off_streetlights_fake.call_count);
}

void test_city_api_lighting_entry_point_should_turn_off_streetlights_when_requested(void)
{
    struct LightingCommand_s command;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    command.should_turn_on = false;

    status = city_api_lighting_entry_point(&command);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(0U, HAL_turn_on_streetlights_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(1U, HAL_turn_off_streetlights_fake.call_count);
}

void test_city_api_traffic_entry_point_should_call_hal_set_traffic_light(void)
{
    struct TrafficCommand_s command;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    command.red_light_duration = TEST_RED_LIGHT_DURATION;
    command.green_light_duration = TEST_GREEN_LIGHT_DURATION;

    status = city_api_traffic_entry_point(&command);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, HAL_set_traffic_light_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(TEST_RED_LIGHT_DURATION,
                           HAL_set_traffic_light_fake.arg0_val);
    TEST_ASSERT_EQUAL_UINT(TEST_GREEN_LIGHT_DURATION,
                           HAL_set_traffic_light_fake.arg1_val);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_temperature_entry_point_should_fail_when_self_is_null);
    RUN_TEST(test_time_entry_point_should_fail_when_self_is_null);
    RUN_TEST(test_traffic_entry_point_should_fail_when_self_is_null);
    RUN_TEST(test_temperature_entry_point_should_read_temperature_from_hal_and_notify_subject);
    RUN_TEST(test_time_entry_point_should_read_time_from_hal_and_notify_subject);
    RUN_TEST(test_traffic_entry_point_should_read_traffic_from_hal_and_notify_subject);
    RUN_TEST(test_city_api_cooling_entry_point_should_fail_when_self_is_null);
    RUN_TEST(test_city_api_lighting_entry_point_should_fail_when_self_is_null);
    RUN_TEST(test_city_api_traffic_entry_point_should_fail_when_self_is_null);
    RUN_TEST(test_city_api_cooling_entry_point_should_call_hal_update_air_conditioner_state);
    RUN_TEST(test_city_api_lighting_entry_point_should_turn_on_streetlights_when_requested);
    RUN_TEST(test_city_api_lighting_entry_point_should_turn_off_streetlights_when_requested);
    RUN_TEST(test_city_api_traffic_entry_point_should_call_hal_set_traffic_light);

    return UNITY_END();
}