#ifndef _SCI_H
#define _SCI_H
  
  
  #include <hidef.h>
  #include <mc9s12g48.h>    


 #define  BUS_CLOCK		   16000000	   //总线频率
 #define     BAUD         38400

 #define sendnummax 10
 extern uchar Data_send[sendnummax];       //定义一个SCI的f发送缓冲器，接收的数据存放在Data_receive数组中




         
extern void  INIT_SCI(void);
extern void  BYTESEND_SCI(uchar data);
extern void  STRINGSEND_SCI(uchar *data1, uint num1);
extern uchar RECEIVE_SCI(void);
extern void  KEYSEND(uchar data2);

extern uchar CHECKSUM(uchar *data,uchar sum_num); 
#endif
   
