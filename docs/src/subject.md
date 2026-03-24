## 1. Module Name

Subject


## 2. Description

Implements the Subject side of the Observer design pattern.

Maintains a list of registered observers and notifies them when an event occurs. Performs no business logic.


## 3. What Does the Module Store

- a fixed-size list of observers
- the number of registered observers


## 4. Abstract Implementation

```c
#ifndef __SMART_CITY_SUBJECT_H__
#define __SMART_CITY_SUBJECT_H__

#include <stdbool.h>
#include <stddef.h>
#include "observer.h"

#define SUBJECT_MAX_OBSERVERS 5

struct Subject
{
    struct Observer *observers[SUBJECT_MAX_OBSERVERS];
    size_t count;
};

void SUBJECT_init(struct Subject *self);

bool SUBJECT_attach(struct Subject *self,
                    struct Observer *observer);

void SUBJECT_notify_all(struct Subject *self,
                    void *context);

#endif /* !__SMART_CITY_SUBJECT_H__ */
```

## 5. Notes

1. The Subject has no knowledge of what observers do - it only calls their `update` callback.

2. Any component that produces events for downstream stages must embed a Subject.
