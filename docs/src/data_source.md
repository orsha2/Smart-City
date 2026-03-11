## 1. Module Name

Data Source


## 2. Description

The Data Source module represents the entry point of raw data into the system pipeline.

A Data Source receives input values from the external environment (for example, the processor or HAL) and forwards them to the next stage in the pipeline.

The module itself does not perform validation or business logic.
Its responsibility is only to propagate incoming data to its observers.

For this reason, a Data Source is implemented as a Subject.


## 3. What Does the Module Store

The Data Source structure stores a subject base used to notify downstream observers.

The Data Source does not store the data value itself.


## 4. Abstract Implementation

```c
#ifndef __SMART_CITY_DATA_SOURCE_H__
#define __SMART_CITY_DATA_SOURCE_H__

#include "subject.h"

struct DataSource
{
    struct Subject subject;
};

void DATA_SOURCE_init(struct DataSource *self);

bool DATA_SOURCE_attach(struct DataSource *self,
                        struct Observer *observer);

void DATA_SOURCE_publish(struct DataSource *self,
                         void *context);

#endif /* !__SMART_CITY_DATA_SOURCE_H__ */
```

## 5. Notes

1. The Data Source does not interpret or validate the data it receives.

2. In the system pipeline, the Data Source is typically connected to a Data Holder.

3. The context parameter contains the raw value received from the entry point.