#ifndef __SMART_CITY_COMMON_H__
#define __SMART_CITY_COMMON_H__

#include <stdbool.h>
#include <stddef.h>

#define IS_VALID_PTR(ptr) (NULL != (ptr))

enum status_e {
    SC_STATUS_SECCUSS = 0,
    SC_STATUS_UNINITIALIZED,
    SC_STATUS_INVALID_ARGUMENT,
    SC_STATUS_NULL_POINTER,
    SC_STATUS_NOT_READY,
    SC_STATUS_FAILURE
};

#endif /* !__SMART_CITY_COMMON_H__ */
