#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <getopt.h>

struct FactArgs
{
	uint64_t begin;
	uint64_t end;
	uint64_t mod;
	uint64_t *work;
};

uint64_t result = 1;
uint64_t fact = 1;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void *ThreadFact(struct FactArgs *args)
{
	unsigned long k;
	pthread_mutex_lock(&mut);
	uint64_t work, fact, begin = args->begin, end = args->end, mod = args->mod;
	work = *(args->work);
	for (k = begin; k <= end; k++)
	{
		work = (uint64_t)(work * k) % mod;
	}
	*(args->work) = work;
	pthread_mutex_unlock(&mut);
}

int main(int argc, char **argv)
{
	uint32_t k = -1;
	uint32_t pnum = -1;
	uint32_t mod = -1;

	static struct option options[] = {
		{"k", required_argument, NULL, 'k'},
		{"pnum", required_argument, NULL, 0},
		{"mod", required_argument, NULL, 0},
		{NULL, 0, NULL, 0}};

	int c = 0;
	int option_index = 0;
	while ((c = getopt_long(argc, argv, "", options, &option_index)) != -1)
	{
		switch (c)
		{
		case 'k':
			k = (uint32_t)atoi(optarg);
			if (k < 0)
			{
				printf("K must be a non-negative integer.\n");
				return -1;
			}
			break;
		case 0:
			switch (option_index)
			{
			case 1:
				pnum = (uint32_t)atoi(optarg);
				if (pnum < 1)
				{
					printf("Pnum must be a positive integer.\n");
					return -1;
				}
				break;
			case 2:
				mod = (uint32_t)atoi(optarg);
				if (mod < 1)
				{
					printf("Mod must be a positive integer.\n");
					return -1;
				}
				break;
			}
		}
	}

	if (k == -1 || pnum == -1 || mod == -1)
	{
		printf("Usage: %s -k \"num\" --pnum=\"num\" --mod=\"num\" \n",
			   argv[0]);
		return 1;
	}

	if (mod <= k)
	{
		printf("All done, fact(%d) mod %d = %d\n", k, mod, 0);
		return 0;
	}

	pthread_t threads[pnum];
	struct FactArgs args[pnum];
	uint64_t n = k / pnum;
	char indivisible = k % pnum == 0 ? '0' : '1';

	for (int i = 0; i < pnum; i++)
	{
		args[i].begin = (uint64_t)i * n + 1;
		args[i].end = (uint64_t)(i + 1) * n;
		args[i].mod = mod;
		args[i].work = &result;
		if (i == pnum - 1 && indivisible == '1')
		{
			args[i].end = (uint64_t)k;
		}
		if (pthread_create(&threads[i], NULL, (void *)ThreadFact, (void *)&args[i]) != 0)
		{
			perror("pthread_create");
			exit(1);
		}
	}

	for (int i = 0; i < pnum; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			perror("pthread_join");
			exit(1);
		}
	}
	printf("All done, fact(%d) mod %d = %d\n", k, mod, result);
	return 0;
}
