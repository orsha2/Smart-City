## 1. Module Name

Event

## 2. Description

Receives validated data from a Data Holder, applies domain logic, and publishes downstream only when its condition is met.

Acts as both an Observer (receives from Data Holder) and a Subject (notifies downstream).

## 3. What Does the Module Store

1. an Observer
2. a Subject

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

1. Each Event implements domain-specific logic. Examples:
   - Lighting: publishes only on state change — 18:00 → lights on, 07:00 → lights off
   - Traffic: applies the traffic light algorithm
