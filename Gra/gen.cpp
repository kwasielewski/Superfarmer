#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

void slosuj()
{
  int a =  (int)time(NULL);
  a = a*7;
  a = a%13;
  a = a*time(NULL);
  a = a - a%1000007;
  srand( getpid() + a );
}

int losowanko()
{
  return rand();
}
