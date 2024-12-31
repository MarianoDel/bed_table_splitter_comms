//---------------------------------------------------------------
// #### PROJECT MICRO-CURRENTS SUPPLY-BRD F103 - Custom Board ###
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### MAIN.C ##################################################
//---------------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "stm32f10x.h"
#include "hard.h"

// #include "adc.h"
#include "dma.h"
#include "dac.h"
#include "tim.h"
#include "gpio.h"
#include "usart_channels.h"
#include "usart.h"

#include "manager.h"
#include "test_functions.h"

#include <stdio.h>
#include <string.h>


// Private Types Constants and Macros ------------------------------------------


// Externals -------------------------------------------------------------------
//--- Externals from timers
volatile unsigned short timer_standby = 0;
volatile unsigned short wait_ms_var = 0;


// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------
void TimingDelay_Decrement(void);
void SysTickError (void);


// Module Functions ------------------------------------------------------------
int main (void)
{
    // Gpio Configuration.
    GpioInit();
    
    // Systick Timer Activation
    if (SysTick_Config(64000))
        SysTickError();

    // Hardware Tests
    // TF_Hardware_Tests ();
    // End of Hardware Tests
    
    // --- main program inits. ---
    Out1_Off ();
    Out2_Off ();
    Pulse_Top_Off ();
    Pulse_Bed_Off ();

    Led_Act_Table_Off ();
    Led_Act_Bed_Off ();
    Led1_Off ();
    
    // -- Enable all Usarts
    UsartRpiConfig ();
    UsartTopConfig ();
    UsartBedConfig ();
    

    //-- Main Loop --------------------------
    
    while (1)
    {
	// Manager_Rpi_Loop ();
	Manager_Only_Top ();

	// Manager_Only_Bed ();

	// Manager_Top_Bed ();

	//led is alive
	// if (!timer_standby)
	// {
	//     timer_standby = 300;
	//     if (Led1_Is_On())
	// 	Led1_Off();
	//     else
	// 	Led1_On();
	// }
    }
}

//--- End of Main ---//


// Other Module Functions ------------------------------------------------------
void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

    if (timer_standby)
        timer_standby--;

    Manager_Timeouts ();

    // Comms_Timeouts ();

    // UsartTxTimeouts ();
}


void SysTickError (void)
{
    //Capture systick error...
    while (1)
    {
        // if (LED)
        //     LED_OFF;
        // else
        //     LED_ON;

        for (unsigned char i = 0; i < 255; i++)
        {
            asm ("nop \n\t"
                 "nop \n\t"
                 "nop \n\t" );
        }
    }
}

//--- end of file ---//

