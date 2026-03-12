## 1. Module Name

Effect

## 2. Description

The Effect module is responsible for executing the final action in the system pipeline.

Effects receive decisions from upstream modules, typically Aggregators or Effects, and apply the required action to the external world.
An Effect does not propagate data further in the pipeline.
Its responsibility is to consume the final decision and execute the corresponding operation.

For this reason, an Effect acts as an Observer.

## 3. What Does the Module Store

The Effect structure stores:

1. an Observer
2. internal state related to the applied action, if needed

## 4. Abstract Implementation

```c
#ifndef __SMART_CITY_EFFECT_H__
#define __SMART_CITY_EFFECT_H__

#include "observer.h"

struct Effect
{
    struct Observer observer;
};

void EFFECT_init(struct Effect *self,
                 observer_update_fn update);

void EFFECT_execute(struct Effect *self,
                     void *context);

#endif /* !__SMART_CITY_EFFECT_H__ */
```

## 5. Notes

An Effect is the final stage in the pipeline.

Effects receive decisions from Aggregators or directly from Triggers, depending on the architecture.

Effects are responsible for interacting with the external environment.

Typical examples of Effects in the Smart City system include:

activating the cooling system

turning streetlights on or off

adjusting traffic light timing

The Effect module does not decide whether an action should occur.
It only executes the action once that decision has already been made.

Because the Effect only receives and consumes events, it acts only as an Observer.
