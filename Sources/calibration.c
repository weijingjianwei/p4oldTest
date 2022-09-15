 #include "derivative.h"      /* derivative-specific definitions */
 #include "calibration.h"
 #include "canMessageHandle.h"
 
 


 uint wantTurnDir=0;           //��Ҫ�����ת�ķ���
 uint wantTurnAngle=0;         //��Ҫ�����ת�ĽǶ�
 
 uint pulseNum = 0;            //��Ҫ��������͵�������
 uint turnFlag = 0;            //�����ת�ı�־λ����ֹ������ѭ��������
 
 unsigned int switchAngle;       //����ʵ��ת���Ƕ�ֵ
 unsigned int calibrationAngle;  //����궨�Ƕ�ֵ
 unsigned int errorAngle;        //�Ƕ����
 uchar switchQualified=SUCCESS;             //SaS���ر궨���Ƿ�ϸ�
 uchar startSasCalibrationResultState;     //��ʼ�ȶԽǶ����ݿ�ʼ����״̬
 


 /******************************************************************************/
/**
  Function Name: void  StartCalibration(void)
 * Description: �궨���̿�ʼ
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
 * Description:  ��ʼ�ⲿ����궨
 * Param:    
 * Return:   
 * Author:  pine
 *****************************************************************************/  
 uint test;
 void StartOutCalibrationFunc(){
     
     if(runstep == startForWardOutCalibration && turnFlag == 1){
     
       //��������ת��ͬ�Ƕ���Ҫ��������
       if(wantTurnAngle==MOTORCONTROL8 && wantTurnDir==FORWARD){           
         
         pulseNum = MOTORCONTROL8/stepDegrees;
         turnFlag = 0;
         DIRECTION = FORWARD; //�����ת
         TIMERON;  //��ʱ��ʹ��
         
       }
     }
    
     if(runstep == startReverseOutCalibration && turnFlag ==1){
        //��������ת��ͬ�Ƕ���Ҫ��������
        if(wantTurnAngle==MOTORCONTROL8 && wantTurnDir==REVERSE){            
         
         pulseNum = MOTORCONTROL8/stepDegrees;
         turnFlag = 0;
         DIRECTION = REVERSE;  //�����ת
         TIMERON;  //��ʱ��ʹ��
        
        }
     }
 }
 
 
  /******************************************************************************/
/**
  Function Name: void  DealCalibrationResult(void)
 * Description:  ����궨֮����Ҫ���������ĺ�������
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
      //�����ⲿ����궨��������(TODO ��ʱ��ת��������ֹͣ�궨����)
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
 * Description:  SAS�궨֮����Ҫ��ȡ�����Ǵ����ĽǶ����ݽ��бȶԣ��ж��Ƿ�ϸ�
                 SAS��������������2�� �ж�Ϊ�ϸ�
 * Param:    
 * Return:   
 * Author:  pine
 *****************************************************************************/
 uint sw1,sw2[3];
 uint errorAngleArray[15];
 uint switchAngleArray[14];
 uint errorAngleIndex = 0;
 void compareAngAngle(void){
       //1����ȡ���صĽǶȱ���
       //2: �͵���궨�ĽǶȽ��бȶ� 
       //�ο��ĵ� ����ת���Ƕ�ΪidΪ39�ĵ��ĺ͵��������ֽ����
       //Motorola LSB��ʽ�� �����ֽڣ�41-47λ��ʾ��λ���������ֽ�(32-39��ʾ��λ)���ܹ�ռ15���ֽ�
       sw2[1] = switchAngle = RxMsgAngel.Data[4];
       sw1=switchAngle = (switchAngle << 8) + (sw2[2]=RxMsgAngel.Data[5]);
       sw2[0]=switchAngle = (switchAngle >> 1);
       switchAngle =  switchAngle/10;
       
       
       
       calibrationAngle = wantTurnAngle;
       
       //�궨���������Ա궨�����ֵΪ��㣬������ת�Ƕ�Ϊ�ȶԽǶ���ֵ����ת֮��Ϊ0����бȶ�
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
           switchQualified =ERROR;   //��Ʒ���ϸ�������2��
       }
       
       
       
 }
 
 
 /******************************************************************************/
/**
  Function Name: void  DealSASCalibrationResult(void)
 * Description:  SAS�궨�������Ǵ����߼�
 * Param:    
 * Return:   
 * Author:  pine
 *****************************************************************************/
 void DealSASCalibrationResult(void){
     
     if(runstep == sasCalibration){
        if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL30){
            
            //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL30;
            turnFlag=1;
            //runstep = 30;
            
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL30){
        
              //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL45;
            turnFlag=1;
            //runstep = 30;
          
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL45){
          
            //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL45;
            turnFlag=1;
            //runstep = 30;
          
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL45){
            //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL60;
            turnFlag=1; 
           
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL60){
        
            //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL60;
            turnFlag=1; 
           
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL60){
           
            //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL90;
            turnFlag=1; 
           
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL90){
        
            //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL90;
            turnFlag=1; 
           
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL90){
            //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL180;
            turnFlag=1; 
        
           
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL180){
        
             //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL180;
            turnFlag=1; 
           
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL180){
        
            //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL360;
            turnFlag=1; 
           
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL360){
        
            //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL360;
            turnFlag=1; 
           
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL360){
             
             //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =FORWARD;
            wantTurnAngle = MOTORCONTROL720;
            turnFlag=1; 
        
           
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL720){
        
             //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            wantTurnDir =REVERSE;
            wantTurnAngle = MOTORCONTROL720;
            turnFlag=1;
           
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL720){
            
             //�ȶԱ궨�ĺͿ����Ƕ����ĽǶ�ֵ
            compareAngAngle();
            turnFlag=1;
            runstep = sasCalibrationEnd;
           
        }
     }
 }
 
 
 /******************************************************************************/
/**
  Function Name: void  SASCalibrationFunc(void)
 * Description: SAS�궨��ʼ        
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
           DIRECTION = FORWARD; //�����ת
           starSasCalibrationState =1; 
           TIMERON;  //��ʱ��ʹ��
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL30){
           pulseNum = MOTORCONTROL30/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //�����ת
           TIMERON;  //��ʱ��ʹ��
           starSasCalibrationState =1;
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL45){
           pulseNum = MOTORCONTROL45/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //�����ת
           TIMERON;  //��ʱ��ʹ��
           starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL45){
           pulseNum = MOTORCONTROL45/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //�����ת
           TIMERON;  //��ʱ��ʹ��
           starSasCalibrationState =1;
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL60){
           pulseNum = MOTORCONTROL60/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //�����ת
           TIMERON;  //��ʱ��ʹ��
           starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL60){
           pulseNum = MOTORCONTROL60/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //�����ת
           TIMERON;  //��ʱ��ʹ��
           starSasCalibrationState =1; 
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL90){
           pulseNum = MOTORCONTROL90/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //�����ת
          TIMERON;  //��ʱ��ʹ��
          starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL90){
           pulseNum = MOTORCONTROL90/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //�����ת
          TIMERON;  //��ʱ��ʹ��
          starSasCalibrationState =1; 
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL180){
           pulseNum = MOTORCONTROL180/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //�����ת
           TIMERON;  //��ʱ��ʹ��
           starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL180){
           pulseNum = MOTORCONTROL180/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //�����ת
           TIMERON;  //��ʱ��ʹ��
           starSasCalibrationState =1; 
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL360){
           pulseNum = MOTORCONTROL360/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //�����ת
           TIMERON;  //��ʱ��ʹ��
           starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL360){
           pulseNum = MOTORCONTROL360/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //�����ת
           TIMERON;  //��ʱ��ʹ��
           starSasCalibrationState =1; 
        }else if(wantTurnDir == FORWARD && wantTurnAngle == MOTORCONTROL720){
           pulseNum = MOTORCONTROL720/stepDegrees;
           turnFlag = 0;
           DIRECTION = FORWARD; //�����ת
           TIMERON;  //��ʱ��ʹ��
           starSasCalibrationState =1; 
        }else if(wantTurnDir == REVERSE && wantTurnAngle == MOTORCONTROL720){
           pulseNum = MOTORCONTROL720/stepDegrees;
           turnFlag = 0;
           DIRECTION = REVERSE; //�����ת
           TIMERON;  //��ʱ��ʹ��
           starSasCalibrationState =1; 
        }
      
     }

}


void DoSasCalibration(void){
      if(runstep == sasCalibration && starSasCalibrationState==1 && switchQualified ==SUCCESS){
           
                //��ֹû�ж������µ�ת���Ƕȣ��ӳ�100ms,���ӳ�������ִ�б궨���
                startSasCalibrationResultState=1;
      }  
}



