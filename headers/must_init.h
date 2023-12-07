#include <stdio.h>
#include <stdlib.h>
#ifndef _MUST_INIT_H
#define _MUST_INIT_H

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

#endif
