#ifndef __PRG_MNG_H
#define __PRG_MNG_H

#include "stdint.h"

// Publice Types

typedef struct transition {
    uint8_t  (* condition)(void);
    void * state;
} transition;

typedef struct state {
    void (*fxn)(void);
    transition * t_table;
    uint8_t table_length;
} state;



void prgMng_init( state * init);
void prgMng_execute(void);
void prgMng_loadNextPrg(state * next)


#endif