//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### USART_CHANNELS.H ######################
//---------------------------------------------

#ifndef _USART_CHANNELS_H_
#define _USART_CHANNELS_H_


// Module Exported Macros ------------------------------------------------------
#define UsartTopConfig()    Usart3Config()
#define UsartTopSend(X)    Usart3Send(X)
#define UsartTopReadBuffer(X,Y)    Usart3ReadBuffer(X,Y)
#define UsartTopHaveData()    Usart3HaveData()
#define UsartTopHaveDataReset()    Usart3HaveDataReset()
#define UsartTopShutdownn()    Usart3Shutdown()

#define UsartBedConfig()    Usart2Config()
#define UsartBedSend(X)    Usart2Send(X)
#define UsartBedReadBuffer(X,Y)    Usart2ReadBuffer(X,Y)
#define UsartBedHaveData()    Usart2HaveData()
#define UsartBedHaveDataReset()    Usart2HaveDataReset()
#define UsartBedShutdownn()    Usart2Shutdown()

#define UsartRpiConfig()    Usart1Config()
#define UsartRpiSend(X)    Usart1Send(X)
#define UsartRpiReadBuffer(X,Y)    Usart1ReadBuffer(X,Y)
#define UsartRpiHaveData()    Usart1HaveData()
#define UsartRpiHaveDataReset()    Usart1HaveDataReset()
#define UsartRpiShutdownn()    Usart1Shutdown()



#endif     /* _USART_CHANNELS_H_ */
