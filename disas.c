#include <ncurses.h>
#include <string.h>

#include "smartbuf.h"
#include "aux.h"
#include "smartar.h"
#include "mnems.h"

char global_return_string[100];

typedef struct DataDump_s DataDump_t;
struct DataDump_s {
    int start;
    int length;
    SmartBuf_t * buffer;
};

typedef struct symbolEntry symbolEntry_t;
struct symbolEntry {
    int adr;
    int range;
    uint8_t type;
    char symbol[10];
};

SmartArray_t * symtab;


char * symbolLookUp(int adr) {
    global_return_string[0] = '\0';
    SA_reset(symtab);
    symbolEntry_t * symentry;
    while ((symentry = (symbolEntry_t *) SA_next(symtab)) != NULL) {
        if (symentry->adr <= adr && symentry->adr + symentry->range >= adr) {
            strcat(global_return_string, " ");
            strcat(global_return_string, symentry->symbol);
        }
    }

    return global_return_string;
}

void symbolPush(int adr, int range, char sym[10]) {
    symbolEntry_t symentry;
    symentry.adr = adr;
    symentry.range = range;
    strcpy(symentry.symbol, sym);
    SA_push(symtab, &symentry);
}


int main () {
   
    symtab = SA_init(sizeof(struct symbolEntry), 40);
    symbolPush(0x0, 0x7ffff, "ROM");
    symbolPush(0x80000, 0x3ffff, "RAM");
    symbolPush(0x90000, 0x2, "k19");
    symbolPush(0xa0000, 0x7, "k15_1");
    symbolPush(0xb0000, 0x7, "k15_2");

    symbolPush(0xfbc0, 0x3ff, "iRam");
    symbolPush(0xff00, 0xff, "ZP");
    symbolPush(0xffc0, 0x2f, "IO");
    symbolPush(0x0,0x0,"reset:");
    symbolPush(0x2, 0x7d, "vtable");

    symbolPush(0xffd0, 0x0, "P8");
    symbolPush(0xffd2, 0x0, "WDMOD");
    symbolPush(0xffd3, 0x0, "WDCR");
    symbolPush(0xffd4, 0x0, "TREG0");
    symbolPush(0xffd5, 0x0, "TREG1");
    symbolPush(0xffd6, 0x0, "TREG2");
    symbolPush(0xffd8, 0x0, "TCLK");
    symbolPush(0xffdb, 0x0, "TRUN");
    symbolPush(0xffe2, 0x0, "TREG5L");
    symbolPush(0xffc3, 0x0, "IRFH");
    symbolPush(0xffc6, 0x0, "P3");
    symbolPush(0xffc7, 0x0, "P3CR");
    symbolPush(0xffc9, 0x0, "P4CR");
    symbolPush(0xffcc, 0x0, "P6");
    symbolPush(0xffcd, 0x0, "P7");
    symbolPush(0xffce, 0x0, "P67CR");
    symbolPush(0xffe4, 0x0, "T4MOD");
    symbolPush(0xffe7, 0x0, "INTEH");
    symbolPush(0xffec, 0x0, "BX");
    symbolPush(0xffed, 0x0, "BY");
    symbolPush(0xffef, 0x0, "ADMOD");
    

    char file[] = "images/kawai_eeprom.bin";
    DataDump_t * dd = xmalloc(sizeof(DataDump_t));
    //dd->start = 0x226f;
    dd->start = 0x0;
    dd->buffer = SB_loadFile(file); //dd->buffer is a SmartBuffer type
    dd->length = dd->buffer->len;
    printf("load file %s, address %05x\n", file, dd->start);

    filltables();

    puts("ok.. now ready to serve..");

    int off = 0x80;
    int lines = 0;
    while (off < dd->length) {
        //print address
        printf("%s %05x : ", symbolLookUp(off), off);
        //printf("%05x : ",off);

        //print memory bytes
        int l;
        int mnem = getMnem((uint8_t *)dd->buffer->start+off);
        if (mnem == -1) l = 1;  else l = mnemonics[mnem].length;
        for (int i = 0; i< 6; i++) {
            if (i < l) printf("%02x ", (uint8_t) *(dd->buffer->start+off+i));
            else printf("   ");
        }

        //print mnemonic
        off += decodeMnem((uint8_t *) dd->buffer->start + off);

        lines++;
        if (lines >= 500) break;
    }

}
