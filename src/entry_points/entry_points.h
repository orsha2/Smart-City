/**
 * @brief Public interface of the Entry Points module.
 *
 * This header defines the boundary functions used to read raw sensor data
 * from the HAL and forward it into the system pipeline, and to forward final
 * system commands to the HAL.
 */
#ifndef __SMART_CITY_ENTRY_POINTS_H__
#define __SMART_CITY_ENTRY_POINTS_H__

/** Headers ******************************************************************/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "common.h"
#include "hal_functions.h"
#include "subject.h"

/** Structs ******************************************************************/
/**
 * @brief Raw temperature data received from the HAL.
 */
struct TemperatureRawData_s {
    uint32_t value;
};

/**
 * @brief Raw time data received from the HAL.
 */
struct TimeRawData_s {
    int64_t value;
};

/**
 * @brief Raw traffic data received from the HAL.
 */
struct TrafficRawData_s {
    uint16_t value;
};

/**
 * @brief Command data for the cooling system.
 */
struct CoolingCommand_s {
    enum HAL_AIR_CONDITIONER_STATE_e state;
    enum HAL_AIR_CONDITIONER_MODE_e mode;
    enum HAL_AIR_CONDITIONER_FAN_LEVEL_e fan_level;
};

/**
 * @brief Command data for the lighting system.
 */
struct LightingCommand_s {
    bool should_turn_on;
};

/**
 * @brief Command data for the traffic light system.
 */
struct TrafficCommand_s {
    size_t red_light_duration;
    size_t green_light_duration;
};

/** Functions ****************************************************************/
/**
 * @brief Reads raw temperature data from the HAL and publishes it to the pipeline.
 *
 * @param[in,out] self Pointer to the subject used to publish the raw temperature data.
 */
enum status_e temperature_entry_point(struct Subject_s *self);

/**
 * @brief Reads raw time data from the HAL and publishes it to the pipeline.
 *
 * @param[in,out] self Pointer to the subject used to publish the raw time data.
 */
enum status_e time_entry_point(struct Subject_s *self);

/**
 * @brief Reads raw traffic data from the HAL and publishes it to the pipeline.
 *
 * @param[in,out] self Pointer to the subject used to publish the raw traffic data.
 */
enum status_e traffic_entry_point(struct Subject_s *self);

/**
 * @brief Sends a cooling command to the HAL.
 *
 * @param[in] self Pointer to the cooling command to apply.
 */
enum status_e city_api_cooling_entry_point(struct CoolingCommand_s *self);

/**
 * @brief Sends a lighting command to the HAL.
 *
 * @param[in] self Pointer to the lighting command to apply.
 */
enum status_e city_api_lighting_entry_point(struct LightingCommand_s *self);

/**
 * @brief Sends a traffic light command to the HAL.
 *
 * @param[in] self Pointer to the traffic command to apply.
 */
enum status_e city_api_traffic_entry_point(struct TrafficCommand_s *self);

#endif /* !__SMART_CITY_ENTRY_POINTS_H__ */