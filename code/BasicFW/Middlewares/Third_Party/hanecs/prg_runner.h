#ifndef __PRG_RUNNER_H
#define __PRG_RUNNER_H

#include "prg_mng.h"

/* Definitions */

/* Typedefs */
typedef enum prgs_e prgs;
/* Structures */
enum prgs_e
{
    PRG_Flash = 0,           // Programm Flash Test
    PRG_ComT,           // Programm Communication Protokol Test
    PRG_Demo,   
    _PRG_END      
};

/*Extern Function Toolset */
/* Setter */
extern void Error_Handler(void);
extern void sendUartMsg(char * str, uint8_t length);
extern void setTimer(uint32_t value);
/* Getter */
extern uint8_t getButtonState(void);
extern uint8_t getPrgTimer0Value(void);
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
uint8_t codImmed(void){ return 1; };

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
uint8_t b1PreAndTimerEq0(void);
uint8_t b1RelAndTimerGt0(void);
uint8_t b1RelAndTimerEq0(void);



prg_handle hPrg1;
state sPrgShow;                                                     // Show Current Program
state sPrgSwtch;                                                    // Switch Programm
state sPrgSwSh;                                                     // Switch or Show
state sPrgDemo;                                                     // Entry Demo Programm
state sPrgComT;                                                     // Start CommunicationTest   

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
        .cnd = codImmed,
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
        .cnd = b1PreAndTimerEq0,
        .to = &sPrgShow
    },
    {
        .cnd = b1Rel,
        .to = &sPrgDemo
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
    sPrgDemo.act = actDemoEnter;
    sPrgDemo.trst_table = ttsPrgDemo;
    sPrgDemo.size = 2;
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
void actDemoEnter(void)
{
    sendUartMsg("Demo timer set to 20\n",sizeof("Demo timer set to 20\n"));
    setTimer(20);
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

#endif