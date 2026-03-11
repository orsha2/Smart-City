## 1. Module Name

Hooks


## 2. Description

The hooks module defines the functions through which external inputs enter the system pipeline.

Entry points receive raw input values from the processor, HAL, or external environment and forward them to the appropriate Data Source.

These functions act as the boundary between the external environment and the internal architecture.

Entry points do not contain system logic.
Their role is only to forward incoming values to the corresponding Data Source.


## 3. What Does the Module Store

The Entry Points module does not store any data.

The module acts purely as a routing layer between the external environment and the internal system pipeline.


## 4. Abstract Implementation

```c
#ifndef __SMART_CITY_HOOKS_H__
#define __SMART_CITY_HOOKS_H__

#include "temperature_data_source.h"
#include "time_data_source.h"
#include "traffic_data_source.h"

void SMART_CITY_on_temperature_update(float temperature);

void SMART_CITY_on_time_update(int hour);

void SMART_CITY_on_traffic_update(int congestion_level);

#endif /* !__SMART_CITY_HOOKS_H__ */
```


Example implementation:

```c
void SMART_CITY_on_temperature_entry_point(float temperature)
{
    ...

    TEMPERATURE_DATA_SOURCE_publish(TEMPERATURE_DATA_SOURCE, &temperature);
}

void SMART_CITY_on_time_entry_point(int hour)
{
    ...

    TIME_DATA_SOURCE_publish(TIME_DATA_SOURCE, &hour);
}

void SMART_CITY_on_traffic_entry_point(int congestion_level)
{
    ...

    TRAFFIC_DATA_SOURCE_publish(TRAFFIC_DATA_SOURCE, &congestion_level);
}
```

