## 1. Module Name
Observer


## 2. Description
The **Observer module** implements the **Observer design pattern**. 

Each observer stores a **callback\update function** that is executed when a notification occurs.


## 3. What Does the Module Store

The Observer structure stores:

- a function pointer used to handle notifications (`update`)
- a boolean `is_ready` flag indicating that the observer finished handling the notification


## 4. Abstract Implementation

```c
#ifndef __SMART_CITY_OBSERVER_H__
#define __SMART_CITY_OBSERVER_H__

#include <stdbool.h>

typedef void (*observer_update_fn)(void *context);

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

1. Whether the observer affects the external world depends on the callback that is provided to it.
The Observer itself only forwards notifications.

2. Any component that propagates information to the next entity in the pipeline must expose an Observer.