#ifndef __PRG_RUNNER_H
#define __PRG_RUNNER_H

#include "prg_mng.h"

/* Definitions */

/* Typedefs */
typedef enum prgs_e prgs;
/* Structures */
enum prgs_e
{
    PRG_Flash = 0,              // Program Flash Test
    PRG_ComT,                   // Program Communication Protokol Test
    PRG_Demo,                   // Program Demo
    PRG_CErr,                   // Program Create Errors
    PRG_PErr,                   // Program Print All Errors
    _PRG_END      
};

/*Extern Function Toolset */
extern void Error_Handler(void);
extern void sendUartMsg(char * str, uint8_t length);
extern void setTimer(uint32_t value);

extern uint8_t getButtonState(void);
extern uint8_t getPrgTimer0Value(void);

extern uint8_t writeError( uint8_t module , uint8_t function , uint8_t number , uint8_t value);
extern uint8_t printErrorData ();

/*Intern Function Toolset*/
/* Setter */
void setCurPrg(uint8_t prg);
/* Getter */
uint8_t getCurPrg(void);

/* Variables */
prgs curPrg = PRG_Flash;
uint32_t prgMng_timer0;

/* Dummy */
void actDoNothing(void){};
uint8_t immediately(void){ return 1; };

/* External Variables */

/* Actions */
void actPrintCurrentPrg(void);
void actNextPrg(void);
void actDemoEnter(void);
void actSetTimer(void);
/* Conditions*/
extern uint8_t b1Pre(void);
extern uint8_t timerEq0(void);
extern uint8_t timerGt0(void);
uint8_t b1Rel(void);
uint8_t b1Pre_TimerEq0_prgEqDemo(void);
uint8_t b1Pre_TimerEq0_prgEqCErr(void);
uint8_t b1Pre_TimerEq0_prgEqPErr(void);
uint8_t b1PreAndTimerEq0(void);
uint8_t b1RelAndTimerGt0(void);
uint8_t b1RelAndTimerEq0(void);



prg_handle hPrg1;
/* Program Selection*/
state sPrgShow;                                                     // Show Current Program
state sPrgSwtch;                                                    // Switch Programm
state sPrgSwSh;                                                     // Switch or Show

/* Program Demo */
state sPrgDemo;                                                     // Entry Demo Programm

/* Program Print all Errors */
state sPrgPErr;                                                     // Entry Print Errors

/* Program Create all Errors */
state sPrgCErr;                                                     // Entry
state sPrgCErrB;                                                    // Base
state sPrgCErrO;                                                    // Leaf or create Error
state sPrgCErrC;                                                    // Create Error


/** 
 * Transitions form sPrgShow 
 * Show Current Program
*/
transition ttsPrgShow[] = 
{ 
    {
        .cnd =b1Pre,
        .to  =&sPrgSwSh
    }
};

/** 
 * Transitions form sPrgSwSh 
 * Switch or Show
*/
transition ttsPrgSwSh[] = 
{ 
    {
        .cnd = b1Pre_TimerEq0_prgEqDemo,
        .to = &sPrgDemo
    },
    {
        .cnd = b1Pre_TimerEq0_prgEqCErr,
        .to = &sPrgCErr
    },
    {
        .cnd = b1Pre_TimerEq0_prgEqCErr,
        .to = &sPrgPErr
    },
    {
        .cnd = b1RelAndTimerGt0,
        .to = &sPrgSwtch
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
        .cnd = immediately,
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


void hPrg1_init(void)
{  
    sPrgShow.act = actPrintCurrentPrg;
    sPrgShow.trst_table = ttsPrgShow;
    sPrgShow.size = 1;
    sPrgSwtch.act = actNextPrg;
    sPrgSwtch.trst_table = ttsPrgSwtch;
    sPrgSwtch.size = 1;
    sPrgSwSh.act = actSetTimer;
    sPrgSwSh.trst_table = ttsPrgSwSh;
    sPrgSwSh.size = 2;
    /* Demo */
    sPrgDemo.act = actDemoEnter;
    sPrgDemo.trst_table = ttsPrgDemo;
    sPrgDemo.size = 1;
    /* PErr */
    sPrgPErr.act = actPErrEnter;
    sPrgPErr.trst_table = ttsPrgPErr;
    sPrgPErr.size = 2;
    /* CErr */
    sPrgCErr.act = actCErrEnter;
    sPrgCErr.trst_table = ttsPrgPErr;
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

    if (prgMng_init(&hPrg1, &sPrgShow)!=PRG_MNG_OK)
    {
        sendUartMsg("prg_runner.h <-> 1\n",sizeof("prg_runner.h <-> 1\n"));
        Error_Handler();
    }
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
void actPrintCurrentPrg(void)
{
    switch (getCurPrg())
    {
        case PRG_Flash:
        {
            sendUartMsg("PRG_Flash\n",sizeof("PRG_Flash\n"));
            break;
        }
        case PRG_ComT:
        {
            sendUartMsg("PRG_ComT\n",sizeof("PRG_ComT\n"));
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
            Error_Handler();
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
/* Program Demo */
void actDemoEnter(void)
{
    sendUartMsg("This is just a Demo Message\n",sizeof("This is just a Demo Message\n"));
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
    setTimer(40);
}
void actCErrCreate(void)
{
    static uint32_t counter = 0;
    sendUartMsg("Creating Error ...\n",sizeof("Creating Error ...\n"));
    if (writeError(counter,counter + counter%7,counter + counter%9,~counter) != PRG_MNG_OK)
    {
        sendUartMsg("Can't write an Error, currently in worg mode.\n",sizeof("Can't write an Error, currently in worg mode.\n"));
    }
}
void actSetTimer(void)
{
    setTimer(20);
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
uint8_t b1Pre_TimerEq0_prgEqDemo(void)
{
    if (b1PreAndTimerEq0() && getCurPrg() == PRG_Demo)
    {
        return 1;
    }
    return 0;
}
uint8_t b1Pre_TimerEq0_prgEqCErr(void)
{
    if (b1PreAndTimerEq0() && getCurPrg() == PRG_CErr)
    {
        return 1;
    }
    return 0;
}
uint8_t b1Pre_TimerEq0_prgEqPErr(void)
{
    if (b1PreAndTimerEq0() && getCurPrg() == PRG_PErr)
    {
        return 1;
    }
    return 0;
}

#endif