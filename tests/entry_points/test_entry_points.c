#include "unity.h"
#include "fff.h"

#include "common.h"
#include "entry_points.h"

DEFINE_FFF_GLOBALS

/** Constants ****************************************************************/
#define TEST_RED_LIGHT_DURATION (45U)
#define TEST_GREEN_LIGHT_DURATION (20U)

/** Fakes ********************************************************************/
FAKE_VOID_FUNC3(HAL_update_air_conditioner_state,
                enum HAL_AIR_CONDITIONER_STATE_e,
                enum HAL_AIR_CONDITIONER_MODE_e,
                enum HAL_AIR_CONDITIONER_FAN_LEVEL_e)

FAKE_VOID_FUNC0(HAL_turn_on_streetlights)
FAKE_VOID_FUNC0(HAL_turn_off_streetlights)
FAKE_VOID_FUNC2(HAL_set_traffic_light, size_t, size_t)

FAKE_VALUE_FUNC2(enum status_e, SUBJECT_notify_all, struct Subject_s *, void *)

/** Functions ****************************************************************/
void setUp(void)
{
    RESET_FAKE(HAL_update_air_conditioner_state);
    RESET_FAKE(HAL_turn_on_streetlights);
    RESET_FAKE(HAL_turn_off_streetlights);
    RESET_FAKE(HAL_set_traffic_light);
    RESET_FAKE(SUBJECT_notify_all);

    FFF_RESET_HISTORY();
}

void tearDown(void)
{
}

/** Read API (inputs) ********************************************************/
void test_temperature_entry_point_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = temperature_entry_point(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_notify_all_fake.call_count);
}

void test_time_entry_point_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = time_entry_point(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_notify_all_fake.call_count);
}

void test_traffic_entry_point_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = traffic_entry_point(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
    TEST_ASSERT_EQUAL_UINT(0U, SUBJECT_notify_all_fake.call_count);
}

void test_temperature_entry_point_should_notify_subject(void)
{
    struct Subject_s subject = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = temperature_entry_point(&subject);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_notify_all_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&subject, SUBJECT_notify_all_fake.arg0_val);
    TEST_ASSERT_NULL(SUBJECT_notify_all_fake.arg1_val);
}

void test_time_entry_point_should_notify_subject(void)
{
    struct Subject_s subject = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = time_entry_point(&subject);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_notify_all_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&subject, SUBJECT_notify_all_fake.arg0_val);
    TEST_ASSERT_NULL(SUBJECT_notify_all_fake.arg1_val);
}

void test_traffic_entry_point_should_notify_subject(void)
{
    struct Subject_s subject = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = traffic_entry_point(&subject);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, SUBJECT_notify_all_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&subject, SUBJECT_notify_all_fake.arg0_val);
    TEST_ASSERT_NULL(SUBJECT_notify_all_fake.arg1_val);
}

void test_temperature_entry_point_should_propagate_notify_all_failure(void)
{
    struct Subject_s subject = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    SUBJECT_notify_all_fake.return_val = SC_STATUS_FAILURE;

    status = temperature_entry_point(&subject);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_FAILURE, status);
}

void test_time_entry_point_should_propagate_notify_all_failure(void)
{
    struct Subject_s subject = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    SUBJECT_notify_all_fake.return_val = SC_STATUS_FAILURE;

    status = time_entry_point(&subject);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_FAILURE, status);
}

void test_traffic_entry_point_should_propagate_notify_all_failure(void)
{
    struct Subject_s subject = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    SUBJECT_notify_all_fake.return_val = SC_STATUS_FAILURE;

    status = traffic_entry_point(&subject);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_FAILURE, status);
}

/** Write API (outputs) ******************************************************/
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
    struct CoolingCommand_s command = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    command.state = HAL_AIR_CONDITIONER_STATE_ON;
    command.mode = HAL_AIR_CONDITIONER_MODE_COOL;
    command.fan_level = HAL_AIR_CONDITIONER_FAN_LEVEL_3;

    status = city_api_cooling_entry_point(&command);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, HAL_update_air_conditioner_state_fake.call_count);
    TEST_ASSERT_EQUAL_INT(command.state, HAL_update_air_conditioner_state_fake.arg0_val);
    TEST_ASSERT_EQUAL_INT(command.mode, HAL_update_air_conditioner_state_fake.arg1_val);
    TEST_ASSERT_EQUAL_INT(command.fan_level, HAL_update_air_conditioner_state_fake.arg2_val);
}

void test_city_api_lighting_entry_point_should_turn_on_streetlights_when_requested(void)
{
    struct LightingCommand_s command = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    command.should_turn_on = true;

    status = city_api_lighting_entry_point(&command);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, HAL_turn_on_streetlights_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(0U, HAL_turn_off_streetlights_fake.call_count);
}

void test_city_api_lighting_entry_point_should_turn_off_streetlights_when_requested(void)
{
    struct LightingCommand_s command = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    command.should_turn_on = false;

    status = city_api_lighting_entry_point(&command);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(0U, HAL_turn_on_streetlights_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(1U, HAL_turn_off_streetlights_fake.call_count);
}

void test_city_api_traffic_entry_point_should_call_hal_set_traffic_light(void)
{
    struct TrafficCommand_s command = {0};
    enum status_e status = SC_STATUS_UNINITIALIZED;

    command.red_light_duration = TEST_RED_LIGHT_DURATION;
    command.green_light_duration = TEST_GREEN_LIGHT_DURATION;

    status = city_api_traffic_entry_point(&command);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(1U, HAL_set_traffic_light_fake.call_count);
    TEST_ASSERT_EQUAL_UINT(TEST_RED_LIGHT_DURATION, HAL_set_traffic_light_fake.arg0_val);
    TEST_ASSERT_EQUAL_UINT(TEST_GREEN_LIGHT_DURATION, HAL_set_traffic_light_fake.arg1_val);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_temperature_entry_point_should_fail_when_self_is_null);
    RUN_TEST(test_time_entry_point_should_fail_when_self_is_null);
    RUN_TEST(test_traffic_entry_point_should_fail_when_self_is_null);

    RUN_TEST(test_temperature_entry_point_should_notify_subject);
    RUN_TEST(test_time_entry_point_should_notify_subject);
    RUN_TEST(test_traffic_entry_point_should_notify_subject);

    RUN_TEST(test_temperature_entry_point_should_propagate_notify_all_failure);
    RUN_TEST(test_time_entry_point_should_propagate_notify_all_failure);
    RUN_TEST(test_traffic_entry_point_should_propagate_notify_all_failure);

    RUN_TEST(test_city_api_cooling_entry_point_should_fail_when_self_is_null);
    RUN_TEST(test_city_api_lighting_entry_point_should_fail_when_self_is_null);
    RUN_TEST(test_city_api_traffic_entry_point_should_fail_when_self_is_null);

    RUN_TEST(test_city_api_cooling_entry_point_should_call_hal_update_air_conditioner_state);
    RUN_TEST(test_city_api_lighting_entry_point_should_turn_on_streetlights_when_requested);
    RUN_TEST(test_city_api_lighting_entry_point_should_turn_off_streetlights_when_requested);
    RUN_TEST(test_city_api_traffic_entry_point_should_call_hal_set_traffic_light);

    return UNITY_END();
}