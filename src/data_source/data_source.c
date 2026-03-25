/** Headers ******************************************************************/
#include "data_source.h"
#include "hal_functions.h"

/** Static callbacks *********************************************************/
static void temperature_update(void *self, void *context)
{
    struct TemperatureDataSource_s *data_source = (struct TemperatureDataSource_s *)self;
    struct TemperatureRawData_s reading = {0};

    (void)context;

    if (!IS_VALID_PTR(data_source)) {
        goto lbl_cleanup;
    }

    reading.value = HAL_read_temperature_sensor();

    SUBJECT_notify_all(&data_source->subject, &reading);

lbl_cleanup:
    return;
}

static void time_update(void *self, void *context)
{
    struct TimeDataSource_s *data_source = (struct TimeDataSource_s *)self;
    struct TimeRawData_s reading = {0};

    (void)context;

    if (!IS_VALID_PTR(data_source)) {
        goto lbl_cleanup;
    }

    reading.value = HAL_read_time_sensor();

    SUBJECT_notify_all(&data_source->subject, &reading);

lbl_cleanup:
    return;
}

static void traffic_update(void *self, void *context)
{
    struct TrafficDataSource_s *data_source = (struct TrafficDataSource_s *)self;
    struct TrafficRawData_s reading = {0};

    (void)context;

    if (!IS_VALID_PTR(data_source)) {
        goto lbl_cleanup;
    }

    reading.value = HAL_read_traffic_sensor();

    SUBJECT_notify_all(&data_source->subject, &reading);

lbl_cleanup:
    return;
}

/** Functions ****************************************************************/
enum status_e DATA_SOURCE_temperature_init(struct TemperatureDataSource_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    status = OBSERVER_init(&self->observer, temperature_update);
    if (SC_STATUS_SUCCESS != status) {
        goto lbl_cleanup;
    }

    status = SUBJECT_init(&self->subject);

lbl_cleanup:
    return status;
}

enum status_e DATA_SOURCE_time_init(struct TimeDataSource_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    status = OBSERVER_init(&self->observer, time_update);
    if (SC_STATUS_SUCCESS != status) {
        goto lbl_cleanup;
    }

    status = SUBJECT_init(&self->subject);

lbl_cleanup:
    return status;
}

enum status_e DATA_SOURCE_traffic_init(struct TrafficDataSource_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    status = OBSERVER_init(&self->observer, traffic_update);
    if (SC_STATUS_SUCCESS != status) {
        goto lbl_cleanup;
    }

    status = SUBJECT_init(&self->subject);

lbl_cleanup:
    return status;
}
