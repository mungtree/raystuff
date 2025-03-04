#include "stdio.h"
#include "string.h"

#include "raylib.h"
#include <glad/glad.h>

#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"
#include "raymath.h"
#include "rlgl.h"

int main(int argc, char **argv) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags
  InitWindow(850, 450, "raygui - test");
  SetTargetFPS(60);

  void *windowHandle = GetWindowHandle();
  bool showMessageBox = false;

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
  Shader shader = LoadShader("resources/shaders/glsl/simpleshader.vs",
                             "resources/shaders/glsl/simpleshader.fs");
  GLuint VBO;
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(0xffffff));

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
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(0);
    // ------------------------------------------------
    // END OPENGL

    EndDrawing();
  }
  CloseWindow();
}
