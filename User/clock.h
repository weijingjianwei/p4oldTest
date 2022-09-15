   #ifndef _CLOCK_H
   #define _CLOCK_H
   
  
  
   #include <hidef.h>
   #include <mc9s12g48.h>    
   
  
   
  

 /********************************************************************/ 
   //#define	INTERNAL_OSCILLATOR    	//please use internal oscillator here 若使用内部晶振，则定义
   #define		EXTERNAL_OSCILLATOR		//please use external oscillator here 若使用外部晶振，则定义
  
   #ifdef	INTERNAL_OSCILLATOR       //if difine the internal oscillator we can change the clock to the frequency we need 
   #define   INTERNAL_BUS_CLOCK  16  //若是定义为内部晶振，在此处可以更改为我们需要的总线频率值
   #endif
  /***********************定义晶振类型*********************************/    
 /********************************************************************/   
      
   extern void INIT_COP(void); 
   extern void INIT_PLL(void);
   extern void INIT_RTI(void);
   
   #endif