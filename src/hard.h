//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### HARD.H #################################
//---------------------------------------------

#ifndef HARD_H_
#define HARD_H_


//----------- Defines For Configuration -------------

//----- Board Configuration -------------------//
//--- Hardware ------------------//
#define HARDWARE_VERSION_1_0    // first prototype


//--- Software ------------------//
#define FIRMWARE_VERSION_1_0    // init version


//-------- Type of Program (depending on software version) ----------------



//-------- Type of Program and Features ----------------
// #define USE_NO_TREATMENT_DETECT    //cuando esta en tratamiento revisa si las potencias tambien
// #define USE_BUZZER_ON_START


//-------- Kind of Reports Sended ----------------

//-------- Others Configurations depending on the formers ------------


//-------- Oscillator and Crystal selection (Freq in startup_clocks.h) ---
#define HSI_INTERNAL_RC
// #define HSE_CRYSTAL_OSC

#ifdef HSE_CRYSTAL_OSC
// #define CRYSTAL_8MHZ
#define CRYSTAL_12MHZ
#endif

#ifdef HSE_CRYSTAL_OSC
// #define SYSCLK_FREQ_72MHz
#define SYSCLK_FREQ_8MHz
#endif

#ifdef HSI_INTERNAL_RC
#define SYSCLK_FREQ_64MHz
// #define SYSCLK_FREQ_8MHz
#endif

//-------- End Of Defines For Configuration ------




//--- Hardware & Software Messages ------------------//
#ifdef HARDWARE_VERSION_1_0
#define HARD "Hardware Version: 1.0"
#endif
#ifdef FIRMWARE_VERSION_1_0
#define SOFT "Firmware Version: 1.0"
#endif
//--- End of Hardware & Software Messages ------------------//



// Exported Types --------------------------------------------------------------
#ifdef HARDWARE_VERSION_1_0

// PA defines ----
// PA0 NC
// PA1 
#define PULSE_BED    ((GPIOA->ODR & 0x0002) != 0)
#define PULSE_BED_ON    (GPIOA->BSRR = 0x00000002)
#define PULSE_BED_OFF    (GPIOA->BSRR = 0x00020000)

// PA2 PA3 Alternative Usart2 Tx Rx (Bed)

// PA4
// PA5
// PA6
// PA7
// PA8 NC

// PA9 PA10 Alternative Usart1 Tx Rx (Rpi)

// PA11
// PA12
// PA13 PA14 PA15 NC jtag

// PB defines ----
// PB0 
// PB1
// PB2 NC

// PB3 PB4 NC jtag
// PB5 
// PB6
// PB7
// PB8
// PB9 NC

// PB10 PB11 Alternative Usart3 Tx Rx (Top)

// PB12
// PB13 NC

// PB14
#define PULSE_TOP    ((GPIOB->ODR & 0x4000) != 0)
#define PULSE_TOP_ON    (GPIOB->BSRR = 0x00004000)
#define PULSE_TOP_OFF    (GPIOB->BSRR = 0x40000000)

// PB15
#define OUT2    ((GPIOB->ODR & 0x8000) != 0)
#define OUT2_ON    (GPIOB->BSRR = 0x00008000)
#define OUT2_OFF    (GPIOB->BSRR = 0x80000000)

// PC defines ----
// PC0 NC
// PC1
#define LED_ACT_TABLE    ((GPIOC->ODR & 0x0002) != 0)
#define LED_ACT_TABLE_ON    (GPIOC->BSRR = 0x00000002)
#define LED_ACT_TABLE_OFF    (GPIOC->BSRR = 0x00020000)

// PC2
#define LED_ACT_BED    ((GPIOC->ODR & 0x0004) != 0)
#define LED_ACT_BED_ON    (GPIOC->BSRR = 0x00000004)
#define LED_ACT_BED_OFF    (GPIOC->BSRR = 0x00040000)

// PC3
#define LED1    ((GPIOC->ODR & 0x0008) != 0)
#define LED1_ON    (GPIOC->BSRR = 0x00000008)
#define LED1_OFF    (GPIOC->BSRR = 0x00080000)

// PC4
// PC5 NC

// PC6
#define OUT1    ((GPIOC->ODR & 0x0040) != 0)
#define OUT1_ON    (GPIOC->BSRR = 0x00000040)
#define OUT1_OFF    (GPIOC->BSRR = 0x00400000)

// PC7
#define IN1    ((GPIOC->IDR & 0x0080) == 0)

// PC8
#define IN2    ((GPIOC->IDR & 0x0100) == 0)

// PC9
// PC10
// PC11
// PC12
// PC13
// PC14
// PC15 NC

// PD defines ----
// PD0 PD1 PD2 NC


#endif //HARDWARE_VERSION_1_0



// Module Exported Functions ---------------------------------------------------
void Led_Act_Table_On (void);
void Led_Act_Bed_On (void);
void Led1_On (void);

void Led_Act_Table_Off (void);
void Led_Act_Bed_Off (void);
void Led1_Off (void);

unsigned char Led_Act_Table_Is_On (void);
unsigned char Led_Act_Bed_Is_On (void);
unsigned char Led1_Is_On (void);

unsigned char In2_Pin (void);
unsigned char In1_Pin (void);

void Out1_On (void);
void Out2_On (void);
void Pulse_Top_On (void);
void Pulse_Bed_On (void);

void Out1_Off (void);
void Out2_Off (void);
void Pulse_Top_Off (void);
void Pulse_Bed_Off (void);

unsigned char Out1_Is_On (void);
unsigned char Out2_Is_On (void);
unsigned char Pulse_Top_Is_On (void);
unsigned char Pulse_Bed_Is_On (void);

#define Led_Act_Top_On()    Led_Act_Table_On()
#define Led_Act_Top_Off()    Led_Act_Table_Off()
#define Led_Act_Top_Is_On()    Led_Act_Table_Is_On()
#endif
