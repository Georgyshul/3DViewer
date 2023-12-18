#include "gl_obj.h"

#include <math.h>
#include <stdlib.h>

gl_obj_t *gl_line_loop(const obj_t *obj) {
  gl_obj_t *gl = (gl_obj_t *)calloc(1, sizeof(gl_obj_t));

  gl->num_facets = obj->num_facets;
  gl->max_vertex = 0;

  gl->line_sizes = (int *)calloc(gl->num_facets, sizeof(int));
  for (int i = 0; i < gl->num_facets; ++i) {
    gl->line_sizes[i] = obj->facets[i].size;
  }

  gl->facets = (double **)calloc(gl->num_facets, sizeof(double *));
  for (int i = 0; i < gl->num_facets; ++i) {
    gl->facets[i] = (double *)calloc(3 * gl->line_sizes[i], sizeof(double));
  }

  for (int i = 0; i < gl->num_facets; ++i) {
    for (int j = 0; j < gl->line_sizes[i]; ++j) {
      double x = obj->vertexes[obj->facets[i].id_vertexes[j]].x;
      double y = obj->vertexes[obj->facets[i].id_vertexes[j]].y;
      double z = obj->vertexes[obj->facets[i].id_vertexes[j]].z;

      gl->facets[i][j * 3] = x;
      gl->facets[i][j * 3 + 1] = y;
      gl->facets[i][j * 3 + 2] = z;

      gl->max_vertex = fmax(gl->max_vertex, x);
      gl->max_vertex = fmax(gl->max_vertex, y);
      gl->max_vertex = fmax(gl->max_vertex, z);
    }
  }

  gl->num_vertexes = obj->num_vertexes;
  gl->vertexes = (double *)calloc(gl->num_vertexes * 3, sizeof(double));
  for (int i = 0; i < gl->num_vertexes; ++i) {
    gl->vertexes[i * 3] = obj->vertexes[i].x;
    gl->vertexes[i * 3 + 1] = obj->vertexes[i].y;
    gl->vertexes[i * 3 + 2] = obj->vertexes[i].z;
  }

  return gl;
}

gl_obj_t *copy_gl_obj_transforation(const gl_obj_t *src,
                                    const trans_setup_t *setup) {
  gl_obj_t *dst = (gl_obj_t *)calloc(1, sizeof(gl_obj_t));

  dst->num_facets = src->num_facets;

  dst->line_sizes = (int *)calloc(dst->num_facets, sizeof(int));
  for (int i = 0; i < dst->num_facets; ++i) {
    dst->line_sizes[i] = src->line_sizes[i];
  }

  dst->facets = (double **)calloc(dst->num_facets, sizeof(double *));
  for (int i = 0; i < dst->num_facets; ++i) {
    dst->facets[i] = (double *)calloc(3 * dst->line_sizes[i], sizeof(double));
  }

  for (int i = 0; i < dst->num_facets; ++i) {
    for (int j = 0; j < dst->line_sizes[i]; ++j) {
      dst->facets[i][j * 3] = src->facets[i][j * 3];
      dst->facets[i][j * 3 + 1] = src->facets[i][j * 3 + 1];
      dst->facets[i][j * 3 + 2] = src->facets[i][j * 3 + 2];
    }
    transformation(dst->facets[i], dst->line_sizes[i], setup);
  }

  dst->num_vertexes = src->num_vertexes;
  dst->vertexes = (double *)calloc(3 * dst->num_vertexes, sizeof(double));
  for (int i = 0; i < dst->num_vertexes; ++i) {
    dst->vertexes[3 * i] = src->vertexes[3 * i];
    dst->vertexes[3 * i + 1] = src->vertexes[3 * i + 1];
    dst->vertexes[3 * i + 2] = src->vertexes[3 * i + 2];
  }
  transformation(dst->vertexes, dst->num_vertexes, setup);

  return dst;
}

void free_gl_obj(gl_obj_t *gl) {
  for (int i = 0; i < gl->num_facets; ++i) {
    free(gl->facets[i]);
  }

  free(gl->line_sizes);
  free(gl->vertexes);
  free(gl->facets);
  free(gl);
}
