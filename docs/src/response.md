## 1. Module Name

Response

## 2. Description

The Response module is responsible for executing the final action in the system pipeline.

Responses receive decisions from upstream modules, typically Aggregators or Events, and apply the required action to the external world.
A Response does not propagate data further in the pipeline.
Its responsibility is to consume the final decision and execute the corresponding operation.

For this reason, a Response acts as an Observer.

## 3. What Does the Module Store

The Response structure stores:

1. an Observer
2. internal state related to the applied action, if needed

## 4. Abstract Implementation

```c
#ifndef __SMART_CITY_RESPONSE_H__
#define __SMART_CITY_RESPONSE_H__

#include "observer.h"

struct Response
{
    struct Observer observer;
};

void RESPONSE_init(struct Response *self,
                 observer_update_fn update);

void RESPONSE_execute(struct Response *self,
                     void *context);

#endif /* !__SMART_CITY_RESPONSE_H__ */
```

## 5. Notes

A Response is the final stage in the pipeline.

Responses receive decisions from Aggregators or directly from Triggers, depending on the architecture.

Responses are responsible for interacting with the external environment.

Typical examples of Responses in the Smart City system include:
- activating the cooling system
- turning streetlights on or off
- adjusting traffic light timing
