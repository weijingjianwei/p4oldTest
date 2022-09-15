 /* #include */
 #include <hidef.h>      /* common defines and macros */
 #include "derivative.h"      /* derivative-specific definitions */
 #include "canMessageHandle.h"
 #include "calibration.h"

 


 uint timebase_1ms=0;
 uint keybasetime=0;
 uint diftime_1ms=0;
 uint diftime_5ms=0;                    //5ms�������ڼ���
 uint diftime_10ms=0;                   //10ms�������ڼ���                    
 uint diftime_20ms=0;                   //20ms�������ڼ���
 uint diftime_50ms=0;                   //50ms�������ڼ���
 uint diftime_100ms=0;                  //100ms�������ڼ���
 uint diftime_200ms=0;                  //200ms�������ڼ���
 uint diftime_300ms=0;                  //300ms�������ڼ���
 uint diftime_500ms=0;                  //500ms�������ڼ���
 uint diftime_1000ms=0;                 //1000ms�������ڼ���(���ڱ궨��λ����1000ms�ӳټ���)
 uint diftime_4000ms;                   //4000ms�������ڼ���(����ÿ��4�뷢��3E��Ϸ���)
 
 
 
 //����ʼ�������¼���ֵ�������жϰ����Ƿ񳤰�
 uchar  startTestNum = 0;
 
 //����ʼ���Ա�־λ  0:δ��ʼ 1:��ʼ
 uchar  startTest = 0;
 
 
 //����λ�������¼���ֵ�������жϰ����Ƿ񳤰�
 uchar  resetTestNum = 0;
 
 //����λ���Ա�־λ  0:δ��ʼ 1:��ʼ
 uchar  resetTest = 0;
 
 //�ȴ����׵�λʱ������±�
 uchar airArriveNum=0;

 
 
     
   
  
  


   
   
  
/*************************************************************/
/*                            �жϺ���                       */
/*************************************************************/
 
 #pragma CODE_SEG __NEAR_SEG NON_BANKED


/*************************************************************/
/*                ʵʱ�жϺ��� ��������ȣ�                  */
/*************************************************************/    
   interrupt void RTI_IT(void){
   //_FEED_COP();
   cansendtime++;
   CPMUFLG_RTIF = 1;                               // clr the RTI interrupt Flag
   timebase_1ms++; 
    //1ms�������ڼ�����ͨ���ñ����ж�5ms����������Ƿ�ʼ 
    keybasetime++;
    diftime_1ms++;
    diftime_5ms++;                                    //5ms�������ڼ�����
    diftime_10ms++;                                   //10ms�������ڼ���
    diftime_20ms++;                                    //20ms�������ڼ���
    diftime_50ms++;
                                       //50ms�������ڼ���
    
   
    diftime_100ms++;                            //100ms�������ڼ���
    
   
    if(runstep == endOutCalibration){
       diftime_200ms++;                                   //200ms�������ڼ���
    }
    
    if(startSasCalibrationResultState == 1){
    diftime_300ms++;
    }
    
    diftime_500ms++;
    
    
    //�궨��λ����1000ms�ӳټ���                                   
    if(runstep == readCalibrationState){
       diftime_1000ms++; 
    }
    
    diftime_4000ms++;                                   //4s�������ڼ���
    
  }

/*************************************************************//* ��ʱ��0�жϺ�����������������            
 * Description: ��ʱ��0 �жϿ��Ƶ������ı仯���Ӷ����������ת
 * Param:   none
 * Return:  none
 * Author:  pine
 
/*************************************************************/ 
//�����ƽ��ת��־λ
uint timerNum;
uint timeSum;
uint interruptNum;
uint calibrationFirstStepState;  //�״ν��뷢��1.8�㱨�ı�־λ
uint sendMesStepNum;             //���32��Ƶ֮�������ж��Ƿ�ת��1.8�����ֵ�������ж��Ƿ���Ҫ���ͽǶȱ���
interrupt void TIM0_IT(void) { 
    //TIMEROFF;
    //timeSum++;
     //TFLG1_C0F=1;
    //MPWM=~MPWM;   
   // _FEED_COP();
    //TC0=TC0_NUM; 
    
  
    //TIMERON ;
    
    
    
   TIMEROFF;
    TFLG1_C0F=1;
    
    //MPWM=~MPWM;
    
       
    _FEED_COP();
    
    TC0=TCNT+10;  

   //ȡ��һ�ε�ƽ��תһ�Σ����η�ת����һ������ 
   timerNum++;          
   interruptNum++;
   
   //��ʼ�궨
   if(runstep == startForWardOutCalibration || runstep == startReverseOutCalibration ){
        //calibrationFirstStepState++;
        
        if(sendMesStepNum <=32){
          MPWM=~MPWM;  
          MPWM=~MPWM;
          
          pulseNum--;
          if(sendMesStepNum == 32){
             StartOutCalibration(wantTurnDir);
          }
          sendMesStepNum++; 
        }else{
           if(sendMesStepNum > 32 && calibrationStepResState ==1) {  //   ���Ե�ʱ��ص���һ���� ���ڲ��� && calibrationStepResState ==1
              MPWM=~MPWM;  
              MPWM=~MPWM;
              pulseNum--;  
              
              if(sendMesStepNum % 32 == 0){
                calibrationStepResState =0;     //������Ӧ�ɹ���־λ��0
                timeSum++;
                StartOutCalibration(wantTurnDir);  
              }
              sendMesStepNum++;
              
           }
        }
   }
   
   //Sas�궨
   if(runstep == sasCalibration){
       MPWM=~MPWM;  
       MPWM=~MPWM;
       pulseNum--; 
   }
   
   
   
 
   /**
   if(timerNum==2){
   
     //ÿ�μ�1���������1,��ζ�ŵ����ת1.8�㣬��Ҫ���͵��״̬���� ��Ҫ�ȴ����ĳɹ���Ӧ֮���ٷ�
     if(runstep == startForWardOutCalibration || runstep == startReverseOutCalibration){
        calibrationFirstStepState++;
        if(calibrationFirstStepState==1){
          StartOutCalibration(wantTurnDir);
        }else{
           if(calibrationStepResState ==1 ){
              timeSum++;
              calibrationStepResState =0;     //������Ӧ�ɹ���־λ��0
              StartOutCalibration(wantTurnDir);  
           }
        }
     }
     
     
     pulseNum--;
     timerNum=0;
   }
   **/
   
   if(pulseNum>=1){
     TIMERON;
   }else{
    TIMEROFF;
    pulseNum=0;
    timeSum=0;
    
    sendMesStepNum = 0;   //�״ν��뷢��1.8�㱨�ı�־λ��0
    
    //����궨֮��Ĵ�����
    DealCalibrationResult();
    //SAS�궨֮��Ĵ�����
    //DealSASCalibrationResult();
    
    //���Sas�궨��ɲ����Ĵ�����
    DoSasCalibration();
    
  } 
  
    
}
/*************************************************************/
/*            ��ʱ��1�жϺ�������������������)              */
/*************************************************************/     
interrupt void TIM1_IT(void){
    
}
              
 /*************************************************************/
/*                CAN���ݽ����жϺ���                        */
/*************************************************************/   

   
interrupt void CANRX_IT(void){                            //���յ�һ���ֽڵ������Ժ�����жϣ���������
    
     
     CANRFLG_RXF = 1;   /* Clear reception flag */  
    
     CAN_Read_Frame();
      
     //turnangle=(RxMsg2b0.Data[0]<<8)+RxMsg2b0.Data[1];
}
      
 /*************************************************************/
/*                CAN���ݷ����жϺ���                        */
/*************************************************************/   

   
interrupt void CANTX_IT(void){
    
}   
/*************************************************************/
/*                SCI���ݽ����жϺ���                        */
/*************************************************************/   

   
interrupt void SCI_IT(void){                            //���յ�һ���ֽڵ������Ժ�����жϣ���������
  
}
     
/*************************************************************/
/*                   ���������жϺ���                        */
/*************************************************************/    
    
interrupt void GPIOAD_IT(void){       
  
  
}
#pragma CODE_SEG DEFAULT 


/******************************************************************************/
/**
 * Function Name: void  INIT_FLAG(void)
 * Description: �ϵ��ʱ���һЩ��ʼ״̬������ֵ
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/  
void INIT_FLAG(){


   //��λ����������Ҫ���õı���
   runstep = 0;
  
   
   //��ʼ���¼���
   startTestNum = 0;
   
   //��λ���¼���
   resetTestNum = 0;
   
   //��ʼ���Ա�־λ
   startTest = 0;
   
   //��λ���Ա�־λ
   resetTest = 0; 
   
   //���׹ر�
   AIRRUN = 0;   
 
   
   //ϵͳ���еƹر�
   RUNLED = 0;
   
   //���ؼ��ͨ���ƹر�
   GOLED = 0;
   
   //���ؼ��NG�ȹر�
   NGLED = 0;
   
   //can���ͼ���ֵ��0
   sendNum = 0;
  
  //*********************���״ֵ̬************************// 
   
   //�رյ��
   TIMEROFF;
   
   //�����ж��Ƿ�ת��1.8�����ֵ ��0
   sendMesStepNum = 0;
   
   //ÿһ���궨�����0
   calibrationStepResState = 0;
   
}



/******************************************************************************/
/**
 * Function Name: void  GUDGE_START_KEY_PUSH(void)
 * Description: �жϿ�ʼ���԰����Ƿ񱻰���
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void GUDGE_START_KEY_PUSH(){
     //PAD3������͵�ƽ���жϰ���������
     if(STARTKEY == 0){
          startTestNum++;
     }else{
          startTestNum=0;
     }
     
     if(startTestNum>=5){
          AIRRUN = 1;   //��������
          startTestNum = 0;
     }
     
     if(AIRRUN == 1 && startTest == 0){
        airArriveNum++;
     }
     
     //��������֮��2s���ȴ����׵�λ֮��������
     if(airArriveNum > 10){
         startTest = 1;  //��ʼ���Ա궨��ʼ
         RUNLED = 1;   //�������е���
         airArriveNum = 0;
     }
}                        

/******************************************************************************/
/**
 * Function Name: void  GUDGE_RESET_KEY_PUSH(void)
 * Description: �жϸ�λ�����Ƿ񱻰���
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/
void GUDGE_RESET_KEY_PUSH(){
   
    //PAD1������͵�ƽ���жϰ���������
     if(RESETKEY == 0){
          resetTestNum++;
     }else{
          resetTestNum=0;
     }
     
     if(resetTestNum>=5){
         
          
          INIT_FLAG();
          
         
     }

}


/******************************************************************************/
/**
 * Function Name: void  ����ͨ�����ָʾ��(void)
 * Description: 
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/
void TestNgOrGoFunc(){
    
    //can������ϱ��ĳ������ر궨������������ת������
    if(canSendState == ERROR  || calibrationStatus == ERROR || switchQualified == ERROR){
          NGLED = 1;
    }
    
    //���ؼ��ͨ��
    if(runstep == sasCalibrationEnd  && switchQualified == SUCCESS ){
          GOLED = 1;
    }
}


/*************************************************************/
/*                   5ms�жϺ���                        */
/*************************************************************/  
void TASK_5MS(){
 
  
   //�궨���̿�ʼ
   StartCalibration();
   
   //���ô���can��Ϣ����  
   CANMESSAGEHADLE();
   
   //�ⲿ����궨��ʼ
   StartOutCalibrationFunc();
   
   //SAS�궨��ʼ
   SASCalibrationFunc();
   
   //����ͨ�����ָʾ��
   TestNgOrGoFunc();
  
    
   
}
 
/*************************************************************/
/*                   10ms�жϺ���                        */
/*************************************************************/  
void TASK_10MS(){
 
   
}

/*************************************************************/
/*                   20ms�жϺ���                        */
/*************************************************************/
void TASK_20MS(){
   
}

/*************************************************************/
/*                   50ms�жϺ���                        */
/*************************************************************/
void TASK_50MS(){
    //���ô���can��Ϣ����  
   // CANMESSAGEHADLE();
   // ConnectLink();
    SendSeed();
    SendSecret();
    DetectionDeviceNo();
    ReadBatchNo();
    ReadHardWareNo();
    ReadSoftWareNo();
    ClearInCalibration();
    StartInCalibration();
    Reset();
    
    //�������߱궨����
    EOLExtend();
    EOLReadPartNum();
    EOLReadHardWareNo();
    EOLReadSoftWareNo();
    EOLsafeAccessSendSeed();
    EOLsafeAccessSendSecret();
    EOLvinCodeWrite();
    EOLvinCodeRead();
    EOLcarConfigWrite();
    EOLremoveMidCalibration();
    EOLmidCalibrationStepFirst();
    EOLmidCalibrationStepSecond();
    EOLclearSSMCode();
    //EOLreadSSMCode();   ʦ���ǿ���ʱû����飬�Ⱥ��Բ���
}

/*************************************************************/
/*                   100ms�жϺ���                        */
/*************************************************************/
void TASK_100MS(){
    GUDGE_START_KEY_PUSH();
    GUDGE_RESET_KEY_PUSH();  
}

/*************************************************************/
/*                   200ms�жϺ���                        */
/*************************************************************/
void TASK_200MS(){
     
    //�����ⲿ����궨��������
   StopOutCalibration(wantTurnDir);
}

/*************************************************************/
/*                   300ms�жϺ���                        */
/*************************************************************/
void TASK_300MS(){
       //������־λ��0
     startSasCalibrationResultState=0;
      
     //������Sas�궨���
     DealSASCalibrationResult();
}

 /*************************************************************/
/*                   500ms�жϺ���                        */
/*************************************************************/
void TASK_500MS(){
     
  ConnectLink();  
}


/*************************************************************/
/*                   1000ms�жϺ���                        */
/*************************************************************/
void TASK_1000MS(){
    ReadCalibrationState();  //��ȡ�궨״̬
}



/*************************************************************/
/*                   4s�жϺ���                        */
/*************************************************************/
void TASK_4S(){  
     Send3EService();
}
  
  

  
/******************************************************************************/
/**
 * Function Name: void  TASKOS(void)
 * Description: �������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void TASKOS(void){
  
  if(diftime_5ms>=1){
    TASK_5MS();
    diftime_5ms=0;
  }
  if(diftime_10ms>=2){
    TASK_10MS();
    diftime_10ms=0;
  }
  if(diftime_20ms>=4){
    TASK_20MS();
    diftime_20ms=0;
  }
  if(diftime_50ms>=10){
    TASK_50MS();
    diftime_50ms=0;
  }
  
  if(diftime_200ms>=40){
    TASK_200MS();
    diftime_200ms=0;
  }
  
  if(diftime_300ms>=60){
    TASK_300MS();
    diftime_300ms=0;
  }
  if(diftime_500ms>=100){
    TASK_500MS();
    diftime_500ms=0;
  }
  
  if(diftime_1000ms>=200){
    TASK_1000MS();
    diftime_1000ms = 0;
  }
  if(diftime_4000ms>=800){
    //TASK_4S();
    diftime_4000ms=0;
  }
}
  



/******************************************************************************/
/**
 * Function Name: void  START_KEY_DETECT(void)
 * Description:  ��ʼ�������¼��  100ms�����ж�
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/  
void START_RESET_KEY_DETECT(void) {
   if(diftime_100ms>=20){
    TASK_100MS();
    diftime_100ms=0;
   }     
}







void main(void)
{
  /* put your own code here */
 DisableInterrupts;       
    
 INIT_PLL();
 //INIT_SCI();
 INIT_CAN();
 INIT_COP();
 INIT_RTI();
 INIT_GPIOAD();
 INIT_GPIOP();
 INIT_GPIOT();
 //INIT_GPIOS();
 INIT_TIM();           
 EnableInterrupts;
 
 INIT_FLAG();
 
 
 for(;;) 
 { 
  
   START_RESET_KEY_DETECT();  //��ʼ����λ�������
  
  
   //��ʼ����
   if(startTest == 1){
    
     TASKOS();
   }
  _FEED_COP(); /* feeds the dog */
 } /* loop forever */
      /* please make sure that you never leave main */
}

