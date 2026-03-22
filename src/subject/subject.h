/**
 * @brief Public interface of the Subject module.
 *
 * This header defines the Subject data structure and the public API used
 * to initialize a subject, attach observers, and notify all registered
 * observers about a new event.
 */
#ifndef __SMART_CITY_SUBJECT_H__
#define __SMART_CITY_SUBJECT_H__

/** Headers ******************************************************************/
#include <stdbool.h>
#include <stddef.h>

#include "observer.h"

/** Constants ****************************************************************/
/**
 * @brief Maximum number of observers that can be attached to a subject.
 */
#define SUBJECT_MAX_OBSERVERS (5)

/** Structs ******************************************************************/
/**
 * @brief Represents a subject in the notification flow.
 *
 * @param observers Fixed size list of registered observers.
 * @param count Number of currently registered observers.
 */
struct Subject_s {
    struct Observer_s *observers[SUBJECT_MAX_OBSERVERS];
    size_t count;
};

/** Functions ****************************************************************/
/**
 * @brief Initialize a subject instance.
 *
 * @param self Pointer to the subject instance to initialize.
 */
enum status_e SUBJECT_init(struct Subject_s *self);

/**
 * @brief Attach an observer to a subject.
 *
 * @param self Pointer to the subject instance.
 * @param observer Pointer to the observer to attach.
 */
bool SUBJECT_attach(struct Subject_s *self, struct Observer_s *observer);

/**
 * @brief Notify all attached observers about a new event.
 *
 * @param self Pointer to the subject instance.
 * @param context User-provided context passed to each observer callback.
 */
enum status_e SUBJECT_notify_all(struct Subject_s *self, void *context);

#endif /* !__SMART_CITY_SUBJECT_H__ */
