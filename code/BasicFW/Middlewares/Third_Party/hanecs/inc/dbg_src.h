#ifndef __DBG_SRC
#define __DBG_SRC
/* Includes ----------------------------------------------- */
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

/* Typedefinitions ---------------------------------------- */
typedef enum prgMng_status_e prgMng_status;
/* Structs ------------------------------------------------ */
enum prgMng_status_e {
    PRG_MNG_OK = 1,
    PRG_MNG_FAILED = 0,
} ;

/* external Function Prototyps ---------------------------- */
extern void sendUartMsg(char * str, uint8_t length);                    /* delete after debugging */
extern void sendUartMsgInt(uint32_t  num, uint8_t base);                    /* delete after debugging */
/* Function Prototyps ------------------------------------- */

/* Function Implementations ------------------------------- */


#endif