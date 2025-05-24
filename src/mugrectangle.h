#ifndef _MY_RECTANGLE_H
#define _MY_RECTANGLE_H

#include "glad/glad.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

extern int m_rectangle_indices[];
extern GLuint m_rectangle_ebo;
extern bool m_rect_init;

struct MugPoint {
  float x;
  float y;
  float z;
} typedef MugPoint;

struct MugRectangle {
  MugPoint vertices[4];
  GLuint vao;
  GLuint vbo;
  GLenum usage;
} typedef MugRectangle;

void init_rectangle_gl();
void exit_rectangle_gl();

MugRectangle *create_mug_rect(MugPoint bl, MugPoint tr, GLenum usage);
void destroy_mug_rect(MugRectangle *mRect);

void draw_mug_rect(MugRectangle *mugRect);
void update_mug_rect(MugRectangle *mRect);

void printMugRect(MugRectangle *mugRect);

#endif /* _MY_RECTANGLE_H */
