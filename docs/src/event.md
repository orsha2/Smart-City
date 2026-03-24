## 1. Module Name

Event

## 2. Description

Receives validated data from a Data Holder, applies domain logic, and always publishes a result downstream.

Acts as both an Observer (receives from Data Holder) and a Subject (notifies downstream Responses).

## 3. What Does the Module Store

1. an Observer
2. a Subject
3. internal state relevant to the condition being evaluated

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
   - Lighting: lights on at 18:00-06:59, lights off at 07:00-17:59
   - Traffic: applies the traffic light algorithm
