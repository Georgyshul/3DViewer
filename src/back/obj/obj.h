#ifndef SRC_BACK_OBJ_OBJ_H_
#define SRC_BACK_OBJ_OBJ_H_

#include <stdbool.h>

#include "transformation.h"

typedef struct vertex {
  double x;
  double y;
  double z;
} vertex_t;

typedef struct facet {
  int *id_vertexes;
  int size;
} facet_t;

typedef struct obj {
  vertex_t *vertexes;
  int num_vertexes;

  facet_t *facets;
  int num_facets;
} obj_t;

bool init_vertex(vertex_t *vertex, char *str);
bool init_facet(facet_t *facet, char *str, int num_obj_vertexes);

void free_facet(facet_t *facet);
void free_obj(obj_t **obj);

#endif  // SRC_BACK_OBJ_OBJ_H_
