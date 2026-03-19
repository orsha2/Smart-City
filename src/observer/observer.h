#ifndef __SMART_CITY_OBSERVER_H__
#define __SMART_CITY_OBSERVER_H__

#include <stdbool.h>

#include "common.h"

typedef void (*observer_update_fn_t)(void *self, void *context);

struct Observer_s {
    observer_update_fn_t update;
    bool is_ready;
};

enum status_e OBSERVER_init(struct Observer_s *self, observer_update_fn_t update);
enum status_e OBSERVER_notify(struct Observer_s *self, void *context);
enum status_e OBSERVER_set_ready(struct Observer_s *self, bool state);

#endif /* !__SMART_CITY_OBSERVER_H__ */
