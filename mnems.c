#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mnems.h"

#define MAXBYTES 6


struct mnem_s mnemonics[] = { // 8-bit transfer
                           {"LD A,r"   , "20+r" ,  2},
                           {"LD r,A"   , "28+r" ,  2},
                           {"LD r,g"   , "f8+g:30+r", 4},
                            {"LD r,n", "30+r:n", 4},
                            {"LD A,(n)", "27:n", 8},
                           {"LD r,(gg)", "e0+gg:28+r", 6},
                            {"LD r,(ix+d)","f0+ix:d:28+r", 10},
                            {"LD r,(HL+A)", "f3:28+r",14},
                            {"LD r,(mn)", "e3:n:m:28+r",10},
                            {"LD r, (n)", "e7:n:28+r",8}, //wrong in data sheet
                            {"LD (n),A","2f:n",8},
                            {"LD (gg),r","e8+gg:20+r",6},
                           {"LD (ix+d),r", "f4+ix:d:20+r", 10},

                            {"LD (gg),n", "e8+gg:37:n", 8},
                            {"LD (ix+d),n", "f4+ix:d:37:n", 12},
                            {"LD (HL+A),n", "f7:37:n", 16},
                            {"LD (vw),n", "eb:w:v:37:n", 12},
                            {"LD (w), n", "37:w:n", 10},
                            // 16-bit trasnfer
                            {"LD HL,rr", "40+rr", 4},
                            {"LD rr, HL", "48+rr", 4},
                            {"LD rr,gg", "f8+gg:38+rr"},

                            {"LD rr,mn", "38+rr:n:m", 6},

                            {"LD HL,(n)","47:n", 10},
                            {"LD rr,(gg)", "e0+gg:48+rr",8},
                            {"LD rr,(ix+d)", "f0+ix:d:48+rr",12},
                            {"LD rr,(HL+A)", "f3:48+rr",16},
                            {"LD rr,(mn)", "e3:n:m:48+rr",12},
                            {"LD rr,(n)", "e7:n:48+rr",10},

                            {"LD (n), HL", "4f:n", 10},
                            {"LD (gg),rr","e8+gg:40+rr",8},
                            {"LD (ix+d),rr","f4+ix:d:40+rr",12},
                            {"LD (HL+A),rr", "f7:40+rr",16},
                            {"LD (mn),rr", "eb:n:m:40+rr",12},
                            {"LD (n),rr", "ef:n:40+rr",10},

                            {"LDW (gg), mn","e8+gg:3f:n:m", 12},
                            {"LDW (ix+d), mn","f4+ix:d:3f:n:m",16},
                            {"LDW (HL+A), mn", "f7:3f:n:m",20},
                           {"LDW (vw), mn", "eb:w:v:3f:n:m"},
                            {"LDW (w), mn", "3f:w:n:m", 14},
                           {"PUSH qq"   , "50+qq",  10},
                           {"POP qq"   , "58+qq",  10},
                            // 3. exchange
                            {"LDIR", "fe:59", 14},
                            {"EXX", "0a",2},
                            // 4. 8-bit arithmetic
                            {"ADD A,g","f8+g:60",4},
            
                            {"ADD A,n", "68:n",4},

                            {"ADD A,(gg)", "e0+gg:60",6},
                            {"ADD A,(ix+d)", "f0+ix:d:60",10},
                            {"ADD A,(HL+A)", "f3:60",14},
                            {"ADD A,(mn)", "e3:n:m:60",10},
                           {"ADD A,(n)"   , "60:n",  8},

                            {"ADD g,n", "f8+g:68:n",6},

                            {"ADC A,(n)", "61:n",8},

                            {"SUB A,g","f8+g:62",4},

                            {"AND A,g", "f8+g:64",4},

                            {"AND A,n","6c:n",4},

                            {"AND A,(gg)","e0+gg:64",6},
                            {"AND A,(n)", "64:n",8},

                            {"OR A,(n)", "66:n",8},

                           {"INC r", "80+r",2},
                            {"INC (n)", "87:n", 10},
                            {"DEC (n)", "8f:n", 10},

                            {"CP A,(gg)","e0+gg:67",6},
                            {"CP A,(ix+d)","f0+ix:d:67",10},
                            {"CP A,(HL+A)","f3:67",14},
                            {"CP A,(mn)","e3:n:m:67",10},
                            {"CP A,(n)","67:n",8},

                            {"CP A,n","6f:n",4},

                            {"CP g,n","f8+g:6f:n",6},

                            {"CP (w),n", "ef:w:6f:n", 10},

                            {"DEC r", "88+r",2},

                            {"DECX (n)","0f:n",10},
                            // 5. special
                           {"NOP", "00",2},

                           {"HALT", "01",4},

                           {"DI", "02",2},
                           {"EI", "03",2},
                           {"SWI", "ff",20},

                            {"MUL HL,n","12:n",16},
                            // 6. 16-bit arithmetic
                            {"ADD HL, gg","f8+gg:70",8},

                            {"ADD HL,mn", "78:n:m",6},

                            {"ADD HL,(gg)", "e0+gg:70",8},
                            {"ADD HL,(n)","70:n",10},

                            {"ADC HL,(n)","71:n",10},

                            {"AND HL,gg", "f8+gg:74",8},

                            {"AND HL,(gg)","e0+gg:74",8},
                            {"AND HL,(ix+d)","f0+ix:d:74",12},
                            {"AND HL,(HL+A)","f3:74",16},
                            {"AND HL,(mn)","e3:n:m:74",12},
                            {"AND HL,(n)","74:n",10},


                            {"CP HL,mn","7f:n:m",6},

                            {"CP HL,gg","f8+gg:77",8},

                            {"CP HL,mn","7f:n:m",6},

                            {"CP HL,(gg)", "e0+gg:77",8},
                            {"CP HL,(ix+d)", "f0+ix:d:77",12},
                            {"CP HL,(HL+A)", "f3:77",16},
                            {"CP HL,(mn)", "e3:n:m:77",12},
                            {"CP HL,(n)", "77:n",10},

                            {"ADD ix, mn","14+ix:n:m",6},

                            {"INC rr", "90+rr", 4},

                            {"INCW (gg)", "e0+gg:97", 12},
                            {"INCW (ix+d)", "f0+ix:d:97", 16},

                            {"DEC rr", "98+rr", 4},

                            {"DECW (gg)","e0+gg:9f",12},
                            {"DECW (ix+d)","f0+ix:d:9f",16},
                            {"DECW (HL+A)","f3:9f",20},
                            {"DECW (mn)","e3:n:m:9f",16},
                            {"DECW (n)", "9f:n",14},
                            // 7. rotate shift
                            {"RLC A", "a0",2},
                            {"RLC g", "f8+g:a0",4},

                            {"RLA", "a2",2},
                            {"RL g", "f8+g:a2"},

                            {"RL (gg)", "e0+gg:a2",8},
                            {"RL (ix+d)", "f0+ix:d:a2",12},
                            {"RL (HL+A)", "f3:a2",16},
                            {"RL (mn)", "e3:n:m:a2",12},
                            {"RL (n)", "e7:n:a2",10},

                            {"RRA", "a3", 2},

                            {"SLA A","a4",2},
                            {"SLA g","f8+g:a4",4},

                            {"SLLA", "a6", 2},
                            {"RLL g", "f8+g:a6", 4},
                            // 8. bit manipulation
                            {"BIT b,g", "f8+g:a8+b", 4},

                            {"BIT b,(gg)", "e0+gg:a8+b",6},
                            {"BIT b,(n)", "a8+b:n", 8},

                            {"SET b,g", "f8+g:b8+b",4},

                            {"SET b,(gg)", "e0+gg:b8+b", 10},
                           {"SET b,(n)", "b8+b:n", 12},

                            {"RES b,g","f8+g:b0+b",4},

                            {"RES b,(n)","b0+b:n",12},
                            // jump
                            {"JR cc, PC+d","c0+cc:d", 4},
                           {"JP mn"    , "1A:n:m"},
                            {"JP cc,mn", "eb:n:m:c0+cc", 12},
                            {"CALL cc, mn", "eb:n:m:d0+cc", 18},
                            {"CALL mn", "1c:n:m", 14},
                            {"CALL PC+cd", "1d:d:c", 16},
                            {"DJNZ PC+d", "18:d", 10},
                            {"DJNZ BC, PC+d", "19:d", 10},
                            {"RET", "1e", 10},
                            {"RET cc", "fe:d0+cc", 14},
                            {"RETI", "1f", 14},
                            // end
                           {"END" }}; 

// here are the symbols defined..
enum {SYM_w = 1, SYM_c, SYM_cd, SYM_v, SYM_r, SYM_g, SYM_rr, SYM_gg, SYM_ix, SYM_qq, SYM_mn, SYM_n, SYM_m, SYM_b, SYM_d, SYM_cc, OPCODE = 128, OPCODE_PLUS = 64};


struct symbol_s {
    char name[3];
    uint8_t id;
    struct symbolvalues_s * st;
    struct symbol_s * nextsymbol; //all symbols are a linked list..
};

struct symbolvalues_s {
    char desig[4];
    uint8_t value;
};

struct symbolvalues_s r_values[8] = {{"A", 6},{"B",0},{"C",1},{"D",2},{"E",3},{"H",4},{"L",5},{""}};
struct symbolvalues_s rr_values[7] = {{"BC", 0},{"DE",1},{"HL",2},{"IX",4},{"IY",5},{"SP",6},{""}};
struct symbolvalues_s qq_values[7] = {{"BC", 0},{"DE",1},{"HL",2},{"IX",4},{"IY",5},{"AF",6},{""}};
struct symbolvalues_s ix_values[4] = {{"IX", 0},{"IY",1},{"SP",2},{""}};
struct symbolvalues_s b_values[9] = {{"0", 0},{"1",1},{"2",2},{"3",3},{"4",4},{"5",5},{"6",6},{"7",7},{""}};
//condition code.. for conditional jumps
struct symbolvalues_s cc_values[23] = {{"F", 0},{" ",8},{"Z",6},{"NZ",0xe},{"C",7},{"NC",0xf},{"PL",0xd},{"MI",5},{"NE",0xe},{"EQ",6},{"OV",4},{"NOV",0xc},{"PE",4},{"PO",0xc},{"GE",9},{"LT",1},{"GT",0xa},{"LE",2},{"UGE",0xf},{"ULT",7},{"UGT",0xb},{"ULE",3},{""}};
    

//statically linked list of symbols..
struct symbol_s r_symtable = {"r", SYM_r, r_values, NULL};
struct symbol_s g_symtable = {"g", SYM_g, r_values, &r_symtable};
struct symbol_s rr_symtable = {"rr", SYM_rr, rr_values, &g_symtable};
struct symbol_s gg_symtable = {"gg", SYM_gg, rr_values, &rr_symtable};
struct symbol_s qq_symtable = {"qq", SYM_qq, qq_values, &gg_symtable};
struct symbol_s ix_symtable = {"ix", SYM_ix, ix_values, &qq_symtable};
struct symbol_s m_symtable = {"m", SYM_m, NULL, &ix_symtable};
struct symbol_s mn_symtable = {"mn", SYM_mn, NULL, &m_symtable};
struct symbol_s n_sym = {"n", SYM_n, NULL, &mn_symtable};
struct symbol_s w_sym = {"w", SYM_w, NULL, &n_sym};
struct symbol_s v_sym = {"v", SYM_v, NULL, &w_sym};
struct symbol_s d_sym = {"d", SYM_d, NULL, &v_sym};
struct symbol_s c_sym = {"c", SYM_c, NULL, &d_sym};
struct symbol_s cc_sym = {"cc", SYM_cc, cc_values, &c_sym};
struct symbol_s cd_sym = {"cd", SYM_cd, NULL, &cc_sym};
struct symbol_s symtable = {"b", SYM_b, b_values, &cd_sym};
//                 ^--- start of linked list


struct opCode_s {
    uint8_t position;
    uint8_t opcode;
    int mnem;
    struct connectList_s * cl;
};

struct connectList_s {
    int size;
    struct opCode_s * OpCo[]; 
};


void add2connectList(struct connectList_s ** cl, struct opCode_s * Opco) {
    if (*cl == NULL) { 
        //no list there.. create one..
printf("create list..wirh Opco %02x\n", Opco->opcode);
        *cl = malloc(sizeof(struct connectList_s) + sizeof(struct connectList_s*));
        (*cl)->size = 1;
        (*cl)->OpCo[0] = Opco;
    } else {
        //create new list but bigger copy the old one into it.. and free the old one
        //why we do it in such a time consuming way?
        struct connectList_s * ncl;
printf("resize list..size %d for opco %02x\n", (*cl)->size,Opco->opcode);
        ncl = malloc(sizeof(struct connectList_s) + sizeof(struct opCode_s*) * ((*cl)->size +1));
        memcpy(ncl, *cl, sizeof(struct connectList_s) + (*cl)->size*sizeof(struct opCode_s*));
        ncl->OpCo[ncl->size] = Opco;
        ncl->size++;
        free(*cl); 
        *cl = ncl;
    } 
}

struct connectList_s * rootOpCodes;


struct opCode_s * createOpCodeStruc(int opcode, int position) {
printf("creat opco %02x", opcode);
    struct opCode_s * ocs;
    ocs = malloc(sizeof(struct opCode_s));
    ocs->position = position;
    ocs->opcode = opcode;
    ocs->mnem = -1;
    ocs->cl = NULL;
    return ocs;
}


//get mnemonic to data..
int getMnemI (uint8_t * data, struct connectList_s * r) {
    if (r == NULL) return -1;
    for (int i = 0; i < r->size; i++) {
        struct opCode_s * o = r->OpCo[i];
        if (data[o->position] == o->opcode) {
//printf("found %02x", o->opcode);
//if (o->mnem == -1) printf("but no mnem!"); else printf("mnem is %d", o->mnem);
            if (o->mnem != -1) return o->mnem;
            int m = getMnemI(data, o->cl); //oh wow an iteration! you did a good job flo..
            if (m != -1) return m;
        }
    }
    return -1;
}

//get mnemonic to data..
int getMnem (uint8_t * data) {
    if (rootOpCodes == NULL) {
        puts("No mnemonics here.."); exit(1);
        return -1;
    }
    return getMnemI(data, rootOpCodes);
}


struct splitMnem_s {
    int mnem;           // mnem
    int numberOfParts;  // number of bytes.. XXX same as SP.length?!
    uint8_t type[MAXBYTES];     // type of byte.. 
                        // (e.g. 0 opcode, opcode with 8bit reg, opcode with 16-bit reg,
                        // opcode with 20-bit reg,
                        // 1 8-bit absolute, 2, 16-bit absolute, 
                        //  3 8-bit relativ, 4 16-bit relativ, 5 8 bit displacement, 6 bit position..
    char parts[MAXBYTES][7];   // code split by colon. F8+g:30+r will be: "f8+g", "30+r"
    int opcode[MAXBYTES];   // opcode of byte.. if opcode plus, then startopcode..
    char base_mnem[5];   //XXX length of base_mnem.. should it be hardcoded?
    //int numberOfOpCodes; 
};

void addchar(char * str, char c) {
    //why is this a function? and not inline?
    str[strlen(str)] = c;
}

struct symbol_s * getSymbolById(int s) {
    struct symbol_s * sym = &symtable;
    do {
        if (sym->id == s) return sym;
        sym = sym->nextsymbol;
    } while (sym != NULL);
    return NULL; // not found..
}


//split the mnem m, aka mnem i into parts..    
//XXX why m AND mnem as an argument? one of them should be enough
struct splitMnem_s splitMnemonic(struct mnem_s * m, int mnem) {
    struct splitMnem_s SP;
    memset(&SP,0,sizeof(struct splitMnem_s)); //clear it.. 
    //why? it relies on at least SP.parts, SP.base_mnem, SP.type is cleared, filled with \0!
    //store mnem
    SP.mnem = mnem; 

    // store base_mnem thats the leading LD or ADD or whatever part..
    char * space;
    space = strchr(m->mnem, ' ');
    if (space != NULL) {
        strncpy(SP.base_mnem, m->mnem, space-m->mnem);//note: SP.base_mnem is filled with \0
    } else {strcpy(SP.base_mnem, m->mnem);} 

    //now split into parts
    char * code = m->code;
    int i = 0;
    while (*code != '\0') {
        if (*code == ':') {code++; i++; continue;};
        if (i > MAXBYTES-1) {puts("fatal: mnemonic has too many bytes!");exit(1);};
        addchar(SP.parts[i], *code);
        code ++;
    }
    mnemonics[mnem].length = ++i;
    SP.numberOfParts = i;  //XXX this and the previous are redundant!

    //well done so far.. now working on the parts..
    for (i = 0; i < SP.numberOfParts; i++) {
        SP.opcode[i] = -1;
        char * endptr;
        //look if there is a hexadecimal leading part..
        uint8_t c = strtol(SP.parts[i], &endptr, 16);
        if (endptr > SP.parts[i]+1) { // there is.. opcode has to be 2 digits at least..
                                      // otherwise 'd' could be recognized as opcode
            SP.type[i] = OPCODE;
            SP.opcode[i] = c;
            if (*endptr == '+') {
                //its a plus opcode.. means opcode + encoded symbol eg 20+r
                SP.type[i] |= OPCODE_PLUS;
                endptr++;
                //compare with symbols from symboltable
                struct symbol_s * sym = &symtable;
                do { 
                    if (strcmp(endptr, sym->name) == 0) { // we are not using strncmp here!
                        SP.type[i] |= sym->id;
                        break; 
                    }
                    sym = sym->nextsymbol;
                } while (sym != NULL);

            }

        } else {
            //no leading hexadecimal part.. -> no opcode
            //look if its a valid symbol
            struct symbol_s * sym = &symtable;
            do {
                if (strcmp(SP.parts[i], sym->name) == 0) { //we are not using strncmp here!
                    SP.type[i] = sym->id; 
                    break;
                }
                sym = sym->nextsymbol;
            } while (sym != NULL);
        }

/*        if (SP.type[i] == 0) {
            printf("splitMnem: Fatal. Couldnt parse this: %s. Fix it!\n", SP.parts[i]);
            exit(1);
        } */
    }
    return SP;
}


char * getdesig(struct symbol_s* sym, int r) {
    int i = 0;
    do { 
        if (sym->st[i].value == r) return sym->st[i].desig;
        i++;
    } while (sym->st[i].desig[0] != '\0');
    return NULL;
}
 

int getvalue (struct splitMnem_s SP, uint8_t * data, int type_id) {
    int value;
    for (int i = 0; i < SP.numberOfParts; i++) {
        if ((SP.type[i] & 0b111111) == type_id) {
            value = data[i];
//printf("value is %d", value);
            if ((SP.type[i] & OPCODE_PLUS) == OPCODE_PLUS) value -= SP.opcode[i];
            return value;
        }
    }
    return -1;
}
 
//returns number of bytes of mnemonic.. XXX
int decodeMnem(uint8_t * data) {
    int mn = getMnem(data);
    if (mn  == -1 ) {
//printf ("%0x, %0x not found!", data[0], data[1]);
        printf("???\n");
        return 1;
    } else {
        struct splitMnem_s SP; //XXX please check if SP is already stored .. in mnemonics struc
        SP = splitMnemonic(&mnemonics[mn], mn);

        char * space;
        space = strchr(mnemonics[mn].mnem, ' ');
        if (space == NULL) { //no arguments at all..
            printf("%s", SP.base_mnem);
        } else {
            printf("%s ", SP.base_mnem);
            space++;
            while (* space != '\0') {
                //search for symb
//printf("search at %ld",space-mnemonics[mn].mnem);
                struct symbol_s * sym = &symtable;
                do {
                    if (strncmp(sym->name, space, strlen(sym->name)) == 0) {
//printf("found %s", sym->name);
                        space += strlen(sym->name);
                        break;
                        //whats teh value?
                    }
                    sym = sym->nextsymbol;
                } while (sym != NULL);
                //not found? 
                if (sym == NULL) {
                    printf("%c", *space);
                    space++;
                    continue;
                }

                struct symbol_s * sy;
                char * desig;
                //now find the symbol in the code.. and print it
                switch (sym->id) {
                    case SYM_d:; // displacement
                        int d;
                        d = getvalue(SP, data, sym->id);
                        if ((int8_t)d < 0) printf("-%02x", (int8_t)-d); else printf("+%02x)",d);
                        //printf ("%02x", (int8_t) d); //XXX its not printing right in the moment..
                        break;
                    case SYM_qq:
                    case SYM_ix:
                    case SYM_b:
                    case SYM_gg:
                    case SYM_r:
                    case SYM_g:
                    case SYM_cc:
                    case SYM_rr:; // register
                        int rr;
                        rr = getvalue(SP, data, sym->id);
//printf("reg is %d", rr);
//fflush(stdout);
                        if (rr == -1) {puts("panic"); exit(1);};
                        sy = getSymbolById(sym->id);
                        if (sy == NULL) {puts("panic");exit(1);}
                        //now find the right designator to 
                        desig = getdesig(sy, rr);
                        if (desig == NULL) {puts("panic"); exit(1);};
                        // print it..    
                        printf("%s",desig);
                        break;
                    case SYM_n:
                    case SYM_w:; //8 bit value
                        int w;
                        w = getvalue(SP, data, sym->id);
                        printf("%02x", w);
                        break;
                    case SYM_mn:; //16 bit value..
                        int m,n;
                        m = getvalue(SP, data, SYM_m);
                        n = getvalue(SP, data, SYM_n);
                        printf("%04x",m*256+n);
                        break;
                }
 
           }
        }
        printf("\n");
        return SP.numberOfParts;
    }
}


struct interimOps_s {
    uint8_t isset;
    uint8_t opcode;
    uint8_t position;
    struct opCode_s * opco;
};


struct opCode_s * findEntryInConnectList (struct connectList_s * cl, uint8_t opco, uint8_t pos) {
    if (cl != NULL) {
        for (int k = 0; k< cl->size; k++) {
            if (cl->OpCo[k]->opcode == opco && cl->OpCo[k]->position == pos) return cl->OpCo[k];
        }
    }
    return NULL;
}


void filltables () {
/*
 opcodes stored in a structure like that, which is created by filltables..
rootOpCodes -> connectList_s
                 entry1  -> opcode_s first opcode -> connectList_s
                                                       entry1  -> opcode_s second opcode -> connectList_s
                                                       entry2  ->
                                                       entryN  ->
    
                 entry2  -> opcode_s first opcode -> connectList_s
                                                       entry1  -> opcode_s secondopcode -> connectList->
                                                       entry2
                 entry3              
                 ...               
                 entryN
                                         .. -> are pointers ..

- entries in rootopCodes shall not be duplicates.. just to save space.. code wont break if otherwise
- how many bytes a mnemonic/code can have is just limited by MAXBYTES and struct mnem_s.
something like "I LOVE YOU", "49:20:4c:4f:56:45:20:59:4f:55" is possible

*/
    printf ("filling tables..\n");

    int i = 0;
    while (strcmp(mnemonics[i].mnem, "END") != 0) {
        printf("working on %s :", mnemonics[i].mnem);
        struct splitMnem_s sm = splitMnemonic(&mnemonics[i],i);
        printf("#%d, NoP %d, parts: ",sm.mnem, sm.numberOfParts);
        for (int j = 0; j < sm.numberOfParts; j++) {
            printf("%s : %x : %d", sm.parts[j], sm.opcode[j],sm.type[j]);
            printf ("|");
        }
        printf("\n");
 
        struct opCode_s * interim[MAXBYTES][25];
        //we need to clear it! 
        memset(interim, 0, sizeof(struct opCode_s *) * MAXBYTES * 25);
        int countOpcodes = 0;


        for (int position = 0; position < sm.numberOfParts; position++) {
            printf("Working on part %s\n", sm.parts[position]);
            if ((sm.type[position] & OPCODE) == OPCODE) {
                //oh.. we found an opcode..
                if ((sm.type[position] & OPCODE_PLUS) == OPCODE_PLUS) {
                    //printf("its a pluscode!");
                    //oh its a plus one..
                    struct symbol_s * sym = getSymbolById(sm.type[position] & 0b111111);
                    int j = 0;
                    do {
                        interim[countOpcodes][j] = createOpCodeStruc (sm.opcode[position]+sym->st[j].value, position);
                        j++;
                    } while (sym->st[j].desig[0] != '\0');
                } else {
                    interim[countOpcodes][0] = createOpCodeStruc (sm.opcode[position], position);
                }
            countOpcodes++;
            }
        }

        //printf("checkpoint alpha"); fflush(stdout);

        //add the first opcode the the rootopcodes connect list
        printf("add first opcode to rootopcodeslist\n"); 
        int j = 0;
        while (interim[0][j] != NULL)  { 
            //check for duplicates
            struct opCode_s * e = findEntryInConnectList(rootOpCodes, interim[0][j]->opcode, interim[0][j]->position);
            if (e != NULL) {
                //printf("duplicate found!  %02x\n", e->opcode);
                free(interim[0][j]);    //we already malloc'd it.. 
                interim[0][j] = e;      //
             } else {
                //printf("no duplicate!\n");
                add2connectList(&rootOpCodes, interim[0][j]);
            }
            j++;
        }

        //printf("checkpoint bravo"); fflush(stdout);

        countOpcodes  = 0;
        do {
            j = 0;
            while (interim[countOpcodes][j] != NULL) {
                if (interim[countOpcodes+1][0] == NULL) { //its the last opcode_s .. so it will get a mnem number
                    printf("set mnem for opcode %02x to %d\n", interim[countOpcodes][j]->opcode, sm.mnem);
                    interim[countOpcodes][j]->mnem = sm.mnem;
                } else {
                    int k = 0;
                    while (interim[countOpcodes+1][k] != NULL) {
                        add2connectList(&interim[countOpcodes][j]->cl, interim[countOpcodes+1][k]);
                        k++;
                    }
                }
                j++;
            }
            printf("countOpcodes %d", countOpcodes);
            countOpcodes++;
        } while (interim[countOpcodes][0] != NULL);

        i++;  //XXX maybe a better name for this i..
    }

    //printf("checkpoint charlie"); fflush(stdout);
}

