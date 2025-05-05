#include <stdio.h>
#include "raylib.h"
#include "stb_ds.h"

struct buffer {
  char **lines;
};

int main(int argc, const char **argv) {
  InitWindow(800, 450, "CED");
  char *file_content = LoadFileText(TextFormat("%s", argc > 1 ? argv[1] : "Makefile"));
  printf("%s\n", file_content);
  int x = 0, y = 0;
  bool isclose = false;
  while (!WindowShouldClose() && !isclose) {
    BeginDrawing();
    ClearBackground((Color){0x0f, 0x0f, 0x0f, 0xff});
    DrawRectangle(x, y, 8, 16, (Color){0xff, 0x0, 0x0, 0xff});
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_F)) {
      x += 8;
    } else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_B)) {
      if (x > 0) x -= 8;
    } else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_N)) {
      y += 16;
    } else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_P)) {
      if (y > 0) y -= 16;
    } else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_G)) {
      isclose = true;
    } else if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_R)) {
      int screen_height = GetScreenHeight();
      int cells = screen_height / 16;
      int mid = cells / 2;
      if (y == 0) {
        y = (mid - 1) * 16;
      } else if (y == (mid - 1) * 16) {
	y = (cells - 1) * 16;
      } else {
        y = 0;
      }
    }
    EndDrawing();
  }

  CloseWindow();
  MemFree(file_content);
  return 0;
}
