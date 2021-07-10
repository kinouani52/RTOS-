/****************************************************************************/
/*  Test task management using LED                                          */
/*                                                                          */
/****************************************************************************/

#include "includes.h"

#define  TASK_STK_SIZE                  64       /* ���������ջ��С     */


OS_STK   TaskStartStkA[TASK_STK_SIZE];
OS_STK   TaskStartStkB[TASK_STK_SIZE];

void   TaskStartA(void *data);                    /* ǰ���������񣨺����� */
void   TaskStartB(void *data);                    /* ǰ���������񣨺����� */


void  main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                   /* ��ֹ���Ź�              */
                     // configure P4.7 as output


    OSInit();                                              /* ��ʼ��uCOS-II */
 OSTaskCreate(TaskStartA, ((void*)0),&TaskStartStkA[TASK_STK_SIZE], 5);
 OSTaskCreate(TaskStartB, ((void*)0), &TaskStartStkB[TASK_STK_SIZE], 6);

    OSStart();                                             /* ��ʼ�������  */
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
