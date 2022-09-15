#ifndef _SCI_H
#define _SCI_H
  
  
  #include <hidef.h>
  #include <mc9s12g48.h>    


 #define  BUS_CLOCK		   16000000	   //����Ƶ��
 #define     BAUD         38400

 #define sendnummax 10
 extern uchar Data_send[sendnummax];       //����һ��SCI��f���ͻ����������յ����ݴ����Data_receive������




         
extern void  INIT_SCI(void);
extern void  BYTESEND_SCI(uchar data);
extern void  STRINGSEND_SCI(uchar *data1, uint num1);
extern uchar RECEIVE_SCI(void);
extern void  KEYSEND(uchar data2);

extern uchar CHECKSUM(uchar *data,uchar sum_num); 
#endif
   
