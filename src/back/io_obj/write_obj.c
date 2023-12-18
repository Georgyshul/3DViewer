#include <stdio.h>

#include "io_obj.h"

void write_obj_file(FILE *fd, obj_t *obj, const trans_setup_t *setup);

bool write_obj(const char *filename, obj_t *obj, const trans_setup_t *setup) {
  FILE *fd = fopen(filename, "w");

  if (fd == NULL) {
    return true;
  }

  write_obj_file(fd, obj, setup);
  fclose(fd);

  return false;
}

void write_obj_file(FILE *fd, obj_t *obj, const trans_setup_t *setup) {
  for (int i = 0; i < obj->num_vertexes; ++i) {
    double vertex[3] = {obj->vertexes[i].x, obj->vertexes[i].y,
                        obj->vertexes[i].z};
    transformation(vertex, 1, setup);

    fprintf(fd, "v %lf %lf %lf\n", vertex[0], vertex[1], vertex[2]);
  }

  fprintf(fd, "\n");

  for (int i = 0; i < obj->num_facets; ++i) {
    fprintf(fd, "f");

    for (int j = 0; j < obj->facets[i].size; ++j) {
      fprintf(fd, " %d", obj->facets[i].id_vertexes[j] + 1);
    }

    fprintf(fd, "\n");
  }
}
