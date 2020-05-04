#include "prg_mng.h"


// Private variables
uint8_t isInitialized;

state * prg_curr;

state * prg_init;
state * prg_next;

// Public Functions
void prgMng_init( state * init)
{
    if (!isInitialized)
    {
        prg_init = init;
        prg_curr = init;
        prg_next = init;
        isInitialized = 1;
    }
}

void prgMng_execute(void)
{
    if (prg_init != prg_next && prg_init == prg_curr)
    {
        prg_init = prg_next;
        prg_curr = prg_next;
    }
    for(uint8_t i = 0; i < (*prg_curr).table_length ; i++)
    {
        if ((*prg_curr).t_table[i].condition==1)
        {
            (*prg_curr).fxn();
            prg_curr = (*prg_curr).t_table[i].to;
        } 
    }
}

void prgMng_loadNextPrg(state * next)
{
    if (prg_curr == prg_next)
    {
        prg_next = next;
    }
}
// Private Functions
