 /* #include */
 #include <hidef.h>      /* common defines and macros */
 #include "derivative.h"      /* derivative-specific definitions */
 #include "canMessageHandle.h"
 #include "calibration.h"

 


 uint timebase_1ms=0;
 uint keybasetime=0;
 uint diftime_1ms=0;
 uint diftime_5ms=0;                    //5ms任务周期计数
 uint diftime_10ms=0;                   //10ms任务周期计数                    
 uint diftime_20ms=0;                   //20ms任务周期计数
 uint diftime_50ms=0;                   //50ms任务周期计数
 uint diftime_100ms=0;                  //100ms任务周期计数
 uint diftime_200ms=0;                  //200ms任务周期计数
 uint diftime_300ms=0;                  //300ms任务周期计数
 uint diftime_500ms=0;                  //500ms任务周期计数
 uint diftime_1000ms=0;                 //1000ms任务周期计数(用于标定复位后开启1000ms延迟计数)
 uint diftime_4000ms;                   //4000ms任务周期计数(用于每隔4秒发送3E诊断服务)
 
 
 
 //程序开始按键按下计数值，用于判断按键是否长按
 uchar  startTestNum = 0;
 
 //程序开始测试标志位  0:未开始 1:开始
 uchar  startTest = 0;
 
 
 //程序复位按键按下计数值，用于判断按键是否长按
 uchar  resetTestNum = 0;
 
 //程序复位测试标志位  0:未开始 1:开始
 uchar  resetTest = 0;
 
 //等待气缸到位时间计数下标
 uchar airArriveNum=0;

 
 
     
   
  
  


   
   
  
/*************************************************************/
/*                            中断函数                       */
/*************************************************************/
 
 #pragma CODE_SEG __NEAR_SEG NON_BANKED


/*************************************************************/
/*                实时中断函数 （任务调度）                  */
/*************************************************************/    
   interrupt void RTI_IT(void){
   //_FEED_COP();
   cansendtime++;
   CPMUFLG_RTIF = 1;                               // clr the RTI interrupt Flag
   timebase_1ms++; 
    //1ms任务周期计数，通过该变量判断5ms的任务调度是否开始 
    keybasetime++;
    diftime_1ms++;
    diftime_5ms++;                                    //5ms任务周期计数，
    diftime_10ms++;                                   //10ms任务周期计数
    diftime_20ms++;                                    //20ms任务周期计数
    diftime_50ms++;
                                       //50ms任务周期计数
    
   
    diftime_100ms++;                            //100ms任务周期计数
    
   
    if(runstep == endOutCalibration){
       diftime_200ms++;                                   //200ms任务周期计数
    }
    
    if(startSasCalibrationResultState == 1){
    diftime_300ms++;
    }
    
    diftime_500ms++;
    
    
    //标定复位后开启1000ms延迟计数                                   
    if(runstep == readCalibrationState){
       diftime_1000ms++; 
    }
    
    diftime_4000ms++;                                   //4s任务周期计数
    
  }

/*************************************************************//* 定时器0中断函数（电机脉冲输出）            
 * Description: 定时器0 中断控制电机脉冲的变化，从而驱动电机旋转
 * Param:   none
 * Return:  none
 * Author:  pine
 
/*************************************************************/ 
//定义电平反转标志位
uint timerNum;
uint timeSum;
uint interruptNum;
uint calibrationFirstStepState;  //首次进入发送1.8°报文标志位
uint sendMesStepNum;             //电机32分频之后，用于判断是否转了1.8°计数值，用于判断是否需要发送角度报文
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

   //取反一次电平翻转一次，两次翻转产生一次脉冲 
   timerNum++;          
   interruptNum++;
   
   //初始标定
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
           if(sendMesStepNum > 32 && calibrationStepResState ==1) {  //   测试的时候关掉这一条件 便于测试 && calibrationStepResState ==1
              MPWM=~MPWM;  
              MPWM=~MPWM;
              pulseNum--;  
              
              if(sendMesStepNum % 32 == 0){
                calibrationStepResState =0;     //报文响应成功标志位清0
                timeSum++;
                StartOutCalibration(wantTurnDir);  
              }
              sendMesStepNum++;
              
           }
        }
   }
   
   //Sas标定
   if(runstep == sasCalibration){
       MPWM=~MPWM;  
       MPWM=~MPWM;
       pulseNum--; 
   }
   
   
   
 
   /**
   if(timerNum==2){
   
     //每次减1代表脉冲减1,意味着电机旋转1.8°，需要发送电机状态报文 需要等待报文成功响应之后再发
     if(runstep == startForWardOutCalibration || runstep == startReverseOutCalibration){
        calibrationFirstStepState++;
        if(calibrationFirstStepState==1){
          StartOutCalibration(wantTurnDir);
        }else{
           if(calibrationStepResState ==1 ){
              timeSum++;
              calibrationStepResState =0;     //报文响应成功标志位清0
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
    
    sendMesStepNum = 0;   //首次进入发送1.8°报文标志位清0
    
    //电机标定之后的处理函数
    DealCalibrationResult();
    //SAS标定之后的处理函数
    //DealSASCalibrationResult();
    
    //电机Sas标定完成步骤后的处理函数
    DoSasCalibration();
    
  } 
  
    
}
/*************************************************************/
/*            定时器1中断函数（电机脉冲输出备用)              */
/*************************************************************/     
interrupt void TIM1_IT(void){
    
}
              
 /*************************************************************/
/*                CAN数据接收中断函数                        */
/*************************************************************/   

   
interrupt void CANRX_IT(void){                            //接收到一个字节的数据以后进入中断，处理数据
    
     
     CANRFLG_RXF = 1;   /* Clear reception flag */  
    
     CAN_Read_Frame();
      
     //turnangle=(RxMsg2b0.Data[0]<<8)+RxMsg2b0.Data[1];
}
      
 /*************************************************************/
/*                CAN数据发送中断函数                        */
/*************************************************************/   

   
interrupt void CANTX_IT(void){
    
}   
/*************************************************************/
/*                SCI数据接收中断函数                        */
/*************************************************************/   

   
interrupt void SCI_IT(void){                            //接收到一个字节的数据以后进入中断，处理数据
  
}
     
/*************************************************************/
/*                   按键输入中断函数                        */
/*************************************************************/    
    
interrupt void GPIOAD_IT(void){       
  
  
}
#pragma CODE_SEG DEFAULT 


/******************************************************************************/
/**
 * Function Name: void  INIT_FLAG(void)
 * Description: 上电的时候的一些初始状态变量赋值
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/  
void INIT_FLAG(){


   //复位按键按下需要重置的变量
   runstep = 0;
  
   
   //开始按下计数
   startTestNum = 0;
   
   //复位按下计数
   resetTestNum = 0;
   
   //开始测试标志位
   startTest = 0;
   
   //复位测试标志位
   resetTest = 0; 
   
   //气缸关闭
   AIRRUN = 0;   
 
   
   //系统运行灯关闭
   RUNLED = 0;
   
   //开关检测通过灯关闭
   GOLED = 0;
   
   //开关检测NG等关闭
   NGLED = 0;
   
   //can发送计数值清0
   sendNum = 0;
  
  //*********************电机状态值************************// 
   
   //关闭电机
   TIMEROFF;
   
   //用于判断是否转了1.8°计数值 清0
   sendMesStepNum = 0;
   
   //每一步标定结果清0
   calibrationStepResState = 0;
   
}



/******************************************************************************/
/**
 * Function Name: void  GUDGE_START_KEY_PUSH(void)
 * Description: 判断开始测试按键是否被按下
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void GUDGE_START_KEY_PUSH(){
     //PAD3口输入低电平则判断按键被按下
     if(STARTKEY == 0){
          startTestNum++;
     }else{
          startTestNum=0;
     }
     
     if(startTestNum>=5){
          AIRRUN = 1;   //气缸运行
          startTestNum = 0;
     }
     
     if(AIRRUN == 1 && startTest == 0){
        airArriveNum++;
     }
     
     //气缸运行之后2s，等待气缸到位之后开启测试
     if(airArriveNum > 10){
         startTest = 1;  //开始测试标定开始
         RUNLED = 1;   //工作运行灯亮
         airArriveNum = 0;
     }
}                        

/******************************************************************************/
/**
 * Function Name: void  GUDGE_RESET_KEY_PUSH(void)
 * Description: 判断复位按键是否被按下
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/
void GUDGE_RESET_KEY_PUSH(){
   
    //PAD1口输入低电平则判断按键被按下
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
 * Function Name: void  测试通过与否指示灯(void)
 * Description: 
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/
void TestNgOrGoFunc(){
    
    //can发送诊断报文出错、开关标定出错、开关正反转检测出错
    if(canSendState == ERROR  || calibrationStatus == ERROR || switchQualified == ERROR){
          NGLED = 1;
    }
    
    //开关检测通过
    if(runstep == sasCalibrationEnd  && switchQualified == SUCCESS ){
          GOLED = 1;
    }
}


/*************************************************************/
/*                   5ms中断函数                        */
/*************************************************************/  
void TASK_5MS(){
 
  
   //标定流程开始
   StartCalibration();
   
   //调用处理can消息函数  
   CANMESSAGEHADLE();
   
   //外部电机标定开始
   StartOutCalibrationFunc();
   
   //SAS标定开始
   SASCalibrationFunc();
   
   //测试通过与否指示灯
   TestNgOrGoFunc();
  
    
   
}
 
/*************************************************************/
/*                   10ms中断函数                        */
/*************************************************************/  
void TASK_10MS(){
 
   
}

/*************************************************************/
/*                   20ms中断函数                        */
/*************************************************************/
void TASK_20MS(){
   
}

/*************************************************************/
/*                   50ms中断函数                        */
/*************************************************************/
void TASK_50MS(){
    //调用处理can消息函数  
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
    
    //进入下线标定流程
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
    //EOLreadSSMCode();   师父那块暂时没加这块，先忽略不计
}

/*************************************************************/
/*                   100ms中断函数                        */
/*************************************************************/
void TASK_100MS(){
    GUDGE_START_KEY_PUSH();
    GUDGE_RESET_KEY_PUSH();  
}

/*************************************************************/
/*                   200ms中断函数                        */
/*************************************************************/
void TASK_200MS(){
     
    //发送外部电机标定结束命令
   StopOutCalibration(wantTurnDir);
}

/*************************************************************/
/*                   300ms中断函数                        */
/*************************************************************/
void TASK_300MS(){
       //计数标志位置0
     startSasCalibrationResultState=0;
      
     //处理电机Sas标定结果
     DealSASCalibrationResult();
}

 /*************************************************************/
/*                   500ms中断函数                        */
/*************************************************************/
void TASK_500MS(){
     
  ConnectLink();  
}


/*************************************************************/
/*                   1000ms中断函数                        */
/*************************************************************/
void TASK_1000MS(){
    ReadCalibrationState();  //读取标定状态
}



/*************************************************************/
/*                   4s中断函数                        */
/*************************************************************/
void TASK_4S(){  
     Send3EService();
}
  
  

  
/******************************************************************************/
/**
 * Function Name: void  TASKOS(void)
 * Description: 任务调度
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
 * Description:  开始按键按下检测  100ms任务判断
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
  
   START_RESET_KEY_DETECT();  //开始、复位按键检测
  
  
   //开始测试
   if(startTest == 1){
    
     TASKOS();
   }
  _FEED_COP(); /* feeds the dog */
 } /* loop forever */
      /* please make sure that you never leave main */
}

