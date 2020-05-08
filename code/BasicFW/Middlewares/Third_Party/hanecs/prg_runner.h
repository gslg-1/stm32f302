#ifndef __PRG_RUNNER_H
#define __PRG_RUNNER_H
#include "prg_mng.h"

/* External Variables */
extern void actPrgCPrg(void * args);
extern uint8_t cndPrgCPrg(void * args);

/* Dummy */
void doNothing(void *args){};


prg_handle hPrg1;
state sPrgCPrg;                                                     // Entry Program Flash Test   
transition tPrgCPrg2CPrg;


transition * ttSPrgCPrg[2] = { &tPrgCPrg2CPrg, NULL};



void hPrg1_init(void)
{  
    /* Setup the States */
    /* Choose Program */
    sPrgCPrg.act = actPrgCPrg;                              // Entry Program Flash Test              
    sPrgCPrg.getActArgs = doNothing;
    sPrgCPrg.trst_table = ttSPrgCPrg;
    
    /* Setup the Transition  */
    tPrgCPrg2CPrg.cnd = cndPrgCPrg;
    tPrgCPrg2CPrg.getCndArgs = doNothing;
    tPrgCPrg2CPrg.to = &sPrgCPrg;

    if (prgMng_init(&hPrg1, &sPrgCPrg))
    {
        /* todo: Add External Error Handler  */
    }
}

#endif