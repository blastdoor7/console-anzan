#include "stdlib.h"
#include "unistd.h"
#include <cstdio>
#include <ncurses.h>
#include <vector>
#include <string>
#include <iostream>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

using namespace std;
const char* padding = "                                                                               ";

char* getline(void)
{
  char* line = (char*)malloc(100);
  char* linep = line;
  size_t lenmax = 100, len = lenmax;
  int c;

  if(line == NULL)
  {
    return NULL;
  }

  for(;;)
  {
    c = fgetc(stdin);

    if(c == EOF)
    {
      break;
    }

    if(--len == 0)
    {
      len = lenmax;
      char * linen = (char*)realloc(linep, lenmax *= 2);

      if(linen == NULL)
      {
        free(linep);
        return NULL;
      }

      line = linen + (line - linep);
      linep = linen;
    }

    if((*line++ = c) == '\n')
    {
      break;
    }
  }

  *line = '\0';
  return linep;
}
int main(int argc,char** argv)
{
  srand(time(NULL));
  vector<long long> numbers;
  long long sum=0;
  double SLEEP_=3;
  int NUMBERS=5;
  int DIGITS=3;
  long long prev=0;
  long long mod=1;

  bool first=true;

  //cout << "RAND_MAX " << RAND_MAX << endl; exit(0);

  if(argc == 4)
  {
    SLEEP_ = strtod(argv[1],NULL);
    NUMBERS = strtol(argv[2],NULL,10);
    DIGITS = strtol(argv[3],NULL,10);
  }

  for(int i=0; i<DIGITS; i++)
  {
    mod*=10;
  }

  for(int i=0; i<NUMBERS; i++)
  {
    long long r=rand()%mod;

    if(DIGITS == 1)
    {
      if(r<1)
      {
        r+=1;
      }
    }

    while(r == prev && first == false)
    {
      r=rand()%mod;

      if(DIGITS == 1)
      {
        if(r<1)
        {
          r+=1;
        }
      }
    }

    first=false;

    if(DIGITS > 1 && r < mod/10)
    {
      r+=(mod/10);
    }

    prev=r;
    numbers.push_back(r);
    sum+=r;
  }

  clear();

  for(int i=0; i<numbers.size(); i++)
  {
    gotoxy(1,1);
    printf("\n\n\n\n\n");
    printf("%20d", numbers[i]);
    printf("\n\n\n\n\n");
    fflush(stdout);
    sleep(SLEEP_);
  }

  clear();
  gotoxy(1,1);
  printf("\n\n\n\n\n");
  printf("%20s answer?"," ");
  char* answer = getline();
  int ans = strtol(answer,NULL,10);

  if(ans == sum)
  {
    printf("\n\n\n\nanswer %d is correct\n",ans);
  }
  else
  {
    printf("\n\n\n\nanswer %d is wrong\n",ans);
    printf("\n sum = %lu = ", sum);

    for(int i=0; i<NUMBERS; i++)
    {
      i!=NUMBERS-1 ? printf("%d + ",numbers[i]) : printf("%d",numbers[i]);
    }

    printf("\n");
  }
}
