#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>

uint64_t r1 = 1;
pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;

uint64_t r2 = 1;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;

void do_one_thing()
{
	pthread_mutex_lock(&mut1);
	for (int i = 0; i < 500000; i++)
		;
	pthread_mutex_lock(&mut2);
	r2++;
	pthread_mutex_unlock(&mut2);
	pthread_mutex_unlock(&mut1);
}
void do_another_thing()
{
	pthread_mutex_lock(&mut2);
	for (int i = 0; i < 500000; i++)
		;
	pthread_mutex_lock(&mut1);
	r2--;
	pthread_mutex_unlock(&mut1);
	pthread_mutex_unlock(&mut2);
}

int main()
{
	pthread_t t1, t2;

	printf("Begin r1 = %d, r2 = %d\n", r1, r2);
	if (pthread_create(&t1, NULL, (void *)do_one_thing, NULL) != 0)
	{
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&t2, NULL, (void *)do_another_thing, NULL) != 0)
	{
		perror("pthread_create");
		exit(1);
	}
	if (pthread_join(t1, NULL) != 0)
	{
		perror("pthread_join");
		exit(1);
	}
	if (pthread_join(t2, NULL) != 0)
	{
		perror("pthread_join");
		exit(1);
	}
	printf("End r1 = %d, r2 = %d\n", r1, r2);
	return 0;
}