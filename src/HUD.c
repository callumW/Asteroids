/*
    File: HUD.c
    Author: Callum Wilson callum.w@outlook.com
    Description: Functions and variables related to drawing the HUD
    Date: 2016/07/29

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
#include "HUD.h"
#include "Window.h"
#include "Game.h"
#include "Input_handling.h"
#include "Draw.h"

const int gc_padding = 3;
SDL_Point g_border_points[5];
SDL_Point g_mouse_rect_points[5];
SDL_Point g_mouse_lines[8];
const int mouse_width = 8;

struct color g_border_color = {61, 213, 62, 255};

void draw_hud()
{
    //SDL_SetRenderDrawColor(g_renderer, g_border_color.r, g_border_color.g,
        //g_border_color.b, g_border_color.a);
    //SDL_RenderDrawLines(g_renderer, g_border_points, 5);
    draw_border();
    if (g_scanning == TRUE)
        draw_radar_beam();
    //draw_string(g_bearing_text, 10, 10, 2, 2);
    //draw_string(g_depth_text, 10, 22, 2, 2);

    draw_mouse_pointer();
}

void init_hud()
{
    SDL_Point tl = {gc_padding, gc_padding};
    SDL_Point tr = {gc_win_width-gc_padding, gc_padding};
    SDL_Point br = {gc_win_width-gc_padding, gc_win_height-gc_padding};
    SDL_Point bl = {gc_padding, gc_win_height-gc_padding};

    g_border_points[0] = tl;
    g_border_points[1] = tr;
    g_border_points[2] = br;
    g_border_points[3] = bl;
    g_border_points[4] = tl;

    SDL_ShowCursor(SDL_DISABLE);
}

void draw_border()
{
    draw_line(g_border_points[0].x, g_border_points[0].y,
        g_border_points[1].x, g_border_points[1].y);

    draw_line(g_border_points[1].x, g_border_points[1].y,
        g_border_points[2].x, g_border_points[2].y);

    draw_line(g_border_points[3].x, g_border_points[3].y,
        g_border_points[2].x, g_border_points[2].y);

    draw_line(g_border_points[4].x, g_border_points[4].y,
        g_border_points[3].x, g_border_points[3].y);
}

void draw_radar_beam()
{
    draw_line(gc_padding, g_radar_beam_y, gc_win_width-gc_padding,
        g_radar_beam_y);//
}

void draw_mouse_pointer()
{
    draw_line(g_mouse_rect_points[0].x, g_mouse_rect_points[0].y,
        g_mouse_rect_points[1].x, g_mouse_rect_points[1].y);

    draw_line(g_mouse_rect_points[1].x, g_mouse_rect_points[1].y,
        g_mouse_rect_points[2].x, g_mouse_rect_points[2].y);

    draw_line(g_mouse_rect_points[2].x, g_mouse_rect_points[2].y,
        g_mouse_rect_points[3].x, g_mouse_rect_points[3].y);

    draw_line(g_mouse_rect_points[3].x, g_mouse_rect_points[3].y,
        g_mouse_rect_points[4].x, g_mouse_rect_points[4].y);

    /* Axis lines */
    /*
    draw_line(g_mouse_lines[0].x, g_mouse_lines[0].y,
        g_mouse_lines[1].x, g_mouse_lines[1].y);

    draw_line(g_mouse_lines[2].x, g_mouse_lines[2].y,
        g_mouse_lines[3].x, g_mouse_lines[3].y);

    draw_line(g_mouse_lines[4].x, g_mouse_lines[4].y,
        g_mouse_lines[5].x, g_mouse_lines[5].y);

    draw_line(g_mouse_lines[6].x, g_mouse_lines[6].y,
        g_mouse_lines[7].x, g_mouse_lines[7].y);
        */

    draw_line(g_mouse_x, gc_padding, g_mouse_x, gc_win_height-gc_padding);
    draw_line(gc_padding, g_mouse_y, gc_win_width-gc_padding, g_mouse_y);
}

void update_mouse_pointer()
{
    SDL_ShowCursor(0);
    /* Top left*/
    g_mouse_rect_points[0].x = g_mouse_x - (mouse_width / 2);
    g_mouse_rect_points[0].y = g_mouse_y - (mouse_width / 2);

    /* Top right */
    g_mouse_rect_points[1].x = g_mouse_x + (mouse_width / 2);
    g_mouse_rect_points[1].y = g_mouse_rect_points[0].y;

    /*Bottom right*/
    g_mouse_rect_points[2].x = g_mouse_x + (mouse_width / 2);
    g_mouse_rect_points[2].y = g_mouse_y + (mouse_width / 2);

    /* Bottom left*/
    g_mouse_rect_points[3].x = g_mouse_rect_points[0].x;
    g_mouse_rect_points[3].y = g_mouse_rect_points[2].y;

    /* Top left*/
    g_mouse_rect_points[4].x = g_mouse_rect_points[0].x;
    g_mouse_rect_points[4].y = g_mouse_rect_points[0].y;

    /* Update axis aligned lines */

    /* Top line */
    g_mouse_lines[0].x = g_mouse_x;
    g_mouse_lines[0].y = g_mouse_y - (mouse_width/2);
    g_mouse_lines[1].x = g_mouse_x;
    g_mouse_lines[1].y = gc_padding;

    /*Right line*/
    g_mouse_lines[2].x = g_mouse_x + (mouse_width/2);
    g_mouse_lines[2].y = g_mouse_y;
    g_mouse_lines[3].x = gc_win_width-gc_padding;
    g_mouse_lines[3].y = g_mouse_y;

    /*Bottom line*/
    g_mouse_lines[4].x = g_mouse_x;
    g_mouse_lines[4].y = g_mouse_y + (mouse_width/2);
    g_mouse_lines[5].x = g_mouse_x;
    g_mouse_lines[5].y = gc_win_height-gc_padding;

    /*Left line*/
    g_mouse_lines[6].x = g_mouse_x - (mouse_width/2);
    g_mouse_lines[6].y = g_mouse_y;
    g_mouse_lines[7].x = gc_padding;
    g_mouse_lines[7].y = g_mouse_y;
}
