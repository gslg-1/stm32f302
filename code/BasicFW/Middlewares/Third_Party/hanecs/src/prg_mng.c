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
    if (t->to->getActArgs != 0)
    {
        void * args = (void *)0;
        
        (t->to->getActArgs)(args);
        (t->to->act)(args);
        hprg->current = t->to;
    }
}



/* Public Function Implementation ---------------------------------------------------------- */


prgMng_status prgMng_init( prg_handle * hprg , state * init)
{
    if (hprg != 0 && hprg->current == 0)
    {
        void * args = (void *)0;

        hprg->current = init;
        (init->getActArgs)(args);
        (init->act)(args);
    
        return PRG_MNG_OK;
    }
    return PRG_MNG_FAILED;
}

prgMng_status prgMng_deinit( prg_handle * hprg)
{
    if (hprg != 0 && hprg->current != 0)
    {
        hprg->current = 0;
        return PRG_MNG_OK;
    }
    return PRG_MNG_FAILED;
}

/**
 * @ todo: May add some timeout variable later to provide more predictability.
*/
prgMng_status prgMng_check(  prg_handle * hprg )
{
    if (hprg != 0 && hprg->current != 0 )
    {
        for (uint8_t i = 0;  hprg->current->trst_table[i] != 0 ; i++)
        {
            if ( hprg->current->trst_table[i] != 0 )
            {
                void * args =(void*)0;
                (*(hprg->current->trst_table[i])).getCndArgs(args);
                if ((*(hprg->current->trst_table[i])).cnd(args))
                {
                    prgMng_switchStat(hprg ,hprg->current->trst_table[i]);
                    return PRG_MNG_OK;
                } 
            }
            
        }
    }
    return PRG_MNG_FAILED;
}