
#include <check.h>
#include <stdlib.h>
#include "../src/fft.h"

START_TEST(test_fft_recursive) {
  int n = 4;
  int i;
  double f_x[] = {-10., 1., 3., 0.};

  double y_erg_real[] = {-6., -13., -8., -13.};
  double y_erg_imag[] = {0., 1., 0., -1.};

  mycomplex *vec = malloc(sizeof(mycomplex) * n);
  mycomplex *y = malloc(sizeof(mycomplex) * n);
  for (i = 0; i < n; ++i) {
    vec[i].real = f_x[i];
    vec[i].imag = 0;
  }
  recursive_fft(vec, y, n, 0);
  for (i = 0; i < n; ++i) {
    ck_assert_msg(y[i].real == y_erg_real[i], 
        "expected: %f - found: %f", y[i].real, y_erg_real[i]);
    ck_assert_msg(y[i].imag == y_erg_imag[i], 
        "expected: %f - found: %f", y[i].imag, y_erg_imag[i]);
  }
  free(vec);
  free(y);
}
END_TEST

Suite *fft_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("FFT");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fft_recursive);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = fft_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
