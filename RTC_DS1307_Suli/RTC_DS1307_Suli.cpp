/*
  RTC_DS1307_Suli.cpp

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

#include "RTC_DS1307_Suli.h"

static void *__I2C_Device;


uint8 decToBcd(uint8 val)
{
    return ( (val/10*16) + (val%10) );
}

//Convert binary coded decimal to normal decimal numbers
uint8 bcdToDec(uint8 val)
{
    return ( (val/16*10) + (val%16) );
}


void rtc_ds1307_init(void *i2c_dev)
{
    __I2C_Device = i2c_dev;
}


/*Function: The clock timing will start */
void rtc_ds1307_start(void)                                 // set the ClockHalt bit low to start the rtc
{
    uint8 dta[2] = {0x00};
    suli_i2c_write(__I2C_Device, DS1307_I2C_ADDRESS, dta, 1);
    
    suli_i2c_read(__I2C_Device, DS1307_I2C_ADDRESS, dta, 1);
    
    dta[1] = dta[0] & 0x7f;
    dta[0] = 0x00;
    suli_i2c_write(__I2C_Device, DS1307_I2C_ADDRESS, dta, 2);
}


/*Function: The clock timing will stop */
void rtc_ds1307_stop(void)         // set the ClockHalt bit high to stop the rtc
{
    uint8 dta[2] = {0x00};
    suli_i2c_write(__I2C_Device, DS1307_I2C_ADDRESS, dta, 1);
    
    suli_i2c_read(__I2C_Device, DS1307_I2C_ADDRESS, dta, 1);
    
    dta[1] = dta[0] | 0x80;
    dta[0] = 0x00;
    
    suli_i2c_write(__I2C_Device, DS1307_I2C_ADDRESS, dta, 2);
}


/*Function: Read time and date from RTC    */
void rtc_ds1307_get_time(struct __time * time_get)
{
    uint8 dta[1] = {0x00};
    suli_i2c_write(__I2C_Device, DS1307_I2C_ADDRESS, dta, 1);
    suli_i2c_read(__I2C_Device, DS1307_I2C_ADDRESS, time_get->data, 7);
    
    time_get->data[0] &= 0x7f;
    time_get->data[2] &= 0x3f;
    for(int i=0; i<7; i++)
    {
        time_get->data[i] = bcdToDec(time_get->data[i]);
    }
}


void rtc_ds1307_set_time(struct __time t)
{
    uint8 dta[8] = {0x00, t.second, t.minute, t.hour, t.week, t.day, t.month, t.year};
    
    for(int i=1; i<8; i++)
    {
        dta[i] = decToBcd(dta[i]);
    }
    
    suli_i2c_write(__I2C_Device, DS1307_I2C_ADDRESS, dta, 8);
}
