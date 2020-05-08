#ifndef __PRG_MNG_H
#define __PRG_MNG_H
/* includes */
#include "stdint.h"

/* typedefs */
typedef enum prgMng_status_e prgMng_status;
typedef void (*action)(void * args);
typedef void (*getArgs)(void * args);
typedef uint8_t (*condition)(void * args);

typedef struct state_s state;
typedef struct transition_s transition;
typedef struct prg_handle_s prg_handle;

/* Enums */
enum prgMng_status_e {
    PRG_MNG_OK = 1,
    PRG_MNG_FAILED = 0,
} ;

/* Publice Types */
struct state_s {
    getArgs getActArgs;
    action act;
    transition * * trst_table;
} ;
struct transition_s {
    getArgs getCndArgs;
    condition cnd;
    state * to;
} ;
struct prg_handle_s {
    state * current;
} ;


/* Public Function Prototyps */
prgMng_status prgMng_init( prg_handle * hprg , state * init);
prgMng_status prgMng_deinit( prg_handle * hprg);

prgMng_status prgMng_check(  prg_handle * hprg );


#endif