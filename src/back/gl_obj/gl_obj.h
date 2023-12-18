#ifndef SRC_BACK_GL_OBJ_GL_OBJ_h_
#define SRC_BACK_GL_OBJ_GL_OBJ_h_

#include "../obj/obj.h"

typedef struct gl_obj {
  double **facets;
  int num_facets;
  int *line_sizes;

  double *vertexes;
  int num_vertexes;

  double max_vertex;
  double center[3];
} gl_obj_t;

gl_obj_t *gl_line_loop(const obj_t *obj);
gl_obj_t *copy_gl_obj_transforation(const gl_obj_t *src,
                                    const trans_setup_t *setup);
void free_gl_obj(gl_obj_t *gl);

#endif  // SRC_BACK_GL_OBJ_GL_OBJ_h_
