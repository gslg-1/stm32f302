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

/* Error Location Identifier Enums */
enum modules_e{
    MOD_MAIN_C,
    PRG_RUNNER_H,
    MODULES_ENUM_END
} ;
enum functions_mod_main_c{
    FNC_main,
    FNC_HAL_UART_RxCpltCallback,
    FNC_MX_DMA_UART2_RX_Init,
    FNC_MX_USART2_UART_Init,
    FNC_SystemClock_Config,
    
    FUNCTIONS_MAINC_ENUM_END
} ;
enum functions_mod_prg_runner_h{
    FNC_actPrintCurrentPrg,
    
    FUNCTIONS_PRGRUNNERH_ENUM_END
} ;
enum reason{
    RSN_BUFFER_OVERFLOW,
    RSN_OPEN_RECEIVE_FRAME_FAILED,
    RSN_INIT_FAILURE,
    RSN_UNEXPECTED_VALUE,

    REASON_ENUM_END
} ;

/* external Function Prototyps ---------------------------- */
extern void sendUartMsg(char * str, uint8_t length);                    /* delete after debugging */
extern void sendUartMsgInt(uint32_t  num, uint8_t base);                    /* delete after debugging */
/* Function Prototyps ------------------------------------- */

/* Function Implementations ------------------------------- */


#endif