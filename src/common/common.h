#ifndef __SMART_CITY_COMMON_H__
#define __SMART_CITY_COMMON_H__

#include <stdbool.h>
#include <stddef.h>

#define IS_VALID_PTR(ptr) (NULL != (ptr))

enum status_e {
    STATUS_SECCUSS = 0,
    STATUS_UNINITIALIZED,
    STATUS_INVALID_ARGUMENT,
    STATUS_NULL_POINTER,
    STATUS_NOT_READY,
    STATUS_FAILURE
};

#endif /* !__SMART_CITY_COMMON_H__ */
