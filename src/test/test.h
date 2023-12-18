#ifndef SRC_TEST_TEST_H_
#define SRC_TEST_TEST_H_

#include <check.h>

void double_eq(double x, double y);

Suite *io_test(void);
Suite *transformation_test(void);
Suite *gl_obj_test(void);

#endif  // SRC_TEST_TEST_H_
