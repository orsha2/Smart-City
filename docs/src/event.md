## 1. Module Name

Event

## 2. Description

The Event module is responsible for evaluating conditions based on incoming data and determining whether the system should proceed to the next stage of processing.

Events receive validated data from a Data Holder and apply conditions to determine whether an event should propagate further in the pipeline.

If the event condition is satisfied, the module notifies its observers and allows the pipeline to continue.
If the condition is not satisfied, the event is ignored...

Because of this behavior, a Event acts as both:

1. an Observer (receives data from a Data Holder)
2. a Subject (notifies downstream components such as Aggregators)

## 3. What Does the Module Store

The Event structure stores:

1. an Observer base used to receive updates from a Data Holder
2. a Subject base used to notify downstream observers
3. internal state relevant to the specific condition being evaluated

## 4. Abstract Implementation

```c
#ifndef __SMART_CITY_EVENT_H__
#define __SMART_CITY_EVENT_H__

#include "observer.h"
#include "subject.h"

struct Event
{
    struct Observer observer;
    struct Subject subject;
};

void EVENT_init(struct Event *self,
                  observer_update_fn update);

bool EVENT_attach(struct Event *self,
                    struct Observer *observer);

#endif /* !__SMART_CITY_EVENT_H__ */
```

## 5. Notes

1. A Event evaluates conditions on validated data received from a Data Holder.

2. Each Event implements domain specific logic. Examples include:
   - temperature threshold detection
   - night/day detection
   - traffic congestion detection
