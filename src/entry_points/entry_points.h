/**
 * @brief Public interface of the Entry Points module.
 *
 * This header defines the boundary functions used to trigger the system
 * pipeline and to forward final system commands to the HAL.
 */
#ifndef __SMART_CITY_ENTRY_POINTS_H__
#define __SMART_CITY_ENTRY_POINTS_H__

/** Headers ******************************************************************/
#include "common.h"
#include "hal_functions.h"
#include "subject.h"

/** Structs ******************************************************************/
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

/** Read API (inputs) ********************************************************/
/**
 * @brief Triggers the temperature pipeline.
 *
 * @param[in,out] self Pointer to the subject to notify.
 */
enum status_e temperature_entry_point(struct Subject_s *self);

/**
 * @brief Triggers the time pipeline.
 *
 * @param[in,out] self Pointer to the subject to notify.
 */
enum status_e time_entry_point(struct Subject_s *self);

/**
 * @brief Triggers the traffic pipeline.
 *
 * @param[in,out] self Pointer to the subject to notify.
 */
enum status_e traffic_entry_point(struct Subject_s *self);

/** Write API (outputs) ******************************************************/
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
