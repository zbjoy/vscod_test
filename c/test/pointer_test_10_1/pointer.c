#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char* c1 = (char*)malloc(10 * sizeof(char));
    char* c2 = (char*)malloc(3 * sizeof(char));
    char* c3 = (char*)malloc(7 * sizeof(char));
    char arr[11] = "0123456789";
    c1 = arr;
    printf("%s\n", c1);
    c2 = c1;
    printf("%s\n", c2);
    c2[3] = '\0';
    printf("%s\n", c2);
    printf("%s\n", c1);
    return 0;
}