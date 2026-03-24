## 1. Module Name

Aggregator

## 2. Description

Synchronizes results from multiple upstream observers and produces a final decision.

Waits until all required inputs are ready before publishing downstream. If any input is not ready, the Aggregator exits and waits for the next event.

Acts as both an Observer (receives from upstream Data Holders) and a Subject (notifies downstream Responses).

## 3. What Does the Module Store

1. an Observer
2. a Subject
3. internal state used to combine upstream inputs

## 4. Abstract Implementation

```c
#ifndef __SMART_CITY_AGGREGATOR_H__
#define __SMART_CITY_AGGREGATOR_H__

#include "observer.h"
#include "subject.h"

struct Aggregator
{
    struct Observer observer;
    struct Subject subject;
};

void AGGREGATOR_init(struct Aggregator *self,
                     observer_update_fn update);

bool AGGREGATOR_attach(struct Aggregator *self,
                       struct Observer *observer);

bool AGGREGATOR_is_all_ready(struct Aggregator *self);

void AGGREGATOR_publish(struct Aggregator *self,
                        void *context);

#endif /* !__SMART_CITY_AGGREGATOR_H__ */
```

## 5. Notes

1. Each upstream observer sets its `is_ready` flag on completion. The Aggregator checks all flags before publishing - if any are unset, it exits and waits for the next event.

2. Upstream subjects are global objects, so their `is_ready` state persists across events. This allows the Aggregator to evaluate readiness correctly when upstream observers complete at different times.

3. The Temperature Aggregator is the concrete example. It receives validated readings from 3 area-specific Data Holders (A, B, C) and holds a list of 3 area states - one per area. The cooling decision:
   - ≥ 2 areas above high threshold → cooling on
   - ≥ 2 areas below low threshold → cooling off
   - otherwise → hold current state

4. There is no Event stage after the Temperature Aggregator. It publishes the cooling command directly to the Cooling Response.
