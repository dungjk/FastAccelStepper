#include <stdio.h>
#include <math.h>

#include <PoorManFloat.h>

void out(const char *name, float x, pmf_logarithmic value) {
  float ld2 = log2(x);
  float pmf = ld2 * 512;
  int16_t pmf_int = (uint16_t)round(pmf);
  puts("");
  printf("// %s = %f  %d = 0x%04x\n", name, pmf, pmf_int, pmf_int);
  if (pmf_int != value) {
    printf("// %s should be 0x%04x\n", name, pmf_int);
  }
  printf("#define %s ((pmf_logarithmic)0x%04x)\n", name, value);
  float back = pow(2.0, float(pmf_int) / 512);
  printf("// => converted back => %.2f\n", back);
}

int main() {
  puts("// Autogenerated by extras/gen_pmf_const/main");
  puts("// DO NOT EDIT");
  puts("#ifndef POORMANFLOATCONST_H");
  puts("#define POORMANFLOATCONST_H");
  puts("");
  puts("#include <PoorManFloat.h>");

  pmf_logarithmic x;

  x = pmfl_from((uint8_t)1);
  out("PMF_CONST_1", 1.0, x);

  x = pmfl_shr(pmfl_from((uint8_t)3), 1);
  out("PMF_CONST_3_DIV_2", 1.5, x);

  x = pmfl_multiply(pmfl_from((uint32_t)16e6), pmfl_from((uint32_t)8e6));
  out("PMF_CONST_128E12", 1.28e14, x);

  x = pmfl_from((uint32_t)16e6);
  out("PMF_CONST_16E6", 1.6e7, x);

  x = pmfl_from((uint16_t)500);
  out("PMF_CONST_500", 500, x);

  x = pmfl_from((uint16_t)1000);
  out("PMF_CONST_1000", 1000, x);

  x = pmfl_from((uint16_t)2000);
  out("PMF_CONST_2000", 2000, x);

  x = pmfl_from((uint16_t)32000);
  out("PMF_CONST_32000", 32000, x);

  x = pmfl_multiply(pmfl_from((uint32_t)16e6), pmfl_from((uint32_t)8e6));
  x = pmfl_sqrt(x);
  out("PMF_CONST_16E6_DIV_SQRT_OF_2", 1.6e7 / sqrt(2), x);

  x = pmfl_from((uint32_t)21e6);
  out("PMF_CONST_21E6", 21e6, x);

  x = pmfl_from((uint16_t)42000);
  out("PMF_CONST_42000", 42000, x);

  x = pmfl_divide(pmfl_from((uint32_t)21e6), pmfl_sqrt(pmfl_from((uint8_t)2)));
  out("PMF_CONST_21E6_DIV_SQRT_OF_2", 21e6 / sqrt(2), x);

  x = pmfl_square(pmfl_from((uint32_t)21e6));
  x = pmfl_shr(x, 1);
  out("PMF_CONST_2205E11", 2.205e14, x);

  x = pmfl_from(__UINT32_MAX__);
  out("PMF_CONST_UINT32_MAX", __UINT32_MAX__, x);

  x = pmfl_from((uint16_t)__UINT16_MAX__);
  out("PMF_CONST_UINT16_MAX", __UINT16_MAX__, x);

  puts("");
  puts("// used in PoorManFloat.cpp as example");
  printf("// ");
  x = pmfl_from((uint16_t)15373);
  out("PMF_CONST_15373", 15373, x);

  puts("#endif");

  return 0;
}
