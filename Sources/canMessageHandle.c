 #include "derivative.h"      /* derivative-specific definitions */
 #include "canMessageHandle.h"
 #include "calibration.h"
 

 
 //******************��ͬ�汾�Ŀ��ؽ��ձ��ı�׼����*************************//
 
 uchar  connectLinkMes[8] = {0x06,0x50,0x03,0x00,0x32,0x00,0xC8,0x00};   //   ����������Ӧ��׼����
 uchar  requestSeedMes[3] = {0x06,0x67,0x01};                            //   ����������Ӧ��׼����ǰ��λ
 uchar  sendSecretKeyMes[8] = {0x02,0x67,0x02,0x00,0x00,0x00,0x00,0x00};  //   ������Կ��Ӧ��׼����
 
 uchar  detectionDeviceNo1Mes[8] = {0x10,0x10,0x62,0xF1,0X87,0X50,0X30,0X33};//  ���Ӳ�����ƺŵ�һ֡��׼����
 uchar  detectionDeviceNo2Mes[8] = {0x21,0x37,0x33,0x30,0x30,0x30,0X30,0X30};//  ���Ӳ�����ƺŵڶ�֡��׼����
 uchar  detectionDeviceNo3Mes[8] = {0x22,0x30,0x31,0x33,0x00,0X00,0X00,0X00};//  ���Ӳ�����ƺŵ���֡��׼����
 
 uchar  batchNo1Mes[8] = {0x10,0x0B,0X62,0XF1,0X8C,0X00,0X00,0X00};          //�����κ���Ӧ��һ֡��׼����
 uchar  batchNo2Mes[8] = {0x21,0x00,0X00,0X00,0X00,0X00,0X00,0X00};          //�����κ���Ӧ�ڶ�֡��׼����
 
 uchar  hardWareNo1Mes[8] = {0x10,0x14,0X62,0XF1,0X91,0X48,0X57,0X2E};       //����Ӧ��Ӳ���汾����Ӧ��һ֡��׼����
 uchar  hardWareNo2Mes[8] = {0x21,0x56,0X2E,0X31,0X2E,0X30,0X2E,0X30};       //����Ӧ��Ӳ���汾����Ӧ��һ֡��׼����
 uchar  hardWareNo3Mes[8] = {0x22,0x2E,0X32,0X32,0X30,0X35,0X30,0X36};       //����Ӧ��Ӳ���汾����Ӧ��һ֡��׼����
 
 uchar  softWareNo1Mes[8] ={0x10,0x14,0X62,0XF1,0X89,0X53,0X57,0X2E};        //����Ӧ������汾����Ӧ��һ֡��׼����
 uchar  softWareNo2Mes[8] ={0x21,0x56,0X2E,0X31,0X2E,0X30,0X2E,0X30};        //����Ӧ������汾����Ӧ�ڶ�֡��׼����
 uchar  softWareNo3Mes[8] ={0x22,0x2E,0X32,0X32,0X30,0X37,0X30,0X36};        //����Ӧ������汾����Ӧ����֡��׼����
 
 uchar  clearInCalibrationMes[8] = {0x05,0x71,0X01,0XFB,0X11,0X00,0X00,0X00};  //����ڲ��궨��Ӧ��׼����
 
 uchar  startInCalibrationMes[8] = {0x05,0x71,0X01,0XFB,0X10,0X00,0X00,0X00};   //�ڲ��궨��ʼ 71 01 FB 10 XX   XX : 00 (δ�궨) XX : 01 (�ѱ궨)
 
 
 uchar startCalibrationStepMes[6] = {0x10,0x08,0x71,0X01,0XFB,0X12};            //��ʼ�궨ÿһ����������

 
 uchar  endOutCalibrationMes1[8] = {0x05,0x71,0X02,0XFB,0X12,0X00,0X00,0X00};  //�ڲ��ѱ궨
 uchar  endOutCalibrationMes2[8] = {0x05,0x71,0X02,0XFB,0X12,0X01,0X00,0X00};  //�ڲ�δ�궨
 uchar  endOutCalibrationMes3[4] = {0x03,0x7F,0x31,0x78};                      //�ڲ��궨δ���
 
 
 uchar  resetMes[8] ={0x02,0x51,0X01,0X00,0X00,0X00,0X00,0X00};                //��λ
 
 uchar  readCalibrationStateMes[5] = {0x10,0x12,0x62,0xFB,0x21};  //�ڲ��Ѿ��궨״̬
 
//============================���߱궨=============================================
 uchar  eolExtendMes[8] = {0x06,0x50,0x03,0x00,0x32,0x00,0xC8,0x00};   //   ������չģʽ 
 
 uchar  eolReadPartNumMes1[8] = {0x10,0x10,0x62,0xF1,0X87,0X50,0X30,0X33};      //  EOL��ȡ��������ŵ�һ֡��׼����
 uchar  eolReadPartNumMes2[8] = {0x21,0x37,0x33,0x30,0x30,0x30,0X30,0X30};      //  EOL��ȡ��������ŵڶ�֡��׼����
 uchar  eolReadPartNumMes3[8] = {0x22,0x30,0x31,0x33,0x00,0X00,0X00,0X00};      //  EOL��ȡ��������ŵ���֡��׼����
 
 uchar  eolhardWareNo1Mes[8] = {0x10,0x14,0X62,0XF1,0X91,0X48,0X57,0X2E};       //EOL ����Ӧ��Ӳ���汾����Ӧ��һ֡��׼����
 uchar  eolhardWareNo2Mes[8] = {0x21,0x56,0X2E,0X31,0X2E,0X30,0X2E,0X30};       //EOL ����Ӧ��Ӳ���汾����Ӧ��һ֡��׼����
 uchar  eolhardWareNo3Mes[8] = {0x22,0x2E,0X32,0X32,0X30,0X35,0X30,0X36};       //EOL ����Ӧ��Ӳ���汾����Ӧ��һ֡��׼����
 
 uchar  eolsoftWareNo1Mes[8] ={0x10,0x14,0X62,0XF1,0X89,0X53,0X57,0X2E};        //EOL ����Ӧ������汾����Ӧ��һ֡��׼����
 uchar  eolsoftWareNo2Mes[8] ={0x21,0x56,0X2E,0X31,0X2E,0X30,0X2E,0X30};        //EOL ����Ӧ������汾����Ӧ�ڶ�֡��׼����
 uchar  eolsoftWareNo3Mes[8] ={0x22,0x2E,0X32,0X32,0X30,0X37,0X30,0X36};        //EOL ����Ӧ������汾����Ӧ����֡��׼����
 
 uchar  safeAccessSendSeedMes[3] = {0x06,0x67,0x01};                             //   EOL��ȫ��������������Ӧ��׼����ǰ��λ
 uchar  safeAccessSendSecretMes[8] = {0x02,0x67,0x02,0x00,0x00,0x00,0x00,0x00};  //  EOL��ȫ���� ������Կ��Ӧ��׼����
 
 uchar  vinCodeWriteMes[8] = {0x03,0x6E,0xF1,0x90,0x00,0x00,0x00,0x00};          //  EOL VIN��д����Ӧ��׼����
 
 uchar  vinCodeReadMes1[8] = {0x10,0x14,0x62,0xF1,0x90,0xC6,0xF0,0x50};          //  EOL VIN���ȡ��Ӧ��һ֡��׼����
 uchar  vinCodeReadMes2[8] = {0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00};          //  EOL VIN���ȡ��Ӧ�ڶ�֡��׼����
 uchar  vinCodeReadMes3[8] = {0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00};          //  EOL VIN���ȡ��Ӧ����֡��׼����
 
 uchar  carConfigWriteMes[8] = {0x03,0x6E,0xF1,0xA1,0x00,0x00,0x00,0x00};          //  EOL ����������Ϣд����Ӧ��׼����
 
 uchar  carConfigReadMes[8] = {0x03,0x62,0xF1,0xA1,0x00,0x00,0x00,0x00};          //  EOL ����������Ϣ��ȡ��Ӧ��׼����
 
 uchar  removeMidCalibrationMes[8] = {0x05,0x71,0x01,0x8B,0xC0,0x00,0x00,0x00};    //  EOL �����λ�궨��Ӧ��׼����
 
 uchar  midCalibrationStep1Mes[8] = {0x05,0x71,0x01,0x8B,0xC1,0x00,0x00,0x00};    //  EOL ת����λ�궨����1��Ӧ��׼����
 uchar  midCalibrationStep2Mes[8] = {0x05,0x71,0x01,0x8B,0xC1,0x00,0x00,0x00};    //  EOL ת����λ�궨����2��Ӧ��׼����
 
 uchar  clearSSMCodeMes[8] = {0x01,0x54,0x00,0x00,0x00,0x00,0x00,0x00};           //  EOL ���SSM��������Ӧ��׼����
 
 //********************************************//
 
 uchar runstep=0;          //���嵱ǰ����
 uchar safeAccessStep=0;      //���߱궨��ȫ���ʲ���(�������ӣ�������Կ)
 uchar midCalibrationStep;    //���߱궨ת����λ�궨(ת����λ�궨����1 ת����λ�궨����2)
 uint sendNum;            //���巢�ʹ���
 unsigned long int seed;  //�������ӱ���
 unsigned long int encryptedMiyao;    //�㷨����֮��õ�����Կ
 mscan_msg_t sendMessage;  //������Ϣ
 uchar sendData[8];        //������Ϣ����
 uchar canSendState;       //���Է��ͱ�־λ
 
 uchar unCalibrationNum;   //δ�궨������־λ ����3�κ󱨴�
 
 uchar calibrationStepResState;  //ÿһ���궨���  1���ɹ���Ӧ 0��δ�ɹ���Ӧ
 
 uchar  calibrationStatus = SUCCESS;           //�궨״̬��־λ
 
 
 
 
 
 
 /******************************************************************************/
/**
  Function Name: void  compateArray(void)
 * Description: ���ձ�������ͱ�׼���ݱȶ�
 * Param:    recevieMes ���ձ������� standardMes ��׼ֵ����  num ��Ҫ�ȶԵĸ���
 * Return:  1 �ȶԳɹ�  0 �ȶ�ʧ�� 
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
 * Description: canЭ���������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/

uint resSuccessNum;
void CANMESSAGEHADLE(void) {
 
   if(canreceiveflag==1){ 
       
     
       /*******step1���ͽ���XXX���Ӻ��յ���ȷ��ָ������������������*******/
       
       if(compareArray(RxMsg.Data,connectLinkMes,8) && runstep==connectLink) {
          
          runstep=requestSeed;  
       }
       
       /*******step2�����������Ӻ��յ���ȷ��ָ�����뷢����Կ����*******/
       if(compareArray(RxMsg.Data,requestSeedMes,3) && runstep==requestSeed) {
          seed=RxMsg.Data[3]; 
          seed=(seed<<8)+RxMsg.Data[4];
          seed=(seed<<8)+RxMsg.Data[5];
          seed=(seed<<8)+RxMsg.Data[6];
          runstep=sendSecretKey;
          
       }
       /*******step3������Կ���յ���ȷ��ָ���������������������*******/
       if(compareArray(RxMsg.Data,sendSecretKeyMes,8)&&runstep==sendSecretKey){
          
          runstep=detectionDeviceNo;      
       }
       
       /*******step4���ͼ���������ƺź��յ���ȷ��ָ����������κ�����*******/
       if((runstep==detectionDeviceNo) &&  compareArray(canSASRXbuff[0],detectionDeviceNo1Mes,8) && compareArray(canSASRXbuff[1],detectionDeviceNo2Mes,8) && compareArray(canSASRXbuff[2],detectionDeviceNo3Mes,8)){
         
          runstep=readBatchNo;
       }
       
       /*******step5���Ͷ����κź��յ���ȷ��ָ���������Ӧ��Ӳ���汾������*******/
       if((runstep==readBatchNo) && compareArray(canSASRXbuff[0],batchNo1Mes,8) && compareArray(canSASRXbuff[1],batchNo2Mes,8) ){
         
          runstep=readHardWareNo;
       }
       
       /*******step6���Ͷ�ȡӲ���汾�ź��յ���ȷ��ָ���������Ӧ������汾������*******/
       if((runstep==readHardWareNo) && compareArray(canSASRXbuff[0],hardWareNo1Mes,8) && compareArray(canSASRXbuff[1],hardWareNo2Mes,8) && compareArray(canSASRXbuff[2],hardWareNo3Mes,8) ){
          
          runstep=readSoftWareNo; 
       }
       /*******step7���Ͷ�ȡ����汾�ź��յ���ȷ��ָ����������ڲ��궨����*******/
       if((runstep==readSoftWareNo) && compareArray(canSASRXbuff[0],softWareNo1Mes,8) && compareArray(canSASRXbuff[1],softWareNo2Mes,8) && compareArray(canSASRXbuff[2],softWareNo3Mes,8)){
          
          runstep=clearInCalibration; 
       }
       
       /*******step8��������ڲ��궨������յ���ȷ��ָ�������ڲ��궨��ʼ����*******/
       if(compareArray(RxMsg.Data,clearInCalibrationMes,8)  && (runstep==clearInCalibration)){
       
          runstep=startInCalibration; 
       }
       
       /*******step9���Ϳ�ʼ�ڲ��궨������յ���ȷ��ָ�������ⲿ����궨��ת��ʼ����*******/
       if(compareArray(RxMsg.Data,startInCalibrationMes,8)  && (runstep==startInCalibration)){
          
             runstep=startForWardOutCalibration;
             wantTurnAngle=MOTORCONTROL8;
             wantTurnDir=FORWARD;
             turnFlag = 1;
       }
       
       //TODO �������Ӧ���ĳɹ�֮�����ִ����һ��1.8��ı궨��������־λ�жϣ�
       if(compareArray(canSASRXbuff[0],startCalibrationStepMes,6) && (runstep == startReverseOutCalibration || runstep == startForWardOutCalibration)){
             calibrationStepResState = 1; 
             resSuccessNum++;
       }
       
      
       
       /*******step10���ͽ����ڲ��궨�����(��ת)���յ���ȷ��ָ�������ⲿ�����ת��ʼ����******
       if(compareArray(RxMsg.Data,endOutCalibrationMes1,8)  && (runstep==startReverseOutCalibration)){
       
          runstep=startReverseOutCalibration;
          wantTurnAngle=MOTORCONTROL8;
          wantTurnDir=REVERSE; 
       }
       **/
       
        /*******step11���ͽ����ڲ��궨�����(��ת)���յ���ȷ��ָ�����븴λ����******/
       if(compareArray(RxMsg.Data,endOutCalibrationMes1,8)  && (runstep==endOutCalibration)){
          runstep=reset; 
       }
       
       /**
       if(compareArray(RxMsg.Data,endOutCalibrationMes1,8) ==0  && (runstep==endOutCalibration)){
           programERROR= 1;
       }
       **/
       
       /*******step12���͸�λ������յ���ȷ��ָ�������ȡ�궨״̬����******/
       if(compareArray(RxMsg.Data,resetMes,8)  && (runstep==reset)){
          runstep=readCalibrationState; 
       } 
       
       /*******step13���Ͷ�ȡ�궨״̬������յ���ȷ��ָ����ݱ궨���ִ�н������Ĳ���******/
       if(compareArray(canSASRXbuff[0],readCalibrationStateMes,5)  && runstep==readCalibrationState){
          
          //���δ�궨������ִ�б궨���̣�����3�κ󱨴�
          if((canSASRXbuff[0][5] & 0x01)==0){
             unCalibrationNum++;
             if(unCalibrationNum == 3){
                 //TODO ����������
                 calibrationStatus = ERROR;
             }
             
             runstep=connectLink; 
          }else{
             //ִ�гɹ����е����߱궨��һ��
             runstep=eolExtend;
          }
          
       } 
       
       //====================�������߱궨����================================//
       
       /*******step4���ͽ�����չ������յ���ȷ��ָ�������ȡ�������������*******/
       if(compareArray(RxMsg.Data,eolExtendMes,8) && runstep==eolExtend) {
          runstep=eolReadPartNum;  
       }
       
       /*******step4��ȡ�������������յ���ȷ��ָ�������ȡ��Ӧ��Ӳ���汾����*******/
       if((runstep==eolReadPartNum) && compareArray(canSASRXbuff[0],eolReadPartNumMes1,8) && compareArray(canSASRXbuff[1],eolReadPartNumMes2,8) && compareArray(canSASRXbuff[2],eolReadPartNumMes3,8)){
         
          runstep=eolReadHardWareNo;
       }
       
       /*******step4��ȡ��Ӧ��Ӳ���汾����յ���ȷ��ָ�������ȡ��Ӧ������汾����*******/
       if((runstep==eolReadHardWareNo) && compareArray(canSASRXbuff[0],eolhardWareNo1Mes,8) && compareArray(canSASRXbuff[1],eolhardWareNo2Mes,8) && compareArray(canSASRXbuff[2],eolhardWareNo3Mes,8)){
         
          runstep=eolReadSoftWareNo;
       }
       
       /*******step4��ȡ��Ӧ������汾����յ���ȷ��ָ�����밲ȫ���ʷ���������������*******/
       if(compareArray(canSASRXbuff[0],eolsoftWareNo1Mes,8) && compareArray(canSASRXbuff[1],eolsoftWareNo2Mes,8) && compareArray(canSASRXbuff[2],eolsoftWareNo3Mes,8) &&  (runstep==eolReadSoftWareNo)){
         
          runstep=safeAccess;
          safeAccessStep = safeAccessSendSeed;
       }
       
       /*******step2�����������Ӻ��յ���ȷ��ָ�����뷢����Կ����*******/
       if(compareArray(RxMsg.Data,safeAccessSendSeedMes,3) && runstep==safeAccess && safeAccessStep == safeAccessSendSeed) {
          seed=RxMsg.Data[3]; 
          seed=(seed<<8)+RxMsg.Data[4];
          seed=(seed<<8)+RxMsg.Data[5];
          seed=(seed<<8)+RxMsg.Data[6];
          runstep=safeAccess; 
          safeAccessStep = safeAccessSendSecret;
       }
       /*******step3������Կ���յ���ȷ��ָ������vin��д������*******/
       if(compareArray(RxMsg.Data,safeAccessSendSecretMes,8) && runstep==safeAccess && safeAccessStep == safeAccessSendSecret){
      
          runstep=vinCodeWrite;      
       }
       
       /*******step3����vin��д������յ���ȷ��ָ������vin���ȡ����*******/
       if(compareArray(RxMsg.Data,vinCodeWriteMes,8) && runstep==vinCodeWrite){
      
          runstep=vinCodeRead;      
       }
       
       
       /*******step3vin���ȡ������յ���ȷ��ָ�����복��������Ϣд������*******/
       if((runstep==vinCodeRead) && compareArray(canSASRXbuff[0],vinCodeReadMes1,8) && compareArray(canSASRXbuff[1],vinCodeReadMes2,8) && compareArray(canSASRXbuff[2],vinCodeReadMes3,8)){
         
          runstep=carConfigWrite;
       }
       
       /*******step3���ͳ���������Ϣд������յ���ȷ��ָ�����복��������Ϣ��ȡ����*******/
       if(compareArray(RxMsg.Data,carConfigWriteMes,8) && runstep==carConfigWrite){
      
          runstep=carConfigRead;      
       }
       
       
       /*******step3���ͳ���������Ϣ��ȡ����յ���ȷ��ָ����������λ�궨����*******/
       if(compareArray(RxMsg.Data,carConfigReadMes,8) && runstep==carConfigRead){
      
          runstep=removeMidCalibration;      
       }
       
       /*******step3���ͽ����λ�궨��������յ���ȷ��ָ������ת����λ�궨(����һ)����*******/
       if(compareArray(RxMsg.Data,removeMidCalibrationMes,8) && runstep==removeMidCalibration){
      
          runstep=midCalibration;
          midCalibrationStep = midCalibrationStep1;      
       }
       
       /*******step3����ת����λ�궨(����һ)����յ���ȷ��ָ������ת����λ�궨(�����)����*******/
       if(compareArray(RxMsg.Data,midCalibrationStep1Mes,8) && runstep==midCalibration && midCalibrationStep == midCalibrationStep1){
      
          runstep=midCalibration;
          midCalibrationStep = midCalibrationStep2;      
       }
       
       /*******step3����ת����λ�궨(�����)����յ���ȷ��ָ���������SSM����������*******/
       if(compareArray(RxMsg.Data,midCalibrationStep2Mes,8) && runstep==midCalibration && midCalibrationStep == midCalibrationStep2){
      
          runstep=clearSSMCode;
       }
       
       /*******step3�������SSM��������������յ���ȷ��ָ�������ȡSSM����������*******/
       if(compareArray(RxMsg.Data,clearSSMCodeMes,8) && runstep==clearSSMCode){
      
          //runstep=readSSMCode;
          runstep = sasCalibration;  //ʦ����ʱû�������һ��������������ģ�⵽��sas�궨�Ĳ���
          wantTurnDir = FORWARD;
          wantTurnAngle = MOTORCONTROL30;
          turnFlag=1;
       }
       
       
       
       
       
       
       
       
       //�������Can���ı�־λ��0,��ʾ���Խ����±�����
       canreceiveflag=0; 
       
       
       
   }
  
}



/******************************************************************************/
/**
  Function Name: void  connectLink(void)
 * Description: ��������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
 void ConnectLink(void) {
      byte sendflag;
      if(runstep==connectLink) {
          sendMessage.u16ID=0X753;    //���ͽ�����������
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
          sendNum++;                            //���ͼ���
          if(sendNum>canRetryNum) {
          sendNum=0;       //���ճɹ�����can�ж��н�����һ��
          canSendState=ERROR;
          }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
      }                          
 }
 
 
/******************************************************************************/
/**
  \Function Name: void  sendseed(void)
 * Description: ����������������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
 void SendSeed(void) {
     byte sendflag;
     if(runstep==requestSeed) {
       sendMessage.u16ID=0X753;    //��������
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
       sendflag=CAN_Send_Frame(sendMessage);  //can����
       sendNum++;                            //���ͼ���
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
    
     } 
 }
 
 
 /******************************************************************************/
/**
  \Function Name: void  encryptTokey(void)
 * Description: �����㷨
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
 * Description: ���� ��Կ����
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void SendSecret(void) {
     byte sendflag; 
     if(runstep==sendSecretKey) {   
        encryptedMiyao = encryptTokey(seed);
        sendMessage.u16ID=0X753;    //������Կ
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
        sendflag=CAN_Send_Frame(sendMessage);  //can����
        sendNum++;                            //���ͼ���
        if(sendNum>canRetryNum){
          canSendState=ERROR;
          sendNum=0;
        }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
    }  
}



/******************************************************************************/
/**
  \Function Name: void  DetectionDeviceNo(void)
 * Description: ���� ����������ƺ�
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void DetectionDeviceNo(void){
     byte sendflag; 
     if(runstep==detectionDeviceNo) {    
        sendMessage.u16ID=0X753;    //����������ƺ�
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
        sendflag=CAN_Send_Frame(sendMessage);  //can����
        sendNum++;                            //���ͼ���
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
        }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}

/******************************************************************************/
/**
  \Function Name: void  ReadBatchNo(void)
 * Description: ���� ��ȡ���κ�
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void ReadBatchNo(void){
     byte sendflag;
     if(runstep==readBatchNo) {    
         sendMessage.u16ID=0X753;    //��ȡ���κ�
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
         sendflag=CAN_Send_Frame(sendMessage);  //can����
         sendNum++;                            //���ͼ���
         if(sendNum>canRetryNum){
            canSendState=ERROR;
            sendNum=0;
         }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  ReadSupplierName(void)
 * Description: ���� ��ȡ��Ӧ������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
/**void ReadSupplierName(void){
     byte sendflag;    
     sendMessage.u16ID=0X753;    //��ȡ��Ӧ������
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
     sendflag=CAN_Send_Frame(sendMessage);  //can����
     sendNum++;                            //���ͼ���
     if(sendNum>10){
        canSendState=ERROR;
        sendNum=0;
     }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
}
**/


/******************************************************************************/
/**
  \Function Name: void  ReadHardWareNo(void)
 * Description: ���� ��ȡӲ���汾������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void ReadHardWareNo(void){
     byte sendflag; 
     if(runstep==readHardWareNo) {    
         sendMessage.u16ID=0X753;    //��ȡӲ���汾��
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
         sendflag=CAN_Send_Frame(sendMessage);  //can����
         sendNum++;                            //���ͼ���
         if(sendNum>canRetryNum){
            canSendState=ERROR;
            sendNum=0;
         }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  ReadSoftWareNo(void)
 * Description: ���� ��ȡ����汾������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void ReadSoftWareNo(void){
     byte sendflag;
     if(runstep==readSoftWareNo) {     
        sendMessage.u16ID=0X753;    //��ȡ����汾��
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
        sendflag=CAN_Send_Frame(sendMessage);  //can����
        sendNum++;                            //���ͼ���
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
         }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}



/******************************************************************************/
/**
  \Function Name: void  ClearInCalibration(void)
 * Description: ���� ����ڲ��궨����
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void ClearInCalibration(void){
     byte sendflag;    
     if(runstep==clearInCalibration) {   
         sendMessage.u16ID=0X753;    //����ڲ��궨����
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
         sendflag=CAN_Send_Frame(sendMessage);  //can����
         sendNum++;                            //���ͼ���
         if(sendNum>canRetryNum){
            canSendState=ERROR;
            sendNum=0;
         }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}



/******************************************************************************/
/**
  \Function Name: void  StartInCalibration(void)
 * Description: ���� �ڲ��궨��ʼ����
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void StartInCalibration(void){
     byte sendflag;
     if(runstep==startInCalibration) {    
         sendMessage.u16ID=0X753;    //����ڲ��궨����
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
         sendflag=CAN_Send_Frame(sendMessage);  //can����
         sendNum++;                            //���ͼ���
         if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
         }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  StartOutCalibration(void)
 * Description: ���� �ⲿ����궨��ʼ����
 * Param:   direction  ����  1�������ת  0:�����ת
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void StartOutCalibration(uchar direction){
     byte sendflag;
     if(runstep==startForWardOutCalibration || runstep==startReverseOutCalibration) {     
          sendMessage.u16ID=0X753;    //����ڲ��궨����
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
          sendflag=CAN_Send_Frame(sendMessage);  //can����
          //sendNum++;                            //���ͼ���
          //if(sendNum>canRetryNum){
            //canSendState=ERROR;
           // sendNum=0;
          //}//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  StopOutCalibration(void)
 * Description: ���� �ⲿ����궨ֹͣ����
 * Param:   direction  ����  1�������ת  0:�����ת
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void StopOutCalibration(uchar direction){
     byte sendflag;    
     if(runstep==endOutCalibration) {  
         sendMessage.u16ID=0X753;    //����ڲ��궨����
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
         sendflag=CAN_Send_Frame(sendMessage);  //can����
         sendNum++;                            //���ͼ���
         if(sendNum>canRetryNum){
            canSendState=ERROR;
            sendNum=0;
         }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
         
     }
} 

/******************************************************************************/
/**
  \Function Name: void  Reset(void)
 * Description: ���� ��λ����
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void Reset(void){
     if(runstep==reset){
        byte sendflag;    
        sendMessage.u16ID=0X753;    //���͸�λ����
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
        sendflag=CAN_Send_Frame(sendMessage);  //can����
        sendNum++;                            //���ͼ���
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
        }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
  }

}



/******************************************************************************/
/**
  \Function Name: void  ReadCalibrationState(void)
 * Description: ���� ��ȡ�궨״̬����
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void ReadCalibrationState(void){
   if(runstep==readCalibrationState){
     byte sendflag;    
     sendMessage.u16ID=0X753;    //���͸�λ����
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
     sendflag=CAN_Send_Frame(sendMessage);  //can����
     sendNum++;                            //���ͼ���
     if(sendNum>canRetryNum){
        canSendState=ERROR;
        sendNum=0;
     }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
    }
}


/******************************************************************************/
/**
  Function Name: void  connectLink(void)
 * Description: ���ÿת1.8�㷢��һ֡��������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
 void SendFrameByStepTurn(uchar direction) {
      byte sendflag;
      if(runstep==startForWardOutCalibration) {
          sendMessage.u16ID=0X753;    //���ͽ�����������
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
          sendNum++;                            //���ͼ���
          if(sendNum>canRetryNum) {
          sendNum=0;       //���ճɹ�����can�ж��н�����һ��
          canSendState=ERROR;
          }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
      }                          
 }
 
 
 /******************************************************************************/
/**
  \Function Name: void  Reset(void)
 * Description: ���� ��λ����
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void Send3EService(void){
    if(runstep==reset) {
        byte sendflag;    
        sendMessage.u16ID=0X753;    //���͸�λ����
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
        sendflag=CAN_Send_Frame(sendMessage);  //can����
        sendNum++;                            //���ͼ���
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
        }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
   }

}


/******************************************************************************/
/**
  \Function Name: void  EOLExtend(void)
 * Description: EOL ������չģʽ
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLExtend(void){
    if(runstep==eolExtend) {
        byte sendflag;    
        sendMessage.u16ID=0X753;    //���ͽ�����չģʽ����
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
        sendflag=CAN_Send_Frame(sendMessage);  //can����
        sendNum++;                            //���ͼ���
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
        }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
   }

}

/******************************************************************************/
/**
  \Function Name: void  EOLReadPartNum(void)
 * Description: EOL ��ȡ���������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLReadPartNum(void){
     byte sendflag; 
     if(runstep==eolReadPartNum) {    
        sendMessage.u16ID=0X753;    //����������ƺ�
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
        sendflag=CAN_Send_Frame(sendMessage);  //can����
        sendNum++;                            //���ͼ���
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
        }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}



/******************************************************************************/
/**
  \Function Name: void  EOLReadHardWareNo(void)
 * Description: ���� EOL��ȡӲ���汾������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLReadHardWareNo(void){
     byte sendflag; 
     if(runstep==eolReadHardWareNo) {    
         sendMessage.u16ID=0X753;    //��ȡӲ���汾��
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
         sendflag=CAN_Send_Frame(sendMessage);  //can����
         sendNum++;                            //���ͼ���
         if(sendNum>canRetryNum){
            canSendState=ERROR;
            sendNum=0;
         }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLReadSoftWareNo(void)
 * Description: ���� EOL��ȡ����汾������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLReadSoftWareNo(void){
     byte sendflag;
     if(runstep==eolReadSoftWareNo) {     
        sendMessage.u16ID=0X753;    //��ȡ����汾��
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
        sendflag=CAN_Send_Frame(sendMessage);  //can����
        sendNum++;                            //���ͼ���
        if(sendNum>canRetryNum){
           canSendState=ERROR;
           sendNum=0;
         }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLsafeAccessSendSeed(void)
 * Description: ���� EOL���߱궨��ȫ���ʷ�������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLsafeAccessSendSeed(void){
     byte sendflag;
     if(runstep==safeAccess && safeAccessStep == safeAccessSendSeed) {     
       sendMessage.u16ID=0X753;    //��ȫ���ʷ�������
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
       sendflag=CAN_Send_Frame(sendMessage);  //can����
       sendNum++;                            //���ͼ���
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLsafeAccessSendSecret(void)
 * Description: ���� EOL���߱궨��ȫ���ʷ�����Կ
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLsafeAccessSendSecret(void) {
     byte sendflag; 
     if(runstep==safeAccess && safeAccessStep == safeAccessSendSecret) {   
        encryptedMiyao = encryptTokey(seed);
        sendMessage.u16ID=0X753;    //���߱궨��ȫ���ʷ�����Կ
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
        sendflag=CAN_Send_Frame(sendMessage);  //can����
        sendNum++;                            //���ͼ���
        if(sendNum>canRetryNum){
          canSendState=ERROR;
          sendNum=0;
        }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
    }  
}


/******************************************************************************/
/**
  \Function Name: void  EOLvinCodeWrite(void)
 * Description: ���� EOL���߱궨VIN��д��
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLvinCodeWrite(void){
     byte sendflag;
     if(runstep==vinCodeWrite) {     
       sendMessage.u16ID=0X753;    //��ȫ���ʷ�������
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
       sendflag=CAN_Send_Frame(sendMessage);  //can����
       sendNum++;                            //���ͼ���
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLvinCodeRead(void)
 * Description: ���� EOL���߱궨VIN���ȡ
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLvinCodeRead(void){
     byte sendflag;
     if(runstep==vinCodeRead) {     
       sendMessage.u16ID=0X753;    //��ȫ���ʷ�������
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
       sendflag=CAN_Send_Frame(sendMessage);  //can����
       sendNum++;                            //���ͼ���
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLcarConfigWrite(void)
 * Description: ���� EOL���߱궨����������Ϣд��
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLcarConfigWrite(void){
     byte sendflag;
     if(runstep==carConfigWrite) {     
       sendMessage.u16ID=0X753;    //��ȫ���ʷ�������
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
       sendflag=CAN_Send_Frame(sendMessage);  //can����
       sendNum++;                            //���ͼ���
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLcarConfigRead(void)
 * Description: ���� EOL���߱궨����������Ϣ��ȡ
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLcarConfigRead(void){
     byte sendflag;
     if(runstep==carConfigRead) {     
       sendMessage.u16ID=0X753;    //��ȫ���ʷ�������
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
       sendflag=CAN_Send_Frame(sendMessage);  //can����
       sendNum++;                            //���ͼ���
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLremoveMidCalibration(void)
 * Description: ���� EOL���߱궨�����λ�궨
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLremoveMidCalibration(void){
     byte sendflag;
     if(runstep==removeMidCalibration) {     
       sendMessage.u16ID=0X753;    //��ȫ���ʷ�������
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
       sendflag=CAN_Send_Frame(sendMessage);  //can����
       sendNum++;                            //���ͼ���
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}

/******************************************************************************/
/**
  \Function Name: void  EOLmidCalibrationStepFirst(void)
 * Description: ���� EOL���߱궨ת����λ�궨����һ
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLmidCalibrationStepFirst(void){
     byte sendflag;
     if(runstep==midCalibration && midCalibrationStep == midCalibrationStep1) {     
       sendMessage.u16ID=0X753;    //��ȫ���ʷ�������
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
       sendflag=CAN_Send_Frame(sendMessage);  //can����
       sendNum++;                            //���ͼ���
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLmidCalibrationStepSecond(void)
 * Description: ���� EOL���߱궨ת����λ�궨�����
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLmidCalibrationStepSecond(void){
     byte sendflag;
     if(runstep==midCalibration && midCalibrationStep == midCalibrationStep2) {     
       sendMessage.u16ID=0X753;    //��ȫ���ʷ�������
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
       sendflag=CAN_Send_Frame(sendMessage);  //can����
       sendNum++;                            //���ͼ���
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}


/******************************************************************************/
/**
  \Function Name: void  EOLclearSSMCode(void)
 * Description: ���� EOL���߱궨���SSM������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLclearSSMCode(void){
     byte sendflag;
     if(runstep==clearSSMCode) {     
       sendMessage.u16ID=0X753;    //��ȫ���ʷ�������
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
       sendflag=CAN_Send_Frame(sendMessage);  //can����
       sendNum++;                            //���ͼ���
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}

/******************************************************************************/
/**
  \Function Name: void  EOLreadSSMCode(void)
 * Description: ���� EOL���߱궨��ȡSSM������
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/ 
void EOLreadSSMCode(void){
     byte sendflag;
     if(runstep==readSSMCode) {     
       sendMessage.u16ID=0X753;    //��ȫ���ʷ�������
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
       sendflag=CAN_Send_Frame(sendMessage);  //can����
       sendNum++;                            //���ͼ���
       if(sendNum>canRetryNum) {
        
        canSendState=ERROR;
        sendNum=0;
       }//����10�η��Ͷ�û�ɹ��򲻷��ͣ�cansendflag=ERROR ,���ڵ���CAN����ָʾ��
     }
}








 



