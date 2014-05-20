/*
  main.cpp
  
  2014 Copyright (c) Seeed Technology Inc.  All right reserved.

  Loovee
  2014-5-21

  Xadow smart watch T3
  This version is improved from T0, the improvement include:
  1. Add a UI manage library to manage the display
  2. Add a time library to control time display
  3. Use Suli-Compatible RTC and OLED library
  
  This demo need:
  1. Xadow - BLE Slave
  2. Xadow - RTC(DS1307)
  3. Xadow - OLED 128_64
  4. Xadow - Mbed v1.02
  5. 170mAH Lipo Battery
  
  Functon:
  1. display time
  2. communication with BLE device
     i. when send a 't' or 'T' to Xadow, Xadow will return the time that get from RTC
     
     ii. send "s....." can set the time, such as "s201403280944003", that meas set time to 2014/3/28 09:44:00 Wed
        the last number indicate week
        
     iii. send a other string to Xadow, Xadow will display it for 3 seconds 
     


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

#include "mbed.h"
#include "pinmap.h"
#include "font_watch.h"
#include "Suli.h"
#include "OLED_128x64_Suli.h"
#include "watch_time.h"
#include "watch_ui.h"
#include "RTC_DS1307_Suli.h"

#define millis  us_ticker_read


DigitalOut blue(P0_20);                     // blue led
DigitalOut white(P0_23);                    // white led

#define I2C_FREQ            100000          // i2c speed

I2C i2c(P0_5, P0_4);                        // sda, scl     

Serial uart(P0_19, P0_18);                  // uart, connect to Xadow BLE



int main()
{
    uart.baud(38400);                       // set baudrate
    
    long timer_time_refresh = millis();     // 
    
    ui.init();
    time_c.init();
    
    ui.drawString((char*)"xadow   smart   watch");
    ui.display();
    wait(3);
    
    time_c.timeRefresh(0);

    char ble_str[40];
    int len_str = 0;
    

    for(;;)
    {

        if((millis()-timer_time_refresh) > 10000)           // refresh time every 10 seconds
        {
            timer_time_refresh = millis();                  // clear timer
            time_c.timeRefresh(0);
        }
        
        while (uart.readable())                             // if get data from BLE
        {
            ble_str[len_str++] = uart.getc();               // save to buff
        }
        
        if(len_str == 1 && (ble_str[0] == 't' || ble_str[0] == 'T'))        // get t command
        {

            len_str = 0;
            r_time t_get;
            
            time_c.timeGet(&t_get);
            uart.printf("%d/%d/%d\r\n", t_get.year, t_get.month, t_get.day);
            uart.printf("%d:%d:%d\r\n", t_get.hour, t_get.minute, t_get.second);
            
        }
        else if(ble_str[0] == 's' && len_str == 16)         // set time
        {
            // s201403280944003
            r_time t_set;
            t_set.second    = (ble_str[13]-'0')*10+(ble_str[14]-'0');
            t_set.minute    = (ble_str[11]-'0')*10+(ble_str[12]-'0');
            t_set.hour      = (ble_str[9]-'0')*10+(ble_str[10]-'0');
            t_set.day       = (ble_str[7]-'0')*10+(ble_str[8]-'0');
            t_set.month     = (ble_str[5]-'0')*10+(ble_str[6]-'0');
            t_set.week      =  ble_str[15]-'0';
            t_set.year      = (ble_str[1]-'0')*1000+(ble_str[2]-'0')*100+(ble_str[3]-'0')*10+(ble_str[4]-'0');
            
            time_c.timeSet(t_set);

        }
        else if(len_str>0)
        {
            len_str -= len_str;
            
            uart.printf("get ok\r\n");
            ble_str[len_str] = '\0';
            ui.drawString(ble_str);
            ui.display();
            wait(3);
            time_c.timeRefresh(1);
        }
    }
}


