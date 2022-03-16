#include <stdint.h>
#include <stddef.h>

struct mnem_s {
    char mnem[15];      //mnemonic
    char code[20];      //code, parts separated by ':', PLUS code like '20+r'
    int cyc;            //number of cycles
    int length;         //length of opcode.. filled by splitMnem
    struct splitMnem_s * sp; //splitMnem filled by splitMnem
};

struct mnem_s mnemonics[];


int getMnem(uint8_t * data);
void filltables ();
int decodeMnem(uint8_t * data);
