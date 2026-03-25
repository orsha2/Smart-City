/**
 * @brief Public interface of the Data Source module.
 *
 * This header defines the raw sensor reading structures and the data source
 * instances used in the notification pipeline. Each data source acts as an
 * observer on the entry point subject and, upon notification, reads a raw
 * value from the HAL and forwards it to its own subject for the next stage.
 *
 * The Observer_s field MUST remain the first member of each DataSource struct
 * so that the update callback can safely cast the self pointer to the full
 * struct type.
 */
#ifndef __SMART_CITY_DATA_SOURCE_H__
#define __SMART_CITY_DATA_SOURCE_H__

/** Headers ******************************************************************/
#include <stdint.h>

#include "common.h"
#include "observer.h"
#include "subject.h"

/** Structs ******************************************************************/
/**
 * @brief Raw temperature reading forwarded as notification context.
 *
 * @param value Raw temperature value in Celsius as returned by the HAL.
 */
struct TemperatureRawData_s {
    uint32_t value;
};

/**
 * @brief Raw time reading forwarded as notification context.
 *
 * @param value Raw time value in HHMMSS format as returned by the HAL.
 */
struct TimeRawData_s {
    int64_t value;
};

/**
 * @brief Raw traffic reading forwarded as notification context.
 *
 * @param value Raw traffic congestion value as returned by the HAL.
 */
struct TrafficRawData_s {
    uint16_t value;
};

/**
 * @brief Temperature data source instance.
 *
 * @param observer Observer registered on the entry point subject.
 * @param subject  Subject used to notify the next stage (data holder).
 */
struct TemperatureDataSource_s {
    struct Observer_s observer;
    struct Subject_s subject;
};

/**
 * @brief Time data source instance.
 *
 * @param observer Observer registered on the entry point subject.
 * @param subject  Subject used to notify the next stage (data holder).
 */
struct TimeDataSource_s {
    struct Observer_s observer;
    struct Subject_s subject;
};

/**
 * @brief Traffic data source instance.
 *
 * @param observer Observer registered on the entry point subject.
 * @param subject  Subject used to notify the next stage (data holder).
 */
struct TrafficDataSource_s {
    struct Observer_s observer;
    struct Subject_s subject;
};

/** Functions ****************************************************************/
/**
 * @brief Initialize a temperature data source instance.
 *
 * @param[in,out] self Pointer to the instance to initialize.
 */
enum status_e DATA_SOURCE_temperature_init(struct TemperatureDataSource_s *self);

/**
 * @brief Initialize a time data source instance.
 *
 * @param[in,out] self Pointer to the instance to initialize.
 */
enum status_e DATA_SOURCE_time_init(struct TimeDataSource_s *self);

/**
 * @brief Initialize a traffic data source instance.
 *
 * @param[in,out] self Pointer to the instance to initialize.
 */
enum status_e DATA_SOURCE_traffic_init(struct TrafficDataSource_s *self);

#endif /* !__SMART_CITY_DATA_SOURCE_H__ */
