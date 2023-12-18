#define _GNU_SOURCE

#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io_obj.h"

int *count_elements(FILE *fd, int num_types, ...);
vertex_t *read_vertexes(FILE *fd, int num_vertexes);
facet_t *read_facets(FILE *fd, int num_facets, int num_vertexes);

obj_t *read_obj_file(FILE *fd);

obj_t *read_obj(const char *filename) {
  FILE *fd = fopen(filename, "r");

  if (fd == NULL) {
    return NULL;
  }

  obj_t *obj = read_obj_file(fd);
  fclose(fd);
  return obj;
}

obj_t *read_obj_file(FILE *fd) {
  setlocale(LC_ALL, "en-US");
  setlocale(LC_NUMERIC, "C");

  obj_t *obj = (obj_t *)calloc(1, sizeof(obj_t));

  int *counter = count_elements(fd, 2, "v ", "f ");
  obj->num_vertexes = counter[0];
  obj->num_facets = counter[1];
  free(counter);

  obj->vertexes = read_vertexes(fd, obj->num_vertexes);
  if (obj->vertexes == NULL) {
    free(obj);
    fseek(fd, 0, SEEK_SET);
    return NULL;
  }

  obj->facets = read_facets(fd, obj->num_facets, obj->num_vertexes);
  if (obj->facets == NULL) {
    free(obj->vertexes);
    free(obj);
    fseek(fd, 0, SEEK_SET);
    return NULL;
  }

  fseek(fd, 0, SEEK_SET);
  return obj;
}

vertex_t *read_vertexes(FILE *fd, int num_vertexes) {
  vertex_t *vertexes = (vertex_t *)calloc(num_vertexes, sizeof(vertex_t));

  bool error = false;
  int index = 0;

  char buff[BUFFERSIZE];
  char *buffer = buff;
  size_t len = BUFFERSIZE;

  while (index != num_vertexes && !error && getline(&buffer, &len, fd) != -1) {
    if (strncmp(buffer, "v ", 2) == 0) {
      error |= init_vertex(&(vertexes[index]), buffer + 1);

      if (!error) {
        ++index;
      }
    }
  }

  if (error) {
    free(vertexes);
    vertexes = NULL;
  }

  fseek(fd, 0, SEEK_SET);
  return vertexes;
}

facet_t *read_facets(FILE *fd, int num_facets, int num_vertexes) {
  facet_t *facets = (facet_t *)calloc(num_facets, sizeof(facet_t));

  bool error = false;
  int index = 0;

  char buff[BUFFERSIZE];
  char *buffer = buff;
  size_t len = BUFFERSIZE;

  while (index != num_facets && !error && getline(&buffer, &len, fd) != -1) {
    if (strncmp(buffer, "f ", 2) == 0) {
      error |= init_facet(&(facets[index]), buffer + 1, num_vertexes);
      ++index;
    }
  }

  if (error) {
    free(facets);
    facets = NULL;
  }

  fseek(fd, 0, SEEK_SET);
  return facets;
}

int *count_elements(FILE *fd, int num_types, ...) {
  va_list vl;
  va_start(vl, num_types);

  int *counter = (int *)calloc(num_types, sizeof(int));

  for (int i = 0; i < num_types; ++i) {
    const char *type = va_arg(vl, const char *);
    fseek(fd, 0, SEEK_SET);

    char buff[BUFFERSIZE];
    char *buffer = buff;
    size_t len = BUFFERSIZE;

    while (getline(&buffer, &len, fd) != -1) {
      if (!strncmp(type, buffer, strlen(type))) {
        ++counter[i];
      }
    }
  }

  fseek(fd, 0, SEEK_SET);
  va_end(vl);
  return counter;
}