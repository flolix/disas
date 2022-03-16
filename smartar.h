typedef struct SmartArray SmartArray_t;


struct SmartArray
{  
    int anzahl;
    int size_of_entry;
    int capacity;
    int pos;
    char data[];
} ;


void  SA_push (SmartArray_t * m, void * data);
SmartArray_t * SA_init(int size_of_entry, int capacity);

void SA_reset(SmartArray_t * m);
void * SA_next(SmartArray_t * m);
void * SA_getX(SmartArray_t * m, int x);

void showMenge(SmartArray_t * m);
void forEachElement(SmartArray_t * m, void (*func) ());





