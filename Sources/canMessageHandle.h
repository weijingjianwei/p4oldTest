#ifndef _CAN_MESSAGE_HANDLE_H
#define _CAN_MESSAGE_HANDLE_H
   
  
  
#include <hidef.h>
#include <mc9s12g48.h>  


//==============不同版本的比对数据宏定义==================//



#define  connectLink 1                 //   建立连接
#define  requestSeed  2                //   请求种子
#define  sendSecretKey   3             //   发送秘钥
#define  detectionDeviceNo 4           //   检测器件控制号
#define  readBatchNo    5              //   读批次号
#define  readHardWareNo 6              //   读硬件版本号
#define  readSoftWareNo 7              //   读软件版本号
#define  clearInCalibration  8         //   清除内部标定
#define  startInCalibration  9         //   内部标定开始
#define  startForWardOutCalibration 10        //   外部电机标定开始(左转)
//#define  endForWardOutCalibration 11        //     外部电机标定结束(左转)

#define  startReverseOutCalibration 11        //   外部电机标定开始(右转)
#define  endOutCalibration 12        //     外部电机标定结束(右转)

#define  reset   13                         //复位
#define  readCalibrationState   14          //读取标定状态

//===========================下线标定======================================//
#define  eolExtend          15               //进入扩展模式
#define  eolReadPartNum     16               //读取零件部件号
#define  eolReadHardWareNo  17               //读硬件版本号
#define  eolReadSoftWareNo  18               //读软件版本号
#define  safeAccess         19               //安全访问
#define  vinCodeWrite       20               //vin码写入
#define  vinCodeRead        21               //vin码读取
#define  carConfigWrite     22               //车辆配置信息写入
#define  carConfigRead      23               //车辆配置信息读取
#define  removeMidCalibration 24             //解除中位标定
#define  midCalibration     25               //转角中位标定
#define  clearSSMCode       26               //清除SSM故障码
#define  readSSMCode        27               //读取SSM故障码
#define  sasCalibration     28               //sas标定开始
#define  sasCalibrationEnd  29               //sas标定开始结束


//===========================下线标定安全访问步骤======================================//
#define  safeAccessSendSeed 1              //下线标定安全访问发送种子
#define  safeAccessSendSecret 2            //下线标定安全访问发送秘钥

//===========================下线标定转角中位标定步骤======================================//
#define  midCalibrationStep1 1              //下线标定转角中位标定步骤1
#define  midCalibrationStep2 2              //下线标定转角中位标定步骤2




   
extern void Send3EService();
extern void CANMESSAGEHADLE();
extern void ConnectLink();
extern void SendSeed();
extern void SendSecret();
extern void DetectionDeviceNo();
extern void ReadBatchNo();
extern void ReadHardWareNo();
extern void ReadSoftWareNo();
extern void ClearInCalibration();
extern void StartInCalibration();
extern  uchar runstep;
extern uchar calibrationStepResState;
extern  uchar canSendState;
extern uint sendNum;
extern uchar calibrationStatus;

   
#endif