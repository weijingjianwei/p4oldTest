   #ifndef _CLOCK_H
   #define _CLOCK_H
   
  
  
   #include <hidef.h>
   #include <mc9s12g48.h>    
   
  
   
  

 /********************************************************************/ 
   //#define	INTERNAL_OSCILLATOR    	//please use internal oscillator here ��ʹ���ڲ���������
   #define		EXTERNAL_OSCILLATOR		//please use external oscillator here ��ʹ���ⲿ��������
  
   #ifdef	INTERNAL_OSCILLATOR       //if difine the internal oscillator we can change the clock to the frequency we need 
   #define   INTERNAL_BUS_CLOCK  16  //���Ƕ���Ϊ�ڲ������ڴ˴����Ը���Ϊ������Ҫ������Ƶ��ֵ
   #endif
  /***********************���徧������*********************************/    
 /********************************************************************/   
      
   extern void INIT_COP(void); 
   extern void INIT_PLL(void);
   extern void INIT_RTI(void);
   
   #endif