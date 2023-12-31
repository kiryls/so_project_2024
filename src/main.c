#include <stdio.h>
#include "include/raylib.h"

int main(int argc, char *argv[]) {

    char *window_title = "Template Project";
    InitWindow(640, 480, window_title);

    char *text = "Hello World";
    int font_size = 20;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(text, GetScreenWidth()/2 - MeasureText(text, font_size)/2, GetScreenHeight()/2 - font_size/2, font_size, DARKGRAY);
        EndDrawing();
    }

    return 0;
}
