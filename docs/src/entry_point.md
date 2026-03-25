## 1. Module Name

Entry Point


## 2. Description

Defines the boundary between external signals and the internal pipeline.

An Entry Point receives a trigger from the processor or HAL and forwards it to downstream modules. It carries no data and performs no HAL read.


## 3. What Does the Module Store

Nothing. Pure trigger routing.


## 4. Abstract Implementation

### Read API (inputs)

Called by the processor or HAL to signal that new data is available.

```c
#ifndef __SMART_CITY_ENTRY_POINT_H__
#define __SMART_CITY_ENTRY_POINT_H__

#include "temperature_data_source.h"
#include "time_data_source.h"
#include "traffic_data_source.h"

void temperature_entry_point(void);

void time_entry_point(void);

void traffic_entry_point(void);

#endif /* !__SMART_CITY_ENTRY_POINT_H__ */
```

Example implementation:

```c
void temperature_entry_point(void)
{
    TEMPERATURE_DATA_SOURCE_publish(TEMPERATURE_DATA_SOURCE);
}

void time_entry_point(void)
{
    TIME_DATA_SOURCE_publish(TIME_DATA_SOURCE);
}

void traffic_entry_point(void)
{
    TRAFFIC_DATA_SOURCE_publish(TRAFFIC_DATA_SOURCE);
}
```

### Write API (outputs)

Called by Response modules to apply a decision to the external world.

```c
void city_api_cooling_entry_point(int cooling_command);

void city_api_lighting_entry_point(int lighting_command);

void city_api_traffic_entry_point(int traffic_command);
```
