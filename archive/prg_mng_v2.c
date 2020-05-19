#include "prg_mng.h"


/* Public Function Implementation ---------------------------------------------------------- */


uint8_t prgMng_init( prg_handle * hprg , const state * init)
{
    if (hprg != 0 && hprg->current == 0)
    {
        hprg->current = init;
        (init->act)();
        return PRG_MNG_OK;
    }
    return PRG_MNG_FAILED;
}

uint8_t prgMng_deinit(  prg_handle * hprg)
{
    if (hprg != 0 && hprg->current != 0)
    {
        hprg->current = 0;
        return PRG_MNG_OK;
    }
    return PRG_MNG_FAILED;
}

const state * prgMng_getState(  prg_handle * hprg )
{
    if (hprg != 0 && hprg->current != 0)
    {
        return hprg->current;
    }
    return NULL;
}

/**
 * @ todo: May add some timeout variable later to provide more predictability.
*/
uint8_t prgMng_checkTrans( prg_handle * hprg )
{
    if (hprg != 0 && hprg->current != 0 )
    {
        for (uint8_t i = 0; hprg->current->tran_t[i] != NULL ; i++)
        {
            state * goal = hprg->current->tran_t[i]();
            if (goal != NULL)
            {
                goal->act();
                hprg->current = goal;
                return PRG_MNG_OK;
            } 
        }
    }
    return PRG_MNG_FAILED;
}