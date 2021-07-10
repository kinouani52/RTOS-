#include "includes.h"
#include "VTerm.h"

int count = 0; //this is for counting switching times
OS_STK Task1Stk[64];
OS_STK Task2Stk[64];
OS_STK StartTaskStk[64];

//task management
void TaskMgtTask1(void *pdata);
void TaskMgtTask2(void *pdata);
static void TaskMgtStartTask(void *pdata);

/********uC/OS-II Demo*****************/
int main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    P1SEL &= ~0x0001;
    P4SEL &= ~ 0x0080;
    P4DIR |= 0x0080;
    P1DIR |= 0x0001;
    /**** INITIALIZATION ****/
    //all as input
  //  P1DIR = 0x0;
 //   P2DIR = 0x0;
 //   P3DIR = 0x0;
  //  P4DIR = 0x0;
  //  P5DIR = 0x0;
  //  P6DIR = 0x0;

    // Frequency
//    InitFreq();

    // LCD init
    VTermInit(1);

    WDTCTL = WDT_MDLY_32; /*设置时钟节拍间隔为32ms*/
    SFRIE1 |= BIT0; /* 开看门狗定时器中断*/

//  lcd_print("---demo ucos-ii task management---\n");
    VTermPrintf("---demo ucos-ii task management---\n");
    VTermPrintf("ID\tSTATUS\n");

    /*---- Any initialization code before starting multitasking ---------------------------------------*/
    OSInit();
    OSTaskCreate(TaskMgtTask1, ((void*)0),&Task1Stk[64], 5);
     OSTaskCreate(TaskMgtTask2, ((void*)0), &Task2Stk[64], 6);

    OSStart();
}

/*============================================
 *this part is about task management
 *
 *===========================================*/
void TaskMgtTask1(void*data){

    WDTCTL = WDT_MDLY_32;
    SFRIE1 |= WDTIE;


 while(1){
     P4OUT |= 0x0080;
  OSTaskSuspend(5);



}
}
void TaskMgtTask2(void*data){
    WDTCTL = WDT_MDLY_32;
    SFRIE1 |= WDTIE;

        while(1){
            P1OUT |= 0x0001;
            OSTimeDly(100);
            OSTaskResume(5);



}
}
