#include "revert_string.h"
#include "stdlib.h"
#include "stdio.h"

void RevertString(char *str)
{
	// your code here
    int count, end, i;
    count = 0;
    while (str[count] != '\0')
        count++;
    end = count - 1;
    char c;
    for (i = 0; i < count / 2; i++)
    {
        c = str[i];
        str[i] = str[end-i];
        str[end-i] = c;
    }
    /*
    char* tmp;
    tmp = (char*)malloc((count+1) * sizeof(char));
    for (i = 0; i < count; i++)
    {
        tmp[i] = str[end-i];
    }
    for (i = 0; i < count; i++)
    {
        str[i] = tmp[i];
    }
    tmp[i] = '\0';
    free(tmp);
    */
}

