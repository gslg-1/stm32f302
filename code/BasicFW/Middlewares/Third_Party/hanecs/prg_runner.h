#ifndef __PRG_RUNNER_H
#define __PRG_RUNNER_H
/**
 * @ Todo:
*/



#include "prg_mng.h"

/* Definitions */

/* Typedefs */
typedef enum prgs_e prgs;
/* Structures */
enum prgs_e
{
    PRG_Demo = 0,               // Program Demo
    PRG_CErr,                   // Program Create Errors
    PRG_HEra,                   // Program Erase HNCS Flash Block
    PRG_TNext,                  // Program Erase HNCS Flash Block
    PRG_PErr,                   // Program Print All Errors
    _PRG_END,
};

/*Extern Function Toolset */
extern void DBG_Error_Handler( uint8_t mod , uint8_t fnx , uint8_t num , uint8_t val );
extern void sendUartMsg(char * str, uint8_t length);
extern void setTimer(uint32_t value);

extern uint8_t getButtonState(void);
extern uint8_t getPrgTimer0Value(void);

extern uint8_t writeError( uint8_t module , uint8_t function , uint8_t number , uint8_t value);
extern uint8_t printErrorData ( void );
extern uint8_t flash_eraseHNCS( void );
extern uint8_t flash_writeNext( void );

extern void resetUartCom(void);

/*Intern Function Toolset*/
/* Setter */
void setCurPrg(uint8_t prg);
/* Getter */
uint8_t getCurPrg(void);

/* Variables */
prgs curPrg = PRG_Demo;
uint32_t prgMng_timer0;

/* Dummy */
void actDoNothing(void){};
uint8_t immediately(void){ return 1; };

/* External Variables */

/* Actions */
/* Program Selection - Button */
void actPrintCurrentPrg(void);
void actNextPrg(void);
void actSetTimer(void);
/* Program Selection - UART */
void actSetCurUartPrg(void);
/* Program Start */
void actPrgStartMsg(void);

/* Program Demo */
void actDemoEnter(void);
/* Program Erase HNCS Flash Block */
void actHEraEnter(void);
/* Test Program - Write Test Package to Flash */
void actTFNextEnter(void);
/* Program Print Error */
void actPErrEnter(void);
/* Program Create Error */
void actCErrEnter(void);
void actCErrBase(void);
void actCErrOr(void);
void actCErrCreate(void);

/* Conditions*/
extern uint8_t b1Pre(void);
extern uint8_t timerEq0(void);
extern uint8_t timerGt0(void);

extern uint8_t uartCmdIsAvailable(void);
extern uint8_t getUartCmd(void);


uint8_t b1Rel(void);
uint8_t prgEqDemo(void);
uint8_t prgEqTNext(void);
uint8_t prgEqHEra(void);
uint8_t prgEqCErr(void);
uint8_t prgEqPErr(void);
uint8_t b1PreAndTimerEq0(void);
uint8_t b1RelAndTimerGt0(void);
uint8_t b1RelAndTimerEq0(void);



prg_handle hPrg1;
/* Program Selection - Button */
state sPrgShow;                                                     // Show Current Program
state sPrgSwtch;                                                    // Switch Programm
state sPrgSwSh;                                                     // Switch or Show
/* Program Selection - UART */
state sUartCmd;  

/* Program Start */
state sPrgStart;

/* Program Demo */
state sPrgDemo;                                                     // Entry Demo Programm

/* Program Print all Errors */
state sPrgHEra;                                                     // Entry Erase HNCS Flash Block
/* Program Print all Errors */
state sPrgTFNext;                                                     // Testprogram -Entry Write Next Flash Package

/* Program Print all Errors */
state sPrgPErr;                                                     // Entry Print Errors

/* Program Create all Errors */
state sPrgCErr;                                                     // Entry
state sPrgCErrB;                                                    // Base
state sPrgCErrO;                                                    // Leaf or create Error
state sPrgCErrC;                                                    // Create Error


/* ------------------ Program Selection - Button ------------------ */
/** 
 * Transitions form sPrgShow 
 * Show Current Program
*/
transition ttsPrgShow[] = 
{ 
    {
        .cnd = uartCmdIsAvailable,
        .to  = &sUartCmd
    },
    {
        .cnd = b1Pre,
        .to  = &sPrgSwSh
    }
};

/** 
 * Transitions form sPrgSwtch
 * Switch Programm
 */
transition ttsPrgSwtch[] = 
{ 
    {
        .cnd = immediately,
        .to = &sPrgShow
    }
};

/** 
 * Transitions form sPrgSwSh 
 * 
*/
transition ttsPrgSwSh[] = 
{ 
    {
        .cnd = b1Rel,
        .to = &sPrgSwtch
    },
    {
        .cnd = timerEq0,
        .to = &sPrgStart
    }
} ;

/* ------------------ Program Selection - UART ------------------ */
/** 
 * Transitions form ttsUartCmd 
 * 
*/
transition ttsUartCmd[] = 
{ 
    {
        .cnd = immediately,
        .to = &sPrgStart
    }
} ;


/* ------------------ Program Start ------------------ */

/** 
 * Transitions form sPrgStart 
 * Switch or Show
*/
transition ttsPrgStart[] = 
{ 
    {
        .cnd = prgEqDemo,
        .to = &sPrgDemo
    },
    {
        .cnd = prgEqHEra,
        .to = &sPrgHEra
    },
    {
        .cnd = prgEqTNext,
        .to = &sPrgTFNext
    },
    {
        .cnd = prgEqCErr,
        .to = &sPrgCErr
    },
    {
        .cnd = prgEqPErr,
        .to = &sPrgPErr
    },
    {
        .cnd = immediately,
        .to = &sPrgSwtch
    }
};


/* ------------------ Program Modes ------------------ */
/** 
 * Transitions form sPrgDemo 
 * Entry Demo Programm
 */
transition ttsPrgDemo[] = 
{ 
    {
        .cnd = b1Rel,
        .to = &sPrgShow
    }
};

/** 
 * Transitions form sPrgPErr 
 * Entry PErr
 */
transition ttsPrgHEra[] = 
{ 
    {
        .cnd = b1Rel,
        .to = &sPrgShow
    }
};
/** 
 * Transitions form sPrgPErr 
 * Entry PErr
 */
transition ttsPrgTFNext[] = 
{ 
    {
        .cnd = b1Rel,
        .to = &sPrgShow
    }
};
/** 
 * Transitions form sPrgPErr 
 * Entry PErr
 */
transition ttsPrgPErr[] = 
{ 
    {
        .cnd = b1Rel,
        .to = &sPrgShow
    }
};


/** 
 * Transitions form sPrgCErr 
 * state sPrgCErr Entry
 */
transition ttsPrgCErr[] = 
{ 
    {
        .cnd = b1Rel,
        .to = &sPrgCErrB
    }
};
/** 
 * Transitions form sPrgCErr 
 * state sPrgCErrB Base
 */
transition ttsPrgCErrB[] = 
{ 
    {
        .cnd = b1Pre,
        .to = &sPrgCErrO
    }
};
/** 
 * Transitions form sPrgCErr 
 * state sPrgCErr Leaf or create Error
 */
transition ttsPrgCErrO[] = 
{ 
    {
        .cnd = b1Rel,
        .to = &sPrgCErrC
    },
    {
        .cnd = timerEq0,
        .to = &sPrgShow
    },
};
/** 
 * Transitions form sPrgCErr 
 * state sPrgCErr Create Error
 */
transition ttsPrgCErrC[] = 
{ 
    {
        .cnd = immediately,
        .to = &sPrgCErrB
    }
};


uint8_t hPrg1_init(void)
{  
    /* Program Selection - Button */
    sPrgShow.act = actPrintCurrentPrg;
    sPrgShow.trst_table = ttsPrgShow;
    sPrgShow.size = 1;

    sPrgSwtch.act = actNextPrg;
    sPrgSwtch.trst_table = ttsPrgSwtch;
    sPrgSwtch.size = 1;
    
    sPrgSwSh.act = actSetTimer;
    sPrgSwSh.trst_table = ttsPrgSwSh;
    sPrgSwSh.size = 2;
    
    /* Program Selection - UART */
    sUartCmd.act = actSetCurUartPrg;
    sUartCmd.trst_table = ttsUartCmd;
    sUartCmd.size = 1;
    
    
    /* Program Start */
    sPrgStart.act = actPrgStartMsg;
    sPrgStart.trst_table = ttsPrgStart;
    sPrgStart.size = 6;

    /* Program Modes */
    /* Demo */
    sPrgDemo.act = actDemoEnter;
    sPrgDemo.trst_table = ttsPrgDemo;
    sPrgDemo.size = 1;
    /* HEra */
    sPrgHEra.act = actHEraEnter;
    sPrgHEra.trst_table = ttsPrgHEra;
    sPrgHEra.size = 1;
    /* TFNext */
    sPrgTFNext.act = actTFNextEnter;
    sPrgTFNext.trst_table = ttsPrgTFNext;
    sPrgTFNext.size = 1;
    /* PErr */
    sPrgPErr.act = actPErrEnter;
    sPrgPErr.trst_table = ttsPrgPErr;
    sPrgPErr.size = 1;
    /* CErr */
    sPrgCErr.act = actCErrEnter;
    sPrgCErr.trst_table = ttsPrgCErr;
    sPrgCErr.size = 1;
    sPrgCErrB.act = actCErrBase;
    sPrgCErrB.trst_table = ttsPrgCErrB;
    sPrgCErrB.size = 1;
    sPrgCErrO.act = actCErrOr;
    sPrgCErrO.trst_table = ttsPrgCErrO;
    sPrgCErrO.size = 2;
    sPrgCErrC.act = actCErrCreate;
    sPrgCErrC.trst_table = ttsPrgCErrC;
    sPrgCErrC.size = 1;

    if (prgMng_init(&hPrg1, &sPrgShow)==PRG_MNG_OK)
    {
        return PRG_MNG_OK;
    }
    return PRG_MNG_FAILED;
}



/* Implementation of the Functions --------------------------------------------------------------*/
/* Intern Function Toolset */
/* Setter */
void setCurPrg(uint8_t prg)
{
    curPrg = prg;
}

/* Getter */
uint8_t getCurPrg(void)
{
    return curPrg;
}


/* Actions */
/* Program Selection - Button */
void actPrintCurrentPrg(void)
{
    switch (getCurPrg())
    {
        case PRG_CErr:
        {
            sendUartMsg("PRG_CErr\n",sizeof("PRG_CErr\n"));
            break;
        }
        case PRG_PErr:
        {
            sendUartMsg("PRG_PErr\n",sizeof("PRG_PErr\n"));
            break;
        }
        case PRG_HEra:
        {
            sendUartMsg("PRG_HEra\n",sizeof("PRG_HEra\n"));
            break;
        }
        case PRG_TNext:
        {
            sendUartMsg("PRG_TNext\n",sizeof("PRG_TNext\n"));
            break;
        }
        case PRG_Demo:
        {
            sendUartMsg("PRG_Demo\n",sizeof("PRG_Demo\n"));
            break;
        }
        default:
        {
            sendUartMsg("Error: actPrintCurrentPrg\n",sizeof("Error: actPrintCurrentPrg\n"));
            DBG_Error_Handler( MOD_PRG_RUNNER_H , FNC_actPrintCurrentPrg , RSN_UNEXPECTED_VALUE , 0 );
        }
    }
}
void actNextPrg(void)
{
    uint8_t curPrg = getCurPrg();
    if (curPrg < _PRG_END-1)
    {
        setCurPrg(curPrg+1);    
    }
    else
    {
        setCurPrg(0);
    }
}
void actSetTimer(void)
{
    setTimer(20);
}

/* Program Selection - UART */
void actSetCurUartPrg(void)
{
    uint8_t cmd = _PRG_END;
    cmd = getUartCmd();
    setCurPrg(cmd);
    resetUartCom();
}

/* Program Start */
void actPrgStartMsg(void)
{
    sendUartMsg("Start Program Mode\n" , sizeof("Start Program Mode\n") );
}

/* Program Demo */
void actDemoEnter(void)
{
    static uint8_t counter = 0;
    sendUartMsg("This is just a Demo Message\n",sizeof("This is just a Demo Message\n"));
    counter++;
    switch (counter%7)
    {
    case 1:
        sendUartMsg("Hallo Vishal\n",sizeof("Hallo Vishal\n"));
        break;
    case 2:
        sendUartMsg("Hallo Mani\n",sizeof("Hallo Mani\n"));
        break;
    case 3:
        sendUartMsg("Hallo Patrick\n",sizeof("Hallo Patrick\n"));
        break;
    case 4:
        sendUartMsg("Hallo Max\n",sizeof("Hallo Max\n"));
        break;
    case 5:
        sendUartMsg("Hallo Sven\n",sizeof("Hallo Sven\n"));
        break;
    case 6:
        sendUartMsg("Hallo Swati\n",sizeof("Hallo Swati\n"));
        break;
    
    default:
        sendUartMsg("Hallo Christina\n",sizeof("Hallo Christina\n"));
        break;
    }
}
/* Program Print All Errors*/
void actHEraEnter(void)
{
    sendUartMsg("Erase hole HNCS Flash Block\n",sizeof("Erase hole HNCS Flash Block\n"));
    if ( flash_eraseHNCS() == PRG_MNG_FAILED )
    {
        sendUartMsg("Couldn\'t erase the HNCS Flash Block.\n",sizeof("Couldn\'t erase the HNCS Flash Block.\n"));
    }
}
/* Program Print All Errors*/
void actTFNextEnter(void)
{
    sendUartMsg("Test - Write Next Element\n",sizeof("Test - Write Next Element\n"));
    if ( flash_writeNext() == PRG_MNG_FAILED )      /*todo - exchange*/
    {
        sendUartMsg("Couldn\'t write the next Block.\n",sizeof("Couldn\'t write the next Block.\n"));
    }
}
/* Program Print All Errors*/
void actPErrEnter(void)
{
    sendUartMsg("Entered the Print All Errors Mode\n",sizeof("Entered the Print All Errors Mode\n"));
    if ( printErrorData() == PRG_MNG_FAILED )
    {
        sendUartMsg("No Error available\n",sizeof("No Error available\n"));
    }
}
/* Program Create Errors */
void actCErrEnter(void)
{
    sendUartMsg("Entered the Error Create Mode\n",sizeof("Entered the Error Create Mode\n"));
}
void actCErrBase(void)
{
    sendUartMsg("Press B1 to create one more Error.\n",sizeof("Press B1 to create one more Error.\n"));
    sendUartMsg("Hold B1 to leaf this mode.\n",sizeof("Hold B1 to leaf this mode.\n"));
}
void actCErrOr(void)
{
    setTimer(20);
}
void actCErrCreate(void)
{
    static uint8_t counter = 0;
    sendUartMsg("Creating Error ...\n",sizeof("Creating Error ...\n"));
    if (writeError(counter,counter+1,counter+2,counter+3) != PRG_MNG_OK)
    {
        sendUartMsg("Can't write an Error, currently in worg mode.\n",sizeof("Can't write an Error, currently in worg mode.\n"));
    }
    counter++;
}


/* Conditions*/
uint8_t b1Pre(void)
{
    return (getButtonState()==0U);
}
uint8_t b1Rel(void)
{
    return (getButtonState()==1U);
}
uint8_t timerEq0(void)
{
    return (getPrgTimer0Value()==0U);
}
uint8_t timerGt0(void)
{
    return (getPrgTimer0Value()>0U);
}
uint8_t b1PreAndTimerEq0(void)
{
    if (getButtonState() == 0U  &&  !getPrgTimer0Value() )
    {
        return 1;
    }
    return 0;
}
uint8_t b1PreAndTimerGt0(void)
{
    if (getButtonState() == 0U  &&  getPrgTimer0Value() > 0U )
    {
        return 1;
    }
    return 0;
}
uint8_t b1RelAndTimerGt0(void)
{
    if (getButtonState() == 1  &&  getPrgTimer0Value() > 0 )
    {
        return 1;
    }
    return 0;
}
uint8_t b1RelAndTimerEq0(void)
{
    if (getButtonState() == 1  &&  !getPrgTimer0Value() )
    {
        return 1;
    }
    return 0;
}
uint8_t prgEqDemo(void)
{
    if (  getCurPrg() == PRG_Demo )
    {
        return 1;
    }
    return 0;
}
uint8_t prgEqHEra(void)
{
    if ( getCurPrg() == PRG_HEra)
    {
        return 1;
    }
    return 0;
}
uint8_t prgEqTNext(void)
{
    if ( getCurPrg() == PRG_TNext)
    {
        return 1;
    }
    return 0;
}
uint8_t prgEqCErr(void)
{
    if ( getCurPrg() == PRG_CErr)
    {
        return 1;
    }
    return 0;
}
uint8_t prgEqPErr(void)
{
    if ( getCurPrg() == PRG_PErr)
    {
        return 1;
    }
    return 0;
}

#endif