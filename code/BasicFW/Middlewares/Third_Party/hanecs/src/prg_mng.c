#include "prg_mng.h"

//static state prg_base;
//static event * prg_table[];
//static uint8_t prg_isInitialized;
//
//// ---------------------------------- Prg Manager -----------------------------------------
//void prg_init( stage s_base , event * e_table[] )
//{
//    prg_setBase( s_base );
//    prg_setTabel ( e_table );
//    prg_isInitialized =1;
//}
//void prg_setBase( stage s_base )
//{
//    prg_base = s_base;
//}
//void prg_setTabel ( event * e_table[] )
//{
//    prg_table = e_table;
//}
//
// ---------------------------------- State Machine -----------------------------------------

// Private variables
uint8_t isInitialized;

state state_curState;



// Public Functions
state prgMng_getCurState(void )
{
    return state_curState;
}

void prgMng_init( state init)
{
    if (!isInitialized)
    {
        state_curState = init;
        isInitialized = 1;
    }
}

void prgMng_exeEvent(event * e, void * args)
{
    if (isInitialized)
    {
        if ((*e).from == state_curState )
        {
            (*e).to(args);
            state_curState = (*e).to;
        }
    }
}

// Private Functions
