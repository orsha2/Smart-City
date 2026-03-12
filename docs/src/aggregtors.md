## 1. Module Name

Aggregator

## 2. Description

The Aggregator module is responsible for collecting results from multiple effects and producing a final decision.

Aggregators receive events from one or more Event modules and combine their results to determine the appropriate action.

This stage is used when a system decision depends on multiple conditions or inputs.

If the aggregation logic determines that a decision should be taken, the Aggregator notifies its observers and passes the result to the next stage in the pipeline.

Because of this behavior, the Aggregator acts as both:

1. an Observer (receives results from Events)
2. a Subject (notifies downstream modules such as Events)

## 3. What Does the Module Store

The Aggregator structure stores:

1. an Observer
2. a Subject base used to notify downstream observers
3. internal state used to combine effect results

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
