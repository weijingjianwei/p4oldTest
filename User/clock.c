/*****************************************************************************

 * File Name: CLOCK
 * Description:  System clock function ,include the PLL, RTI, COP . 
 * Author:  pine
 * Date: 2022-09-09
 
 *****************************************************************************/
 #include "clock.h"
 
 
 
 
/******************************************************************************/
/**
 * Function Name: void INIT_PLL(void)
 * Description: Initial the system clock PLL 初始化锁相环  
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/

/*************************************************************/
/*                      初始化锁相环                         */
/*                  使用外部晶振：8MHz                      */
/*                  设置总线频率：16MHz                      */
/*************************************************************/
void INIT_PLL(void) 
{
   
#ifdef INTERNAL_OSCILLATOR            /*external or internal oscillator 确定是内部时钟还是外部晶振*/
     CPMUOSC_OSCE  = 0;               /*********disable external oscillator使能内部晶振***********/
    
     CPMUCLKS = CPMUCLKS_PLLSEL_MASK +     	// system clock are derived from PLLCLK, Fbus = Fpll/2
               CPMUCLKS_PCE_MASK +        	// COP continue to run at STOP mode
               CPMUCLKS_PRE_MASK +        	// RTI continue to run at STOP mode
               CPMUCLKS_COPOSCSEL1_MASK + 	// COP clock source is ACLK derived from a trimmable internal RC-Oscillator
               CPMUCLKS_PSTP;			        	// Oscillator continues to run in Stop Mode (Pseudo Stop Mode)
    
       //PLLCLK=2×OSCCLK×(SYNDIV+1)/(REFDIV+1), fbus=PLLCLK/2
    CPMUPOSTDIV = 0;           
    CPMUSYNR =INTERNAL_BUS_CLOCK - 1;         /*************** INTERNAL_BUS_CLOCK在头文件中预定义，可在那里改成需要的总线频率********/

    while(CPMUFLG_LOCK==0);          /****************wait until the PLLCLK is LOCKED 等待PLLCLK锁定*************************/
       	 _FEED_COP(); /* feeds the dog */
   
    
#else
  #ifdef EXTERNAL_OSCILLATOR 
    
    CPMUPROT=0x26;                         /***Disable protection of clock configuration registers 解除时钟配置保护***/                 
    CPMUOSC_OSCE=1;                       /*********************enable external oscillator 使能外部晶振***************/
   
    while(CPMUOSC_OSCPINS_EN==0);          /******等待外部晶振使能 Wait until the oscillator is enable ***********/
    while(CPMUFLG_UPOSC==0);              /****等待PLL完成 Wait until the oscillator is qualified by the PLL ****/
  
    CPMUCLKS &=(~0x40);                  /******* Oscillator is disabled in Stop Mode 在停止模式是晶振不使能********/
    CPMUCLKS |= 0x80;                   /***System clocks are derived from PLLCLK, fbus=fPLL/2设置PLLCLK为系统时钟***/
    while(CPMUCLKS != 0xDF)             /***Make sure the System clocks are derived from PLLCLK确定PLLCLK设置为系统时钟***/
		{
			CPMUCLKS = 0xDF;			            /******Set system clocks are derived from PLLCLK again 再次设置PLLCLK为系统时钟***/
		}
                    //PLLCLK=2×OSCCLK×(SYNDIV+1)/(REFDIV+1), fbus=PLLCLK/2
   
    CPMUREFDIV = 0x80;                /*********REFDIV的值为1 fREF=fOSC/(REFDIV + 1)bit7.bit6由fREF决定***************/
    CPMUSYNR=0x01;                    /******SYNDIV的值为1   fVCO = 2 × fREF × (SYNDIV + 1)bit7.bit6由fvco决定 ********/
   
    CPMUPOSTDIV=0x00;                /****************If PLL is locked (LOCK=1) =   fPLL=fVCO/(POSTDIV+1)*************/
    CPMUPLL=0x10;                    /***************01=1%  PLL Frequency Modulation Enable Bits*****************************/

    while(CPMUFLG_LOCK==0);          /****************wait until the PLLCLK is LOCKED 等待PLLCLK锁定*************************/
    CPMUPROT=0x00;                   /**********Enable protection of clock configuration registers 设置时钟配置保护**********/  
    
  #endif               
#endif
  
  }
 


 /******************************************************************************/
/**
 * Function Name: void INIT_COP(void)
 * Description: Initial the COP 初始化看门狗，时钟复位周期为1.048576S  
 * Param:   None
 * Return:  none
 * Author:  pine
 *****************************************************************************/

/*************************************************************/
/*                      初始化看门狗                         */
/*************************************************************/
  void INIT_COP(void)
{
  CPMUPROT=0x26;              //解除时钟配置保护     
  CPMUCLKS &=(~0x10);        //选择时钟源
  CPMUCLKS |=0x01;          //设置时钟源为晶振时钟
  CPMUCOP = 0x07;          //设置看门狗复位间隔, 2^24个晶振周期，为1.048576s
  CPMUPROT=0x00;           //使能时钟配置保护
 }   
 
 
  /******************************************************************************/
/**
 * Function Name: void INIT_RTI(void)
 * Description: Initial the RTI 初始化实时时钟，时钟中断周期**S  
 * Param:   None
 * Return:  none
 * Author:  pine
 *****************************************************************************/

  
/*************************************************************/
/*                       初始化实时中断                      */
/*************************************************************/
void INIT_RTI(void)
{
  CPMUPROT=0x26;           //解除时钟配置保护
  CPMUCLKS |=0x02;        //RTI时钟源为晶振时钟     
  CPMUINT = 0x80;         //使能实时中断
  //CPMURTI = 0XA7;   
  CPMURTI = 0XB7;      //8M 设置实时中断的时间间隔为5ms
  CPMUPROT=0x00;          //使能时钟配置保护
}






























