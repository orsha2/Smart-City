## 1. Module Name

Data Holder

## 2. Description

The Data Holder module is responsible for storing validated data in a structured format.

It receives raw input data from a Data Source, validates the value, and stores it inside a typed data structure.

Once the data is validated and stored, the module notifies downstream observers with the processed data.

For this reason, a Data Holder acts as both:

1. an Observer (receives data from a Data Source)
2. a Subject (notifies Events)

## 3. What Does the Module Store

The Data Holder structure stores:

1. an Observer base used to receive updates from a Data Source

2. a Subject base used to notify downstream observers

3. a typed data structure containing the validated value

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

1. In the system pipeline, Data Holders usually notify Event modules.

2. Because the Data Holder is both an Observer and a Subject, it acts as a processing stage in the pipeline.
