## 1. Module Name

Data Holder

## 2. Description

Receives and manipulates raw data from a Data Source into a typed structure and notifies downstream observers.

Acts as both an Observer (receives from Data Source) and a Subject (notifies downstream).

## 3. What Does the Module Store

1. an Observer
2. a Subject

## 4. Abstract Implementation

```c
#ifndef __SMART_CITY_DATA_HOLDER_H__
#define __SMART_CITY_DATA_HOLDER_H__

#include "observer.h"

struct DataHolder
{
    struct Observer observer;
    struct Subject subject;
    void *data;
};

void DATA_HOLDER_init(struct DataHolder *self);

bool DATA_HOLDER_attach(struct DataHolder *self,
                       struct Observer *observer);

/* Callback executed when new data arrives */
void DATA_HOLDER_update(void *context);

/* Publish the stored data to downstream observers */
void DATA_HOLDER_publish(struct DataHolder *self);

#endif /* __SMART_CITY_DATA_HOLDER_H__ */
```

## 5. Notes

1. Downstream consumers are either an Event or an Aggregator, depending on the pipeline branch.

2. Data access follows a notify + fetch pattern: downstream consumers are notified via the observer callback, then read the data by referencing the global Data Holder instance and its fields directly.

3. `DATA_HOLDER_init` takes no `observer_update_fn` - the update callback is wired during concrete initialization, not at the abstract level.
