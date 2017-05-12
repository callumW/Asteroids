/*
    File: Window.h
    Author: Callum Wilson callum.w@outlook.com
    Description: Functions and variables relating to the game window and
    rendering to it.
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
#ifndef WINDOW_H
#define WINDOW_H
#include "SDL.h"
#include "SDL_opengl.h"

#ifdef __APPLE__
#include <OpenGL/glu.h>
#endif

#ifdef __linux__
#include <GL/glu.h>
#endif

#ifdef __WIN32__
#include <GL/glu.h>
#endif

#include "Bool.h"
#include "Settings.h"
#include "Platform.h"

extern SDL_Window* g_window;
extern SDL_GLContext* g_gl_context;

extern int gc_win_width;
extern int gc_win_height;
//extern const char* gc_title;

extern long g_frames;
extern char g_title_text[];

extern BOOL g_fullscreen;

/*
    Clear the screen with blackness.
*/
void clear_screen();

/*
    Present the screen to the user
*/
void show_screen();

/*
    Initialise SDL systems and create a window and renderer
    \param set The desired game settings
    \return 0 upon success, not-zero otherwise
*/
int initialise_window(const struct Game_setting* set);

/*
    Initialise some openGL fluff
    \return 0 upon success, not-zero otherwise
*/
int init_opengl();

/*
    print the frames per second in the window title
*/
void print_fps(int fps);
#endif
