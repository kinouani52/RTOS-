/****************************************************************************/
/*  Test task management using LED                                          */
/*                                                                          */
/****************************************************************************/

#include "includes.h"

#define  TASK_STK_SIZE                  64       /* 定义任务堆栈大小     */


OS_STK   TaskStartStkA[TASK_STK_SIZE];
OS_STK   TaskStartStkB[TASK_STK_SIZE];

void   TaskStartA(void *data);                    /* 前导声明任务（函数） */
void   TaskStartB(void *data);                    /* 前导声明任务（函数） */


void  main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                   /* 禁止看门狗              */
                     // configure P4.7 as output


    OSInit();                                              /* 初始化uCOS-II */
 OSTaskCreate(TaskStartA, ((void*)0),&TaskStartStkA[TASK_STK_SIZE], 5);
 OSTaskCreate(TaskStartB, ((void*)0), &TaskStartStkB[TASK_STK_SIZE], 6);

    OSStart();                                             /* 开始任务调度  */
}

void TaskStartA(void*data){

    WDTCTL = WDT_MDLY_32;
    SFRIE1 |= WDTIE;

    P4DIR |= 0x0080;
 while(1){   P4OUT |= 0x0080;
    OSTimeDly(10);
}
}
void TaskStartB(void*data){
    WDTCTL = WDT_MDLY_32;
    SFRIE1 |= WDTIE;
    P4DIR |= 0x0080;
        while(1){   P4OUT &= ~ 0x0080;
       OSTimeDly(20);
}
}
