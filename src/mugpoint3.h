#ifndef _MUG_POINT3_H
#define _MUG_POINT3_H

#include "stdio.h"

struct MugPoint3 {
  float x;
  float y;
  float z;
} typedef MugPoint3;

void copyMugPoint(MugPoint3 *src, MugPoint3 *dst);
void printMugPoint3(MugPoint3 *point);
#endif /* _MUG_POINT3_H */
