#ifndef __SMART_CITY_ENTRY_POINTS_FAKES_H__
#define __SMART_CITY_ENTRY_POINTS_FAKES_H__

/** Headers ******************************************************************/

#include "fff.h"

#include "common.h"
#include "entry_points.h"
#include "subject.h"

/** Globals ******************************************************************/

extern struct Subject_s *g_subject_seen;
extern struct TemperatureRawData_s g_temperature_raw_data;
extern struct TimeRawData_s g_time_raw_data;
extern struct TrafficRawData_s g_traffic_raw_data;

/** FFF **********************************************************************/

DECLARE_FAKE_VALUE_FUNC(uint32_t, HAL_read_temperature_sensor);
DECLARE_FAKE_VALUE_FUNC(int64_t, HAL_read_time_sensor);
DECLARE_FAKE_VALUE_FUNC(uint16_t, HAL_read_traffic_sensor);

DECLARE_FAKE_VOID_FUNC(HAL_update_air_conditioner_state,
                       enum HAL_AIR_CONDITIONER_STATE_e,
                       enum HAL_AIR_CONDITIONER_MODE_e,
                       enum HAL_AIR_CONDITIONER_FAN_LEVEL_e);
DECLARE_FAKE_VOID_FUNC(HAL_turn_on_streetlights);
DECLARE_FAKE_VOID_FUNC(HAL_turn_off_streetlights);
DECLARE_FAKE_VOID_FUNC(HAL_set_traffic_light, size_t, size_t);

DECLARE_FAKE_VALUE_FUNC(enum status_e, SUBJECT_notify_all, struct Subject_s *, void *);

/** Functions ****************************************************************/

void ENTRY_POINTS_FAKES_reset(void);

enum status_e naive_temperature_notify_all_fake(struct Subject_s *self,
                                                void *context);

enum status_e naive_time_notify_all_fake(struct Subject_s *self,
                                         void *context);

enum status_e naive_traffic_notify_all_fake(struct Subject_s *self,
                                            void *context);

#endif /* !__SMART_CITY_ENTRY_POINTS_FAKES_H__ */