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

#include "watch_time.h"
#include "watch_ui.h"
#include "font_watch.h"

extern I2C i2c;

static char NameMonth[12][4] = {

    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Set",
    "Oct",
    "Nov",
    "Dec",
};


/*
 * initialize
 */
void watch_time::init()
{
    rtc_ds1307_init(&i2c);
    rtc_ds1307_get_time(&time_now);
    rtc_ds1307_get_time(&time_buf);
    flg_refresh = 1;
}


/*
 * clear display
 */
void watch_time::clear()
{
    ui.clear();
}


/*
 * set time
 */
void watch_time::timeSet(r_time t)                  // set time
{
    memcpy(time_buf.data, time_now.data, 7);
    memcpy(time_now.data, t.data, 7);
}



/*
 * set time
 */
void watch_time::timeGet(r_time *t)                 // get time
{
    memcpy((*t).data, time_now.data, 7);
}



/*
 * time update, get time from rtc, or other device
 */
void watch_time::timeUpdate()                       // update time to time_now & time_buf
{
    // update time
    
    memcpy(time_buf.data, time_now.data, 7);
    
    rtc_ds1307_get_time(&time_now);
    
    if(time_now.minute != time_buf.minute)
    {
        flg_refresh = 1;
    }
    
}

/*
 * time refresh
 * mode: 0 - when minute change
 *       1 - update whatever
 */
void watch_time::timeRefresh(unsigned char mode)                      // time display refresh
{
    timeUpdate();
    
    if(!flg_refresh && !mode)return;
    
    flg_refresh = 0;

    clear();
    
    drawOshw();

    // refresh day
    int color_ = 1;
    int y = 40+16;

    for(int i=0; i<3; i++)
    {
        ui.drawChar(NameMonth[time_now.month-1][i], 8*i, y, color_);
    }
    ui.drawFont_small(30, y, color_, font_ascii[time_now.day/10+'0'-32]);
    ui.drawFont_small(38, y, color_, font_ascii[time_now.day%10+'0'-32]);
    
    
    // display 2 lines
    for(int i=0; i<63; i++)
    {
        drawPixel(i, 56+16);
        drawPixel(i, 57+16);
    }
    
    // refresh time
    y = 76;
    
    ui.drawFont(0, y, color_, font_num[time_now.hour/10]);
    ui.drawFont(14, y, color_, font_num[time_now.hour%10]);

    ui.drawBuff(28, 74, 7, 32, 1, font_dot);                    // draw ':'
    ui.drawFont(38, y, color_, font_num[time_now.minute/10]);
    ui.drawFont(52, y, color_, font_num[time_now.minute%10]);

    // display
    display();
    
}

/*
 * draw the logo of OSHW
 */
void watch_time::drawOshw()
{
    ui.drawBuff(12, 0+16, 40, 40, 1, font_ophw);
}


/*
 * draw a pixel
 */
void watch_time::drawPixel(int x, int y)
{
    ui.drawPixel(x, y, 1);
}


/*
 * display.
 */
void watch_time::display()                             // display all
{
    ui.display();
}

watch_time time_c;


