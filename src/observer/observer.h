/**
 * @brief Public interface of the Observer module.
 *
 * This header defines the Observer data structure and the public API used
 * to initialize an observer, notify it, and update its readiness state.
 */
#ifndef __SMART_CITY_OBSERVER_H__
#define __SMART_CITY_OBSERVER_H__

/** Headers ******************************************************************/
#include <stdbool.h>

#include "common.h"

/** Functions ****************************************************************/
/**
 * @brief Callback type invoked when an observer receives a notification.
 *
 * @param[in,out] self Pointer to the observer instance that receives the notification.
 * @param[in,out] context User provided context forwarded by the caller of OBSERVER_notify().
 */
typedef void (*observer_update_fn_t)(void *self, void *context);

/**
 * @brief Represents a single observer in the notification flow.
 *
 * @param update Callback invoked when the observer is notified.
 * @param is_ready Indicates whether the observer finished handling the latest notification.
 */
struct Observer_s {
    observer_update_fn_t update;
    bool is_ready;
};

/**
 * @brief Initialize an observer instance.
 *
 * @param[out] self Pointer to the observer instance to initialize.
 * @param[in] update Callback function invoked when the observer is notified.
 */
enum status_e OBSERVER_init(struct Observer_s *self, observer_update_fn_t update);

/**
 * @brief Notify an observer about a new event.
 *
 * @param[in,out] self Pointer to the observer instance to notify.
 * @param[in] context User-provided context passed to the observer callback.
 */
enum status_e OBSERVER_notify(struct Observer_s *self, void *context);

/**
 * @brief Update the readiness state of an observer.
 *
 * @param[out] self Pointer to the observer instance to update.
 * @param[in] state New readiness state to assign.
 */
enum status_e OBSERVER_set_ready(struct Observer_s *self, bool state);

#endif /* !__SMART_CITY_OBSERVER_H__ */
