#ifndef _MUG_SIMPLE_RECTANGLE_ENGINE
#define _MUG_SIMPLE_RECTANGLE_ENGINE

#include "mugpoint3.h"
#include "mugrectangle.h"

#define _MUG_SRE_INITIAL_CAPACITY 128

struct _MugEngineRect {
  MugPoint3 points[4];
} typedef _MugEngineRect;

struct MugSimpleRectangleEngine {
  _MugEngineRect *rectangles;
  GLuint *ebo_buffer;
  int num_rects;
  int capacity;
  bool modified;
  GLuint vbo;
  GLuint vao;
  GLuint ebo;
} typedef MugSimpleRectangleEngine;

MugSimpleRectangleEngine *mug_create_simple_rectangle_engine();
void mug_simple_add_mugrect(MugSimpleRectangleEngine *engine,
                            MugRectangle *rect);
void mug_simple_add_rect(MugSimpleRectangleEngine *engine, MugPoint3 bl,
                         MugPoint3 tr);

void mug_resize_sre_capacity(MugSimpleRectangleEngine *engine,
                             int new_capacity);
void mug_resize_sre_ebo(MugSimpleRectangleEngine *engine, int new_capacity);
void mug_simple_render(MugSimpleRectangleEngine *engine);

void print_mug_engine(MugSimpleRectangleEngine *engine);

#endif /* _MUG_SIMPLE_RECTANGLE_ENGINE */
