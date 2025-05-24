#include "mugrectangle.h"

int m_rectangle_indices[] = {0, 1, 3, 1, 2, 3};
GLuint m_rectangle_ebo;
bool m_rect_init = false;

/* Util Functions*/

void copyMugPoint(MugPoint *src, MugPoint *dst);
// End Util

void init_rectangle_gl() {
  if (m_rect_init)
    return;
  glGenBuffers(1, &m_rectangle_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rectangle_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_rectangle_indices),
               m_rectangle_indices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_rect_init = true;
}

void exit_rectangle_gl() {
  if (!m_rect_init)
    return;
  glDeleteBuffers(1, &m_rectangle_ebo);
  m_rect_init = false;
}

MugRectangle *create_mug_rect(MugPoint bl, MugPoint tr, GLenum usage) {
  MugRectangle *mRect = calloc(1, sizeof(MugRectangle));
  mRect->usage = usage;
  copyMugPoint(&tr, &mRect->vertices[0]);
  copyMugPoint(&bl, &mRect->vertices[2]);

  MugPoint *br = &mRect->vertices[1];
  br->x = tr.x;
  br->y = bl.y;

  MugPoint *tl = &mRect->vertices[3];
  tl->x = bl.x;
  tl->y = tr.y;

  glGenBuffers(1, &mRect->vbo);
  glGenVertexArrays(1, &mRect->vao);

  glBindVertexArray(mRect->vao);
  glBindBuffer(GL_ARRAY_BUFFER, mRect->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(mRect->vertices), mRect->vertices,
               usage);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  return mRect;
}

void destroy_mug_rect(MugRectangle *mRect) {
  glDeleteVertexArrays(1, &mRect->vao);
  glDeleteBuffers(1, &mRect->vbo);
  free(mRect);
}

void draw_mug_rect(MugRectangle *mugRect) {
  glBindVertexArray(mugRect->vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rectangle_ebo);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void update_mug_rect(MugRectangle *mRect) {
  glBindBuffer(GL_ARRAY_BUFFER, mRect->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(mRect->vertices), mRect->vertices,
               mRect->usage);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void copyMugPoint(MugPoint *src, MugPoint *dst) {
  dst->x = src->x;
  dst->y = src->y;
  dst->z = src->z;
}

void printMugPoint(MugPoint *mugPoint) {
  printf("MugPoint[%f, %f, %f]", mugPoint->x, mugPoint->y, mugPoint->z);
}

void printMugRect(MugRectangle *mugRect) {
  printf("MugRectangle[vao: %d, vbo %d]\n", mugRect->vao, mugRect->vbo);
  printf("\tBL: ");
  printMugPoint(&mugRect->vertices[2]);
  printf("\n\tTL: ");
  printMugPoint(&mugRect->vertices[3]);
  printf("\n\tBR: ");
  printMugPoint(&mugRect->vertices[1]);
  printf("\n\tTR: ");
  printMugPoint(&mugRect->vertices[0]);
  printf("\n");
}
