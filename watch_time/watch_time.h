/*
  watch_time.h
  Xadow Open Source Watch time display manage

  2014 Copyright (c) Seeed Technology Inc.  All right reserved.

  Loovee
  2014-5-20

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
#ifndef __WATCH_TIME_TIME_H__
#define __WATCH_TIME_TIME_H__


#include "RTC_DS1307_Suli.h"
#include "OLED_128x64_Suli.h"

class watch_time{

public:
    
    void init(); 
    void timeSet(r_time t);                 // set time
    void timeGet(r_time *t);                // get time
    void timeRefresh(unsigned char mode);   // display time
    
private:
    
    void drawPixel(int x, int y);           // draw a pixel
    void display();                         // display all
    void drawOshw();                        // draw open hardware logo
    void clear();
    void timeUpdate();                      // update time to time_now & time_buf


private:
    

    char flg_refresh;                       // if need to refresh time
    
    r_time time_now;                        // time now
    r_time time_buf;                        // time buff
};

extern watch_time time_c;

#endif
