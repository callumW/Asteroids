/*
    File: Game.c
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

#include "Game.h"
#include "HUD.h"
#include "Bool.h"
#include "SDL_opengl.h"
#include "Draw.h"
#include "Missile.h"
#include "Explosion.h"
#include "Explosion_List.h"
#include "Missile_List.h"

#include <math.h>

long g_previous_time = 0;
long g_current_time = 0;
long g_start_time = 0;

int g_radar_beam_y = 0;
const float gc_radar_beam_speed = 0.15f;
const int gc_radar_beam_delay = 500;
int g_scan_start_time = 0;
int g_last_scan_end = 0;
BOOL g_scanning = FALSE;

float missile_speed = 0.1f;

Mix_Chunk* launch_sound = NULL;
Mix_Chunk* bomb_sound = NULL;

void draw_all()
{
    float r, g, b;
    glClear(GL_COLOR_BUFFER_BIT);
    r = (float) g_border_color.r / 255;
    g = (float) g_border_color.g / 255;
    b = (float) g_border_color.b / 255;
    glColor3f(r, g, b);
    //draw_line(0, 0, 20, 20);
    draw_hud();
    draw_missiles();
    draw_explosions();
}

void update()
{
    g_frames++;
    update_radar_beam();
    update_missiles();
    update_explosions();
}

void init_timers()
{
    g_start_time = SDL_GetTicks();
    g_current_time = g_start_time;
    g_scan_start_time = g_start_time;
    g_previous_time = 0;
}

void update_timers()
{
    g_previous_time = g_current_time;
    g_current_time = SDL_GetTicks();
}

void update_radar_beam()
{
    if (g_scanning == TRUE) {
        g_radar_beam_y = (g_current_time - g_scan_start_time) *
            gc_radar_beam_speed;
        if (g_radar_beam_y > gc_win_height - gc_padding) {
            g_scanning = FALSE;
            g_radar_beam_y = gc_padding;
            g_last_scan_end = SDL_GetTicks();
        }
    }
    else {
        //if (g_current_time - g_last_scan_end > gc_radar_beam_delay)
            //g_scanning = TRUE;
        g_scan_start_time = SDL_GetTicks();
    }
}

void update_missile(struct Missile* missile)
{
    //printf("updating a missile\n");
    
    //work out location
    float next_x, next_y;
    next_x = cosf(missile->angle) * missile_speed * (g_current_time - g_previous_time);
    next_y = sinf(missile->angle) * missile_speed * (g_current_time - g_previous_time);

    //update location
    missile->x += next_x;
    missile->y += next_y;

    //printf("moved missile to: %f, %f\n", next_x, next_y);

    //check if exploded
        //create explosion and delete missile
    if (missile->detination_time < g_current_time)
    {
        missile->alive = FALSE;
        add_explosion(missile->x, missile->y,  missile->explosion_radius, 350, 0);
        if (Mix_PlayChannel(-1, bomb_sound, 0) == -1)
        {
            printf("failed to play bomb sound!\n");
        }
    }
}

void update_missiles()
{
    //printf("Updating missiles\n");
    struct Missile_Node* current_missile = get_missile_head();
    
    while (current_missile != NULL)
    {
        update_missile(current_missile->missile);
        current_missile = current_missile->next;
    }

    cull_missiles();
}


void update_explosion(struct Explosion* exp)
{
    //update the time to live?
    //adjust radius based upon time

    exp->time_to_live -= (g_current_time - g_previous_time);

    exp->current_radius = exp->max_radius * ( 1.0f - (exp->time_to_live / 500.0));

    if (exp->time_to_live < 0)
    {
        exp->alive = FALSE;
    }
}


void update_explosions()
{
    struct Explosion_Node* current_explosion = get_explosion_head();

    while (current_explosion != NULL)
    {
        update_explosion(current_explosion->explosion);
        current_explosion = current_explosion->next;
    }
    
    cull_explosions();
}

void cull_explosions()
{
    struct Explosion_Node* current_explosion = get_explosion_head();
    struct Explosion_Node* next_explosion = NULL;

    while (current_explosion != NULL)
    {
        next_explosion = current_explosion->next;
        if (current_explosion->explosion->alive == FALSE)
        {
            remove_explosion(current_explosion->explosion);
        }

        current_explosion = next_explosion;

    }
}

void fire_missile(int id, float target_x, float target_y, float origin_x, float origin_y)
{
    float angle = atan((double)((target_y - origin_y) / (target_x - origin_x)));
    //angle is wrong...
    if (target_x < origin_x && target_y < origin_y)
    {
        angle = atan((double)((origin_y - target_y) / (origin_x - target_x)));
        angle -= 3.14;
    }

    float dist = sqrtf((target_x - origin_x) * (target_x - origin_x) + (target_y - origin_y)*(target_y - origin_y));
    float time = dist / missile_speed;

    add_missile(origin_x, origin_y, angle, g_current_time, g_current_time + time, 60, id);
    if (Mix_PlayChannel(-1, launch_sound, 0) == -1)
    {
        printf("Failed to play missile sound\n");
    }
}

void unfire_missile()
{
    struct Missile_Node* node = get_missile_tail();

    if (node != NULL)
        remove_missile(node->missile);
}

void cull_missiles()
{
    struct Missile_Node* current_missile = get_missile_head();
    struct Missile_Node* next_missile = NULL;

    while (current_missile != NULL)
    {
        next_missile = current_missile->next;
        if (current_missile->missile->alive == FALSE)
        {
            remove_missile(current_missile->missile);
        }

        current_missile = next_missile;
    }
}

void load_audio_files()
{
    launch_sound = Mix_LoadWAV("media/missile_launch2.WAV");
    bomb_sound = Mix_LoadWAV("media/bomb_sound.WAV");

    if (launch_sound == NULL || bomb_sound == NULL)
    {
        printf("Failed to load launch sound\n");
        return;
    }
}
void clean_up()
{
    Mix_FreeChunk(launch_sound);
    Mix_FreeChunk(bomb_sound);
}