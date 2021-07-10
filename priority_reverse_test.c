#include "includes.h"
#include "VTerm.h"



#define TASK_STK_SIZE       64          // Size of each task's stacks (# of WORDs)



OS_STK StartTaskStk[TASK_STK_SIZE];
OS_STK Task0Stk[TASK_STK_SIZE];
OS_STK Task1Stk[TASK_STK_SIZE];
OS_STK Task2Stk[TASK_STK_SIZE];
OS_EVENT *mutex;


void PrioRevStartTask (void *pdata);
void PrioReverseTask0(void *pdata);
void PrioReverseTask1(void *pdata);
void PrioReverseTask2(void *pdata);



/********uC/OS-II Demo*****************/
int main(void)
{



    WDTCTL = WDTPW + WDTHOLD;
    /**** INITIALIZATION ****/
    //all as input
    P1DIR = 0x0;
    P2DIR = 0x0;
    P3DIR = 0x0;
    P4DIR = 0x0;
    P5DIR = 0x0;
    P6DIR = 0x0;
    P1DIR |= 0x0001;
    P4DIR |= 0x0080;
    P1DIR |= 0x0010;
    P1DIR |= 0x0020;
    P1SEL &= ~0x0020;
    P1SEL &= ~0x0001;
    P4SEL &= ~0x0080;
    P1SEL &= ~0x0010;
    VTermInit(1);



    WDTCTL = WDT_MDLY_32; /*设置时钟节拍间隔为32ms*/
    SFRIE1 |= BIT0; /* 开看门狗定时器中断*/



    /*---- Any initialization code before starting multitasking ---------------------------------------*/
    OSInit();

    //OSTaskCreate(PrioRevStartTask,(void*)0x12345678L,(void *)&StartTaskStk[TASK_STK_SIZE-1],3); //demo ucos-ii priority reverse
   OSTaskCreate(PrioRevStartTask,(void*)0x1234,(void *)&StartTaskStk[TASK_STK_SIZE-1],3); //demo ucos-ii priority reverse




    OSStart();
}



/*============================================
 *this part is about priority reverse
 *
 *===========================================*/
void PrioRevStartTask (void *pdata){
    pdata = pdata;
    mutex = OSSemCreate(0);

    OSTaskCreate(PrioReverseTask0, ((void*) 0), &Task0Stk[TASK_STK_SIZE], 5);
     //  OSTaskCreate(PrioReverseTask1, ((void*) 0), &Task1Stk[TASK_STK_SIZE], 5);
       OSTaskCreate(PrioReverseTask2, ((void*) 0), &Task2Stk[TASK_STK_SIZE], 6);

OSTaskSuspend(3);
}



void PrioReverseTask0(void *data)
{
    WDTCTL = WDT_MDLY_32;
    SFRIE1 = WDTIE;
  // INT8U err;
    while (1)
    {
        OSTimeDlyHMSM(0, 0, 0, 75);
        P1OUT ^= 0x0001;
        OSTimeDlyHMSM(0, 0, 0, 100);
        P1OUT ^= 0x0001;
        OSSemPost(mutex);
        P1OUT ^= 0x0001;
        OSTimeDlyHMSM(0, 0, 0, 75);

      /*  // VTermPrintf("T0 is executing ...\n");
       // P1OUT ^= 0x0001;
       // OSTimeDly(200);
        // VTermPrintf("T0 is is loading to the system\n");
        //  VTermPrintf("T0 is trying to get mutex.\n");
        P1OUT ^= 0x0020;
        OSSemPend(mutex, 0, &err);
        P1OUT ^= 0x0001; // locked the mutex
        OSTimeDly(200);
        P1OUT ^= 0x0001; // releasing the mutex
        OSSemPost(mutex);*/
    };
}
;



void PrioReverseTask1(void *data)
{
    WDTCTL = WDT_MDLY_32;
    SFRIE1 = WDTIE;
    while (1)
    {
        //VTermPrintf("T1 is executing..\n");
        P1OUT ^=(0x0010);
        OSTimeDly(100);
        // VTermPrintf("T1 is Running well\n");
        P1OUT ^= 0x0020; // runing well
        OSTimeDly(100);
    };
}
;



void PrioReverseTask2(void *data)
{
    WDTCTL = WDT_MDLY_32;
    SFRIE1 = WDTIE;
    INT8U err;
    while (1)
    {
        OSSemPend(mutex, 0, &err);
        P4OUT ^= 0x0080;
        OSTimeDlyHMSM(0, 0, 0, 75);
        P4OUT ^= 0x0080;
        /*
        //VTermPrintf("T2 is trying to get mutex.\n");
        P4OUT ^= 0x0080;
        OSSemPend(mutex, 0, &err);
        P4OUT ^= 0x0080;
        //VTermPrintf("T2 got mutex.\n");
        OSTimeDly(200);
        P4OUT ^= 0x0080;
        //VTermPrintf("T2 mutex released.\n");
        OSSemPost(mutex);
        */
    };
}
;
