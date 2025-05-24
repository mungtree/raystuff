#include "mugmanager.h"
#include "stdio.h"
#include "string.h"

#include "raylib.h"
#include <glad/glad.h>

#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"
#include "mugrectangle.h"
#include "raymath.h"
#include "rlgl.h"

int main(int argc, char **argv) {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags
  InitWindow(850, 450, "raygui - test");
  SetTargetFPS(60);
  glDisable(GL_CULL_FACE);
  void *windowHandle = GetWindowHandle();
  bool showMessageBox = false;

  init_mugtree();

  float vertices[] = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f  // top left
  };
  int indices[] = {0, 1, 3, 1, 2, 3};
  Shader shader = LoadShader("resources/shaders/glsl/simpleshader.vs",
                             "resources/shaders/glsl/simpleshader.fs");

  MugRectangle *mRect =
      create_mug_rect((MugPoint){-0.5f, -0.5f, 0.0f},
                      (MugPoint){0.5f, 0.5f, 0.0f}, GL_DYNAMIC_DRAW);
  printMugRect(mRect);

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
    mRect->vertices[0].x += 0.01;
    if (mRect->vertices[0].x >= 1) {
      mRect->vertices[0].x = -0.5;
    }
    mRect->vertices[1].x += 0.01;
    if (mRect->vertices[1].x >= 1) {
      mRect->vertices[1].x = -0.5;
    }
    update_mug_rect(mRect);
    draw_mug_rect(mRect);
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
