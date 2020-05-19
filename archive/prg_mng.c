#include "prg_mng.h"


// Private variables
uint8_t isInitialized = 0;

const prgMng_prg * prg_current ;
const prgMng_prg * prg_next ;

const (*state_curr)(void (* next)());
const (*state_next)(void * next);

// Public Functions
void prgMng_init( prgMng_prg  * init)
{
    if (!isInitialized)
    {
        prg_current = init;
        prg_next = init;
        state_curr = (*prg_current).state_init;
        state_next = (*prg_current).state_init;
    }
    else
    {
        // Todo: Add Error Handle
    }
    
}

void prgMng_execute(void)
{
    void * tmp = NULL;
    if( state_curr != state_next)
    {
        state_curr = state_next;
        state_curr(state_next);
    }
    if (prg_current != prg_next && state_next == (*prg_current).state_init)
    {
        prg_current = prg_next;
    }
}

void prgMng_loadNextPrg(prgMng_prg * next)
{
    if (prg_current == prg_next)
    {
        prg_next = next; 
    }
}

// Private Functions
