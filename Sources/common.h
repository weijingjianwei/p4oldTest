#ifndef _COMMON_H
#define _COMMON_H
   
//һЩ��������ı���

#define   TIMERON   TSCR1_TEN=1    //��ʱ��ʹ��
#define   TIMEROFF  TSCR1_TEN=0    //��ʱ���ر�

#define  RUN 0
#define  STOP  1


//==============�ɹ�ʧ�ܱ�־λ=================//
#define  ERROR 1
#define  SUCCESS  2
  
#define   MPWM         PTP_PTP0         //PP0��������
#define   DIRECTION    PTP_PTP1         //PP1���Ƶ��ת��
#define   GOLED        PTP_PTP2         //PP2����GO��
#define   NGLED        PTP_PTP3         //pp3����NG��
#define   RUNLED       PTT_PTT3         //PT3���ƹ������е�
#define   AIRRUN       PTT_PTT2         //PT2�������׹���
#define   STARTKEY     PT1AD_PT1AD3     //PT3������ƿ�ʼ�����ź�
#define   RESETKEY     PT1AD_PT1AD1     //PT1������ƿ�ʼ�����ź�

  

#define   TC0_NUM  10

#define   canRetryNum  100  //����can�������Դ���

                       


    

#endif