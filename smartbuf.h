#include <stdlib.h>

typedef struct SmartBuf SmartBuf_t;

struct SmartBuf
{
  char * name;
    int size;
    int sizeofentry;
    int len;
    char * start;
};

SmartBuf_t * SB_loadFile(char * filename);
SmartBuf_t * SB_init(int startgrosse, char * name);
char SB_get(SmartBuf_t * buf, int off);
void SB_put (SmartBuf_t * list, int anfang, int lenge);
void SB_push (SmartBuf_t * ar, char value);
void SB_clear (SmartBuf_t * ar);
void SB_free (SmartBuf_t * ar);

