#ifndef _CAN_MESSAGE_HANDLE_H
#define _CAN_MESSAGE_HANDLE_H
   
  
  
#include <hidef.h>
#include <mc9s12g48.h>  


//==============��ͬ�汾�ıȶ����ݺ궨��==================//



#define  connectLink 1                 //   ��������
#define  requestSeed  2                //   ��������
#define  sendSecretKey   3             //   ������Կ
#define  detectionDeviceNo 4           //   ����������ƺ�
#define  readBatchNo    5              //   �����κ�
#define  readHardWareNo 6              //   ��Ӳ���汾��
#define  readSoftWareNo 7              //   ������汾��
#define  clearInCalibration  8         //   ����ڲ��궨
#define  startInCalibration  9         //   �ڲ��궨��ʼ
#define  startForWardOutCalibration 10        //   �ⲿ����궨��ʼ(��ת)
//#define  endForWardOutCalibration 11        //     �ⲿ����궨����(��ת)

#define  startReverseOutCalibration 11        //   �ⲿ����궨��ʼ(��ת)
#define  endOutCalibration 12        //     �ⲿ����궨����(��ת)

#define  reset   13                         //��λ
#define  readCalibrationState   14          //��ȡ�궨״̬

//===========================���߱궨======================================//
#define  eolExtend          15               //������չģʽ
#define  eolReadPartNum     16               //��ȡ���������
#define  eolReadHardWareNo  17               //��Ӳ���汾��
#define  eolReadSoftWareNo  18               //������汾��
#define  safeAccess         19               //��ȫ����
#define  vinCodeWrite       20               //vin��д��
#define  vinCodeRead        21               //vin���ȡ
#define  carConfigWrite     22               //����������Ϣд��
#define  carConfigRead      23               //����������Ϣ��ȡ
#define  removeMidCalibration 24             //�����λ�궨
#define  midCalibration     25               //ת����λ�궨
#define  clearSSMCode       26               //���SSM������
#define  readSSMCode        27               //��ȡSSM������
#define  sasCalibration     28               //sas�궨��ʼ
#define  sasCalibrationEnd  29               //sas�궨��ʼ����


//===========================���߱궨��ȫ���ʲ���======================================//
#define  safeAccessSendSeed 1              //���߱궨��ȫ���ʷ�������
#define  safeAccessSendSecret 2            //���߱궨��ȫ���ʷ�����Կ

//===========================���߱궨ת����λ�궨����======================================//
#define  midCalibrationStep1 1              //���߱궨ת����λ�궨����1
#define  midCalibrationStep2 2              //���߱궨ת����λ�궨����2




   
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