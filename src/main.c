/*
    File: main.c
    Author: Callum Wilson callum.w@outlook.com
    Description: A prototype for a radar-turn-based game.
    Date: 2016/07/27

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

#include "SDL.h"

#include "Input_handling.h"
#include "Window.h"
#include "Game.h"
#include "HUD.h"
#include "Bool.h"
#include "Settings.h"

#include <stdio.h>

#undef main

int main(int argc, char** argv)
{
	int last_fps_check;
    /*
    if (argc > 1) {
        int i = 0;
        while (i<argc) {
            char* param = argv[i];
            int size = sizeof(param) / sizeof(char);
            int j = 0;
            while (param[j] != '\0') {
                if (param[j] == '-' && j < size - 1) {
                    if (param[j+1] == 'f' || param[j+1] == 'F')
                        g_fullscreen = TRUE;
                }
                j++;
            }
            i++;
        }
    }*/
    struct Game_setting settings = request_settings();
    if (initialise_window(&settings) != 0) {
        printf("Failed to setup critical components!\nself destructing in");
        printf(" 10 seconds...\n");
        return 1;
    }
    init_timers();
    init_hud();

    last_fps_check = SDL_GetTicks();
    print_fps(999);
    while (g_running == TRUE) {
        update_timers();
        handle_input();

        update();

        if (g_current_time - last_fps_check > 500) {
            int fps = 1000 / (g_current_time - g_previous_time);
            print_fps(fps);
            last_fps_check = g_current_time;
        }

        //clear_screen();
        draw_all();
        show_screen();
    }

	SDL_Quit();
    return 0;
}
