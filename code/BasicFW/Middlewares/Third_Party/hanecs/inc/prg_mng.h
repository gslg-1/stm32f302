#ifndef __PRG_MNG_H
#define __PRG_MNG_H

#include "stdint.h"

// Publice Types
typedef struct transition_s transition;
typedef struct state_s state;


struct transition_s {
    uint8_t  (* condition)(void);
    state * to;
};

struct state_s{
    void (*fxn)(void);
    transition * t_table;
    uint8_t table_length;
};



void prgMng_init( state * init);
void prgMng_execute(void);
void prgMng_loadNextPrg(state * next);


#endif