#include "unity.h"
#include "fff.h"

#include "common.h"
#include "data_holder.h"
#include "data_source.h"
#include "entry_points.h"
#include "subject.h"

DEFINE_FFF_GLOBALS

/** Constants ****************************************************************/
#define TEST_VALID_TEMPERATURE (30U)

/** Fakes ********************************************************************/
FAKE_VALUE_FUNC0(uint32_t, HAL_read_temperature_sensor)
FAKE_VALUE_FUNC0(int64_t, HAL_read_time_sensor)
FAKE_VALUE_FUNC0(uint16_t, HAL_read_traffic_sensor)
FAKE_VOID_FUNC3(HAL_update_air_conditioner_state,
                enum HAL_AIR_CONDITIONER_STATE_e,
                enum HAL_AIR_CONDITIONER_MODE_e,
                enum HAL_AIR_CONDITIONER_FAN_LEVEL_e)
FAKE_VOID_FUNC0(HAL_turn_on_streetlights)
FAKE_VOID_FUNC0(HAL_turn_off_streetlights)
FAKE_VOID_FUNC2(HAL_set_traffic_light, size_t, size_t)

/** Globals ******************************************************************/
static struct Subject_s raw_data_subject;
static struct TemperatureDataSource_s raw_data_ds;
static struct TemperatureDataHolder_s raw_data_dh;

/** Functions ****************************************************************/
void setUp(void)
{
    RESET_FAKE(HAL_read_temperature_sensor);
    RESET_FAKE(HAL_read_time_sensor);
    RESET_FAKE(HAL_read_traffic_sensor);
    RESET_FAKE(HAL_update_air_conditioner_state);
    RESET_FAKE(HAL_turn_on_streetlights);
    RESET_FAKE(HAL_turn_off_streetlights);
    RESET_FAKE(HAL_set_traffic_light);

    FFF_RESET_HISTORY();

    SUBJECT_init(&raw_data_subject);
    DATA_SOURCE_temperature_init(&raw_data_ds);
    DATA_HOLDER_temperature_init(&raw_data_dh);

    SUBJECT_attach(&raw_data_subject, &raw_data_ds.observer);
    SUBJECT_attach(&raw_data_ds.subject, &raw_data_dh.observer);
}

void tearDown(void)
{
}

/** Happy flow ***************************************************************/
void test_temperature_pipeline_happy_flow(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    HAL_read_temperature_sensor_fake.return_val = TEST_VALID_TEMPERATURE;

    status = temperature_entry_point(&raw_data_subject);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_TRUE(raw_data_dh.is_valid);
    TEST_ASSERT_EQUAL_UINT32(TEST_VALID_TEMPERATURE, raw_data_dh.data.celsius);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_temperature_pipeline_happy_flow);

    return UNITY_END();
}
