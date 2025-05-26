#include "mugpoint3.h"

void copyMugPoint(MugPoint3 *src, MugPoint3 *dst) {
  dst->x = src->x;
  dst->y = src->y;
  dst->z = src->z;
}

void printMugPoint3(MugPoint3 *point) {
  printf("MugPoint[%f, %f, %f]", point->x, point->y, point->z);
}
