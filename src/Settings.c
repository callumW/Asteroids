/*
    File: Settings.c
    Author: Callum Wilson callum.w@outlook.com
    Description: Provides an interface to the user requesting their desired
        game settings.
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
#include "Settings.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

struct Game_setting default_settings[] = {
    {800, 600, FALSE},
    {1024, 768, FALSE},
    {1280, 800, FALSE},
    {1280, 1024, FALSE},
    {1366, 768, FALSE},
    {1920, 1080, FALSE},
    {800, 600, TRUE},
    {1024, 768, TRUE},
    {1280, 800, TRUE},
    {1280, 1024, TRUE},
    {1366, 768, TRUE},
    {1920, 1080, TRUE}
};

struct Game_setting request_settings()
{
    int max_default = sizeof(default_settings) / sizeof(struct Game_setting);
    int i, setting_choice = -1;
    char input[10];
    struct Game_setting settings = {0, 0, FALSE};
    BOOL valid_input = TRUE, valid_choice = FALSE;

    do {
        printf("\nPlease choose a setting choice:\n");
        for (i=0; i<max_default; i++) {
            fprintf(stdout, "Choice: %-3.1d  | %4.1dx%-4.1d Fullscreen: %s\n",
                i, default_settings[i].width, default_settings[i].height,
                (default_settings[i].fullscreen == TRUE) ? "Yes" : "No");
        }
        printf("\nEnter the number corresponding to your desired choice and");
        printf(" then hit enter:" );

        fgets(input, 10, stdin);
        i = 0;
        while(input[i] != '\0' && input[i] != '\n') {
            if (isdigit(input[i]) == 0) {
                valid_input = FALSE;
                break;
            }
            i++;
        }

        if (valid_input == TRUE)
            setting_choice = atoi(input);

        if (setting_choice >= 0 && setting_choice < max_default) {
            settings = default_settings[setting_choice];
            valid_choice = TRUE;
        }
        else {
            printf("\nThat is not a valid option!\n");
            valid_input = TRUE;    //Can't forget to reset this
        }
    }
    while (valid_choice == FALSE);

    printf("You picked option: %d\n", setting_choice);
    return settings;
}
