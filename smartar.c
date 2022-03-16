#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "smartar.h"
#include "debug.h"

//alle Elemente haben die gleiche Grösse..

void SA_free(SmartArray_t * m)
{
  free(m);
  if (DEBUG) printf("SA_free\n");
}


SmartArray_t * SA_init(int size_of_entry, int capacity)
{
    SmartArray_t * p;
    p = malloc(sizeof(SmartArray_t)+ size_of_entry * capacity);
    p->size_of_entry = size_of_entry;
    p->capacity = capacity;
    p->anzahl = 0;
    p->pos = 0;
    return p;  
};

void SA_reset(SmartArray_t * m)
{
  m->pos = -1;
}

void * SA_next(SmartArray_t * m)
{
    m->pos++;
    return SA_getX(m, m->pos); 
}

void * SA_getX(SmartArray_t * m, int x)
{
    if (x >= m->anzahl) return NULL;
    return &m->data[x*m->size_of_entry]; 
}

void SA_push(SmartArray_t * m, void * data) {
  memcpy(&m->data[m->anzahl*m->size_of_entry], data, m->size_of_entry);  
    m->anzahl++;
}
