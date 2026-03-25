## 1. Module Name

Data Source

## 2. Description

Reads raw data from HAL and publishes it downstream. Typically performs no validation or business logic.

Triggered by an Entry Point. Acts as a Subject.

## 3. What Does the Module Store

A Subject. Does not store the data value itself.

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

void DATA_SOURCE_publish(struct DataSource *self);

#endif /* !__SMART_CITY_DATA_SOURCE_H__ */
```

## 5. Notes

1. Reads and publishes raw - typically no interpretation or validation.

2. Does not self-trigger. Reads only when called by an Entry Point.

3. Downstream consumers are typically Data Holders.
