#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/raylib.h"

#define FPS 60
#define SCREEN_W 640
#define SCREEN_H 480
#define MASTER_ARGS 1 // 0:exec_path

int main(int argc, char *argv[]) {

    if (argc < MASTER_ARGS) {
        printf("ERROR: master process needs more args. Provided:");
        for(int i = 0; i < argc; ++i) {
            printf(" %s", argv[i]);
        }
        printf("\n");
        exit(EXIT_FAILURE);
    }

    char *window_title = "Chain Reaction";
    InitWindow(SCREEN_W, SCREEN_H, window_title);

    char *text = "Hello World";
    int font_size = 20;

    SetTargetFPS(FPS);
    int fps_sync = 0;
    bool text_is_black = true;
    Color text_color;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        if(fps_sync % FPS == 0) {
            if(text_is_black) {
                text_color = BLACK;
            } else {
                text_color = RED;
            }
            text_is_black = !text_is_black;
        }
        DrawText(
            text, 
            GetScreenWidth()/2 - MeasureText(text, font_size)/2, 
            GetScreenHeight()/2 - font_size/2, 
            font_size, 
            text_color
        );
        EndDrawing();
        fps_sync++;
    }

    return 0;
}
