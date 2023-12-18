#include "test.h"

int main(void) {
  int nf = 0;

  Suite *s1 = io_test();
  Suite *s2 = transformation_test();
  Suite *s3 = gl_obj_test();

  SRunner *sr1 = srunner_create(s1);
  SRunner *sr2 = srunner_create(s2);
  SRunner *sr3 = srunner_create(s3);

  srunner_run_all(sr1, CK_ENV);
  srunner_run_all(sr2, CK_ENV);
  srunner_run_all(sr3, CK_ENV);

  nf |= srunner_ntests_failed(sr1);
  nf |= srunner_ntests_failed(sr2);
  nf |= srunner_ntests_failed(sr3);

  srunner_free(sr1);
  srunner_free(sr2);
  srunner_free(sr3);

  return nf == 0 ? 0 : 1;
}

void double_eq(double x, double y) {
  double difference = fabs(x - y);
  ck_assert(difference < 1e-7);
}