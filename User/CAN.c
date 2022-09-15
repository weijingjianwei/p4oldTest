/*****************************************************************************

 * File Name: CAN
 * Description:  System CAN communication ,include the can_initial, can send,can read 
 * Author:  pine
 * Date: 2022-09-09
 
 *****************************************************************************/


#include "can.h"


#define CAN_BUS_SLEEP_ENABLE

mscan_msg_r RxMsg;
mscan_msg_r RxMsgAngel;
mscan_msg_t TxMsg;
 uchar canreceiveflag;  uchar canreceiveflag1;
byte ext_osc=8;     // 外部晶振为8兆
//byte ext_osc=16;
 
/******************************************************************************/
/**
 * Function Name: CAN_Init(void)
 * Description: Initial CAN  
 * Param:   none
 * Return:  none
 * Author: pine
 *****************************************************************************/
void INIT_CAN(void){

    CANCTL0 = 0x01;    /* MSCAN in initialization mode */
    while (!(CANCTL1_INITAK)) ;	        /* Wait for initialization mode acknowledge */
  /*CANCTL1  CANBTR0  CANBTR1  CANIDAC  CANIDAR0-7  CANIDMR0-7 must initial in initialization mode*/      
    CANCTL1_CANE = 1;      /* Enable MSCAN module */
    CANCTL1_CLKSRC = 0;    /* Clock source is OSCCLK */    
    //CANCTL1_BORM=1;
    CANCTL1_LISTEN = 0;    /* Not listen only mode */                   
    CANBTR1 = (TSEG2<<4) + TSEG1 ;         // fclk=fosc*(TSEG+1)*(TESG2+1)/CANBTR0  500kbps 
    if(ext_osc == 8) CANBTR0 = 0; 
    else if(ext_osc == 16) CANBTR0 = 3; 
    CANBTR0=CANBTR0+ (SJ<<6);
    CANIDAC_IDAM = 0x1;    // Four 16-bit acceptanc filter
    // accept all the ID on CAN bus
    CANIDMR0 = vCANIDMR0;    // ignore corresponding acceptance code register bit;
    CANIDMR1 = vCANIDMR1;    // ignore corresponding acceptance code register bit;
    CANIDMR2 = vCANIDMR2;    // ignore corresponding acceptance code register bit;
    CANIDMR3 = vCANIDMR3;    // ignore corresponding acceptance code register bit;
    CANIDMR4 = vCANIDMR4;    // ignore corresponding acceptance code register bit;
    CANIDMR5 = vCANIDMR5;    // ignore corresponding acceptance code register bit;
    CANIDMR6 = vCANIDMR6;    // ignore corresponding acceptance code register bit;
    CANIDMR7 = vCANIDMR7;    // ignore corresponding acceptance code register bit;
    
    CANIDAR0 = vCANIDAR0;
    CANIDAR1 = vCANIDAR1;
    CANIDAR2 = vCANIDAR2;
    CANIDAR3 = vCANIDAR3;
    CANIDAR4 = vCANIDAR4;
    CANIDAR5 = vCANIDAR5;
    CANIDAR6 = vCANIDAR6;
    CANIDAR7 = vCANIDAR7; 
    CANCTL0_INITRQ = 0;            /* Exit initialization mode request */
  
   while (CANCTL1_INITAK);               	/* Wait for normal mode */
                      
#ifdef CAN_BUS_SLEEP_ENABLE

    CANCTL0_WUPE = 1;       // enable wakeup
    CANRIER_WUPIE = 1;      // enable wakeup interrupt. It can be modified after exit initialzation
    
    CANCTL1_WUPM = vWUPM;   // 0: wakeup at any dominant level
                            // 1: wakeup at a dominant pulse above t_wup
#endif                        
  
   while(!(CANCTL0_SYNCH));                   /* Wait for CAN synchronization */
    CANRFLG_RXF = 1;       /* Clear receiver flags */                                   
    CANRIER_RXFIE = 1;     /* Enable Full Receive Buffer interrupt */  
    //CANMISC=0x01;
    CANRIER=CANRIER|0x08; //only buss off or txerr  CSIF  set
    
#ifdef CAN_TX_interrupt
    CANTIER_TXEIE0 = 1;
    CANTIER_TXEIE1 = 1;
    CANTIER_TXEIE2 = 1;
#endif    
    
}
/******************************************************************************/
/**
 * Function Name: CAN_Send_Frame(mscan_msg_t msg)
 * Description: CAN send message 
 * Param:   msg
 * Return:  none
 * Author:  pine
 *****************************************************************************/
byte CAN_Send_Frame(mscan_msg_t msg)
{   
    /* Transmission buffer */
    byte u8TxBuffer = {0};
  
    /* Index to data within the transmission buffer */ 
    byte u8Index;
    
    if (!CANTFLG)              /* Retrun if Transmit Buffer is full */
     return ERR_BUFFER_FULL;
     cansendtime=0;
    CANTBSEL = CANTFLG;       /* Select lowest empty buffer */
    u8TxBuffer = CANTBSEL;		/* Backup selected buffer */
    
    msg.u16ID = msg.u16ID<<5;
    CANTXIDR0 =  msg.u16ID/256;
    CANTXIDR1 =  msg.u16ID%256;
    
   
 //  *((dword *) ((dword)(&CANTXIDR0)))= msg.u32ID;   /* Load Id to IDR Registers */
        
        
        for (u8Index=0;u8Index<(msg.u8Length);u8Index++) {
        *(&CANTXDSR0 + u8Index) = (msg.u8TxData)[u8Index];  
        }

    CANTXDLR = msg.u8Length;   /* Set Data Length Code */
    CANTXTBPR = msg.u8Prio;    /* Set Priority */
    CANTFLG = u8TxBuffer;  /* Start transmission */
                
    while ( (CANTFLG & u8TxBuffer) != u8TxBuffer)
           if( cansendtime>=30) {
             cansendtime=0;
             return ERR ;
             _FEED_COP();
           }/* feeds the dog */ /* Wait for Transmission completion */
            
    return NO_ERR;
 }
  
/******************************************************************************/
/**
 * Function Name: CAN_Read_Frame(void)
 * Description: Read CAN Message 
 * Param:   msg
 * Return:  none
 * Author:  pine
 *****************************************************************************/
 uchar canSASRXbuff[10][8];
 byte canBuffIndex=0;
 byte canBuffFormId=0x10;
 
 uchar firstFrameState;        //判断报文是否是首帧的标志位
 uchar canMesEndState;         //接收每个请求报文结束标志位
 uchar canMesByteNum;          //当前连续帧can报文数据字节数
 uchar canMesByteSum;          //连续发送的can报文数据字节总数
 void CAN_Read_Frame(void)
 
 {
    uint id=0;
    byte i;  
    id =  CANRXIDR0;
    id =( (id << 8)+ CANRXIDR1 )>>5;
  switch(id)
   {
    case SASRX_ID:
   
 
    RxMsg.u16ID=id; 
    RxMsg.u8Length = (CANRXDLR & 0x0F);
    
    for(i=0;i<RxMsg.u8Length;i++)
      RxMsg.Data[i] =  *(&CANRXDSR0 + i); 
    //连续帧结束标志位
    canMesEndState  = 0;
    //首帧0x01开始的报文
    if((RxMsg.Data[0]&0xF0)==0x10){
         canMesByteNum  = 0;
         firstFrameState = 1;  //首帧标志位置1
         canMesByteSum  =  RxMsg.Data[1];    //连续发送的can报文数据字节总数
         canMesByteNum = canMesByteNum + 6;  //首帧can报文有效字节数
         canBuffIndex = 0;
         for(i=0;i<RxMsg.u8Length;i++){
            canSASRXbuff[canBuffIndex][i] =RxMsg.Data[i]; 
         }
         canBuffIndex++;
            
          
    //连续帧0x2#开始的报文    
    }else if(((RxMsg.Data[0] & 0x20) == 0x20) && firstFrameState ==1){
        canMesByteNum = canMesByteNum + 7;  //连续帧can报文有效字节数
        for(i=0;i<RxMsg.u8Length;i++){
            canSASRXbuff[canBuffIndex][i] =RxMsg.Data[i]; 
        }
       
        //已经到连续发送末尾帧
        if(canMesByteNum >= canMesByteSum){
            canMesEndState = 1;
            canreceiveflag = 1;
            
        }else{
           canBuffIndex++; 
        }
       
        
    }else{
       for(i=0;i<RxMsg.u8Length;i++){
            canSASRXbuff[0][i] =0x00;
            canSASRXbuff[1][i] =0x00;
            canSASRXbuff[2][i] =0x00; 
       }
       
       firstFrameState = 0;
       canreceiveflag =1;
    }
                  
    //canreceiveflag=1;
  break;
 
 
  case SASSTAUE_ID:
   
 
    RxMsgAngel.u16ID=id; 
    RxMsgAngel.u8Length = (CANRXDLR & 0x0F);
    
    for(i=0;i<RxMsgAngel.u8Length;i++)
    RxMsgAngel.Data[i] =  *(&CANRXDSR0 + i); 
    canreceiveflag1=1;
 
 
  break;
 
 }
 }
