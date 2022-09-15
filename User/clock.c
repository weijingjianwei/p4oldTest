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
 * Description: Initial the system clock PLL ��ʼ�����໷  
 * Param:   none
 * Return:  none
 * Author:  pine
 *****************************************************************************/

/*************************************************************/
/*                      ��ʼ�����໷                         */
/*                  ʹ���ⲿ����8MHz                      */
/*                  ��������Ƶ�ʣ�16MHz                      */
/*************************************************************/
void INIT_PLL(void) 
{
   
#ifdef INTERNAL_OSCILLATOR            /*external or internal oscillator ȷ�����ڲ�ʱ�ӻ����ⲿ����*/
     CPMUOSC_OSCE  = 0;               /*********disable external oscillatorʹ���ڲ�����***********/
    
     CPMUCLKS = CPMUCLKS_PLLSEL_MASK +     	// system clock are derived from PLLCLK, Fbus = Fpll/2
               CPMUCLKS_PCE_MASK +        	// COP continue to run at STOP mode
               CPMUCLKS_PRE_MASK +        	// RTI continue to run at STOP mode
               CPMUCLKS_COPOSCSEL1_MASK + 	// COP clock source is ACLK derived from a trimmable internal RC-Oscillator
               CPMUCLKS_PSTP;			        	// Oscillator continues to run in Stop Mode (Pseudo Stop Mode)
    
       //PLLCLK=2��OSCCLK��(SYNDIV+1)/(REFDIV+1), fbus=PLLCLK/2
    CPMUPOSTDIV = 0;           
    CPMUSYNR =INTERNAL_BUS_CLOCK - 1;         /*************** INTERNAL_BUS_CLOCK��ͷ�ļ���Ԥ���壬��������ĳ���Ҫ������Ƶ��********/

    while(CPMUFLG_LOCK==0);          /****************wait until the PLLCLK is LOCKED �ȴ�PLLCLK����*************************/
       	 _FEED_COP(); /* feeds the dog */
   
    
#else
  #ifdef EXTERNAL_OSCILLATOR 
    
    CPMUPROT=0x26;                         /***Disable protection of clock configuration registers ���ʱ�����ñ���***/                 
    CPMUOSC_OSCE=1;                       /*********************enable external oscillator ʹ���ⲿ����***************/
   
    while(CPMUOSC_OSCPINS_EN==0);          /******�ȴ��ⲿ����ʹ�� Wait until the oscillator is enable ***********/
    while(CPMUFLG_UPOSC==0);              /****�ȴ�PLL��� Wait until the oscillator is qualified by the PLL ****/
  
    CPMUCLKS &=(~0x40);                  /******* Oscillator is disabled in Stop Mode ��ֹͣģʽ�Ǿ���ʹ��********/
    CPMUCLKS |= 0x80;                   /***System clocks are derived from PLLCLK, fbus=fPLL/2����PLLCLKΪϵͳʱ��***/
    while(CPMUCLKS != 0xDF)             /***Make sure the System clocks are derived from PLLCLKȷ��PLLCLK����Ϊϵͳʱ��***/
		{
			CPMUCLKS = 0xDF;			            /******Set system clocks are derived from PLLCLK again �ٴ�����PLLCLKΪϵͳʱ��***/
		}
                    //PLLCLK=2��OSCCLK��(SYNDIV+1)/(REFDIV+1), fbus=PLLCLK/2
   
    CPMUREFDIV = 0x80;                /*********REFDIV��ֵΪ1 fREF=fOSC/(REFDIV + 1)bit7.bit6��fREF����***************/
    CPMUSYNR=0x01;                    /******SYNDIV��ֵΪ1   fVCO = 2 �� fREF �� (SYNDIV + 1)bit7.bit6��fvco���� ********/
   
    CPMUPOSTDIV=0x00;                /****************If PLL is locked (LOCK=1) =   fPLL=fVCO/(POSTDIV+1)*************/
    CPMUPLL=0x10;                    /***************01=1%  PLL Frequency Modulation Enable Bits*****************************/

    while(CPMUFLG_LOCK==0);          /****************wait until the PLLCLK is LOCKED �ȴ�PLLCLK����*************************/
    CPMUPROT=0x00;                   /**********Enable protection of clock configuration registers ����ʱ�����ñ���**********/  
    
  #endif               
#endif
  
  }
 


 /******************************************************************************/
/**
 * Function Name: void INIT_COP(void)
 * Description: Initial the COP ��ʼ�����Ź���ʱ�Ӹ�λ����Ϊ1.048576S  
 * Param:   None
 * Return:  none
 * Author:  pine
 *****************************************************************************/

/*************************************************************/
/*                      ��ʼ�����Ź�                         */
/*************************************************************/
  void INIT_COP(void)
{
  CPMUPROT=0x26;              //���ʱ�����ñ���     
  CPMUCLKS &=(~0x10);        //ѡ��ʱ��Դ
  CPMUCLKS |=0x01;          //����ʱ��ԴΪ����ʱ��
  CPMUCOP = 0x07;          //���ÿ��Ź���λ���, 2^24���������ڣ�Ϊ1.048576s
  CPMUPROT=0x00;           //ʹ��ʱ�����ñ���
 }   
 
 
  /******************************************************************************/
/**
 * Function Name: void INIT_RTI(void)
 * Description: Initial the RTI ��ʼ��ʵʱʱ�ӣ�ʱ���ж�����**S  
 * Param:   None
 * Return:  none
 * Author:  pine
 *****************************************************************************/

  
/*************************************************************/
/*                       ��ʼ��ʵʱ�ж�                      */
/*************************************************************/
void INIT_RTI(void)
{
  CPMUPROT=0x26;           //���ʱ�����ñ���
  CPMUCLKS |=0x02;        //RTIʱ��ԴΪ����ʱ��     
  CPMUINT = 0x80;         //ʹ��ʵʱ�ж�
  //CPMURTI = 0XA7;   
  CPMURTI = 0XB7;      //8M ����ʵʱ�жϵ�ʱ����Ϊ5ms
  CPMUPROT=0x00;          //ʹ��ʱ�����ñ���
}






























