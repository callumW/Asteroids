/*
    File: Window.c
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
#include "Window.h"
#include "Game.h"
#include <stdio.h>
#include <math.h>
SDL_Window* g_window = NULL;
SDL_GLContext* g_gl_context = NULL;

int gc_win_width = 800;
int gc_win_height = 600;

long g_frames = 0;
char g_title_text[] = "Radar v0.1.1 FPS: [000]";

BOOL g_fullscreen = FALSE;

void clear_screen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void show_screen()
{
    SDL_GL_SwapWindow(g_window);
}

int initialise_window(const struct Game_setting* set)
{
    gc_win_width = set->width;
    gc_win_height = set->height;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS) != 0) {
        printf("Failed to initialise SDL!\nError: %s\n", SDL_GetError());
        return 1;
    }

    if (set->fullscreen == TRUE) {
        g_window = SDL_CreateWindow(g_title_text, SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, gc_win_width, gc_win_height,
            SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN|SDL_WINDOW_OPENGL);
        if (g_window != NULL)
            SDL_GetWindowSize(g_window, &gc_win_width, &gc_win_height);
    }
    else {
        g_window = SDL_CreateWindow(g_title_text, SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, gc_win_width,
            gc_win_height, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
    }

    if (g_window == NULL) {
        printf("Failed to create SDL Window!\nError: %s\n", SDL_GetError());
        return 2;
    }

    if (init_opengl() != 0) {
        printf("Failed to initialise openGL\n");
        return 5;
    }
/*
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED|
        SDL_RENDERER_TARGETTEXTURE|SDL_RENDERER_PRESENTVSYNC);

    if (g_renderer == NULL) {
        printf("Failed to create SDL Renderer!\nError: %s\n", SDL_GetError());
        return 3;
    }
*/
    return 0;
}

void print_fps(int fps)
{
	int hundreds, tens;
    if (fps > 999) {
        fps = 999;
    }
    else {
        hundreds = fps / 100;
        fps -= hundreds * 100;
        tens = fps / 10;
        fps -= tens * 10;

        g_title_text[19] = '0' + hundreds;
        g_title_text[20] = '0' + tens;
        g_title_text[21] = '0' + fps;

        SDL_SetWindowTitle(g_window, g_title_text);
    }
}

int init_opengl()
{
	GLenum error;
    g_gl_context = SDL_GL_CreateContext(g_window);
    if (g_gl_context == NULL) {
        printf("Failed to create openGL context!\nError: %s\n", SDL_GetError());
        return 1;
    }

    //Enable vysnc
    if (SDL_GL_SetSwapInterval(1) != 0) {
        printf("WARNING: Could not enable vsync in openGL.\n");
    }

    error = GL_NO_ERROR;

    /* Init projection matrix */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /******* IMPORTANT !!!!!!! ************/
    /* Convert coord systems to our normal system with 0, 0 in top left */
    glOrtho( 0.0, gc_win_width, gc_win_height, 0.0, 1.0, -1.0 );

    /* Check for error */
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initialising projection matrix!\n");
        printf("Error: %s\n", gluErrorString(error));
        return 1;
    }

    /* Initialise Model view */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Check for error */
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initialising model view matrix!\n");
        printf("Error: %s\n", gluErrorString(error));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   //Set clear color

    /* Check for error */
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error setting clear color for openGL!\n");
        printf("Error: %s\n", gluErrorString(error));
        return 1;
    }
    return 0;
}
