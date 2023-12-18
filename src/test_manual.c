#include <stdio.h>

#include "back/io_obj/io_obj.h"
#include "back/obj/obj.h"

int main() {
  obj_t *obj = read("cube.obj", NULL);

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  free_obj(&obj);
  return 0;
}