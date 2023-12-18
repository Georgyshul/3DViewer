#include "../back/obj/transformation.h"

#include <math.h>
#include <stdbool.h>

#include "../back/io_obj/io_obj.h"
#include "../back/obj/obj.h"
#include "test.h"

// transformation
START_TEST(transformation_0) {
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

  double vertex1[3] = {0, 1, 2};
  transformation(vertex1, 1, &setup);

  double_eq(vertex1[0], 0.0);
  double_eq(vertex1[1], 1.0);
  double_eq(vertex1[2], 2.0);

  double vertex2[3] = {3, 4, 5};
  transformation(vertex2, 1, &setup);

  double_eq(vertex2[0], 3.0);
  double_eq(vertex2[1], 4.0);
  double_eq(vertex2[2], 5.0);

  double vertex3[3] = {6, 7, 8};
  transformation(vertex3, 1, &setup);

  double_eq(vertex3[0], 6.0);
  double_eq(vertex3[1], 7.0);
  double_eq(vertex3[2], 8.0);
}
END_TEST

START_TEST(transformation_1) {
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

  double vertex1[3] = {0, 1, 2};
  transformation(vertex1, 1, &setup);

  double_eq(vertex1[0], 1.0);
  double_eq(vertex1[1], 3.0);
  double_eq(vertex1[2], 5.0);

  double vertex2[3] = {3, 4, 5};
  transformation(vertex2, 1, &setup);

  double_eq(vertex2[0], 4.0);
  double_eq(vertex2[1], 6.0);
  double_eq(vertex2[2], 8.0);

  double vertex3[3] = {6, 7, 8};
  transformation(vertex3, 1, &setup);

  double_eq(vertex3[0], 7.0);
  double_eq(vertex3[1], 9.0);
  double_eq(vertex3[2], 11.0);
}
END_TEST

START_TEST(transformation_2) {
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

  double vertex1[3] = {0, 1, 2};
  transformation(vertex1, 1, &setup);

  double_eq(vertex1[0], 1.0);
  double_eq(vertex1[1], 4.0);
  double_eq(vertex1[2], 5.0);

  double vertex2[3] = {3, 4, 5};
  transformation(vertex2, 1, &setup);

  double_eq(vertex2[0], 10.0);
  double_eq(vertex2[1], 10.0);
  double_eq(vertex2[2], 8.0);

  double vertex3[3] = {6, 7, 8};
  transformation(vertex3, 1, &setup);

  double_eq(vertex3[0], 19.0);
  double_eq(vertex3[1], 16.0);
  double_eq(vertex3[2], 11.0);
}
END_TEST

START_TEST(transformation_3) {
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

  double vertex1[3] = {0, 1, 2};
  transformation(vertex1, 1, &setup);

  double_eq(vertex1[0], 1.0);
  double_eq(vertex1[1], 0.0);
  double_eq(vertex1[2], 5.0);

  double vertex2[3] = {3, 4, 5};
  transformation(vertex2, 1, &setup);

  double_eq(vertex2[0], 10.0);
  double_eq(vertex2[1], -3.0);
  double_eq(vertex2[2], 11.0);

  double vertex3[3] = {6, 7, 8};
  transformation(vertex3, 1, &setup);

  double_eq(vertex3[0], 19.0);
  double_eq(vertex3[1], -6.0);
  double_eq(vertex3[2], 17.0);
}
END_TEST

START_TEST(transformation_4) {
  double C_90 = 1.57079633;
  trans_setup_t setup;
  init_trans_setup(&setup, 0, 0, 0, 1, 1, 1, 0, C_90, 0);

  // v 0.0 1.0 2.0 1.0
  // v 3.0 4.0 5.0 1.0
  // v 6.0 7.0 8.0 1.0
  //
  // f v1 v2 v3

  // after transformation

  // v 2.0 1.0 0.0
  // v 5.0 4.0 -3.0
  // v 8.0 7.0 -6.0

  double vertex1[3] = {0, 1, 2};
  transformation(vertex1, 1, &setup);

  double_eq(vertex1[0], 2);
  double_eq(vertex1[1], 1);
  double_eq(vertex1[2], 0);

  double vertex2[3] = {3, 4, 5};
  transformation(vertex2, 1, &setup);

  double_eq(vertex2[0], 5);
  double_eq(vertex2[1], 4);
  double_eq(vertex2[2], -3);

  double vertex3[3] = {6, 7, 8};
  transformation(vertex3, 1, &setup);

  double_eq(vertex3[0], 8);
  double_eq(vertex3[1], 7);
  double_eq(vertex3[2], -6);
}
END_TEST

Suite *transformation_test(void) {
  Suite *s1 = suite_create("transformation tests");

  TCase *transformation = tcase_create("transformation tests");
  suite_add_tcase(s1, transformation);
  tcase_add_test(transformation, transformation_0);
  tcase_add_test(transformation, transformation_1);
  tcase_add_test(transformation, transformation_2);
  tcase_add_test(transformation, transformation_3);
  tcase_add_test(transformation, transformation_4);

  return s1;
}