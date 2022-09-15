#ifndef _CALIBRATION_H
#define _CALIBRATION_H
   
  
  
#include <hidef.h>
#include <mc9s12g48.h>  


//==============��ͬ�汾�ıȶ����ݺ궨��==================//
#define  FORWARD 0                 //   �����ת
#define  REVERSE 1                 //   �����ת

//#define   stepDegrees    1.8       //    ���һ�������Ӧת���ĽǶ���ֵ
#define   stepDegrees    0.05625       //    ���һ�������Ӧת���ĽǶ���ֵ

                  


//���ת���Ƕ�����
#define  MOTORCONTROL30 30
#define  MOTORCONTROL45 45
#define  MOTORCONTROL60 60
#define  MOTORCONTROL90 90
#define  MOTORCONTROL180 180
#define  MOTORCONTROL360 360
#define  MOTORCONTROL720 720

#define  MOTORCONTROL8  783


extern void StartOutCalibrationFunc();
extern void DealCalibrationResult();
extern void SASCalibrationFunc();
extern uint pulseNum;
extern uint turnFlag;
extern uint wantTurnDir;          
extern uint wantTurnAngle;
extern uchar startSasCalibrationResultState;
extern uchar switchQualified;

   
#endif