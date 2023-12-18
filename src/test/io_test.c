#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "../back/io_obj/io_obj.h"
#include "../back/obj/obj.h"
#include "test.h"

// read_obj
START_TEST(read_obj_0) {
  obj_t *obj = read_obj("test/test_samples/test_sample_0.obj");

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  ck_assert_ptr_ne(obj, NULL);
  ck_assert_int_eq(obj->num_vertexes, 3);

  double_eq(obj->vertexes[0].x, 0.0);
  double_eq(obj->vertexes[0].y, 1.0);
  double_eq(obj->vertexes[0].z, 2.0);

  double_eq(obj->vertexes[1].x, 3.0);
  double_eq(obj->vertexes[1].y, 4.0);
  double_eq(obj->vertexes[1].z, 5.0);

  double_eq(obj->vertexes[2].x, 6.0);
  double_eq(obj->vertexes[2].y, 7.0);
  double_eq(obj->vertexes[2].z, 8.0);

  ck_assert_int_eq(obj->num_facets, 1);

  ck_assert_int_eq(obj->facets[0].size, 3);

  ck_assert_int_eq(obj->facets[0].id_vertexes[0], 0);
  ck_assert_int_eq(obj->facets[0].id_vertexes[1], 1);
  ck_assert_int_eq(obj->facets[0].id_vertexes[2], 2);

  free_obj(&obj);
}
END_TEST

START_TEST(read_obj_1) {
  obj_t *obj = read_obj("test/test_samples/test_sample_1.obj");

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f fv1 v2 v3

  ck_assert_ptr_eq(obj, NULL);
}
END_TEST

START_TEST(read_obj_2) {
  obj_t *obj = read_obj("test/test_samples/test_sample_2.obj");

  // v 0.0 1.0 2.0 1.0
  //
  // f v1 v2

  ck_assert_ptr_eq(obj, NULL);
}
END_TEST

START_TEST(read_obj_3) {
  obj_t *obj = read_obj("test/test_samples/test_sample_3.obj");

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  //
  // f v1 v2 v3

  ck_assert_ptr_eq(obj, NULL);
}
END_TEST

START_TEST(read_obj_4) {
  obj_t *obj = read_obj("test/test_samples/test_sample_4.obj");

  // v 234.34546 12323445.23414 123234.2342
  // v -56756.4354355 0 456.345456
  // v 3454.234 534.234254 -234.345234
  // v -456.3454252 -1.0 -73465.344654
  //
  // f v4 v2 v1 v3
  // f v1 v2 v3
  // f v1 v4 v3

  ck_assert_ptr_ne(obj, NULL);
  ck_assert_int_eq(obj->num_vertexes, 4);

  double_eq(obj->vertexes[0].x, 234.34546);
  double_eq(obj->vertexes[0].y, 12323445.23414);
  double_eq(obj->vertexes[0].z, 123234.2342);

  double_eq(obj->vertexes[1].x, -56756.4354355);
  double_eq(obj->vertexes[1].y, 0);
  double_eq(obj->vertexes[1].z, 456.345456);

  double_eq(obj->vertexes[2].x, 3454.234);
  double_eq(obj->vertexes[2].y, 534.234254);
  double_eq(obj->vertexes[2].z, -234.345234);

  double_eq(obj->vertexes[3].x, -456.3454252);
  double_eq(obj->vertexes[3].y, -1.0);
  double_eq(obj->vertexes[3].z, -73465.344654);

  ck_assert_int_eq(obj->num_facets, 3);

  facet_t *facet;
  facet = &(obj->facets[0]);
  ck_assert_int_eq(facet->size, 4);

  ck_assert_int_eq(facet->id_vertexes[0], 3);
  ck_assert_int_eq(facet->id_vertexes[1], 1);
  ck_assert_int_eq(facet->id_vertexes[2], 0);
  ck_assert_int_eq(facet->id_vertexes[3], 2);

  facet = &(obj->facets[1]);
  ck_assert_int_eq(facet->size, 3);

  ck_assert_int_eq(facet->id_vertexes[0], 0);
  ck_assert_int_eq(facet->id_vertexes[1], 1);
  ck_assert_int_eq(facet->id_vertexes[2], 2);

  facet = &(obj->facets[2]);
  ck_assert_int_eq(facet->size, 3);

  ck_assert_int_eq(facet->id_vertexes[0], 0);
  ck_assert_int_eq(facet->id_vertexes[1], 3);
  ck_assert_int_eq(facet->id_vertexes[2], 2);

  free_obj(&obj);
}
END_TEST

START_TEST(read_obj_5) {
  obj_t *obj = read_obj("test/test_samples/test_sample_5.obj");

  // v   7       1 198435
  // v     0      1       0
  // v 1 12.2           5
  //
  // f    v 1  v 2    v 3

  ck_assert_ptr_ne(obj, NULL);
  ck_assert_int_eq(obj->num_vertexes, 3);

  double_eq(obj->vertexes[0].x, 7);
  double_eq(obj->vertexes[0].y, 1);
  double_eq(obj->vertexes[0].z, 198435);

  double_eq(obj->vertexes[1].x, 0);
  double_eq(obj->vertexes[1].y, 1);
  double_eq(obj->vertexes[1].z, 0);

  double_eq(obj->vertexes[2].x, 1);
  double_eq(obj->vertexes[2].y, 12.2);
  double_eq(obj->vertexes[2].z, 5);

  ck_assert_int_eq(obj->num_facets, 1);

  facet_t *facet;
  facet = &(obj->facets[0]);
  ck_assert_int_eq(facet->size, 3);

  ck_assert_int_eq(facet->id_vertexes[0], 0);
  ck_assert_int_eq(facet->id_vertexes[1], 1);
  ck_assert_int_eq(facet->id_vertexes[2], 2);

  free_obj(&obj);
}
END_TEST

START_TEST(read_obj_6) {
  obj_t *obj = read_obj("test/test_samples/test_sample_6.obj");

  // v 1._.23 12 23

  ck_assert_ptr_eq(obj, NULL);
}
END_TEST

START_TEST(read_obj_7) {
  obj_t *obj = read_obj("test/test_samples/test_sample_7.obj");

  // v 12 34 f

  ck_assert_ptr_eq(obj, NULL);
}
END_TEST

START_TEST(read_obj_8) {
  obj_t *obj = read_obj("test/test_samples/test_sample_8.obj");

  ck_assert_ptr_ne(obj, NULL);
  free_obj(&obj);
}
END_TEST

START_TEST(read_obj_9) {
  obj_t *obj = read_obj("test/test_samples/test_sample_9.obj");

  ck_assert_ptr_ne(obj, NULL);
  free_obj(&obj);
}
END_TEST

// write_obj
START_TEST(write_obj_0) {
  obj_t *obj = read_obj("test/test_samples/test_sample_0.obj");
  ck_assert_ptr_ne(obj, NULL);

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  bool error = write_obj("test/test_samples/write.obj", obj, NULL);
  ck_assert(!error);
  free_obj(&obj);

  obj = read_obj("test/test_samples/write.obj");

  ck_assert_ptr_ne(obj, NULL);
  ck_assert_int_eq(obj->num_vertexes, 3);

  double_eq(obj->vertexes[0].x, 0.0);
  double_eq(obj->vertexes[0].y, 1.0);
  double_eq(obj->vertexes[0].z, 2.0);

  double_eq(obj->vertexes[1].x, 3.0);
  double_eq(obj->vertexes[1].y, 4.0);
  double_eq(obj->vertexes[1].z, 5.0);

  double_eq(obj->vertexes[2].x, 6.0);
  double_eq(obj->vertexes[2].y, 7.0);
  double_eq(obj->vertexes[2].z, 8.0);

  ck_assert_int_eq(obj->num_facets, 1);

  ck_assert_int_eq(obj->facets[0].size, 3);

  ck_assert_int_eq(obj->facets[0].id_vertexes[0], 0);
  ck_assert_int_eq(obj->facets[0].id_vertexes[1], 1);
  ck_assert_int_eq(obj->facets[0].id_vertexes[2], 2);

  free_obj(&obj);
}
END_TEST

START_TEST(write_obj_1) {
  trans_setup_t setup;
  init_trans_setup(&setup, 0, 0, 0, 1, 1, 1, 0, 0, 0);

  obj_t *obj = read_obj("test/test_samples/test_sample_0.obj");
  ck_assert_ptr_ne(obj, NULL);

  // before transformation

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  // after transformation

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0

  bool error = write_obj("test/test_samples/write1.obj", obj, &setup);
  ck_assert(!error);
  free_obj(&obj);

  obj = read_obj("test/test_samples/write1.obj");

  ck_assert_ptr_ne(obj, NULL);
  ck_assert_int_eq(obj->num_vertexes, 3);

  double_eq(obj->vertexes[0].x, 0.0);
  double_eq(obj->vertexes[0].y, 1.0);
  double_eq(obj->vertexes[0].z, 2.0);

  double_eq(obj->vertexes[1].x, 3.0);
  double_eq(obj->vertexes[1].y, 4.0);
  double_eq(obj->vertexes[1].z, 5.0);

  double_eq(obj->vertexes[2].x, 6.0);
  double_eq(obj->vertexes[2].y, 7.0);
  double_eq(obj->vertexes[2].z, 8.0);

  ck_assert_int_eq(obj->num_facets, 1);

  ck_assert_int_eq(obj->facets[0].size, 3);

  ck_assert_int_eq(obj->facets[0].id_vertexes[0], 0);
  ck_assert_int_eq(obj->facets[0].id_vertexes[1], 1);
  ck_assert_int_eq(obj->facets[0].id_vertexes[2], 2);

  free_obj(&obj);
}
END_TEST

START_TEST(write_obj_2) {
  trans_setup_t setup;
  init_trans_setup(&setup, 1, 2, 3, 1, 1, 1, 0, 0, 0);

  obj_t *obj = read_obj("test/test_samples/test_sample_0.obj");
  ck_assert_ptr_ne(obj, NULL);

  // before transformation

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  // after transformation

  // v 1.0 3.0 5.0
  // v 4.0 6.0 8.0
  // v 7.0 9.0 11.0

  bool error = write_obj("test/test_samples/write2.obj", obj, &setup);
  ck_assert(!error);
  free_obj(&obj);

  obj = read_obj("test/test_samples/write2.obj");

  ck_assert_ptr_ne(obj, NULL);
  ck_assert_int_eq(obj->num_vertexes, 3);

  double_eq(obj->vertexes[0].x, 1.0);
  double_eq(obj->vertexes[0].y, 3.0);
  double_eq(obj->vertexes[0].z, 5.0);

  double_eq(obj->vertexes[1].x, 4.0);
  double_eq(obj->vertexes[1].y, 6.0);
  double_eq(obj->vertexes[1].z, 8.0);

  double_eq(obj->vertexes[2].x, 7.0);
  double_eq(obj->vertexes[2].y, 9.0);
  double_eq(obj->vertexes[2].z, 11.0);

  ck_assert_int_eq(obj->num_facets, 1);

  ck_assert_int_eq(obj->facets[0].size, 3);

  ck_assert_int_eq(obj->facets[0].id_vertexes[0], 0);
  ck_assert_int_eq(obj->facets[0].id_vertexes[1], 1);
  ck_assert_int_eq(obj->facets[0].id_vertexes[2], 2);

  free_obj(&obj);
}
END_TEST

START_TEST(write_obj_3) {
  trans_setup_t setup;
  init_trans_setup(&setup, 1, 2, 3, 3, 2, 1, 0, 0, 0);

  obj_t *obj = read_obj("test/test_samples/test_sample_0.obj");
  ck_assert_ptr_ne(obj, NULL);

  // before transformation

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  // after transformation

  // v 1.0 4.0 5.0
  // v 10.0 10.0 8.0
  // v 19.0 16.0 11.0

  bool error = write_obj("test/test_samples/write3.obj", obj, &setup);
  ck_assert(!error);
  free_obj(&obj);

  obj = read_obj("test/test_samples/write3.obj");

  ck_assert_ptr_ne(obj, NULL);
  ck_assert_int_eq(obj->num_vertexes, 3);

  double_eq(obj->vertexes[0].x, 1.0);
  double_eq(obj->vertexes[0].y, 4.0);
  double_eq(obj->vertexes[0].z, 5.0);

  double_eq(obj->vertexes[1].x, 10.0);
  double_eq(obj->vertexes[1].y, 10.0);
  double_eq(obj->vertexes[1].z, 8.0);

  double_eq(obj->vertexes[2].x, 19.0);
  double_eq(obj->vertexes[2].y, 16.0);
  double_eq(obj->vertexes[2].z, 11.0);

  ck_assert_int_eq(obj->num_facets, 1);

  ck_assert_int_eq(obj->facets[0].size, 3);

  ck_assert_int_eq(obj->facets[0].id_vertexes[0], 0);
  ck_assert_int_eq(obj->facets[0].id_vertexes[1], 1);
  ck_assert_int_eq(obj->facets[0].id_vertexes[2], 2);

  free_obj(&obj);
}
END_TEST

START_TEST(write_obj_4) {
  double C_90 = 1.57079633;
  trans_setup_t setup;
  init_trans_setup(&setup, 1, 2, 3, 3, 2, 1, C_90, 0, 0);

  obj_t *obj = read_obj("test/test_samples/test_sample_0.obj");
  ck_assert_ptr_ne(obj, NULL);

  // before transformation

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  // after transformation

  // v 1.0 0.0 5.0
  // v 10.0 -3.0 11.0
  // v 19.0 -6.0 17.0

  bool error = write_obj("test/test_samples/write4.obj", obj, &setup);
  ck_assert(!error);
  free_obj(&obj);

  obj = read_obj("test/test_samples/write4.obj");

  ck_assert_ptr_ne(obj, NULL);
  ck_assert_int_eq(obj->num_vertexes, 3);

  double_eq(obj->vertexes[0].x, 1.0);
  double_eq(obj->vertexes[0].y, 0.0);
  double_eq(obj->vertexes[0].z, 5.0);

  double_eq(obj->vertexes[1].x, 10.0);
  double_eq(obj->vertexes[1].y, -3.0);
  double_eq(obj->vertexes[1].z, 11.0);

  double_eq(obj->vertexes[2].x, 19.0);
  double_eq(obj->vertexes[2].y, -6.0);
  double_eq(obj->vertexes[2].z, 17.0);

  ck_assert_int_eq(obj->num_facets, 1);

  ck_assert_int_eq(obj->facets[0].size, 3);

  ck_assert_int_eq(obj->facets[0].id_vertexes[0], 0);
  ck_assert_int_eq(obj->facets[0].id_vertexes[1], 1);
  ck_assert_int_eq(obj->facets[0].id_vertexes[2], 2);

  free_obj(&obj);
}
END_TEST

Suite *io_test(void) {
  Suite *s1 = suite_create("io tests");

  TCase *read_obj = tcase_create("read obj tests");
  suite_add_tcase(s1, read_obj);
  tcase_add_test(read_obj, read_obj_0);
  tcase_add_test(read_obj, read_obj_1);
  tcase_add_test(read_obj, read_obj_2);
  tcase_add_test(read_obj, read_obj_3);
  tcase_add_test(read_obj, read_obj_4);
  tcase_add_test(read_obj, read_obj_5);
  tcase_add_test(read_obj, read_obj_6);
  tcase_add_test(read_obj, read_obj_7);
  tcase_add_test(read_obj, read_obj_8);
  tcase_add_test(read_obj, read_obj_9);

  TCase *write_obj = tcase_create("write obj with transformation tests");
  suite_add_tcase(s1, write_obj);
  tcase_add_test(write_obj, write_obj_0);
  tcase_add_test(write_obj, write_obj_1);
  tcase_add_test(write_obj, write_obj_2);
  tcase_add_test(write_obj, write_obj_3);
  tcase_add_test(write_obj, write_obj_4);

  return s1;
}
