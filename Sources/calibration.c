 #include "derivative.h"      /* derivative-specific definitions */
 #include "calibration.h"
 #include "canMessageHandle.h"
 
 


 uint wantTurnDir=0;           //想要电机旋转的方向
 uint wantTurnAngle=0;         //想要电机旋转的角度
 
 uint pulseNum = 0;            //需要给电机发送的脉冲数
 uint turnFlag = 0;            //电机旋转的标志位，防止主函数循环无限跑
 
 unsigned int switchAngle;       //开关实际转动角度值
 unsigned int calibrationAngle;  //电机标定角度值
 unsigned int errorAngle;        //角度误差
 uchar switchQualified=SUCCESS;             //SaS开关标定的是否合格
 uchar startSasCalibrationResultState;     //开始比对角度数据开始步骤状态
 


 /******************************************************************************/
/**
  Function Name: void  StartCalibration(void)
 * Description: 标定流程开始
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void StartCalibration(){
   if(runstep==0){ 
      runstep=connectLink;
   } 
}

 
 /******************************************************************************/
/**
  Function Name: void  StartOutCalibrationFunc(void)
 * Description:  开始外部电机标定
 * Param:    
 * Return:   
 * Author:  pine
 *****************************************************************************/  
 uint test;
 void StartOutCalibrationFunc(){
     
     if(runstep == startForWardOutCalibration && turnFlag == 1){
     
       //计算电机旋转不同角度需要的脉冲数
       if(wantTurnAngle==MOTORCONTROL8 && wantTurnDir==FORWARD){           
         
         pulseNum = MOTORCONTROL8/stepDegrees;
         turnFlag = 0;
         DIRECTION = FORWARD; //电机正转
         TIMERON;  //定时器使能
         
       }
     }
    
     if(runstep == startReverseOutCalibration && turnFlag ==1){
        //计算电机旋转不同角度需要的脉冲数
        if(wantTurnAngle==MOTORCONTROL8 && wantTurnDir==REVERSE){            
         
         pulseNum = MOTORCONTROL8/stepDegrees;
         turnFlag = 0;
         DIRECTION = REVERSE;  //电机反转
         TIMERON;  //定时器使能
        
        }
     }
 }
 
 
  /******************************************************************************/
/**
  Function Name: void  DealCalibrationResult(void)
 * Description:  电机标定之后，需要分情况处理的后续步骤
 * Param:    
 * Return:   
 * Author:  pine
 *****************************************************************************/
 int a=0;
 int go =0; 
 void DealCalibrationResult(void){
       a++;
     if(runstep==startForWardOutCalibration ){
      turnFlag=1;
      runstep = startReverseOutCalibration;
      wantTurnAngle=MOTORCONTROL8;
      wantTurnDir=REVERSE; 
      //发送外部电机标定结束命令(TODO 暂时正转结束不发停止标定命令)
      // StopOutCalibration(wantTurnDir);
    }else if(runstep==startReverseOutCalibration){
      turnFlag=1;
      runstep = endOutCalibration;
      go=1;
    }
 }
 
 
  /******************************************************************************/
/**
  Function Name: void  compareAngAngle(void)
 * Description:  SAS标定之后，需要读取开关那传来的角度数据进行比对，判断是否合格
                 SAS的输出精度满足≤2° 判定为合格
 * Param:    
 * Return:   
 * Author:  pine
 *****************************************************************************/
 uint sw1,sw2[3];
 uint errorAngleArray[15];
 uint switchAngleArray[14];
 uint errorAngleIndex = 0;
 void compareAngAngle(void){
       //1：读取开关的角度报文
       //2: 和电机标定的角度进行比对 
       //参考文档 开关转动角度为id为39的第四和第五两个字节组成
       //Motorola LSB格式， 第五字节（41-47位表示低位），第四字节(32-39表示高位)，总共占15个字节
       sw2[1] = switchAngle = RxMsgAngel.Data[4];
       sw1=switchAngle = (switchAngle << 8) + (sw2[2]=RxMsgAngel.Data[5]);
       sw2[0]=switchAngle = (switchAngle >> 1);
       switchAngle =  switchAngle/10;
       
       
       
       calibrationAngle = wantTurnAngle;
       
       //标定过程中是以标定过后的值为零点，所以正转角度为比对角度正值，反转之后为0°进行比对
       switch(wantTurnDir){
         case  FORWARD:
               if(calibrationAngle>=switchAngle){
                     errorAngle =  calibrationAngle - switchAngle;
               }else{
                     errorAngle =  switchAngle - calibrationAngle;
               }
               break;
               
         case  REVERSE:
               errorAngle = switchAngle;
               break;
               
         default:
               break;
       }
       
      
       errorAngleArray[errorAngleIndex]  =  errorAngle;
       switchAngleArray[errorAngleIndex] =  switchAngle;
       errorAngleIndex++;
       
       if(errorAngle > 2){
           switchQualified =ERROR;   //产品不合格，误差大于2°
       }
       
       
       
 }
 
 
 /******************************************************************************/
/**
  Function Name: void  DealSASCalibrationResult(void)
 * Description:  SAS标定结束后都是处理逻辑
 * Param:    
 * Return:   
 * Author:  pine
 *****************************************************************************/
 void DealSASCalibrationResult(void){
     
     if(runstep == sasCalibration){
        if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL30){
            
            //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL30;
            turnFlag=1;
            //runstep = 30;
            
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL30){
        
              //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL45;
            turnFlag=1;
            //runstep = 30;
          
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL45){
          
            //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL45;
            turnFlag=1;
            //runstep = 30;
          
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL45){
            //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL60;
            turnFlag=1; 
           
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL60){
        
            //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL60;
            turnFlag=1; 
           
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL60){
           
            //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL90;
            turnFlag=1; 
           
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL90){
        
            //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL90;
            turnFlag=1; 
           
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL90){
            //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL180;
            turnFlag=1; 
        
           
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL180){
        
             //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL180;
            turnFlag=1; 
           
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL180){
        
            //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL360;
            turnFlag=1; 
           
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL360){
        
            //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL360;
            turnFlag=1; 
           
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL360){
             
             //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL720;
            turnFlag=1; 
        
           
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL720){
        
             //比对标定的和开关那读到的角度值
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL720;
            turnFlag=1;
           
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL720){
            
             //比对标定的和开关那读到的角度值
            compareAngAngle();
            turnFlag=1;
            runstep = sasCalibrationEnd;
           
        }
     }
 }
 
 
 /******************************************************************************/
/**
  Function Name: void  SASCalibrationFunc(void)
 * Description: SAS标定开始        
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/
uchar starSasCalibrationState; 
void  SASCalibrationFunc(void){
     
     if(runstep == sasCalibration && turnFlag==1 && switchQualified ==SUCCESS){
     
        if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL30){
           pulseNum = MOTORCONTROL30/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //电机正转
           starSasCalibrationState =1; 
           TIMERON;  //定时器使能
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL30){
           pulseNum = MOTORCONTROL30/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //电机反转
           TIMERON;  //定时器使能
           starSasCalibrationState =1;
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL45){
           pulseNum = MOTORCONTROL45/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //电机正转
           TIMERON;  //定时器使能
           starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL45){
           pulseNum = MOTORCONTROL45/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //电机反转
           TIMERON;  //定时器使能
           starSasCalibrationState =1;
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL60){
           pulseNum = MOTORCONTROL60/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //电机正转
           TIMERON;  //定时器使能
           starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL60){
           pulseNum = MOTORCONTROL60/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //电机正转
           TIMERON;  //定时器使能
           starSasCalibrationState =1; 
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL90){
           pulseNum = MOTORCONTROL90/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //电机正转
          TIMERON;  //定时器使能
          starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL90){
           pulseNum = MOTORCONTROL90/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //电机正转
          TIMERON;  //定时器使能
          starSasCalibrationState =1; 
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL180){
           pulseNum = MOTORCONTROL180/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //电机正转
           TIMERON;  //定时器使能
           starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL180){
           pulseNum = MOTORCONTROL180/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //电机正转
           TIMERON;  //定时器使能
           starSasCalibrationState =1; 
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL360){
           pulseNum = MOTORCONTROL360/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //电机正转
           TIMERON;  //定时器使能
           starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL360){
           pulseNum = MOTORCONTROL360/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //电机正转
           TIMERON;  //定时器使能
           starSasCalibrationState =1; 
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL720){
           pulseNum = MOTORCONTROL720/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //电机正转
           TIMERON;  //定时器使能
           starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL720){
           pulseNum = MOTORCONTROL720/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //电机正转
           TIMERON;  //定时器使能
           starSasCalibrationState =1; 
        }
      
     }

}


void DoSasCalibration(void){
      if(runstep == sasCalibration && starSasCalibrationState==1 && switchQualified ==SUCCESS){
           
                //防止没有读到最新的转动角度，延迟100ms,在延迟任务中执行标定结果
                startSasCalibrationResultState=1;
      }  
}



