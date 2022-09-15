 #include "derivative.h"      /* derivative-specific definitions */
 #include "canMessageHandle.h"
 #include "calibration.h"
 

 
 //******************不同版本的开关接收报文标准数据*************************//
 
 uchar  connectLinkMes[8] = {0x06,0x50,0x03,0x00,0x32,0x00,0xC8,0x00};   //   建立连接响应标准报文
 uchar  requestSeedMes[3] = {0x06,0x67,0x01};                            //   请求种子响应标准报文前三位
 uchar  sendSecretKeyMes[8] = {0x02,0x67,0x02,0x00,0x00,0x00,0x00,0x00};  //   发送秘钥响应标准报文
 
 uchar  detectionDeviceNo1Mes[8] = {0x10,0x10,0x62,0xF1,0X87,0X50,0X30,0X33};//  检测硬件控制号第一帧标准报文
 uchar  detectionDeviceNo2Mes[8] = {0x21,0x37,0x33,0x30,0x30,0x30,0X30,0X30};//  检测硬件控制号第二帧标准报文
 uchar  detectionDeviceNo3Mes[8] = {0x22,0x30,0x31,0x33,0x00,0X00,0X00,0X00};//  检测硬件控制号第三帧标准报文
 
 uchar  batchNo1Mes[8] = {0x10,0x0B,0X62,0XF1,0X8C,0X00,0X00,0X00};          //读批次号响应第一帧标准报文
 uchar  batchNo2Mes[8] = {0x21,0x00,0X00,0X00,0X00,0X00,0X00,0X00};          //读批次号响应第二帧标准报文
 
 uchar  hardWareNo1Mes[8] = {0x10,0x14,0X62,0XF1,0X91,0X48,0X57,0X2E};       //读供应商硬件版本号响应第一帧标准报文
 uchar  hardWareNo2Mes[8] = {0x21,0x56,0X2E,0X31,0X2E,0X30,0X2E,0X30};       //读供应商硬件版本号响应第一帧标准报文
 uchar  hardWareNo3Mes[8] = {0x22,0x2E,0X32,0X32,0X30,0X35,0X30,0X36};       //读供应商硬件版本号响应第一帧标准报文
 
 uchar  softWareNo1Mes[8] ={0x10,0x14,0X62,0XF1,0X89,0X53,0X57,0X2E};        //读供应商软件版本号响应第一帧标准报文
 uchar  softWareNo2Mes[8] ={0x21,0x56,0X2E,0X31,0X2E,0X30,0X2E,0X30};        //读供应商软件版本号响应第二帧标准报文
 uchar  softWareNo3Mes[8] ={0x22,0x2E,0X32,0X32,0X30,0X37,0X30,0X36};        //读供应商软件版本号响应第三帧标准报文
 
 uchar  clearInCalibrationMes[8] = {0x05,0x71,0X01,0XFB,0X11,0X00,0X00,0X00};  //清除内部标定响应标准报文
 
 uchar  startInCalibrationMes[8] = {0x05,0x71,0X01,0XFB,0X10,0X00,0X00,0X00};   //内部标定开始 71 01 FB 10 XX   XX : 00 (未标定) XX : 01 (已标定)
 
 
 uchar startCalibrationStepMes[6] = {0x10,0x08,0x71,0X01,0XFB,0X12};            //开始标定每一步发送命令

 
 uchar  endOutCalibrationMes1[8] = {0x05,0x71,0X02,0XFB,0X12,0X00,0X00,0X00};  //内部已标定
 uchar  endOutCalibrationMes2[8] = {0x05,0x71,0X02,0XFB,0X12,0X01,0X00,0X00};  //内部未标定
 uchar  endOutCalibrationMes3[4] = {0x03,0x7F,0x31,0x78};                      //内部标定未完成
 
 
 uchar  resetMes[8] ={0x02,0x51,0X01,0X00,0X00,0X00,0X00,0X00};                //复位
 
 uchar  readCalibrationStateMes[5] = {0x10,0x12,0x62,0xFB,0x21};  //内部已经标定状态
 
//============================下线标定=============================================
 uchar  eolExtendMes[8] = {0x06,0x50,0x03,0x00,0x32,0x00,0xC8,0x00};   //   进入扩展模式 
 
 uchar  eolReadPartNumMes1[8] = {0x10,0x10,0x62,0xF1,0X87,0X50,0X30,0X33};      //  EOL读取零件部件号第一帧标准报文
 uchar  eolReadPartNumMes2[8] = {0x21,0x37,0x33,0x30,0x30,0x30,0X30,0X30};      //  EOL读取零件部件号第二帧标准报文
 uchar  eolReadPartNumMes3[8] = {0x22,0x30,0x31,0x33,0x00,0X00,0X00,0X00};      //  EOL读取零件部件号第三帧标准报文
 
 uchar  eolhardWareNo1Mes[8] = {0x10,0x14,0X62,0XF1,0X91,0X48,0X57,0X2E};       //EOL 读供应商硬件版本号响应第一帧标准报文
 uchar  eolhardWareNo2Mes[8] = {0x21,0x56,0X2E,0X31,0X2E,0X30,0X2E,0X30};       //EOL 读供应商硬件版本号响应第一帧标准报文
 uchar  eolhardWareNo3Mes[8] = {0x22,0x2E,0X32,0X32,0X30,0X35,0X30,0X36};       //EOL 读供应商硬件版本号响应第一帧标准报文
 
 uchar  eolsoftWareNo1Mes[8] ={0x10,0x14,0X62,0XF1,0X89,0X53,0X57,0X2E};        //EOL 读供应商软件版本号响应第一帧标准报文
 uchar  eolsoftWareNo2Mes[8] ={0x21,0x56,0X2E,0X31,0X2E,0X30,0X2E,0X30};        //EOL 读供应商软件版本号响应第二帧标准报文
 uchar  eolsoftWareNo3Mes[8] ={0x22,0x2E,0X32,0X32,0X30,0X37,0X30,0X36};        //EOL 读供应商软件版本号响应第三帧标准报文
 
 uchar  safeAccessSendSeedMes[3] = {0x06,0x67,0x01};                             //   EOL安全访问请求种子响应标准报文前三位
 uchar  safeAccessSendSecretMes[8] = {0x02,0x67,0x02,0x00,0x00,0x00,0x00,0x00};  //  EOL安全访问 发送秘钥响应标准报文
 
 uchar  vinCodeWriteMes[8] = {0x03,0x6E,0xF1,0x90,0x00,0x00,0x00,0x00};          //  EOL VIN码写入响应标准报文
 
 uchar  vinCodeReadMes1[8] = {0x10,0x14,0x62,0xF1,0x90,0xC6,0xF0,0x50};          //  EOL VIN码读取响应第一帧标准报文
 uchar  vinCodeReadMes2[8] = {0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00};          //  EOL VIN码读取响应第二帧标准报文
 uchar  vinCodeReadMes3[8] = {0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00};          //  EOL VIN码读取响应第三帧标准报文
 
 uchar  carConfigWriteMes[8] = {0x03,0x6E,0xF1,0xA1,0x00,0x00,0x00,0x00};          //  EOL 车辆配置信息写入响应标准报文
 
 uchar  carConfigReadMes[8] = {0x03,0x62,0xF1,0xA1,0x00,0x00,0x00,0x00};          //  EOL 车辆配置信息读取响应标准报文
 
 uchar  removeMidCalibrationMes[8] = {0x05,0x71,0x01,0x8B,0xC0,0x00,0x00,0x00};    //  EOL 解除中位标定响应标准报文
 
 uchar  midCalibrationStep1Mes[8] = {0x05,0x71,0x01,0x8B,0xC1,0x00,0x00,0x00};    //  EOL 转角中位标定步骤1响应标准报文
 uchar  midCalibrationStep2Mes[8] = {0x05,0x71,0x01,0x8B,0xC1,0x00,0x00,0x00};    //  EOL 转角中位标定步骤2响应标准报文
 
 uchar  clearSSMCodeMes[8] = {0x01,0x54,0x00,0x00,0x00,0x00,0x00,0x00};           //  EOL 清除SSM故障码响应标准报文
 
 //********************************************//
 
 uchar runstep=0;          //定义当前步骤
 uchar safeAccessStep=0;      //下线标定安全访问步骤(发送种子，发送秘钥)
 uchar midCalibrationStep;    //下线标定转角中位标定(转角中位标定步骤1 转角中位标定步骤2)
 uint sendNum;            //定义发送次数
 unsigned long int seed;  //接收种子变量
 unsigned long int encryptedMiyao;    //算法加密之后得到的秘钥
 mscan_msg_t sendMessage;  //发送消息
 uchar sendData[8];        //发送消息数组
 uchar canSendState;       //可以发送标志位
 
 uchar unCalibrationNum;   //未标定次数标志位 超过3次后报错
 
 uchar calibrationStepResState;  //每一步标定结果  1：成功响应 0：未成功响应
 
 uchar  calibrationStatus = SUCCESS;           //标定状态标志位
 
 
 
 
 
 
 /******************************************************************************/
/**
  Function Name: void  compateArray(void)
 * Description: 接收报文数组和标准数据比对
 * Param:    recevieMes 接收报文数组 standardMes 标准值数组  num 需要比对的个数
 * Return:  1 比对成功  0 比对失败 
 * Author:  pine
 *****************************************************************************/ 
 int  compareArray(byte recevieMes[],byte standardMes[],int num){
	int i;
	for(i = 0; i < num; i++)
	{
		if (recevieMes[i] != standardMes[i])
		{
			return 0;
		}
		i++;
	}
	return 1;
}


 
 /******************************************************************************/
/**
  Function Name: void  canmessagehandle(void)
 * Description: can协议命令解析
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/

uint resSuccessNum;
void CANMESSAGEHADLE(void) {
 
   if(canreceiveflag==1){ 
       
     
       /*******step1发送建立XXX连接后，收到正确的指令，则进入请求种子命令*******/
       
       if(compareArray(RxMsg.Data,connectLinkMes,8) && runstep==connectLink) {
          
          runstep=requestSeed;  
       }
       
       /*******step2发送请求种子后，收到正确的指令，则进入发送秘钥命令*******/
       if(compareArray(RxMsg.Data,requestSeedMes,3) && runstep==requestSeed) {
          seed=RxMsg.Data[3]; 
          seed=(seed<<8)+RxMsg.Data[4];
          seed=(seed<<8)+RxMsg.Data[5];
          seed=(seed<<8)+RxMsg.Data[6];
          runstep=sendSecretKey;
          
       }
       /*******step3发送秘钥后，收到正确的指令，则进入检测控制器件号命令*******/
       if(compareArray(RxMsg.Data,sendSecretKeyMes,8)&&runstep==sendSecretKey){
          
          runstep=detectionDeviceNo;      
       }
       
       /*******step4发送检测器件控制号后，收到正确的指令，则进入读批次号命令*******/
       if((runstep==detectionDeviceNo) &&  compareArray(canSASRXbuff[0],detectionDeviceNo1Mes,8) && compareArray(canSASRXbuff[1],detectionDeviceNo2Mes,8) && compareArray(canSASRXbuff[2],detectionDeviceNo3Mes,8)){
         
          runstep=readBatchNo;
       }
       
       /*******step5发送读批次号后，收到正确的指令，则进入读供应商硬件版本号命令*******/
       if((runstep==readBatchNo) && compareArray(canSASRXbuff[0],batchNo1Mes,8) && compareArray(canSASRXbuff[1],batchNo2Mes,8) ){
         
          runstep=readHardWareNo;
       }
       
       /*******step6发送读取硬件版本号后，收到正确的指令，则进入读供应商软件版本号命令*******/
       if((runstep==readHardWareNo) && compareArray(canSASRXbuff[0],hardWareNo1Mes,8) && compareArray(canSASRXbuff[1],hardWareNo2Mes,8) && compareArray(canSASRXbuff[2],hardWareNo3Mes,8) ){
          
          runstep=readSoftWareNo; 
       }
       /*******step7发送读取软件版本号后，收到正确的指令，则进入清除内部标定命令*******/
       if((runstep==readSoftWareNo) && compareArray(canSASRXbuff[0],softWareNo1Mes,8) && compareArray(canSASRXbuff[1],softWareNo2Mes,8) && compareArray(canSASRXbuff[2],softWareNo3Mes,8)){
          
          runstep=clearInCalibration; 
       }
       
       /*******step8发送清除内部标定命令后，收到正确的指令，则进入内部标定开始命令*******/
       if(compareArray(RxMsg.Data,clearInCalibrationMes,8)  && (runstep==clearInCalibration)){
       
          runstep=startInCalibration; 
       }
       
       /*******step9发送开始内部标定命令后，收到正确的指令，则进入外部电机标定正转开始命令*******/
       if(compareArray(RxMsg.Data,startInCalibrationMes,8)  && (runstep==startInCalibration)){
          
             runstep=startForWardOutCalibration;
             wantTurnAngle=MOTORCONTROL8;
             wantTurnDir=FORWARD;
             turnFlag = 1;
       }
       
       //TODO 必须等响应报文成功之后才能执行下一步1.8°的标定，给个标志位判断？
       if(compareArray(canSASRXbuff[0],startCalibrationStepMes,6) && (runstep == startReverseOutCalibration || runstep == startForWardOutCalibration)){
             calibrationStepResState = 1; 
             resSuccessNum++;
       }
       
      
       
       /*******step10发送结束内部标定命令后(正转)，收到正确的指令，则进入外部电机反转开始命令******
       if(compareArray(RxMsg.Data,endOutCalibrationMes1,8)  && (runstep==startReverseOutCalibration)){
       
          runstep=startReverseOutCalibration;
          wantTurnAngle=MOTORCONTROL8;
          wantTurnDir=REVERSE; 
       }
       **/
       
        /*******step11发送结束内部标定命令后(反转)，收到正确的指令，则进入复位命令******/
       if(compareArray(RxMsg.Data,endOutCalibrationMes1,8)  && (runstep==endOutCalibration)){
          runstep=reset; 
       }
       
       /**
       if(compareArray(RxMsg.Data,endOutCalibrationMes1,8) ==0  && (runstep==endOutCalibration)){
           programERROR= 1;
       }
       **/
       
       /*******step12发送复位命令后，收到正确的指令，则进入读取标定状态命令******/
       if(compareArray(RxMsg.Data,resetMes,8)  && (runstep==reset)){
          runstep=readCalibrationState; 
       } 
       
       /*******step13发送读取标定状态命令后，收到正确的指令，根据标定结果执行接下来的操作******/
       if(compareArray(canSASRXbuff[0],readCalibrationStateMes,5)  && runstep==readCalibrationState){
          
          //如果未标定：重新执行标定流程：超过3次后报错
          if((canSASRXbuff[0][5] & 0x01)==0){
             unCalibrationNum++;
             if(unCalibrationNum == 3){
                 //TODO 报错处理流程
                 calibrationStatus = ERROR;
             }
             
             runstep=connectLink; 
          }else{
             //执行成功进行到下线标定第一步
             runstep=eolExtend;
          }
          
       } 
       
       //====================进入下线标定流程================================//
       
       /*******step4发送进入扩展命令后，收到正确的指令，则进入读取零件部件号命令*******/
       if(compareArray(RxMsg.Data,eolExtendMes,8) && runstep==eolExtend) {
          runstep=eolReadPartNum;  
       }
       
       /*******step4读取零件部件号命令，收到正确的指令，则进入读取供应商硬件版本命令*******/
       if((runstep==eolReadPartNum) && compareArray(canSASRXbuff[0],eolReadPartNumMes1,8) && compareArray(canSASRXbuff[1],eolReadPartNumMes2,8) && compareArray(canSASRXbuff[2],eolReadPartNumMes3,8)){
         
          runstep=eolReadHardWareNo;
       }
       
       /*******step4读取供应商硬件版本命令，收到正确的指令，则进入读取供应商软件版本命令*******/
       if((runstep==eolReadHardWareNo) && compareArray(canSASRXbuff[0],eolhardWareNo1Mes,8) && compareArray(canSASRXbuff[1],eolhardWareNo2Mes,8) && compareArray(canSASRXbuff[2],eolhardWareNo3Mes,8)){
         
          runstep=eolReadSoftWareNo;
       }
       
       /*******step4读取供应商软件版本命令，收到正确的指令，则进入安全访问发送请求种子命令*******/
       if(compareArray(canSASRXbuff[0],eolsoftWareNo1Mes,8) && compareArray(canSASRXbuff[1],eolsoftWareNo2Mes,8) && compareArray(canSASRXbuff[2],eolsoftWareNo3Mes,8) &&  (runstep==eolReadSoftWareNo)){
         
          runstep=safeAccess;
          safeAccessStep = safeAccessSendSeed;
       }
       
       /*******step2发送请求种子后，收到正确的指令，则进入发送秘钥命令*******/
       if(compareArray(RxMsg.Data,safeAccessSendSeedMes,3) && runstep==safeAccess && safeAccessStep == safeAccessSendSeed) {
          seed=RxMsg.Data[3]; 
          seed=(seed<<8)+RxMsg.Data[4];
          seed=(seed<<8)+RxMsg.Data[5];
          seed=(seed<<8)+RxMsg.Data[6];
          runstep=safeAccess; 
          safeAccessStep = safeAccessSendSecret;
       }
       /*******step3发送秘钥后，收到正确的指令，则进入vin码写入命令*******/
       if(compareArray(RxMsg.Data,safeAccessSendSecretMes,8) && runstep==safeAccess && safeAccessStep == safeAccessSendSecret){
      
          runstep=vinCodeWrite;      
       }
       
       /*******step3发送vin码写入命令，收到正确的指令，则进入vin码读取命令*******/
       if(compareArray(RxMsg.Data,vinCodeWriteMes,8) && runstep==vinCodeWrite){
      
          runstep=vinCodeRead;      
       }
       
       
       /*******step3vin码读取命令后，收到正确的指令，则进入车辆配置信息写入命令*******/
       if((runstep==vinCodeRead) && compareArray(canSASRXbuff[0],vinCodeReadMes1,8) && compareArray(canSASRXbuff[1],vinCodeReadMes2,8) && compareArray(canSASRXbuff[2],vinCodeReadMes3,8)){
         
          runstep=carConfigWrite;
       }
       
       /*******step3发送车辆配置信息写入命令，收到正确的指令，则进入车辆配置信息读取命令*******/
       if(compareArray(RxMsg.Data,carConfigWriteMes,8) && runstep==carConfigWrite){
      
          runstep=carConfigRead;      
       }
       
       
       /*******step3发送车辆配置信息读取命令，收到正确的指令，则进入解除中位标定命令*******/
       if(compareArray(RxMsg.Data,carConfigReadMes,8) && runstep==carConfigRead){
      
          runstep=removeMidCalibration;      
       }
       
       /*******step3发送解除中位标定命令命令，收到正确的指令，则进入转角中位标定(步骤一)命令*******/
       if(compareArray(RxMsg.Data,removeMidCalibrationMes,8) && runstep==removeMidCalibration){
      
          runstep=midCalibration;
          midCalibrationStep = midCalibrationStep1;      
       }
       
       /*******step3发送转角中位标定(步骤一)命令，收到正确的指令，则进入转角中位标定(步骤二)命令*******/
       if(compareArray(RxMsg.Data,midCalibrationStep1Mes,8) && runstep==midCalibration && midCalibrationStep == midCalibrationStep1){
      
          runstep=midCalibration;
          midCalibrationStep = midCalibrationStep2;      
       }
       
       /*******step3发送转角中位标定(步骤二)命令，收到正确的指令，则进入清除SSM故障码命令*******/
       if(compareArray(RxMsg.Data,midCalibrationStep2Mes,8) && runstep==midCalibration && midCalibrationStep == midCalibrationStep2){
      
          runstep=clearSSMCode;
       }
       
       /*******step3发送清除SSM故障码命令命令，收到正确的指令，则进入读取SSM故障码命令*******/
       if(compareArray(RxMsg.Data,clearSSMCodeMes,8) && runstep==clearSSMCode){
      
          //runstep=readSSMCode;
          runstep = sasCalibration;  //师父暂时没加上最后一步，所以这里先模拟到了sas标定的步骤
          wantTurnDir = FORWARD;
          wantTurnAngle = MOTORCONTROL30;
          turnFlag=1;
       }
       
       
       
       
       
       
       
       
       //允许接收Can报文标志位置0,表示可以接收新报文了
       canreceiveflag=0; 
       
       
       
   }
  
}



/******************************************************************************/
/**
  Function Name: void  connectLink(void)
 * Description: 建立连接
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
 void ConnectLink(void) {
      byte sendflag;
      if(runstep==connectLink) {
          sendMessage.u16ID=0X753;    //发送建立连接命令
          sendMessage.u8Prio=0;
          sendMessage.u8Length=8;      //0X753 02 10 03 00 00 00 00 00
          sendData[0]=0x02;
          sendData[1]=0X10;
    		  sendData[2]=0x03;
    		  sendData[3]=0x00;
    		  sendData[4]=0x00;
    		  sendData[5]=0x00;
    		  sendData[6]=0x00;
    		  sendData[7]=0x00;
          sendMessage.u8TxData=sendData;
         
          sendflag=CAN_Send_Frame(sendMessage);
          sendNum++;                            //发送计数
          if(sendNum>canRetryNum) {
          sendNum=0;       //接收成功后在can中断中进入下一步
          canSendState=ERROR;
          }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
      }                          
 }
 
 
/******************************************************************************/
/**
  \Function Name: void  sendseed(void)
 * Description: 发送请求种子命令
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
 void SendSeed(void) {
     byte sendflag;
     if(runstep==requestSeed) {
       sendMessage.u16ID=0X753;    //请求种子
       sendMessage.u8Prio=0;
       sendMessage.u8Length=8;      //0X753 02 27 01 00 00 00 00 00
       sendData[0]=0x02;
       sendData[1]=0X27;
       sendData[2]=0x01;
       sendData[3]=0x00;
       sendData[4]=0x00;
       sendData[5]=0x00;
       sendData[6]=0x00;
       sendData[7]=0x00;
       sendMessage.u8TxData=sendData;
       sendflag=CAN_Send_Frame(sendMessage);  //can发送
       sendNum++;                            //发送计数
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
    
     } 
 }
 
 
 /******************************************************************************/
/**
  \Function Name: void  encryptTokey(void)
 * Description: 加密算法
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
unsigned long int encryptTokey(unsigned long int seed) { 
  unsigned long int Key=0; 
  unsigned long int dwNewKeywrd = 0;
  unsigned long dwKey1 = 0;
  unsigned long dwKey2 = 0;
  unsigned long dwKey3 = 0;
  unsigned long dwKey4 = 0;
  unsigned char a = 0x96,b = 0x09,c = 0x8B, d = 0x08;
  unsigned char dwSeed1 = (seed >> 24)&0XFF;
  unsigned char dwSeed2=(seed >> 16)&0XFF;
  unsigned char dwSeed3=(seed >> 8)&0XFF;
  unsigned char dwSeed4=seed&0XFF;
  
  
  dwKey1 = (a * (dwSeed1 * dwSeed1) )+ (b * (dwSeed2 * dwSeed2)) + (c * (dwSeed1 * dwSeed2));
	dwKey2 = (a * dwSeed1) + (b * dwSeed2) +(d * (dwSeed1*dwSeed2));
	dwKey3 = (a * (dwSeed3*dwSeed4)) + (b * (dwSeed4*dwSeed4)) +(c * (dwSeed3*dwSeed4));
	dwKey4 = (a * (dwSeed3*dwSeed4)) + (b * dwSeed4) + (d * (dwSeed3*dwSeed4));
	dwNewKeywrd =((dwKey1 & 0xFF)<<24)+((dwKey2 & 0xFF)<<16) + ((dwKey3 & 0xFF) << 8) +(dwKey4 & 0xFF);
  
  return dwNewKeywrd; 
}
 
/******************************************************************************/
/**
  \Function Name: void  sendSecret(void)
 * Description: 发送 秘钥命令
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void SendSecret(void) {
     byte sendflag; 
     if(runstep==sendSecretKey) {   
        encryptedMiyao = encryptTokey(seed);
        sendMessage.u16ID=0X753;    //发送秘钥
        sendMessage.u8Prio=0;
        sendMessage.u8Length=8;      //0x753 06 27 02 04 C6 F0 50 00 
        sendData[0]=0x06;
        sendData[1]=0X27;
        sendData[2]=0x02;
        sendData[3]=(encryptedMiyao>>24)&0XFF;
        sendData[4]=(encryptedMiyao>>16)&0XFF;
        sendData[5]=(encryptedMiyao>>8)&0XFF;
        sendData[6]=encryptedMiyao&0XFF;
        sendData[7]=0x00;
        sendMessage.u8TxData=sendData;
        sendflag=CAN_Send_Frame(sendMessage);  //can发送
        sendNum++;                            //发送计数
        if(sendNum>canRetryNum){
          canSendState=ERROR;
          sendNum=0;
        }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
    }  
}



/******************************************************************************/
/**
  \Function Name: void  DetectionDeviceNo(void)
 * Description: 发送 检测器件控制号
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void DetectionDeviceNo(void){
     byte sendflag; 
     if(runstep==detectionDeviceNo) {    
        sendMessage.u16ID=0X753;    //检测器件控制号
        sendMessage.u8Prio=0;
        sendMessage.u8Length=8;      //0x753 03 22 F1 87 00 00 00 00 
        sendData[0]=0x03;
        sendData[1]=0x22;
        sendData[2]=0xF1;
        sendData[3]=0x87;;
        sendData[4]=0x00;
        sendData[5]=0x00;
        sendData[6]=0x00;
        sendData[7]=0x00;
        sendMessage.u8TxData=sendData;
        sendflag=CAN_Send_Frame(sendMessage);  //can发送
        sendNum++;                            //发送计数
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
        }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}

/******************************************************************************/
/**
  \Function Name: void  ReadBatchNo(void)
 * Description: 发送 读取批次号
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void ReadBatchNo(void){
     byte sendflag;
     if(runstep==readBatchNo) {    
         sendMessage.u16ID=0X753;    //读取批次号
         sendMessage.u8Prio=0;
         sendMessage.u8Length=8;      //0x753 03 22 F1 8C 00 00 00 00 
         sendData[0]=0x03;
         sendData[1]=0x22;
         sendData[2]=0xF1;
         sendData[3]=0x8C;;
         sendData[4]=0x00;
         sendData[5]=0x00;
         sendData[6]=0x00;
         sendData[7]=0x00;
         sendMessage.u8TxData=sendData;
         sendflag=CAN_Send_Frame(sendMessage);  //can发送
         sendNum++;                            //发送计数
         if(sendNum>canRetryNum){
            canSendState=ERROR;
            sendNum=0;
         }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  ReadSupplierName(void)
 * Description: 发送 读取供应商名称
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
/**void ReadSupplierName(void){
     byte sendflag;    
     sendMessage.u16ID=0X753;    //读取供应商名称
     sendMessage.u8Prio=0;
     sendMessage.u8Length=8;      //0x753 03 22 F1 8A 00 00 00 00 
     sendData[0]=0x03;
     sendData[1]=0x22;
     sendData[2]=0xF1;
     sendData[3]=0x8A;;
     sendData[4]=0x00;
     sendData[5]=0x00;
     sendData[6]=0x00;
     sendData[7]=0x00;
     sendMessage.u8TxData=sendData;
     sendflag=CAN_Send_Frame(sendMessage);  //can发送
     sendNum++;                            //发送计数
     if(sendNum>10){
        canSendState=ERROR;
        sendNum=0;
     }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
}
**/


/******************************************************************************/
/**
  \Function Name: void  ReadHardWareNo(void)
 * Description: 发送 读取硬件版本号命令
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void ReadHardWareNo(void){
     byte sendflag; 
     if(runstep==readHardWareNo) {    
         sendMessage.u16ID=0X753;    //读取硬件版本号
         sendMessage.u8Prio=0;
         sendMessage.u8Length=8;      //0x753 03 22 F1 91 00 00 00 00 
         sendData[0]=0x03;
         sendData[1]=0x22;
         sendData[2]=0xF1;
         sendData[3]=0x91;;
         sendData[4]=0x00;
         sendData[5]=0x00;
         sendData[6]=0x00;
         sendData[7]=0x00;
         sendMessage.u8TxData=sendData;
         sendflag=CAN_Send_Frame(sendMessage);  //can发送
         sendNum++;                            //发送计数
         if(sendNum>canRetryNum){
            canSendState=ERROR;
            sendNum=0;
         }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  ReadSoftWareNo(void)
 * Description: 发送 读取软件版本号命令
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void ReadSoftWareNo(void){
     byte sendflag;
     if(runstep==readSoftWareNo) {     
        sendMessage.u16ID=0X753;    //读取软件版本号
        sendMessage.u8Prio=0;
        sendMessage.u8Length=8;      //0x753 03 22 F1 89 00 00 00 00 
        sendData[0]=0x03;
        sendData[1]=0x22;
        sendData[2]=0xF1;
        sendData[3]=0x89;;
        sendData[4]=0x00;
        sendData[5]=0x00;
        sendData[6]=0x00;
        sendData[7]=0x00;
        sendMessage.u8TxData=sendData;
        sendflag=CAN_Send_Frame(sendMessage);  //can发送
        sendNum++;                            //发送计数
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
         }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}



/******************************************************************************/
/**
  \Function Name: void  ClearInCalibration(void)
 * Description: 发送 清除内部标定命令
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void ClearInCalibration(void){
     byte sendflag;    
     if(runstep==clearInCalibration) {   
         sendMessage.u16ID=0X753;    //清除内部标定命令
         sendMessage.u8Prio=0;
         sendMessage.u8Length=8;      //0x753 04 31 01 FB 11 00 00 00 
         sendData[0]=0x04;
         sendData[1]=0x31;
         sendData[2]=0x01;
         sendData[3]=0xFB;;
         sendData[4]=0x11;
         sendData[5]=0x00;
         sendData[6]=0x00;
         sendData[7]=0x00;
         sendMessage.u8TxData=sendData;
         sendflag=CAN_Send_Frame(sendMessage);  //can发送
         sendNum++;                            //发送计数
         if(sendNum>canRetryNum){
            canSendState=ERROR;
            sendNum=0;
         }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}



/******************************************************************************/
/**
  \Function Name: void  StartInCalibration(void)
 * Description: 发送 内部标定开始命令
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void StartInCalibration(void){
     byte sendflag;
     if(runstep==startInCalibration) {    
         sendMessage.u16ID=0X753;    //清除内部标定命令
         sendMessage.u8Prio=0;
         sendMessage.u8Length=8;      //0x753 04 31 01 FB 10 00 00 00 
         sendData[0]=0x04;
         sendData[1]=0x31;
         sendData[2]=0x01;
         sendData[3]=0xFB;;
         sendData[4]=0x10;
         sendData[5]=0x00;
         sendData[6]=0x00;
         sendData[7]=0x00;
         sendMessage.u8TxData=sendData;
         sendflag=CAN_Send_Frame(sendMessage);  //can发送
         sendNum++;                            //发送计数
         if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
         }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  StartOutCalibration(void)
 * Description: 发送 外部电机标定开始命令
 * Param:   direction  方向  1：电机正转  0:电机反转
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void StartOutCalibration(uchar direction){
     byte sendflag;
     if(runstep==startForWardOutCalibration || runstep==startReverseOutCalibration) {     
          sendMessage.u16ID=0X753;    //清除内部标定命令
          sendMessage.u8Prio=0;
          sendMessage.u8Length=8;      //0x753 07 31 01 FB 12 X0 X1 X2 
          sendData[0]=0x07;
          sendData[1]=0x31;
          sendData[2]=0x01;
          sendData[3]=0xFB;
          sendData[4]=0x12;
          sendData[5]=0x01 & direction;
          sendData[6]=0x00;
          sendData[7]=0x00;
          sendMessage.u8TxData=sendData;
          sendflag=CAN_Send_Frame(sendMessage);  //can发送
          //sendNum++;                            //发送计数
          //if(sendNum>canRetryNum){
            //canSendState=ERROR;
           // sendNum=0;
          //}//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  StopOutCalibration(void)
 * Description: 发送 外部电机标定停止命令
 * Param:   direction  方向  1：电机正转  0:电机反转
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void StopOutCalibration(uchar direction){
     byte sendflag;    
     if(runstep==endOutCalibration) {  
         sendMessage.u16ID=0X753;    //清除内部标定命令
         sendMessage.u8Prio=0;
         sendMessage.u8Length=8;      //0x753 05 31 01 FB 12 X0 00 00 
         sendData[0]=0x05;
         sendData[1]=0x31;
         sendData[2]=0x02;
         sendData[3]=0xFB;;
         sendData[4]=0x12;
         sendData[5]=0x01 & direction;
         sendData[6]=0x00;
         sendData[7]=0x00;
         sendMessage.u8TxData=sendData;
         sendflag=CAN_Send_Frame(sendMessage);  //can发送
         sendNum++;                            //发送计数
         if(sendNum>canRetryNum){
            canSendState=ERROR;
            sendNum=0;
         }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
         
     }
} 

/******************************************************************************/
/**
  \Function Name: void  Reset(void)
 * Description: 发送 复位命令
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void Reset(void){
     if(runstep==reset){
        byte sendflag;    
        sendMessage.u16ID=0X753;    //发送复位命令
        sendMessage.u8Prio=0;
        sendMessage.u8Length=8;      //0x753 02 11 01 00 00 00 00 00 
        sendData[0]=0x02;
        sendData[1]=0x11;
        sendData[2]=0x01;
        sendData[3]=0x00;;
        sendData[4]=0x00;
        sendData[5]=0x00;
        sendData[6]=0x00;
        sendData[7]=0x00;
        sendMessage.u8TxData=sendData;
        sendflag=CAN_Send_Frame(sendMessage);  //can发送
        sendNum++;                            //发送计数
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
        }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
  }

}



/******************************************************************************/
/**
  \Function Name: void  ReadCalibrationState(void)
 * Description: 发送 读取标定状态命令
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void ReadCalibrationState(void){
   if(runstep==readCalibrationState){
     byte sendflag;    
     sendMessage.u16ID=0X753;    //发送复位命令
     sendMessage.u8Prio=0;
     sendMessage.u8Length=8;      //0x753 03 22 FB 13 00 00 00 00 
     sendData[0]=0x03;
     sendData[1]=0x22;
     sendData[2]=0xFB;
     sendData[3]=0x21;;
     sendData[4]=0x00;
     sendData[5]=0x00;
     sendData[6]=0x00;
     sendData[7]=0x00;
     sendMessage.u8TxData=sendData;
     sendflag=CAN_Send_Frame(sendMessage);  //can发送
     sendNum++;                            //发送计数
     if(sendNum>canRetryNum){
        canSendState=ERROR;
        sendNum=0;
     }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
    }
}


/******************************************************************************/
/**
  Function Name: void  connectLink(void)
 * Description: 电机每转1.8°发送一帧报文数据
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
 void SendFrameByStepTurn(uchar direction) {
      byte sendflag;
      if(runstep==startForWardOutCalibration) {
          sendMessage.u16ID=0X753;    //发送建立连接命令
          sendMessage.u8Prio=0;
          sendMessage.u8Length=8;      //0X753 31 01 FB 12 00 00 00 00
          sendData[0]=0x31;
          sendData[1]=0X01;
    		  sendData[2]=0xFB;
    		  sendData[3]=0x12;
    		  sendData[4]=0x00;
    		  sendData[5]=0x00 & direction;
    		  sendData[6]=0x00;
    		  sendData[7]=0x00;
          sendMessage.u8TxData=sendData;
         
          sendflag=CAN_Send_Frame(sendMessage);
          sendNum++;                            //发送计数
          if(sendNum>canRetryNum) {
          sendNum=0;       //接收成功后在can中断中进入下一步
          canSendState=ERROR;
          }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
      }                          
 }
 
 
 /******************************************************************************/
/**
  \Function Name: void  Reset(void)
 * Description: 发送 复位命令
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void Send3EService(void){
    if(runstep==reset) {
        byte sendflag;    
        sendMessage.u16ID=0X753;    //发送复位命令
        sendMessage.u8Prio=0;
        sendMessage.u8Length=8;      //0x753 02 3E 80 00 00 00 00 00 
        sendData[0]=0x02;
        sendData[1]=0x3E;
        sendData[2]=0x80;
        sendData[3]=0x00;;
        sendData[4]=0x00;
        sendData[5]=0x00;
        sendData[6]=0x00;
        sendData[7]=0x00;
        sendMessage.u8TxData=sendData;
        sendflag=CAN_Send_Frame(sendMessage);  //can发送
        sendNum++;                            //发送计数
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
        }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
   }

}


/******************************************************************************/
/**
  \Function Name: void  EOLExtend(void)
 * Description: EOL 进入扩展模式
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLExtend(void){
    if(runstep==eolExtend) {
        byte sendflag;    
        sendMessage.u16ID=0X753;    //发送进入扩展模式命令
        sendMessage.u8Prio=0;
        sendMessage.u8Length=8;      //0x753 02 10 03 00 00 00 00 00 
        sendData[0]=0x02;
        sendData[1]=0x10;
        sendData[2]=0x03;
        sendData[3]=0x00;;
        sendData[4]=0x00;
        sendData[5]=0x00;
        sendData[6]=0x00;
        sendData[7]=0x00;
        sendMessage.u8TxData=sendData;
        sendflag=CAN_Send_Frame(sendMessage);  //can发送
        sendNum++;                            //发送计数
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
        }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
   }

}

/******************************************************************************/
/**
  \Function Name: void  EOLReadPartNum(void)
 * Description: EOL 读取零件部件号
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLReadPartNum(void){
     byte sendflag; 
     if(runstep==eolReadPartNum) {    
        sendMessage.u16ID=0X753;    //检测器件控制号
        sendMessage.u8Prio=0;
        sendMessage.u8Length=8;      //0x753 03 22 F1 87 00 00 00 00 
        sendData[0]=0x03;
        sendData[1]=0x22;
        sendData[2]=0xF1;
        sendData[3]=0x87;;
        sendData[4]=0x00;
        sendData[5]=0x00;
        sendData[6]=0x00;
        sendData[7]=0x00;
        sendMessage.u8TxData=sendData;
        sendflag=CAN_Send_Frame(sendMessage);  //can发送
        sendNum++;                            //发送计数
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
        }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}



/******************************************************************************/
/**
  \Function Name: void  EOLReadHardWareNo(void)
 * Description: 发送 EOL读取硬件版本号命令
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLReadHardWareNo(void){
     byte sendflag; 
     if(runstep==eolReadHardWareNo) {    
         sendMessage.u16ID=0X753;    //读取硬件版本号
         sendMessage.u8Prio=0;
         sendMessage.u8Length=8;      //0x753 03 22 F1 91 00 00 00 00 
         sendData[0]=0x03;
         sendData[1]=0x22;
         sendData[2]=0xF1;
         sendData[3]=0x91;;
         sendData[4]=0x00;
         sendData[5]=0x00;
         sendData[6]=0x00;
         sendData[7]=0x00;
         sendMessage.u8TxData=sendData;
         sendflag=CAN_Send_Frame(sendMessage);  //can发送
         sendNum++;                            //发送计数
         if(sendNum>canRetryNum){
            canSendState=ERROR;
            sendNum=0;
         }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLReadSoftWareNo(void)
 * Description: 发送 EOL读取软件版本号命令
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLReadSoftWareNo(void){
     byte sendflag;
     if(runstep==eolReadSoftWareNo) {     
        sendMessage.u16ID=0X753;    //读取软件版本号
        sendMessage.u8Prio=0;
        sendMessage.u8Length=8;      //0x753 03 22 F1 89 00 00 00 00 
        sendData[0]=0x03;
        sendData[1]=0x22;
        sendData[2]=0xF1;
        sendData[3]=0x89;;
        sendData[4]=0x00;
        sendData[5]=0x00;
        sendData[6]=0x00;
        sendData[7]=0x00;
        sendMessage.u8TxData=sendData;
        sendflag=CAN_Send_Frame(sendMessage);  //can发送
        sendNum++;                            //发送计数
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
         }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLsafeAccessSendSeed(void)
 * Description: 发送 EOL下线标定安全访问发送种子
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLsafeAccessSendSeed(void){
     byte sendflag;
     if(runstep==safeAccess && safeAccessStep == safeAccessSendSeed) {     
       sendMessage.u16ID=0X753;    //安全访问发送种子
       sendMessage.u8Prio=0;
       sendMessage.u8Length=8;      //0X753 02 27 01 00 00 00 00 00
       sendData[0]=0x02;
       sendData[1]=0X27;
       sendData[2]=0x01;
       sendData[3]=0x00;
       sendData[4]=0x00;
       sendData[5]=0x00;
       sendData[6]=0x00;
       sendData[7]=0x00;
       sendMessage.u8TxData=sendData;
       sendflag=CAN_Send_Frame(sendMessage);  //can发送
       sendNum++;                            //发送计数
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLsafeAccessSendSecret(void)
 * Description: 发送 EOL下线标定安全访问发送秘钥
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLsafeAccessSendSecret(void) {
     byte sendflag; 
     if(runstep==safeAccess && safeAccessStep == safeAccessSendSecret) {   
        encryptedMiyao = encryptTokey(seed);
        sendMessage.u16ID=0X753;    //下线标定安全访问发送秘钥
        sendMessage.u8Prio=0;
        sendMessage.u8Length=8;      //0x753 06 27 02 04 C6 F0 50 00 
        sendData[0]=0x06;
        sendData[1]=0X27;
        sendData[2]=0x02;
        sendData[3]=(encryptedMiyao>>24)&0XFF;
        sendData[4]=(encryptedMiyao>>16)&0XFF;
        sendData[5]=(encryptedMiyao>>8)&0XFF;
        sendData[6]=encryptedMiyao&0XFF;
        sendData[7]=0x00;
        sendMessage.u8TxData=sendData;
        sendflag=CAN_Send_Frame(sendMessage);  //can发送
        sendNum++;                            //发送计数
        if(sendNum>canRetryNum){
          canSendState=ERROR;
          sendNum=0;
        }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
    }  
}


/******************************************************************************/
/**
  \Function Name: void  EOLvinCodeWrite(void)
 * Description: 发送 EOL下线标定VIN码写入
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLvinCodeWrite(void){
     byte sendflag;
     if(runstep==vinCodeWrite) {     
       sendMessage.u16ID=0X753;    //安全访问发送种子
       sendMessage.u8Prio=0;
       sendMessage.u8Length=8;      //0X753 03 2E F1 90 00 00 00 00
       sendData[0]=0x03;
       sendData[1]=0X2E;
       sendData[2]=0xF1;
       sendData[3]=0x90;
       sendData[4]=0x00;
       sendData[5]=0x00;
       sendData[6]=0x00;
       sendData[7]=0x00;
       sendMessage.u8TxData=sendData;
       sendflag=CAN_Send_Frame(sendMessage);  //can发送
       sendNum++;                            //发送计数
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLvinCodeRead(void)
 * Description: 发送 EOL下线标定VIN码读取
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLvinCodeRead(void){
     byte sendflag;
     if(runstep==vinCodeRead) {     
       sendMessage.u16ID=0X753;    //安全访问发送种子
       sendMessage.u8Prio=0;
       sendMessage.u8Length=8;      //0X753 03 22 F1 90 00 00 00 00
       sendData[0]=0x03;
       sendData[1]=0X22;
       sendData[2]=0xF1;
       sendData[3]=0x90;
       sendData[4]=0x00;
       sendData[5]=0x00;
       sendData[6]=0x00;
       sendData[7]=0x00;
       sendMessage.u8TxData=sendData;
       sendflag=CAN_Send_Frame(sendMessage);  //can发送
       sendNum++;                            //发送计数
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLcarConfigWrite(void)
 * Description: 发送 EOL下线标定车辆配置信息写入
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLcarConfigWrite(void){
     byte sendflag;
     if(runstep==carConfigWrite) {     
       sendMessage.u16ID=0X753;    //安全访问发送种子
       sendMessage.u8Prio=0;
       sendMessage.u8Length=8;      //0X753 03 22 F1 90 00 00 00 00
       sendData[0]=0x03;
       sendData[1]=0X2E;
       sendData[2]=0xF1;
       sendData[3]=0xA1;
       sendData[4]=0x00;
       sendData[5]=0x00;
       sendData[6]=0x00;
       sendData[7]=0x00;
       sendMessage.u8TxData=sendData;
       sendflag=CAN_Send_Frame(sendMessage);  //can发送
       sendNum++;                            //发送计数
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLcarConfigRead(void)
 * Description: 发送 EOL下线标定车辆配置信息读取
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLcarConfigRead(void){
     byte sendflag;
     if(runstep==carConfigRead) {     
       sendMessage.u16ID=0X753;    //安全访问发送种子
       sendMessage.u8Prio=0;
       sendMessage.u8Length=8;      //0X753 03 22 F1 A1 00 00 00 00
       sendData[0]=0x03;
       sendData[1]=0X22;
       sendData[2]=0xF1;
       sendData[3]=0xA1;
       sendData[4]=0x00;
       sendData[5]=0x00;
       sendData[6]=0x00;
       sendData[7]=0x00;
       sendMessage.u8TxData=sendData;
       sendflag=CAN_Send_Frame(sendMessage);  //can发送
       sendNum++;                            //发送计数
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLremoveMidCalibration(void)
 * Description: 发送 EOL下线标定解标中位标定
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLremoveMidCalibration(void){
     byte sendflag;
     if(runstep==removeMidCalibration) {     
       sendMessage.u16ID=0X753;    //安全访问发送种子
       sendMessage.u8Prio=0;
       sendMessage.u8Length=8;      //0X753 04 31 01 8B C0 00 00 00
       sendData[0]=0x04;
       sendData[1]=0X31;
       sendData[2]=0x01;
       sendData[3]=0x8B;
       sendData[4]=0xC0;
       sendData[5]=0x00;
       sendData[6]=0x00;
       sendData[7]=0x00;
       sendMessage.u8TxData=sendData;
       sendflag=CAN_Send_Frame(sendMessage);  //can发送
       sendNum++;                            //发送计数
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}

/******************************************************************************/
/**
  \Function Name: void  EOLmidCalibrationStepFirst(void)
 * Description: 发送 EOL下线标定转角中位标定步骤一
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLmidCalibrationStepFirst(void){
     byte sendflag;
     if(runstep==midCalibration && midCalibrationStep == midCalibrationStep1) {     
       sendMessage.u16ID=0X753;    //安全访问发送种子
       sendMessage.u8Prio=0;
       sendMessage.u8Length=8;      //0X753 04 31 01 8B C0 00 00 00
       sendData[0]=0x04;
       sendData[1]=0X31;
       sendData[2]=0x01;
       sendData[3]=0x8B;
       sendData[4]=0xC1;
       sendData[5]=0x00;
       sendData[6]=0x00;
       sendData[7]=0x00;
       sendMessage.u8TxData=sendData;
       sendflag=CAN_Send_Frame(sendMessage);  //can发送
       sendNum++;                            //发送计数
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLmidCalibrationStepSecond(void)
 * Description: 发送 EOL下线标定转角中位标定步骤二
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLmidCalibrationStepSecond(void){
     byte sendflag;
     if(runstep==midCalibration && midCalibrationStep == midCalibrationStep2) {     
       sendMessage.u16ID=0X753;    //安全访问发送种子
       sendMessage.u8Prio=0;
       sendMessage.u8Length=8;      //0X753 04 31 01 8B C0 00 00 00
       sendData[0]=0x04;
       sendData[1]=0X31;
       sendData[2]=0x03;
       sendData[3]=0x8B;
       sendData[4]=0xC1;
       sendData[5]=0x00;
       sendData[6]=0x00;
       sendData[7]=0x00;
       sendMessage.u8TxData=sendData;
       sendflag=CAN_Send_Frame(sendMessage);  //can发送
       sendNum++;                            //发送计数
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLclearSSMCode(void)
 * Description: 发送 EOL下线标定清除SSM故障码
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLclearSSMCode(void){
     byte sendflag;
     if(runstep==clearSSMCode) {     
       sendMessage.u16ID=0X753;    //安全访问发送种子
       sendMessage.u8Prio=0;
       sendMessage.u8Length=8;      //0X753 04 14 FF FF FF 00 00 00
       sendData[0]=0x04;
       sendData[1]=0X14;
       sendData[2]=0xFF;
       sendData[3]=0xFF;
       sendData[4]=0xFF;
       sendData[5]=0x00;
       sendData[6]=0x00;
       sendData[7]=0x00;
       sendMessage.u8TxData=sendData;
       sendflag=CAN_Send_Frame(sendMessage);  //can发送
       sendNum++;                            //发送计数
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}

/******************************************************************************/
/**
  \Function Name: void  EOLreadSSMCode(void)
 * Description: 发送 EOL下线标定读取SSM故障码
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLreadSSMCode(void){
     byte sendflag;
     if(runstep==readSSMCode) {     
       sendMessage.u16ID=0X753;    //安全访问发送种子
       sendMessage.u8Prio=0;
       sendMessage.u8Length=8;      //0X753 03 19 02 09 00 00 00 00
       sendData[0]=0x03;
       sendData[1]=0X19;
       sendData[2]=0x02;
       sendData[3]=0x09;
       sendData[4]=0x00;
       sendData[5]=0x00;
       sendData[6]=0x00;
       sendData[7]=0x00;
       sendMessage.u8TxData=sendData;
       sendflag=CAN_Send_Frame(sendMessage);  //can发送
       sendNum++;                            //发送计数
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//连续10次发送都没成功则不发送，cansendflag=ERROR ,用于点亮CAN错误指示灯
     }
}








 



