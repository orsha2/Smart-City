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
struct TemperatureRawData_s {
    uint32_t value;
};

struct TimeRawData_s {
    int64_t value;
};

struct TrafficRawData_s {
    uint16_t value;
};

struct CoolingCommand_s {
    enum HAL_AIR_CONDITIONER_STATE_e state;
    enum HAL_AIR_CONDITIONER_MODE_e mode;
    enum HAL_AIR_CONDITIONER_FAN_LEVEL_e fan_level;
};

struct LightingCommand_s {
    bool should_turn_on;
};

struct TrafficCommand_s {
    size_t red_light_duration;
    size_t green_light_duration;
};

/** Functions ****************************************************************/
enum status_e temperature_entry_point(struct Subject_s *self);

enum status_e time_entry_point(struct Subject_s *self);

enum status_e traffic_entry_point(struct Subject_s *self);

enum status_e city_api_cooling_entry_point(struct CoolingCommand_s *self);

enum status_e city_api_lighting_entry_point(struct LightingCommand_s *self);

enum status_e city_api_traffic_entry_point(struct TrafficCommand_s *self);

#endif /* !__SMART_CITY_ENTRY_POINTS_H__ */
