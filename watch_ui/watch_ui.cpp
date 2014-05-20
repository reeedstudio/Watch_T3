/*
  watch_ui.cpp
  Xadow Open Source Watch ui display manage

  2014 Copyright (c) Seeed Technology Inc.  All right reserved.

  Loovee
  2014-5-21

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
#include "watch_ui.h"
#include "OLED_128x64_Suli.h"
#include "font_watch.h"


extern I2C i2c;

/*
 * initizlize
 */
void watch_ui::init()
{
    memset(pixel, 0x00, 1024);          // clear pixel
    oled_128x64_init(&i2c);             // oled initialize
}


/*
 * draw pixel
 */
void watch_ui::drawPixel(int _x, int _y, unsigned int color)
{
    int x = 127-_y;
    int y = _x;
    
    int n = y/8;
    n = 128*n+x;
    
    int bit = y%8;
    
    if(color)
    pixel[n] |= (0x01<<bit);
    else
    pixel[n] &= ~(0x01<<bit);
}


/*
 * display
 * only this functin can refresh oled
 * the following function such as clear, drawBuff....can only change the pixel buff,
 * but will not refresh oled
 */
void watch_ui::display()
{
    for(int i=0; i<8; i++)
    {
        oled_128x64_XY(i,0);
        for(int j=0; j<128; j++)
        {
            oled_128x64_dta(pixel[128*i+j]);
        }
    }
}


/*
 * clear pixel
 */
void watch_ui::clear()
{
    memset(pixel, 0x00, 1024);
}


/*
 * drawBuff
 */
void watch_ui::drawBuff(int x, int y, int buf_len, int buf_width, int color, const unsigned char *buff)
{
    for(int i=0; i<(buf_width/8); i++)
    {
        for(int j=0; j<buf_len; j++)
        {
            for(int k=0; k<8; k++)
            {
                int clr_ = (buff[i*buf_len+j] & (0x01<<k)) ? color : 0;
                drawPixel(j+x, 8*i+k+y, clr_);
            }
        }
    }
}


/*
 * draw font
 */
void watch_ui::drawFont(int x, int y, int color, const unsigned char *font)
{
    drawBuff(x, y, 11, 32, color, font);
}


/*
 * draw small font
 */
void watch_ui::drawFont_small(int x, int y, int color, const unsigned char *font)
{
    drawBuff(x, y, 8, 16, color, font);
}


/*
 * draw char
 */
void watch_ui::drawChar(char c, int x, int y, int color)
{
    c = c-32;
    drawBuff(x, y, 8, 16, color, font_ascii[c]);
}


/*
 * 
 */
void watch_ui::drawString(char *str)
{
    
    int x=0, y=0;
    
    int pix = 0;
    
    while(*str)
    {
        drawChar(*str, x, y, 1);
        str++;
        x += 8;
        pix++;
        
        if(pix == 8)
        {
            pix = 0;
            x = 0;
            y += 16;
        }
    }
}

watch_ui ui;
