#include<iostream>
#include<stdlib.h>
#include<time.h>


int losowanko()
{
  srand( time(NULL) );
  return rand();
}
