/**
 * @file hal_functions.h
 * @brief Describe the HAL interface exported for the user.
 * @date 05/03/2026
 * @autor AP
 */

#ifndef __HAL_FUNCTIONS_H__
#define __HAL_FUNCTIONS_H__

/** Headers ****************************************************************/
#include <stddef.h>
#include <stdint.h>

/** Enums ******************************************************************/
/**
 * @brief Define the modes for an air conditioner.
 */
enum HAL_AIR_CONDITIONER_STATE_e {
    HAL_AIR_CONDITIONER_STATE_INVALID = -1,
    HAL_AIR_CONDITIONER_STATE_OFF,
    HAL_AIR_CONDITIONER_STATE_ON,
};

/**
 * @brief Define the modes for an air conditioner.
 */
enum HAL_AIR_CONDITIONER_MODE_e {
    HAL_AIR_CONDITIONER_MODE_INVALID = -1,
    HAL_AIR_CONDITIONER_MODE_COOL,
    HAL_AIR_CONDITIONER_MODE_HEAT,
};

/**
 * @brief Define the fan levels of an air conditioner.
 */
enum HAL_AIR_CONDITIONER_FAN_LEVEL_e {
    HAL_AIR_CONDITIONER_FAN_LEVEL_INVALID = -1,
    HAL_AIR_CONDITIONER_FAN_LEVEL_1,
    HAL_AIR_CONDITIONER_FAN_LEVEL_2,
    HAL_AIR_CONDITIONER_FAN_LEVEL_3,
    HAL_AIR_CONDITIONER_FAN_LEVEL_4,
};

/** Functions **************************************************************/
/**
 * @brief Reads the temprature of the city.
 *
 * @return The temperature in Celsius.
 *
 * @note The return value should be validated.
 */
uint32_t HAL_read_temperature_sensor(void);

/**
 * @brief Reads the current time of the city.
 *
 * @return The current time in the following format:
 *         HH:MM:SS
 *         For exmaple:
 *         152311 - The time is 15:23 and 11 seconds.
 *
 * @note The return value should be validated.
 */
int64_t HAL_read_time_sensor(void);

/**
 * @brief Gets the current traffic congestion in the city.
 *
 * @return The traffic congestion in percentages.
 *
 * @note The return value should be validated.
 */
uint16_t HAL_read_traffic_sensor(void);

/**
 * @brief Update the air conditioner's state.
 *
 * @param[in] state - req - The state of the air conditioner.
 * @param[in] mode - req - The mode of the air conditioner to activate.
 * @param[in] fan_level - req - The fan level of the air conditioner to
 * activate.
 *
 * @note If the @ref state given is @ref HAL_AIR_CONDITIONER_STATE_OFF, then
 * the @mode and @fan_level will be ignored.
 */
void HAL_update_air_conditioner_state(enum HAL_AIR_CONDITIONER_STATE_e state,
                                      enum HAL_AIR_CONDITIONER_MODE_e mode,
                                      enum HAL_AIR_CONDITIONER_FAN_LEVEL_e fan_level);

/**
 * @brief Turn on the streetlights.
 */
void HAL_turn_on_streetlights(void);

/**
 * @brief Turn off the streetlights.
 */
void HAL_turn_off_streetlights(void);

/**
 * @brief Set the traffic lights duration.
 *
 * @param[in] red_light_duration - req - The new duration of the red light in
 * seconds.
 * @param[in] green_light_duration - req - The new duration of the green light
 * in seconds.
 */
void HAL_set_traffic_light(size_t red_light_duration, size_t green_light_duration);

#endif /** __HAL_FUNCTIONS_H__ */
