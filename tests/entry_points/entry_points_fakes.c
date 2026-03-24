/** Headers ******************************************************************/

#include "entry_points_fakes.h"

/** FFF **********************************************************************/

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(uint32_t, HAL_read_temperature_sensor);
FAKE_VALUE_FUNC(int64_t, HAL_read_time_sensor);
FAKE_VALUE_FUNC(uint16_t, HAL_read_traffic_sensor);

FAKE_VOID_FUNC(HAL_update_air_conditioner_state,
               enum HAL_AIR_CONDITIONER_STATE_e,
               enum HAL_AIR_CONDITIONER_MODE_e,
               enum HAL_AIR_CONDITIONER_FAN_LEVEL_e);
FAKE_VOID_FUNC(HAL_turn_on_streetlights);
FAKE_VOID_FUNC(HAL_turn_off_streetlights);
FAKE_VOID_FUNC(HAL_set_traffic_light, size_t, size_t);

FAKE_VALUE_FUNC(enum status_e, SUBJECT_notify_all, struct Subject_s *, void *);

/** Globals ******************************************************************/

struct Subject_s *g_subject_seen = NULL;
struct TemperatureRawData_s g_temperature_raw_data = {0};
struct TimeRawData_s g_time_raw_data = {0};
struct TrafficRawData_s g_traffic_raw_data = {0};

/** Functions ****************************************************************/

void ENTRY_POINTS_FAKES_reset(void)
{
    RESET_FAKE(HAL_read_temperature_sensor);
    RESET_FAKE(HAL_read_time_sensor);
    RESET_FAKE(HAL_read_traffic_sensor);
    RESET_FAKE(HAL_update_air_conditioner_state);
    RESET_FAKE(HAL_turn_on_streetlights);
    RESET_FAKE(HAL_turn_off_streetlights);
    RESET_FAKE(HAL_set_traffic_light);
    RESET_FAKE(SUBJECT_notify_all);

    FFF_RESET_HISTORY();

    g_subject_seen = NULL;
    g_temperature_raw_data.value = 0U;
    g_time_raw_data.value = 0;
    g_traffic_raw_data.value = 0U;
}

enum status_e naive_temperature_notify_all_fake(struct Subject_s *self,
                                                void *context)
{
    struct TemperatureRawData_s *raw_data = NULL;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self) || !IS_VALID_PTR(context)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    raw_data = (struct TemperatureRawData_s *)context;

    g_subject_seen = self;
    g_temperature_raw_data = *raw_data;

    status = SC_STATUS_SUCCESS;

lbl_cleanup:
    return status;
}

enum status_e naive_time_notify_all_fake(struct Subject_s *self,
                                         void *context)
{
    struct TimeRawData_s *raw_data = NULL;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self) || !IS_VALID_PTR(context)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    raw_data = (struct TimeRawData_s *)context;

    g_subject_seen = self;
    g_time_raw_data = *raw_data;

    status = SC_STATUS_SUCCESS;

lbl_cleanup:
    return status;
}

enum status_e naive_traffic_notify_all_fake(struct Subject_s *self,
                                            void *context)
{
    struct TrafficRawData_s *raw_data = NULL;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self) || !IS_VALID_PTR(context)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    raw_data = (struct TrafficRawData_s *)context;

    g_subject_seen = self;
    g_traffic_raw_data = *raw_data;

    status = SC_STATUS_SUCCESS;

lbl_cleanup:
    return status;
}