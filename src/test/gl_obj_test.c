#include "../back/gl_obj/gl_obj.h"

#include <math.h>
#include <stdbool.h>

#include "../back/io_obj/io_obj.h"
#include "../back/obj/obj.h"
#include "test.h"

// gl_line_loop
START_TEST(gl_line_loop_0) {
  obj_t *obj = read_obj("test/test_samples/test_sample_0.obj");

  ck_assert_ptr_ne(obj, NULL);

  gl_obj_t *gl_obj = gl_line_loop(obj);
  ck_assert_ptr_ne(gl_obj, NULL);

  ck_assert_int_eq(gl_obj->num_facets, obj->num_facets);
  ck_assert_int_eq(gl_obj->num_vertexes, obj->num_vertexes);

  for (int i = 0; i < gl_obj->num_facets; ++i) {
    ck_assert_int_eq(gl_obj->line_sizes[i], obj->facets[i].size);

    for (int j = 0; j < gl_obj->line_sizes[i]; ++j) {
      double_eq(gl_obj->facets[i][3 * j],
                obj->vertexes[obj->facets[i].id_vertexes[j]].x);
      double_eq(gl_obj->facets[i][3 * j + 1],
                obj->vertexes[obj->facets[i].id_vertexes[j]].y);
      double_eq(gl_obj->facets[i][3 * j + 2],
                obj->vertexes[obj->facets[i].id_vertexes[j]].z);
    }
  }

  ck_assert_int_eq(gl_obj->num_vertexes, obj->num_vertexes);
  for (int i = 0; i < gl_obj->num_vertexes; ++i) {
    double_eq(gl_obj->vertexes[3 * i], obj->vertexes[i].x);
    double_eq(gl_obj->vertexes[3 * i + 1], obj->vertexes[i].y);
    double_eq(gl_obj->vertexes[3 * i + 2], obj->vertexes[i].z);
  }

  free_obj(&obj);
  free_gl_obj(gl_obj);
}
END_TEST

START_TEST(gl_line_loop_1) {
  obj_t *obj = read_obj("test/test_samples/test_sample_4.obj");

  ck_assert_ptr_ne(obj, NULL);

  gl_obj_t *gl_obj = gl_line_loop(obj);
  ck_assert_ptr_ne(gl_obj, NULL);

  ck_assert_int_eq(gl_obj->num_facets, obj->num_facets);
  ck_assert_int_eq(gl_obj->num_vertexes, obj->num_vertexes);

  for (int i = 0; i < gl_obj->num_facets; ++i) {
    ck_assert_int_eq(gl_obj->line_sizes[i], obj->facets[i].size);

    for (int j = 0; j < gl_obj->line_sizes[i]; ++j) {
      double_eq(gl_obj->facets[i][3 * j],
                obj->vertexes[obj->facets[i].id_vertexes[j]].x);
      double_eq(gl_obj->facets[i][3 * j + 1],
                obj->vertexes[obj->facets[i].id_vertexes[j]].y);
      double_eq(gl_obj->facets[i][3 * j + 2],
                obj->vertexes[obj->facets[i].id_vertexes[j]].z);
    }
  }

  ck_assert_int_eq(gl_obj->num_vertexes, obj->num_vertexes);
  for (int i = 0; i < gl_obj->num_vertexes; ++i) {
    double_eq(gl_obj->vertexes[3 * i], obj->vertexes[i].x);
    double_eq(gl_obj->vertexes[3 * i + 1], obj->vertexes[i].y);
    double_eq(gl_obj->vertexes[3 * i + 2], obj->vertexes[i].z);
  }

  free_obj(&obj);
  free_gl_obj(gl_obj);
}
END_TEST

START_TEST(gl_line_loop_2) {
  obj_t *obj = read_obj("test/test_samples/test_sample_5.obj");

  ck_assert_ptr_ne(obj, NULL);

  gl_obj_t *gl_obj = gl_line_loop(obj);
  ck_assert_ptr_ne(gl_obj, NULL);

  ck_assert_int_eq(gl_obj->num_facets, obj->num_facets);
  ck_assert_int_eq(gl_obj->num_vertexes, obj->num_vertexes);

  for (int i = 0; i < gl_obj->num_facets; ++i) {
    ck_assert_int_eq(gl_obj->line_sizes[i], obj->facets[i].size);

    for (int j = 0; j < gl_obj->line_sizes[i]; ++j) {
      double_eq(gl_obj->facets[i][3 * j],
                obj->vertexes[obj->facets[i].id_vertexes[j]].x);
      double_eq(gl_obj->facets[i][3 * j + 1],
                obj->vertexes[obj->facets[i].id_vertexes[j]].y);
      double_eq(gl_obj->facets[i][3 * j + 2],
                obj->vertexes[obj->facets[i].id_vertexes[j]].z);
    }
  }

  ck_assert_int_eq(gl_obj->num_vertexes, obj->num_vertexes);
  for (int i = 0; i < gl_obj->num_vertexes; ++i) {
    double_eq(gl_obj->vertexes[3 * i], obj->vertexes[i].x);
    double_eq(gl_obj->vertexes[3 * i + 1], obj->vertexes[i].y);
    double_eq(gl_obj->vertexes[3 * i + 2], obj->vertexes[i].z);
  }

  free_obj(&obj);
  free_gl_obj(gl_obj);
}
END_TEST

// copy_gl_obj_transforation
START_TEST(copy_gl_obj_transforation_0) {
  obj_t *obj = read_obj("test/test_samples/test_sample_0.obj");
  ck_assert_ptr_ne(obj, NULL);

  trans_setup_t setup;
  init_trans_setup(&setup, 0, 0, 0, 1, 1, 1, 0, 0, 0);

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  // after transformation

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0

  gl_obj_t *gl_obj = gl_line_loop(obj);
  ck_assert_ptr_ne(gl_obj, NULL);

  gl_obj_t *copy = copy_gl_obj_transforation(gl_obj, &setup);
  ck_assert_ptr_ne(copy, NULL);

  free_obj(&obj);
  free_gl_obj(gl_obj);

  double_eq(copy->facets[0][0], 0.0);
  double_eq(copy->facets[0][1], 1.0);
  double_eq(copy->facets[0][2], 2.0);

  double_eq(copy->facets[0][3], 3.0);
  double_eq(copy->facets[0][4], 4.0);
  double_eq(copy->facets[0][5], 5.0);

  double_eq(copy->facets[0][6], 6.0);
  double_eq(copy->facets[0][7], 7.0);
  double_eq(copy->facets[0][8], 8.0);

  for (int i = 0; i < copy->num_vertexes; ++i) {
    double_eq(copy->facets[0][3 * i], copy->vertexes[3 * i]);
    double_eq(copy->facets[0][3 * i + 1], copy->vertexes[3 * i + 1]);
    double_eq(copy->facets[0][3 * i + 2], copy->vertexes[3 * i + 2]);
  }

  free_gl_obj(copy);
}
END_TEST

START_TEST(copy_gl_obj_transforation_1) {
  obj_t *obj = read_obj("test/test_samples/test_sample_0.obj");
  ck_assert_ptr_ne(obj, NULL);

  trans_setup_t setup;
  init_trans_setup(&setup, 1, 2, 3, 1, 1, 1, 0, 0, 0);

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  // after transformation

  // v 1.0 3.0 5.0
  // v 4.0 6.0 8.0
  // v 7.0 9.0 11.0

  gl_obj_t *gl_obj = gl_line_loop(obj);
  ck_assert_ptr_ne(gl_obj, NULL);

  gl_obj_t *copy = copy_gl_obj_transforation(gl_obj, &setup);
  ck_assert_ptr_ne(copy, NULL);

  free_obj(&obj);
  free_gl_obj(gl_obj);

  double_eq(copy->facets[0][0], 1.0);
  double_eq(copy->facets[0][1], 3.0);
  double_eq(copy->facets[0][2], 5.0);

  double_eq(copy->facets[0][3], 4.0);
  double_eq(copy->facets[0][4], 6.0);
  double_eq(copy->facets[0][5], 8.0);

  double_eq(copy->facets[0][6], 7.0);
  double_eq(copy->facets[0][7], 9.0);
  double_eq(copy->facets[0][8], 11.0);

  for (int i = 0; i < copy->num_vertexes; ++i) {
    double_eq(copy->facets[0][3 * i], copy->vertexes[3 * i]);
    double_eq(copy->facets[0][3 * i + 1], copy->vertexes[3 * i + 1]);
    double_eq(copy->facets[0][3 * i + 2], copy->vertexes[3 * i + 2]);
  }

  free_gl_obj(copy);
}
END_TEST

START_TEST(copy_gl_obj_transforation_2) {
  obj_t *obj = read_obj("test/test_samples/test_sample_0.obj");
  ck_assert_ptr_ne(obj, NULL);

  trans_setup_t setup;
  init_trans_setup(&setup, 1, 2, 3, 3, 2, 1, 0, 0, 0);

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  // after transformation

  // v 1.0 4.0 5.0
  // v 10.0 10.0 8.0
  // v 19.0 16.0 11.0

  gl_obj_t *gl_obj = gl_line_loop(obj);
  ck_assert_ptr_ne(gl_obj, NULL);

  gl_obj_t *copy = copy_gl_obj_transforation(gl_obj, &setup);
  ck_assert_ptr_ne(copy, NULL);

  free_obj(&obj);
  free_gl_obj(gl_obj);

  double_eq(copy->facets[0][0], 1.0);
  double_eq(copy->facets[0][1], 4.0);
  double_eq(copy->facets[0][2], 5.0);

  double_eq(copy->facets[0][3], 10.0);
  double_eq(copy->facets[0][4], 10.0);
  double_eq(copy->facets[0][5], 8.0);

  double_eq(copy->facets[0][6], 19.0);
  double_eq(copy->facets[0][7], 16.0);
  double_eq(copy->facets[0][8], 11.0);

  for (int i = 0; i < copy->num_vertexes; ++i) {
    double_eq(copy->facets[0][3 * i], copy->vertexes[3 * i]);
    double_eq(copy->facets[0][3 * i + 1], copy->vertexes[3 * i + 1]);
    double_eq(copy->facets[0][3 * i + 2], copy->vertexes[3 * i + 2]);
  }

  free_gl_obj(copy);
}
END_TEST

START_TEST(copy_gl_obj_transforation_3) {
  obj_t *obj = read_obj("test/test_samples/test_sample_0.obj");
  ck_assert_ptr_ne(obj, NULL);

  double C_90 = 1.57079633;
  trans_setup_t setup;
  init_trans_setup(&setup, 1, 2, 3, 3, 2, 1, C_90, 0, 0);

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  // after transformation

  // v 1.0 0.0 5.0
  // v 10.0 -3.0 11.0
  // v 19.0 -6.0 17.0

  gl_obj_t *gl_obj = gl_line_loop(obj);
  ck_assert_ptr_ne(gl_obj, NULL);

  gl_obj_t *copy = copy_gl_obj_transforation(gl_obj, &setup);
  ck_assert_ptr_ne(copy, NULL);

  free_obj(&obj);
  free_gl_obj(gl_obj);

  double_eq(copy->facets[0][0], 1.0);
  double_eq(copy->facets[0][1], 0.0);
  double_eq(copy->facets[0][2], 5.0);

  double_eq(copy->facets[0][3], 10.0);
  double_eq(copy->facets[0][4], -3.0);
  double_eq(copy->facets[0][5], 11.0);

  double_eq(copy->facets[0][6], 19.0);
  double_eq(copy->facets[0][7], -6.0);
  double_eq(copy->facets[0][8], 17.0);

  for (int i = 0; i < copy->num_vertexes; ++i) {
    double_eq(copy->facets[0][3 * i], copy->vertexes[3 * i]);
    double_eq(copy->facets[0][3 * i + 1], copy->vertexes[3 * i + 1]);
    double_eq(copy->facets[0][3 * i + 2], copy->vertexes[3 * i + 2]);
  }

  free_gl_obj(copy);
}
END_TEST

Suite *gl_obj_test(void) {
  Suite *s1 = suite_create("gl obj tests");

  TCase *gl_line_loop = tcase_create("gl_line_loop_tests");
  suite_add_tcase(s1, gl_line_loop);
  tcase_add_test(gl_line_loop, gl_line_loop_0);
  tcase_add_test(gl_line_loop, gl_line_loop_1);
  tcase_add_test(gl_line_loop, gl_line_loop_2);

  TCase *copy_gl_obj_transforation = tcase_create("copy_gl_obj_transforation");
  suite_add_tcase(s1, copy_gl_obj_transforation);
  tcase_add_test(copy_gl_obj_transforation, copy_gl_obj_transforation_0);
  tcase_add_test(copy_gl_obj_transforation, copy_gl_obj_transforation_1);
  tcase_add_test(copy_gl_obj_transforation, copy_gl_obj_transforation_2);
  tcase_add_test(copy_gl_obj_transforation, copy_gl_obj_transforation_3);

  return s1;
}
