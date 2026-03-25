/**
 * @brief Public interface of the Data Holder module.
 *
 * This header defines the validated data structures and the data holder
 * instances used in the notification pipeline. Each data holder acts as an
 * observer on a data source subject. Upon notification it receives the raw
 * sensor reading, validates the value, and stores the parsed result.
 *
 * The Observer_s field MUST remain the first member of each DataHolder struct
 * so that the update callback can safely cast the self pointer to the full
 * struct type.
 */
#ifndef __SMART_CITY_DATA_HOLDER_H__
#define __SMART_CITY_DATA_HOLDER_H__

/** Headers ******************************************************************/
#include <stdbool.h>
#include <stdint.h>

#include "common.h"
#include "observer.h"

/** Constants ****************************************************************/
/**
 * @brief Maximum valid temperature reading (in Celsius).
 */
#define DATA_HOLDER_TEMPERATURE_MAX (100U)

/**
 * @brief Maximum valid time reading (HHMMSS format, represents 23:59:59).
 */
#define DATA_HOLDER_TIME_MAX (235959LL)

/**
 * @brief Maximum valid traffic congestion percentage.
 */
#define DATA_HOLDER_TRAFFIC_MAX (100U)

/** Structs ******************************************************************/
/**
 * @brief Validated temperature data.
 *
 * @param celsius Validated temperature value in Celsius.
 */
struct TemperatureData_s {
    uint32_t celsius;
};

/**
 * @brief Validated time data.
 *
 * @param hhmmss Validated time value in HHMMSS format.
 */
struct TimeData_s {
    int64_t hhmmss;
};

/**
 * @brief Validated traffic congestion data.
 *
 * @param congestion_percent Validated traffic congestion percentage (0-100).
 */
struct TrafficData_s {
    uint16_t congestion_percent;
};

/**
 * @brief Temperature data holder instance.
 *
 * @param observer Observer registered on the temperature data source subject.
 * @param data     Validated temperature data populated on each notification.
 * @param is_valid Indicates whether the last received reading was valid.
 */
struct TemperatureDataHolder_s {
    struct Observer_s observer;
    struct TemperatureData_s data;
    bool is_valid;
};

/**
 * @brief Time data holder instance.
 *
 * @param observer Observer registered on the time data source subject.
 * @param data     Validated time data populated on each notification.
 * @param is_valid Indicates whether the last received reading was valid.
 */
struct TimeDataHolder_s {
    struct Observer_s observer;
    struct TimeData_s data;
    bool is_valid;
};

/**
 * @brief Traffic data holder instance.
 *
 * @param observer Observer registered on the traffic data source subject.
 * @param data     Validated traffic data populated on each notification.
 * @param is_valid Indicates whether the last received reading was valid.
 */
struct TrafficDataHolder_s {
    struct Observer_s observer;
    struct TrafficData_s data;
    bool is_valid;
};

/** Functions ****************************************************************/
/**
 * @brief Initialize a temperature data holder instance.
 *
 * @param[in,out] self Pointer to the instance to initialize.
 */
enum status_e DATA_HOLDER_temperature_init(struct TemperatureDataHolder_s *self);

/**
 * @brief Initialize a time data holder instance.
 *
 * @param[in,out] self Pointer to the instance to initialize.
 */
enum status_e DATA_HOLDER_time_init(struct TimeDataHolder_s *self);

/**
 * @brief Initialize a traffic data holder instance.
 *
 * @param[in,out] self Pointer to the instance to initialize.
 */
enum status_e DATA_HOLDER_traffic_init(struct TrafficDataHolder_s *self);

#endif /* !__SMART_CITY_DATA_HOLDER_H__ */
