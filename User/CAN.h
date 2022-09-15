    #ifndef _CAN_H
    #define _CAN_H
   
  
  
   #include <hidef.h>
   #include <mc9s12g48.h>  
   
/*  can transmitte measege */   
typedef struct 
{
	uint  u16ID;	
	byte  u8Prio;
	byte  u8Length;
	byte  *u8TxData;    
	
}mscan_msg_t;

/*  can receive measege */ 
typedef struct 
{
   uint u16ID;	
	byte  u8Length;
	byte  Data[8];
	
}mscan_msg_r;
  extern  uchar canreceiveflag; 
   extern uchar canreceiveflag1;
   extern uchar canMesEndState;

extern mscan_msg_r RxMsg;
extern mscan_msg_r RxMsgAngel;
extern mscan_msg_t TxMsg;
extern uint cansendtime;
extern uchar canSASRXbuff[10][8];
/* CAN ID definition: Standard Id 0x6C7 formatted to be loaded in IDRx */

#define SASTX_ID 0x723  //开关诊断报文请求id  
#define SASRX_ID 0x75B  //开关诊断报文响应id 
#define CAN1RX_ID 0x010
#define CAN1TX_ID 0x020
#define SASSTAUE_ID 0x39  //获取开关转动角度数据响应id
   

/* Error Flags Definition */
#define NO_ERR 0x00
#define ERR 0x01
#define ERR_BUFFER_FULL 0x80 



//#define TSEG1 1
//#define TSEG2 4
#define TSEG1 10
#define TSEG2 3
#define SJ 2
#define vCANIDMR0 0xff
#define vCANIDMR1 0xff
#define vCANIDMR2 0xff
#define vCANIDMR3 0xff
#define vCANIDMR4 0xff
#define vCANIDMR5 0xff
#define vCANIDMR6 0xff
#define vCANIDMR7 0xff

#define vCANIDAR0 0xff
#define vCANIDAR1 0xff
#define vCANIDAR2 0xff
#define vCANIDAR3 0xff
#define vCANIDAR4 0xff
#define vCANIDAR5 0xff
#define vCANIDAR6 0xff
#define vCANIDAR7 0xff

#define vWUPM 0



extern void INIT_CAN(void);
extern byte CAN_Send_Frame(mscan_msg_t msg);
extern void CAN_Read_Frame(void);
extern void CAN_Sleep(void);
void READV(void);
byte GET_BUS_OFF_STATE(void);
   
   #endif