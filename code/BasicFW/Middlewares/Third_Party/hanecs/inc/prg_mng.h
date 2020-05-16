#ifndef __PRG_MNG_H
#define __PRG_MNG_H
/* includes */
#include "dbg_src.h"

/* typedefs */
typedef void (*action)(void);
typedef uint8_t (*condition)(void);

typedef struct state_s state;
typedef struct transition_s transition;
typedef struct prg_handle_s prg_handle;

/* External Functions */
/* Enums */

/* Publice Types */
struct state_s {
    action act;
    transition * trst_table;
    uint8_t size;
} ;
struct transition_s {
    condition cnd;
    state * to;
} ;
struct prg_handle_s {
    state * current;
} ;



/* Public Function Prototyps */
uint8_t prgMng_init( prg_handle * hprg , state * init);
uint8_t prgMng_deinit( prg_handle * hprg);

state * prgMng_getState( prg_handle * hprg );
uint8_t prgMng_check(  prg_handle * hprg );


#endif