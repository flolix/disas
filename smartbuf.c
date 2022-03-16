#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "smartbuf.h"
#include "debug.h"
#include "aux.h"


SmartBuf_t * SB_loadFile(char * filename) {
  if (DEBUG) printf("Open '%s' as stream ..", filename);
  FILE * datei;
  datei = fopen(filename, "r");
  SmartBuf_t * dateilist;
  if (datei == NULL) {
    if (DEBUG) printf(" failed\n");
    printf("Couldnt open file %s.\n", filename);
    exit(1);
  } else {
    if (DEBUG) printf(" OK ->");
    int size_of_file;
    fseek(datei, 0, SEEK_END);
    size_of_file = ftell(datei);
    fseek(datei, 0, SEEK_SET);
    if (DEBUG) printf("Size %i bytes\n", size_of_file);

    dateilist = SB_init(size_of_file +1, "file");
    if (DEBUG) printf("read file ...");
    while (feof(datei) == 0) {
        fread(dateilist->start, size_of_file, 1, datei);  // load it in one run
        dateilist->len = size_of_file;
    }
    fclose(datei);	
    debprint(" successful\n");

    return dateilist;
  }
}

int SB_searchChar(SmartBuf_t * list, int anfang, char c)
{
  char * cp;
  cp = memchr(list->start+anfang, c, list->len-anfang);
  if (cp == NULL) return -1;
	//printf("char gefunden:%i", cp-list->start);
	return cp - list->start;
}

void SB_put(SmartBuf_t * list, int anfang, int lenge)
{
  int i;
  for (i = anfang ; i < lenge + anfang; i++) putchar(*(list->start+i));
}

void SB_show (SmartBuf_t * list)
{
	int i;
	//printf("CharList:CharList:Name: %s, Länge:%i\n", list->name, list->len);
	for (i=0; i< list->len; i++)  putchar( *(list->start+i));
	//putchar('\n');
}

SmartBuf_t * SB_init (int startgrosse, char * name)
{
  SmartBuf_t *da;
  da = xmalloc(sizeof(SmartBuf_t));
  da->size = startgrosse;
	da->sizeofentry = sizeof(char);
  da->start = xmalloc(da->size * da->sizeofentry);
  da->len = 0;
  da->name = xmalloc(strlen(name)+1);
  strcpy(da->name, name);
  
  if (DEBUG == true)
  { 
    printf("SmartBuf:init:Liste %s erstellt ", da->name); 
    printf("mit %i Bytes initialisiert\n", da->size * da->sizeofentry);
  }
  return da;
}


void SB_push (SmartBuf_t * ar, char value) {
    if (ar->len > ar->size) {
        if (DEBUG) {
            printf("SmartBuf:push:\"%s\" ist zu klein! Vergrössern auf ", ar->name);
            printf("%i...\n", ar->size * 2 * ar->sizeofentry);
        }
        //vergrössern
        void * zwischenpointer;
        int zwischengrosse;
        zwischenpointer = ar->start;
        zwischengrosse = ar->size;
        ar->size = zwischengrosse * 2;
        ar->start = xmalloc(ar->size * ar->sizeofentry);
        //umkopieren
        memcpy(ar->start, zwischenpointer, zwischengrosse * ar->sizeofentry);
        free(zwischenpointer);
    }

    *((char*)ar->start + ar->len) = value;
    ar->len++;
}

char SB_get (SmartBuf_t * buf, int off) {
    if (off >= buf->len) {
        printf("out");
        return 0;
    }
    return *(buf->start+off);
}

void SB_clear(SmartBuf_t * ar) {
  free(ar->start);
  ar->start = xmalloc(ar->size * sizeof(char));
  ar->len = 0; 
}

void SB_free(SmartBuf_t * ar)
{
  if (DEBUG)
  {
    printf("CharList:freeCharList:List %s freed\n", ar->name);
  }

  free(ar->start);
  free(ar->name);
  free(ar);
}


