#include "mugmanager.h"
#include "stdio.h"
#include "string.h"

#include "raylib.h"
#include <glad/glad.h>

#define RAYGUI_IMPLEMENTATION
#include "rlgl.h"

#include "mug_simple_rectangle_engine.h"
#include "mugrectangle.h"
#include "raygui.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>
/**
 * Returns a random number between 0 and 1
 */
double mrand() { return (double)rand() / (double)RAND_MAX; }

int main(int argc, char **argv) {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags
  InitWindow(850, 450, "raygui - test");
  SetTargetFPS(60);
  glDisable(GL_CULL_FACE);
  void *windowHandle = GetWindowHandle();
  bool showMessageBox = false;

  init_mugtree();
  Shader shader = LoadShader("resources/shaders/glsl/simpleshader.vs",
                             "resources/shaders/glsl/simpleshader.fs");

  MugRectangle *mRect =
      create_mug_rect((MugPoint3){-0.5f, -0.5f, 0.0f},
                      (MugPoint3){0.5f, 0.5f, 0.0f}, GL_DYNAMIC_DRAW);
  MugSimpleRectangleEngine *engine = mug_create_simple_rectangle_engine();
  for (int i = 0; i < 20; i++) {
    float blx = -((float)mrand());
    float bly = -((float)mrand());
    float trx = blx + (mrand() / 2.0f);
    float try = bly + (mrand() / 2.0f);

    if (trx >= 1.0f) trx = 1.0f;
    if (try >= 1.0f) try = 1.0f;

    mug_simple_add_rect(engine, (MugPoint3){blx, bly, 0.0},
                        (MugPoint3){trx, try, 0.0});
  }

  GLint timeLoc = glGetUniformLocation(shader.id, "time");

  print_mug_engine(engine);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(0xfff0ff));

    if (GuiButton((Rectangle){24, 24, 120, 30}, "#191#Show Message")) {
      showMessageBox = true;
    }
    if (showMessageBox) {
      int result =
          GuiMessageBox((Rectangle){85, 70, 250, 100}, "#191#Message Box",
                        "Hi! This is a message!", "Nice;Cool");
      if (result >= 0) {
        showMessageBox = false;
      }
    }

    // OPENGL
    // ------------------------------------------------
    glUseProgram(shader.id);
    /*
    create_mug_rectect->vertices[0].x += 0.01;
    if (mRect->vertices[0].x >= 1) {
      mRect->vertices[0].x = -0.5;
    }
    mRect->vertices[1].x += 0.01;
    if (mRect->vertices[1].x >= 1) {
      mRect->vertices[1].x = -0.5;
    }
    update_mug_rect(mRect);
    draw_mug_rect(mRect);
    */
    float timeValue = sin(mrand());
    glUniform1f(timeLoc, timeValue);
    mug_simple_render(engine);
    glUseProgram(0);
    // ------------------------------------------------
    // END OPENGL

    EndDrawing();
  }
  destroy_mug_rect(mRect);
  mRect = NULL;

  cleanup_mugtree();

  CloseWindow();
}
