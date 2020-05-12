#ifndef __LOGGER_H
#define __LOGGER_H

#include "dbg_logger.h"

/* Typedefintions -------------------------------------*/
typedef enum signature_e signature;
/* Structures -----------------------------------------*/
enum signature_e {
    SIGNATURE_FREE = 0,
    SIGNATURE_ERROR = 0xDEAD0101,
    SIGNATURE_WARNING = 0xABCDEF98, 
} ;


#endif