#include "mug_simple_rectangle_engine.h"
#include "mugpoint3.h"
#include "mugrectangle.h"
#include <string.h>

MugSimpleRectangleEngine *mug_create_simple_rectangle_engine() {
  MugSimpleRectangleEngine *engine =
      calloc(1, sizeof(MugSimpleRectangleEngine));

  engine->num_rects = 0;
  engine->capacity = _MUG_SRE_INITIAL_CAPACITY;
  engine->rectangles =
      malloc(_MUG_SRE_INITIAL_CAPACITY * sizeof(_MugEngineRect));
  engine->colors = malloc(_MUG_SRE_INITIAL_CAPACITY * sizeof(MugPoint3));

  engine->modified = true;
  engine->ebo_buffer = NULL;
  engine->shader_id = 0;
  mug_resize_sre_ebo(engine, _MUG_SRE_INITIAL_CAPACITY);

  // Element Buffer
  glGenBuffers(1, &engine->ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, engine->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, engine->capacity * sizeof(GLuint),
               engine->ebo_buffer, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // VAO & VBO
  glGenVertexArrays(1, &engine->vao);
  glGenBuffers(1, &engine->vbo);
  glBindVertexArray(engine->vao);
  glBindBuffer(GL_ARRAY_BUFFER, engine->vbo);

  // Color SBO
  glGenBuffers(1, &engine->color_sbo);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, engine->color_sbo);
  glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(MugPoint3) * engine->capacity,
               engine->colors, GL_DYNAMIC_STORAGE_BIT);
  // glNamedBufferStorage(engine->color_sbo, sizeof(MugPoint3) *
  // engine->capacity,
  //                     engine->colors, GL_DYNAMIC_STORAGE_BIT);
  // Vertex Data
  glBufferData(GL_ARRAY_BUFFER, sizeof(_MugEngineRect) * engine->capacity,
               engine->rectangles, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  return engine;
}

void mug_simple_add_rect(MugSimpleRectangleEngine *engine, MugPoint3 bl,
                         MugPoint3 tr) {
  if (engine->num_rects + 1 >= engine->capacity) {
    mug_resize_sre_capacity(engine, engine->capacity * 2);
  }

  _MugEngineRect nr;
  copyMugPoint(&tr, &nr.points[0]);
  copyMugPoint(&bl, &nr.points[2]);
  MugPoint3 *br = &nr.points[1];
  br->x = tr.x;
  br->y = bl.y;
  br->z = 0.0f;

  MugPoint3 *tl = &nr.points[3];
  tl->x = bl.x;
  tl->y = tr.y;
  tl->z = 0.0f;

  engine->rectangles[engine->num_rects] = nr;
  engine->num_rects++;
  engine->modified = true;
}

void mug_simple_render(MugSimpleRectangleEngine *engine) {
  glBindVertexArray(engine->vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, engine->ebo);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, engine->color_sbo);

  if (engine->shader_id != 0)
    glUseProgram(engine->shader_id);

  if (engine->modified) {
    glBindBuffer(GL_ARRAY_BUFFER, engine->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_MugEngineRect) * engine->capacity,
                 engine->rectangles, GL_DYNAMIC_DRAW);
    glNamedBufferStorage(engine->color_sbo,
                         sizeof(MugPoint3) * engine->capacity, engine->colors,
                         GL_DYNAMIC_STORAGE_BIT);
    engine->modified = false;
  }

  glDrawElements(GL_TRIANGLES, 6 * engine->num_rects, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  if (engine->shader_id != 0)
    glUseProgram(0);
}

void mug_resize_sre_capacity(MugSimpleRectangleEngine *engine,
                             int new_capacity) {
  if (engine->capacity >= new_capacity)
    return;

  _MugEngineRect *nrects = malloc(new_capacity * sizeof(_MugEngineRect));
  memcpy(nrects, engine->rectangles,
         engine->num_rects * sizeof(_MugEngineRect));

  _MugEngineRect *old_rects = engine->rectangles;
  free(old_rects);

  engine->rectangles = nrects;
  engine->capacity = new_capacity;
  engine->modified = true;
}

void mug_resize_sre_ebo(MugSimpleRectangleEngine *engine, int new_capacity) {
  if (engine == NULL)
    return;

  GLuint *nbuf = malloc(6 * new_capacity * sizeof(GLuint));
  for (int i = 0; i < new_capacity; i++) {
    int vecOff = 4 * i;
    int idxOff = 6 * i;
    nbuf[idxOff + 0] = vecOff + 0;
    nbuf[idxOff + 1] = vecOff + 1;
    nbuf[idxOff + 2] = vecOff + 3;
    nbuf[idxOff + 3] = vecOff + 1;
    nbuf[idxOff + 4] = vecOff + 2;
    nbuf[idxOff + 5] = vecOff + 3;
  }
  if (engine->ebo_buffer != NULL)
    free(engine->ebo_buffer);

  engine->ebo_buffer = nbuf;
  engine->modified = true;
  engine->capacity = new_capacity;
}

void print_mug_engine(MugSimpleRectangleEngine *engine) {
  printf("[SimpleRectangleEngine] - Capacity: [%d/%d]\n", engine->num_rects,
         engine->capacity);
  printf("\t(Rectangles):\n");
  for (int i = 0; i < engine->num_rects; i++) {
    _MugEngineRect *rect = &engine->rectangles[i];
    printf("\t\tRectangle %d\n", i);
    printf("\t\tBL: ");
    printMugPoint3(&rect->points[2]);
    printf("\n\t\tTL: ");
    printMugPoint3(&rect->points[3]);
    printf("\n\t\tBR: ");
    printMugPoint3(&rect->points[1]);
    printf("\n\t\tTR: ");
    printMugPoint3(&rect->points[0]);
    printf("\t\t\t---\n\n");
  }
  printf("\t(Indices):\n");
  for (int i = 0; i < engine->num_rects; i++) {
    int offset = 6 * i;
    GLuint *indices = engine->ebo_buffer;
    printf("\t\t[%d,%d,%d,%d,%d,%d]\n", indices[offset + 0],
           indices[offset + 1], indices[offset + 2], indices[offset + 3],
           indices[offset + 4], indices[offset + 5]);
  }
  printf("\t(End)\n");
}
