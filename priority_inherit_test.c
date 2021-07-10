#include "includes.h"
#include "VTerm.h"

OS_EVENT *mutex;

//#define	TASK_STK_SIZE			64       	// Size of each task's stacks (# of WORDs)
#define	TASK_STK_SIZE			64
#define	N_TASKS				3        	// Number of identical tasks

OS_STK		Task0Stk[N_TASKS][TASK_STK_SIZE];	// Tasks stacks
OS_STK      Task1Stk[N_TASKS][TASK_STK_SIZE];    // Tasks stacks
OS_STK      Task2Stk[N_TASKS][TASK_STK_SIZE];    // Tasks stacks
OS_STK		StartTaskStk[TASK_STK_SIZE];		// TaskStart  task stack
INT8U		TaskData[N_TASKS];			// Parameters to pass to each task

OS_EVENT*mutex;

//prio inherit
//void  PI_Task(void *pdata);
void PI_Task0(void *pdata);
void PI_Task1(void *pdata);
void PI_Task2(void *pdata);
void  PI_TaskStartCreateTasks (void);
static void PI_StartTask(void *pdata);

/********uC/OS-II Demo*****************/
int main( void )
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
 
  
  // Frequency
  //InitFreq();
 
  // LCD init
  //LCDInit();
  //LCDContrast(0x45);

  VTermInit(1);
  WDTCTL = WDT_MDLY_32; /*设置时钟节拍间隔为32ms*/
  SFRIE1 |= BIT0; /* 开看门狗定时器中断*/
  
  
  //lcd_print("---demo ucos-ii priority inherit---\n\n");
  VTermPrintf("---demo ucos-ii priority inherit---\n\n");
  /*---- Any initialization code before starting multitasking ---------------------------------------*/
  OSInit(); 
  OSTaskCreate(PI_StartTask,(void*)0x12345678L,(void *)&StartTaskStk[TASK_STK_SIZE-1],2);//demo ucos-ii priority inherit
  OSStart();
}


/*============================================
*this part is about priority inherit
*
*===========================================*/
static void PI_StartTask(void *pdata) {
    INT8U err;

    mutex = OSMutexCreate(3, &err);
    OSTaskCreate(PI_Task0, ((void*)0) ,&Task0Stk[N_TASKS][TASK_STK_SIZE], 4);
    OSTaskCreate(PI_Task1,((void*)0) ,&Task1Stk[N_TASKS][TASK_STK_SIZE], 5);
    OSTaskCreate(PI_Task2, (void*)0] ,&Task1Stk[N_TASKS][TASK_STK_SIZE], 6);
}

void PI_Task0(void *data)
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
    }
}
void PI_Task1(void *data)
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
    }
}
void PI_Task2(void *data)
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
    }
}
