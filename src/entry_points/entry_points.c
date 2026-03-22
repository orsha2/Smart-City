/** Headers ******************************************************************/
#include "entry_points.h"

/** Functions ****************************************************************/
enum status_e temperature_entry_point(struct Subject_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;
    struct TemperatureRawData_s raw_data = {0};

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    raw_data.value = HAL_read_temperature_sensor();

    status = SUBJECT_notify_all(self, &raw_data);

lbl_cleanup:
    return status;
}

enum status_e time_entry_point(struct Subject_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;
    struct TimeRawData_s raw_data = {0};

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    raw_data.value = HAL_read_time_sensor();

    status = SUBJECT_notify_all(self, &raw_data);

lbl_cleanup:
    return status;
}

enum status_e traffic_entry_point(struct Subject_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;
    struct TrafficRawData_s raw_data = {0};

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    raw_data.value = HAL_read_traffic_sensor();

    status = SUBJECT_notify_all(self, &raw_data);

lbl_cleanup:
    return status;
}

enum status_e city_api_cooling_entry_point(struct CoolingCommand_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    HAL_update_air_conditioner_state(self->state, self->mode, self->fan_level);

    status = SC_STATUS_SUCCESS;

lbl_cleanup:
    return status;
}

enum status_e city_api_lighting_entry_point(struct LightingCommand_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    if (self->should_turn_on) {
        HAL_turn_on_streetlights();
    } else {
        HAL_turn_off_streetlights();
    }

    status = SC_STATUS_SUCCESS;

lbl_cleanup:
    return status;
}

enum status_e city_api_traffic_entry_point(struct TrafficCommand_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    HAL_set_traffic_light(self->red_light_duration, self->green_light_duration);

    status = SC_STATUS_SUCCESS;

lbl_cleanup:
    return status;
}
