/*
  RTC_DS1307_Suli.h

  This is a Suly compatible Library

  2014 Copyright (c) Seeed Technology Inc.  All right reserved.

  Loovee
  2014-4-17

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, digital_compass_write_reg to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __RTC_DS1307_SULI_H__
#define __RTC_DS1307_SULI_H__

#include "Suli.h"

#define DS1307_I2C_ADDRESS (0x68<<1)

#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6
#define SUN 7

typedef struct __time{

    union
    {
        uint8 data[7];
        
        struct
        {
            uint8 second;
            uint8 minute;
            uint8 hour;
            uint8 week;
            uint8 day;
            uint8 month;
            uint8 year;                     // 2013 -> 13        
        };
    };

} r_time;



void rtc_ds1307_init(void *i2c_dev);
void rtc_ds1307_start(void);
void rtc_ds1307_stop(void);
void rtc_ds1307_get_time(struct __time * time_get);
void rtc_ds1307_set_time(struct __time t);

#endif
