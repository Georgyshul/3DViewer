#include "obj.h"

#include <stdlib.h>
#include <string.h>

int count_v_ints(char *input);
int read_v_id(char *input, char **ptr);

bool init_vertex(vertex_t *vertex, char *str) {
  char *next = str;
  bool error = false;

  vertex->x = strtod(str, &str);
  vertex->y = strtod(str, &str);
  vertex->z = strtod(str, &next);

  if (next == str) {
    error = true;
  }

  return error;
}

bool init_facet(facet_t *facet, char *input, int num_obj_vertexes) {
  int num_vertex = count_v_ints(input);
  if (num_vertex < 1) {
    return true;
  }
  int *id_vertexes = (int *)calloc(num_vertex, sizeof(int));

  int error = false;
  for (int i = 0; i < num_vertex && !error; ++i) {
    int vertex_index = read_v_id(input, &input);
    if (vertex_index == 0 || vertex_index > num_obj_vertexes) {
      error = true;
    } else {
      id_vertexes[i] = vertex_index - 1;
    }
  }

  if (!error) {
    facet->size = num_vertex;
    facet->id_vertexes = id_vertexes;
  } else {
    free(id_vertexes);
  }

  return error;
}

int count_v_ints(char *input) {
  int counter = 0;

  int id;
  do {
    id = read_v_id(input, &input);
    ++counter;
  } while (id != 0);

  return --counter;
}

int read_v_id(char *input, char **ptr) {
  int id;

  if (*input == '/') {
    while (*input != ' ') {
      ++input;
    }
  }

  while (*input == ' ') {
    ++input;
  }

  char *input_cp = input;
  if (input[0] == 'v') {
    ++input;
    id = strtol(input, &input, 10);
  } else if (*input >= '0' && *input <= '9') {
    id = strtol(input, &input, 10);
  }

  if (input_cp == input) {
    id = 0;
    *ptr = NULL;
  } else {
    *ptr = input;
  }

  return id;
}

void free_facet(facet_t *facet) { free(facet->id_vertexes); }

void free_obj(obj_t **data) {
  obj_t *obj = *data;

  for (int i = 0; i < obj->num_facets; ++i) {
    free_facet(&(obj->facets[i]));
  }
  free(obj->facets);

  free(obj->vertexes);

  free(*data);
  *data = NULL;
}
