#ifndef _CALIBRATION_H
#define _CALIBRATION_H
   
  
  
#include <hidef.h>
#include <mc9s12g48.h>  


//==============不同版本的比对数据宏定义==================//
#define  FORWARD 0                 //   电机正转
#define  REVERSE 1                 //   电机反转

//#define   stepDegrees    1.8       //    电机一个脉冲对应转动的角度数值
#define   stepDegrees    0.05625       //    电机一个脉冲对应转动的角度数值

                  


//电机转动角度配置
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