#include <stdio.h>

int CallMe()
{
    printf("Hello from %s\n", __FUNCTION__);
    return 99;
}
