//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### HARD.C #################################
//---------------------------------------------
#include "hard.h"
#include "stm32f10x.h"

#include "tim.h"
#include "usart.h"

#include <stdio.h>


// Module Private Types Constants and Macros -----------------------------------


// Externals -------------------------------------------------------------------



// Globals ---------------------------------------------------------------------
volatile unsigned short led_timer = 0;


// Module Private Functions ----------------------------------------------------


// Module Functions ------------------------------------------------------------
void Led_Act_Table_On (void)
{
    LED_ACT_TABLE_ON;
}


void Led_Act_Bed_On (void)
{
    LED_ACT_BED_ON;
}


void Led1_On (void)
{
    LED1_ON;
}


void Led_Act_Table_Off (void)
{
    LED_ACT_TABLE_OFF;
}


void Led_Act_Bed_Off (void)
{
    LED_ACT_BED_OFF;
}


void Led1_Off (void)
{
    LED1_OFF;
}


unsigned char Led_Act_Table_Is_On (void)
{
    return LED_ACT_TABLE;
}


unsigned char Led_Act_Bed_Is_On (void)
{
    return LED_ACT_BED;
}


unsigned char Led1_Is_On (void)
{
    return LED1;
}


unsigned char In2_Pin (void)
{
    return IN2;
}


unsigned char In1_Pin (void)
{
    return IN1;
}


void Out1_On (void)
{
    OUT1_ON;
}


void Out2_On (void)
{
    OUT2_ON;
}


void Pulse_Top_On (void)
{
    PULSE_TOP_ON;
}


void Pulse_Bed_On (void)
{
    PULSE_BED_ON;
}


void Out1_Off (void)
{
    OUT1_OFF;
}


void Out2_Off (void)
{
    OUT2_OFF;
}


void Pulse_Top_Off (void)
{
    PULSE_TOP_OFF;
}


void Pulse_Bed_Off (void)
{
    PULSE_BED_OFF;
}


unsigned char Out1_Is_On (void)
{
    return OUT1;
}


unsigned char Out2_Is_On (void)
{
    return OUT2;
}


unsigned char Pulse_Top_Is_On (void)
{
    return PULSE_TOP;
}


unsigned char Pulse_Bed_Is_On (void)
{
    return PULSE_BED;
}


void Hard_Timeouts (void)
{
    if (led_timer)
        led_timer--;
    
}

//--- end of file ---//
