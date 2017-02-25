#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   /*clock_t start_t, end_t, total_t;
   int i;

   start_t = clock();
   printf("Starting of the program, start_t = %ld\n", start_t);
    
   printf("Going to scan a big loop, start_t = %ld\n", start_t);
   for(i=0; i< 10000000; i++)
   {
   }
   end_t = clock();
   printf("End of the big loop, end_t = %ld\n", end_t);
   
   total_t = (double) (clock() - start_t) *1000 / CLOCKS_PER_SEC;
   printf("Total time taken by CPU: %.5g\n", total_t);
   printf("Exiting of the program...\n");*/

   int msec = 0, trigger = 40, i = 0, iterations = 0; /* 10ms */
   clock_t before = clock();

   do {
      for(i=0; i< 10000000; i++)
      {
      }
      clock_t difference = clock() - before;
      msec = difference * 1000 / CLOCKS_PER_SEC;
      iterations++;
   } while ( msec < trigger );

   printf("Time taken %d seconds %d milliseconds (%d iterations)\n",
     msec/1000, msec%1000, iterations);

   trigger = 800
   do {
      for(i=0; i< 10000000; i++)
      {
      }
      clock_t difference = clock() - before;
      msec = difference * 1000 / CLOCKS_PER_SEC;
      iterations++;
   } while ( msec < trigger );

   printf("Time taken %d seconds %d milliseconds (%d iterations)\n",
     msec/1000, msec%1000, iterations);

   int j;
   char a[50];
   char *ap = a;

   for (j = 5; j < 15; j++) {
       ap += sprintf(ap, "%d ", j);
   }

   printf("%s\n", a);

   return(0);
}