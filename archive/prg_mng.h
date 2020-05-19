#ifndef __PRG_MNG_H
#define __PRG_MNG_H

#include "stdint.h"

// Publice Types
typedef struct prgMng_prg_s {
    void (*state_init)(void);
} prgMng_prg;


void prgMng_init( prgMng_prg  * init);
void prgMng_execute(void);
void prgMng_loadNextPrg(prgMng_prg * next);
void prgMng_nextState()


#endif