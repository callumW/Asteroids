/*
    File: Draw.c
    Author: Callum Wilson callum.w@outlook.com
    Description: Function definitions for Draw.h
    Date: 2016/08/04

COPYRIGHT (c) 2016 Callum Wilson

MIT License

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.



     _    _               _ _               _____
    | |  | |             | (_)             |  __ \
    | |__| | _____      _| |_ _ __   __ _  | |__) |_ _ ___ ___
    |  __  |/ _ \ \ /\ / / | | '_ \ / _` | |  ___/ _` / __/ __|
    | |  | | (_) \ V  V /| | | | | | (_| | | |  | (_| \__ \__ \
    |_|  |_|\___/ \_/\_/ |_|_|_| |_|\__, | |_|   \__,_|___/___/
                                    __/ |
                                   |___/
               _____
              / ____|
             | |  __  __ _ _ __ ___   ___  ___
             | | |_ |/ _` | '_ ` _ \ / _ \/ __|
             | |__| | (_| | | | | | |  __/\__ \
              \_____|\__,_|_| |_| |_|\___||___/
*/
#include "Draw.h"
#include "Missile_List.h"
#include "Explosion_List.h"

void draw_line(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);
        //glVertex2f(normalise_x(x1), normalise_y(y1));
        //glVertex2f(normalise_x(x2), normalise_y(y2));
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
    glEnd();
}
void draw_linef(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
        //glVertex2f(normalise_xf(x1), normalise_yf(y1));
        //glVertex2f(normalise_xf(x2), normalise_yf(y2));
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void draw_circlef(float x, float y, float radius)
{
    int i;
    glBegin(GL_POLYGON);
        for (i = 0; i < 360; i++)
        {
            glVertex2f(x + sin(i * (3.14 / 180)) * radius, y + cos(i * (3.14 / 180)) * radius);
        }
    glEnd();
}

float normalise_y(int y)
{
    if (y == 0)
        return 1.0f;
    return 1.0f - (y*2.0f / gc_win_height);
}

float normalise_yf(float y)
{
    if (y == 0.0f)
        return 1.0f;
    return 1.0f - (y*2.0f / gc_win_height);
}

float normalise_x(int x)
{
    if (x == 0)
        return -1.0f;
    return (x*2.0f / gc_win_width) - 1.0f;
}

float normalise_xf(float x)
{
    if (x == 0.0f)
        return -1.0f;
    return (x*2.0f / gc_win_width) - 1.0f;
}

void draw_missiles()
{
    struct Missile_Node* current_missile = get_missile_head();
    float x1, y1, x2, y2;
    while (current_missile != NULL)
    {
        x1 = current_missile->missile->start_x;
        y1 = current_missile->missile->start_y;

        x2 = current_missile->missile->x;
        y2 = current_missile->missile->y;

        //draw_line((int) x1, (int) y1, (int) x2, (int) y2);
        draw_linef(x1, y1, x2, y2);
        draw_line(0, 0, 10, 10);
        current_missile = current_missile->next;
    }
}

void draw_explosions()
{
    struct Explosion_Node* current_explosion = get_explosion_head();
    float x1, y1;
    while (current_explosion != NULL)
    {
        x1 = current_explosion->explosion->x;
        y1 = current_explosion->explosion->y;


        draw_circlef(x1, y1, current_explosion->explosion->current_radius);
        
        current_explosion = current_explosion->next;
    }
}
