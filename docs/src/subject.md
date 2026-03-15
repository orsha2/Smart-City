## 1. Module Name

Subject


## 2. Description

The Subject module implements the Subject side of the Observer design pattern.

A Subject maintains a collection of observers and is responsible for notifying them when a new event occurs.

The Subject itself does not perform business logic.
It only manages observers and propagates notifications.


## 3. What Does the Module Store

The Subject structure stores:

- a fixed size list of observers
- the number of registered observers

This allows the subject to iterate over all observers and notify them when needed.


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

1. The Subject does not know what the observers do.
   It only effects their update callback.

2. The Subject acts as the event distributor in the system pipeline.

3. Any component that produces events for other components should expose a Subject.
