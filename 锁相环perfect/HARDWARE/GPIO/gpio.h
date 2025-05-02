#ifndef	__GPIO_H__
#define	__GPIO_H__


/**
  * @brief  	Êä³ö¶Ë¿Ú
  * @param  
  * @retval
  */
#define		LED0		PDout(11)
#define		LED1		PDout(13) 
#define		LED2		PDout(15)


#define		EN0		PDout(12)	  
#define		EN1		PDout(14)	
#define		EN2		PDout(0)	
#define		EN3		PDout(1)	
#define		EN4		PDout(2)	
#define		EN5		PDout(3)	
#define		EN6		PDout(4)	
#define		EN7		PDout(7)	

#define		BUZZER	PBout(9)




  /**
    * @brief  º¯Êý
    * @param  
    * @retval 
    */
void GPIO_Config_Init(void)	;


#endif

