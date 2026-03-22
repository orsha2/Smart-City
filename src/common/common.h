/**
 * @brief Common definitions for the SC project.
 *
 * This header provides shared basic utilities used across the project.
 */
#ifndef __SMART_CITY_COMMON_H__
#define __SMART_CITY_COMMON_H__

/** Headers ******************************************************************/
#include <stdbool.h>
#include <stddef.h>

/** Constants ****************************************************************/
/**
 * @brief Check whether the given pointer is valid.
 *
 * @param ptr Pointer to check.
 *
 * @return true if the pointer is not NULL, otherwise false.
 */
#define IS_VALID_PTR(ptr) (NULL != (ptr))

/** Enums ********************************************************************/
/**
 * @brief Common status codes returned by SC modules.
 */
enum status_e {
    SC_STATUS_SUCCESS = 0,
    SC_STATUS_UNINITIALIZED,
    SC_STATUS_INVALID_ARGUMENT,
    SC_STATUS_NULL_POINTER,
    SC_STATUS_NOT_READY,
    SC_STATUS_FAILURE
};

#endif /* !__SMART_CITY_COMMON_H__ */
