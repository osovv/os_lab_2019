#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "mult.h"
#define h_addr h_addr_list[0]

struct Server
{
  char ip[255];
  int port;
};

bool ConvertStringToUI64(const char *str, uint64_t *val)
{
  char *end = NULL;
  unsigned long long i = strtoull(str, &end, 10);
  if (errno == ERANGE)
  {
    fprintf(stderr, "Out of uint64_t range: %s\n", str);
    return false;
  }

  if (errno != 0)
    return false;

  *val = i;
  return true;
}

int main(int argc, char **argv)
{
  uint64_t k = -1;
  uint64_t mod = -1;
  char servers[255] = {'\0'}; // TODO: explain why 255
  // Max length of filename is 255 chars (ext4)
  // Max length of pathname is 4095 chars. (limit of kernel)

  while (true)
  {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"k", required_argument, 0, 0},
                                      {"mod", required_argument, 0, 0},
                                      {"servers", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, &option_index);

    if (c == -1)
      break;

    switch (c)
    {
    case 0:
    {
      switch (option_index)
      {
      case 0:
        ConvertStringToUI64(optarg, &k);
        if (k < 0)
        {
          printf("k should be a non-negative number!\n");
          return -1;
        }
        break;
      case 1:
        ConvertStringToUI64(optarg, &mod);
        if (mod < 1)
        {
          printf("mod should be a non-negative number!\n");
          return -1;
        }
        break;
      case 2:
        // TODO: your code here
        memcpy(servers, optarg, strlen(optarg));
        break;
      default:
        printf("Index %d is out of options\n", option_index);
      }
    }
    break;

    case '?':
      printf("Arguments error\n");
      break;
    default:
      fprintf(stderr, "getopt returned character code 0%o?\n", c);
    }
  }

  if (k == -1 || mod == -1 || !strlen(servers))
  {
    fprintf(stderr, "Using: %s --k 1000 --mod 5 --servers /path/to/file\n",
            argv[0]);
    return 1;
  }

  FILE *fp = fopen(servers, "r");
  if (fp == NULL)
  {
    printf("Could not open file %s\n", servers);
    return 0;
  }
  unsigned int servers_num = 0;
  char c;
  for (c = getc(fp); c != EOF; c = getc(fp))
    if (c == '\n')
      servers_num = servers_num + 1;
  fclose(fp);

  struct Server *to = malloc(sizeof(struct Server) * servers_num);

  int i = 0;
  char buffer[256];

  fp = fopen(servers, "r");

  while (fgets(buffer, sizeof(buffer), fp))
  {

    strcpy(to[i].ip, strtok(buffer, ":"));
    to[i].port = atoi(strtok(NULL, ":"));
    printf("Client #%d %s:%d\n", i + 1, to[i].ip, to[i].port);
    i++;
  }
  fclose(fp);
  int i;

  uint64_t step = k / servers_num;

  uint64_t result = 1;
  for (int i = 0; i < servers_num; i++)
  {
    struct hostent *hostname = gethostbyname(to[i].ip);
    if (hostname == NULL)
    {
      fprintf(stderr, "gethostbyname failed with %s\n", to[i].ip);
      exit(1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(to[i].port);
    server.sin_addr.s_addr = *((unsigned long *)hostname->h_addr);

    int sck = socket(AF_INET, SOCK_STREAM, 0);
    if (sck < 0)
    {
      fprintf(stderr, "Socket creation failed!\n");
      exit(1);
    }

    if (connect(sck, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
      fprintf(stderr, "Connection failed\n");
      exit(1);
    }

    // TODO: for one server
    // parallel between servers
    uint64_t begin = (uint64_t)i * step;
    uint64_t end = (uint64_t)(i + 1) * step;
    if (i == servers_num - 1 && k % servers_num != 0)
      end = k;

    char task[sizeof(uint64_t) * 3];
    memcpy(task, &begin, sizeof(uint64_t));
    memcpy(task + sizeof(uint64_t), &end, sizeof(uint64_t));
    memcpy(task + 2 * sizeof(uint64_t), &mod, sizeof(uint64_t));

    if (send(sck, task, sizeof(task), 0) < 0)
    {
      fprintf(stderr, "Send failed\n");
      exit(1);
    }

    char response[sizeof(uint64_t)];
    if (recv(sck, response, sizeof(response), 0) < 0)
    {
      fprintf(stderr, "Recieve failed\n");
      exit(1);
    }

    // TODO: from one server
    // unite results
    uint64_t answer = 0;
    memcpy(&answer, response, sizeof(uint64_t));
    printf("answer: %llu\n", answer);

    result = result * answer;
    result = result % mod;

    close(sck);
  }
  pritnf("Result: %llu", result);

  free(to);

  return 0;
}
