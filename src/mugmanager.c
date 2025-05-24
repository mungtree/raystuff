#include "mugmanager.h"
#include "mugrectangle.h"

bool _has_mug_init = false;

void init_mugtree() {
  if (_has_mug_init)
    return;
  init_rectangle_gl();
  _has_mug_init = true;
}

void cleanup_mugtree() {
  exit_rectangle_gl();
  _has_mug_init = false;
}
