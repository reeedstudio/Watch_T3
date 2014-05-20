/*
  watch_ui.cpp
  Xadow Open Source Watch ui display manage

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
#ifndef __WATCH_UI_H__
#define __WATCH_UI_H__

#include "mbed.h"

class watch_ui{

public:
    
    void init();
    void drawPixel(int _x, int _y, unsigned int color);
    void display();
    void clear();

    void drawBuff(int x, int y, int buf_len, int buf_width, int color, const unsigned char *buff);
    void drawFont(int x, int y, int color, const unsigned char *font);
    void drawFont_small(int x, int y, int color, const unsigned char *font);
    void drawChar(char c, int x, int y, int color);
    void drawString(char *str);

private:
    
    unsigned char pixel[1024];

};

extern watch_ui ui;



#endif
