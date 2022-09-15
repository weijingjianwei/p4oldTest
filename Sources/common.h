#ifndef _COMMON_H
#define _COMMON_H
   
//一些公共定义的变量

#define   TIMERON   TSCR1_TEN=1    //定时器使能
#define   TIMEROFF  TSCR1_TEN=0    //定时器关闭

#define  RUN 0
#define  STOP  1


//==============成功失败标志位=================//
#define  ERROR 1
#define  SUCCESS  2
  
#define   MPWM         PTP_PTP0         //PP0控制脉冲
#define   DIRECTION    PTP_PTP1         //PP1控制电机转向
#define   GOLED        PTP_PTP2         //PP2控制GO灯
#define   NGLED        PTP_PTP3         //pp3控制NG灯
#define   RUNLED       PTT_PTT3         //PT3控制工作运行灯
#define   AIRRUN       PTT_PTT2         //PT2控制气缸工作
#define   STARTKEY     PT1AD_PT1AD3     //PT3输入控制开始测试信号
#define   RESETKEY     PT1AD_PT1AD1     //PT1输入控制开始测试信号

  

#define   TC0_NUM  10

#define   canRetryNum  100  //发送can报文重试次数

                       


    

#endif