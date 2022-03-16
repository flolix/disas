#include <stdio.h>
#include <stdbool.h>
#include "debug.h"

bool debug = false;

void debprint (char *string)
{
  if (DEBUG == true)
  {
    printf("%s",string);
    //puts(string);
  } 
}

