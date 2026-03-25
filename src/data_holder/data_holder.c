/** Headers ******************************************************************/
#include "data_holder.h"
#include "data_source.h"

/** Static callbacks *********************************************************/
static void temperature_update(void *self, void *context)
{
    struct TemperatureDataHolder_s *data_holder = (struct TemperatureDataHolder_s *)self;
    struct TemperatureRawData_s *reading = (struct TemperatureRawData_s *)context;

    if (!IS_VALID_PTR(data_holder)) {
        goto lbl_cleanup;
    }

    data_holder->is_valid = false;

    if (!IS_VALID_PTR(reading)) {
        goto lbl_cleanup;
    }

    if (reading->value > DATA_HOLDER_TEMPERATURE_MAX) {
        goto lbl_cleanup;
    }

    data_holder->data.celsius = reading->value;
    data_holder->is_valid = true;

lbl_cleanup:
    return;
}

static void time_update(void *self, void *context)
{
    struct TimeDataHolder_s *data_holder = (struct TimeDataHolder_s *)self;
    struct TimeRawData_s *reading = (struct TimeRawData_s *)context;

    if (!IS_VALID_PTR(data_holder)) {
        goto lbl_cleanup;
    }

    data_holder->is_valid = false;

    if (!IS_VALID_PTR(reading)) {
        goto lbl_cleanup;
    }

    if (reading->value < 0 || reading->value > DATA_HOLDER_TIME_MAX) {
        goto lbl_cleanup;
    }

    data_holder->data.hhmmss = reading->value;
    data_holder->is_valid = true;

lbl_cleanup:
    return;
}

static void traffic_update(void *self, void *context)
{
    struct TrafficDataHolder_s *data_holder = (struct TrafficDataHolder_s *)self;
    struct TrafficRawData_s *reading = (struct TrafficRawData_s *)context;

    if (!IS_VALID_PTR(data_holder)) {
        goto lbl_cleanup;
    }

    data_holder->is_valid = false;

    if (!IS_VALID_PTR(reading)) {
        goto lbl_cleanup;
    }

    if (reading->value > DATA_HOLDER_TRAFFIC_MAX) {
        goto lbl_cleanup;
    }

    data_holder->data.congestion_percent = reading->value;
    data_holder->is_valid = true;

lbl_cleanup:
    return;
}

/** Functions ****************************************************************/
enum status_e DATA_HOLDER_temperature_init(struct TemperatureDataHolder_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    self->is_valid = false;

    status = OBSERVER_init(&self->observer, temperature_update);

lbl_cleanup:
    return status;
}

enum status_e DATA_HOLDER_time_init(struct TimeDataHolder_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    self->is_valid = false;

    status = OBSERVER_init(&self->observer, time_update);

lbl_cleanup:
    return status;
}

enum status_e DATA_HOLDER_traffic_init(struct TrafficDataHolder_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    self->is_valid = false;

    status = OBSERVER_init(&self->observer, traffic_update);

lbl_cleanup:
    return status;
}
