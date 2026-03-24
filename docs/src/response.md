## 1. Module Name

Response

## 2. Description

Executes the final action in the pipeline. Receives a decision from an upstream Aggregator or Event and applies it to the external world.

Does not propagate further. Acts as an Observer only.

## 3. What Does the Module Store

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

Concrete examples in the Smart City system:
- activating the cooling system
- turning streetlights on or off
- adjusting traffic light timing
