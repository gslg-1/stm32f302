#include "prg_mng.h"



/* Private Function Prototyps -------------------------------------------------------------- */
void prgMng_switchStat(prg_handle * hprg , transition * t);

/* Private Function Implementation --------------------------------------------------------- */

/**
 * Private function of the Program Manager;
 * Check for the conditions befor starting.
*/
void prgMng_switchStat(prg_handle * hprg , transition * t)
{
    (t->to->act)();
    hprg->current = t->to;
}



/* Public Function Implementation ---------------------------------------------------------- */


uint8_t prgMng_init( prg_handle * hprg , state * init)
{
    if (hprg != 0 && hprg->current == 0)
    {
        hprg->current = init;
        (init->act)();
        return PRG_MNG_OK;
    }
    return PRG_MNG_FAILED;
}

uint8_t prgMng_deinit( prg_handle * hprg)
{
    if (hprg != 0 && hprg->current != 0)
    {
        hprg->current = 0;
        return PRG_MNG_OK;
    }
    return PRG_MNG_FAILED;
}

state * prgMng_getState( prg_handle * hprg )
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
uint8_t prgMng_check(  prg_handle * hprg )
{
    if (hprg != 0 && hprg->current != 0 )
    {
        uint8_t len= hprg->current->size;
        for (uint8_t i = 0; i < len ; i++)
        {
            if ( (hprg->current->trst_table +i) != 0 )
            {
                
                if ((*(hprg->current->trst_table + i)).cnd())
                {
                    prgMng_switchStat(hprg ,(hprg->current->trst_table +i));
                    return PRG_MNG_OK;
                } 
            }
            
        }
    }
    return PRG_MNG_FAILED;
}