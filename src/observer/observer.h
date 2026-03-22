/**
 * @brief Public interface of the Observer module.
 *
 * This header defines the Observer data structure and the public API used
 * to initialize an observer, notify it, and update its readiness state.
 */
#ifndef __SMART_CITY_OBSERVER_H__
#define __SMART_CITY_OBSERVER_H__

#include <stdbool.h>

#include "common.h"

/**
 * @brief Callback type invoked when an observer receives a notification.
 *
 * @param self - Pointer to the observer instance that receives the notification.
 *
 * @param context - User-provided context forwarded by the caller of OBSERVER_notify().
 */
typedef void (*observer_update_fn_t)(void *self, void *context);

/**
 * @brief Represents a single observer in the notification flow.
 *
 * @param update - Callback invoked when the observer is notified.
 * @param is_ready - Indicates whether the observer finished handling the latest notification.
 */
struct Observer_s {
    observer_update_fn_t update;
    bool is_ready;
};

enum status_e OBSERVER_init(struct Observer_s *self, observer_update_fn_t update);

enum status_e OBSERVER_notify(struct Observer_s *self, void *context);

enum status_e OBSERVER_set_ready(struct Observer_s *self, bool state);

#endif /* !__SMART_CITY_OBSERVER_H__ */
