#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "debug.h"
#include "aux.h"

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
 
int levenshtein(char *s1, char *s2, bool nocase) {
    unsigned int x, y, s1len, s2len;
    unsigned int last;
    const unsigned int ersetz_value = 1;
    const unsigned int insert_value = 1;
    const unsigned int delete_value = 1;
    s1len = strlen(s1);
    s2len = strlen(s2);
    if (nocase == true) {
		  for (x = 0; x<s2len; x++) s2[x] = tolower(s2[x]);
		  for (y = 0; y<s1len; y++) s1[y] = tolower(s1[y]);
    }
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++) {
            last = ersetz_value;
            if (s1[y-1] == s2[x-1]) last = 0;
            //if ((tolower(s1[y-1]) == s2[x-1]) && (toupper(s1[y-1]) != s2[x-1])) last = 1;
            //last = (tolower(s1[y-1]) == tolower(s2[x-1]) ? 0 : 1);  
            matrix[x][y] = MIN3(matrix[x-1][y] + insert_value, matrix[x][y-1] + delete_value, matrix[x-1][y-1]+last);
        }
    printf("  ");
    for (x = 1;x<=s2len;x++) printf(" %c", s2[x-1]); 
		printf("\n");
    for (y = 1; y<=s1len; y++) {
      printf("%c ", s1[y-1]);
		  for (x = 1;x<=s2len; x++)
			  printf("%2i", matrix[x][y]);
			printf("\n");
    }
    return(matrix[s2len][s1len]);
}  


void * xmalloc (size_t n)
{
  void *p;
  p = malloc (n);
  if (p == NULL) 
  {
    printf("Error: not enough mem! abort"); 
    exit(1);
  }
  return p;
}

void showString(char * string, int start, int end)
{
  int i;
  if (DEBUG) printf("%i bis %i:", start, end);
  for (i = start; i < end; ++i) putchar(string[i]);
}


void showMem(char *ptr, int n)
{
  int i;
  for (i=0 ; i< n; i++) { printf("%i,", (int) *(ptr+i));}
  printf("\n");
}

void showStringPtr(char * string, int n)
{
  int i;
  for (i = 0; i < n; i++) putchar(string[i]);
};

char * memcasechr(char * start, char needle, int n)
{
  char lower;
  char upper;
  char * lowerpos;
  char * upperpos;
  lower = tolower(needle);
  upper = toupper(needle);
  //printf("Suche nach %c und %c \n", lower, upper);
  lowerpos = memchr(start, lower, n);
  upperpos = memchr(start, upper, n);
  if ((lowerpos == NULL) && (upperpos == NULL)) return NULL;
  if (lowerpos == NULL) return upperpos;
  if (upperpos == NULL) return lowerpos;
  if (lowerpos < upperpos) return lowerpos; 
  return upperpos;
}


