/* logtail.c - version 0.1

Written by Petter Lindquist <petter@hig.se>
at University College of Gavle

030922 - initial release

Disclaimer: Comes with no warranty what so ever. Use at your own risk!

How to compile:
gcc -O2 -Wall -pedantic logtail.c -o logtail

*/

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  FILE *logfh,*offsetfh;
  int offs;
  char buf[256];

  if(argc!=3)
    {
      printf("Usag: %s logfile offsetfile\n",argv[0]);
      exit(-1);
    }
  
  offsetfh=fopen(argv[2],"r");
  if(!offsetfh)
    {
      offs=0;
    }
  else
    {
      fgets(buf,200,offsetfh);
/*       buf[i+1]=0; */
/*       printf("%d:%s:\n",i,buf); */
      offs=atoi(buf);
      fclose(offsetfh);
    }
  
/*   printf("offset=%d\n",offs); */

  logfh=fopen(argv[1],"r");
  if(!logfh)
    {
      printf("Can't open %s for reading\n",argv[1]);
      exit(-1);
    }

  if(offs)
    {
      if(fseek(logfh,offs,SEEK_SET))
	{
	  /* logrotate probably gave us a new file */
	  rewind(logfh);
	}
    }

  while(fgets(buf,256,logfh))
    {
      printf("%s",buf);
    }
  offs=ftell(logfh);
  fclose(logfh);

  offsetfh=fopen(argv[2],"w+");
  if(!offsetfh)
    {
      printf("Can't open %s for writing\n",argv[2]);
      exit(-1);
    }
  else
    {
      fprintf(offsetfh,"%d",offs);
      fclose(offsetfh);
    }
  return 0;
}
