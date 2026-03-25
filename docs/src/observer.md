## 1. Module Name
Observer


## 2. Description
Implements the Observer side of the Observer design pattern.

Stores a callback function executed when a notification is received.


## 3. What Does the Module Store

- `update` - function pointer invoked on notification
- `is_ready` - flag set when the observer finishes handling a notification


## 4. Abstract Implementation

```c
#ifndef __SMART_CITY_OBSERVER_H__
#define __SMART_CITY_OBSERVER_H__

#include <stdbool.h>

typedef void (*observer_update_fn)(void *self, void *context);

struct Observer
{
    observer_update_fn update;
    bool is_ready;
};
void OBSERVER_init(struct Observer *self,
                                 observer_update_fn update);
void OBSERVER_notify(struct Observer *self, void *context);
void OBSERVER_set_ready(struct Observer *self, bool state);

#endif /* !__SMART_CITY_OBSERVER_H__ */
```


## 5. Notes

1. The Observer only forwards notifications. What happens inside `update` is the responsibility of the concrete implementation.

2. Any component that receives data from an upstream stage must embed an Observer.
