#include "sum.h"
#include "stdint.h"
int Sum(const struct SumArgs *args)
{
  int sum = 0;
  for (int i = args->begin; i < args->end; i++)
  {
    sum = (sum + args->array[i]) % UINT32_MAX;
  }
  return sum;
}
