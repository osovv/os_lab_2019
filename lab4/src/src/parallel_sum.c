#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#include "from_lab3/find_min_max.h"
#include <sys/types.h>
#include <getopt.h>
#include "sum.h"

void *ThreadSum(void *args)
{
  struct SumArgs *sum_args = (struct SumArgs *)args;
  return (void *)(size_t)Sum(sum_args);
}

int main(int argc, char **argv)
{
  uint32_t threads_num = -1;
  uint32_t array_size = -1;
  uint32_t seed = -1;

  static struct option options[] = {
      {"threads_num", required_argument, NULL, 0},
      {"array_size", required_argument, NULL, 0},
      {"seed", required_argument, NULL, 0},
      {NULL, 0, NULL, 0}};

  int c = 0;
  int option_index = 0;
  while ((c = getopt_long(argc, argv, "", options, &option_index)) != -1)
  {
    switch (c)
    {
    case 0:
      switch (option_index)
      {
      case 0:
        threads_num = (uint32_t)atoi(optarg);
        if (threads_num < 1)
        {
          printf("Threads number must be a positive integer.\n");
          return -1;
        }
        break;
      case 1:
        array_size = (uint32_t)atoi(optarg);
        if (array_size < 1)
        {
          printf("Array size must be a positive integer.\n");
          return -1;
        }
        break;
      case 2:
        seed = (uint32_t)atoi(optarg);
        if (seed == 0 && strcmp(optarg, "0") != 0)
        {
          printf("Seed must be a non-negative integer.\n");
          return -1;
        }
        if (seed < 0)
        {
          printf("Seed must be a non-negative integer.\n");
          return -1;
        }
        break;
      }
    }
  }

  if (seed == -1 || array_size == -1 || threads_num == -1)
  {
    printf("Usage: %s --seed \"num\" --array_size \"num\" --threads_num \"num\" \n",
           argv[0]);
    return 1;
  }

  if (threads_num > array_size)
  {
    printf("Threads number cant be bigger than array size.\n");
    return 1;
  }
  printf("Threads num: %d\n", threads_num);
  printf("Array size: %d\n", array_size);

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);
  for (int i = 0; i < array_size; i++)
    array[i] = 10;
  //   printf("%d ", array[i]);
  // printf("\n");

  pthread_t threads[threads_num];
  struct SumArgs args[threads_num];

  int n = (int)array_size / threads_num;
  args->array = array;
  for (uint32_t i = 0; i < threads_num; i++)
  {
    args->begin = (int)n * i;
    args->end = (int)n * (i + 1);
    printf("%d -- %d\n", args->begin, args->end);
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args))
    {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  struct timeval start_time;
  gettimeofday(&start_time, NULL);

  int total_sum = 0;
  for (uint32_t i = 0; i < threads_num; i++)
  {
    int sum = 0;
    pthread_join(threads[i], (void **)&sum);
    printf("%d\n", sum);
    total_sum = (total_sum + sum) % UINT32_MAX;
  }

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  free(array);
  printf("Total: %d\n", total_sum);
  printf("Elapsed time: %fms\n", elapsed_time);
  return 0;
}
