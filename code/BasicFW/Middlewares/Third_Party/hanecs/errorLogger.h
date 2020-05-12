#ifndef __ERRORLOGGER_H
#define __ERRORLOGGER_H

#include "logger.h"

/* Typedefs ---------------------------------------------------- */
typdef struct errorData_s errorData;
/* Structs ----------------------------------------------------- */
struct errorData_s
{
    uint32_t * signature;
    uint8_t module;
    uint8_t function;
    uint8_t number;
    uint8_t value;
} ;

/* External Variables ------------------------------------------ */
/* Variables --------------------------------------------------- */
Log ErrorLogger;

/* External Functions */
extern void sendUartMsg(char * str, uint8_t length);
extern void Error_Handler(void);
/* Function Prototyps ------------------------------------------ */
uint8_t initErrorLog(uint32_t * start, uint32_t * end);
uint8_t writeError( uint8_t module , uint8_t function , uint8_t number , uint8_t value);
uint8_t printErrorData ();
/* Special Functions ------------------------------------------- */
void errorStringBuilder( char * str, uint8_t strLength , uint8_t module , uint8_t function , uint8_t number , uint8_t value );

/* Function Implementation ------------------------------------- */
uint8_t initErrorLog(uint32_t * start, uint32_t * end)
{
    if (start != NULL && end > start + 2)
    {
        if (logger_init(  ErrorLogger , SIGNATURE_ERROR , 2 , start , end ) != PRG_MNG_OK)
        {
            return PRG_MNG_FAILED;
        }
        return PRG_MNG_OK;
    }
    return PRG_MNG_FAILED;
}
uint8_t writeError( uint8_t module , uint8_t function , uint8_t number , uint8_t value)
{
    errorData ed = {
        .signature = ErrorLogger.signature,
        .module = module,
        .function = function,
        .number = number,
        .value = value
    } ;
    logger_add( ErrorLogger ,  ed );     /* Ignor the result if it doesn't work we lose the error but thats ok*/
}

uint8_t printErrorData ()
{
    if (logger_switch ( ErrorLogger , LOG_MODE_READ ) == PRG_MNG_OK )
    {
        errorData * ed  = NULL;
        uint32_t * cur = NULL;
        uint msgLength = 99;
        char msg[msgLength]; 
        logger_PgetFirst( ErrorLogger , cur );
        ed = (errorData *)cur;
        errorStringBuilder( msg , msgLength , ed->module , ed->function , ed->number , ed->value );
        sendUartMsg(msg,msgLength);
        while (logger_PgetNext( ErrorLogger , cur) != PRG_MNG_FAILED )
        {
            ed = (errorData *)cur;
            errorStringBuilder( msg , msgLength , ed->module , ed->function , ed->number , ed->value );
            sendUartMsg(msg,msgLength);
        }
        if (logger_switch ( ErrorLogger , LOG_MODE_WRITE_FREE ) != PRG_MNG_OK )
        {
            Error_Handler();
        }
        return PRG_MNG_OK;
    }
    return PRG_MNG_FAILED;
}

void errorStringBuilder( char * str, uint8_t strLength , uint8_t module , uint8_t function , uint8_t number , uint8_t value )
{
    /* String clear */
    memset(str,0,strLength);
    /* String Cat */
    char mod[3];
    char func[3];
    char num[3];
    char value[3];
    itoa( module , mod , 10 );
    itoa( function , func , 10 );
    itoa( number , num , 10 );
    itoa( value , value , 10 );

    strcat( str , "Error -> ( m:" );
    strcat( str , mod );
    strcat( str , " | f:" );
    strcat( str , func );
    strcat( str , " | #:" );
    strcat( str , num );
    strcat( str , " | v:" );
    strcat( str , value );
    strcat( str , " )" );
}

#endif