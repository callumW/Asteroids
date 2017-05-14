/*
    File: Game.h
    Author: Callum Wilson callum.w@outlook.com
    Description: Gameplay related functions for the radar-turn-based game.
    Date: 2016/07/28

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
#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "Window.h"
#include "Input_handling.h"
#include "Bool.h"
#include "Platform.h"
#include "Missile_List.h"

extern long g_previous_time;
extern long g_current_time;
extern long g_start_time;

extern int g_radar_beam_y;
extern const float gc_radar_beam_speed;
extern const int gc_radar_beam_delay;
extern int g_scan_start_time;
extern int g_last_scan_end;
extern BOOL g_scanning;

/*
    Draw everything that should be on screen, on screen.
*/
void draw_all();

/*
    Update the game
*/
void update();

/*
    initialise the timing values
*/
void init_timers();

/*
    Update the timiing values
*/
void update_timers();

/*
    Update the state of the radar beam
*/
void update_radar_beam();

/*
    Update an individual missile
*/
void update_missile(struct Missile* missile);


/*
    Update the missiles
*/
void update_missiles();

void update_explosion();

/*
    Update the exposions
*/
void update_explosions();

/*
    Fire a missile!
*/
void fire_missile(int id, float target_x, float target_y, float origin_x, float origin_y);

/*
    Unfire missile!
*/
void unfire_missile();
#endif
