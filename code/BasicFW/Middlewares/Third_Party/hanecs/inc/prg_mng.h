#ifndef __PRG_MNG_H
#define __PRG_MNG_H

#include "stdint.h"

// Publice Types
typedef void (*state)(void * args);

typedef struct transition_s {
    //void (*from)(void * args); 
    //void (*to)(void * args);
    state from;
    state to;
} event;


state prgMng_getCurState(void );

void prgMng_init( state init);
void prgMng_exeEvent(event * e, void * args);


#endif