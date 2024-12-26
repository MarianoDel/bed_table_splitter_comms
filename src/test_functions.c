//----------------------------------------------------------
// #### MAGNET PROJECT - Custom Board ####
// ## Internal Test Functions Module
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### TEST_FUNCTIONS.C ###################################
//----------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "test_functions.h"
#include "hard.h"
#include "stm32f10x.h"
#include "gpio.h"
#include "adc.h"
#include "usart_channels.h"
#include "usart.h"
#include "dma.h"
#include "tim.h"

#include <stdio.h>
#include <string.h>


// Externals -------------------------------------------------------------------
extern volatile unsigned short wait_ms_var;
extern volatile unsigned short timer_standby;
extern volatile unsigned char timer_6_uif_flag;
extern volatile unsigned char rx_int_handler;
// extern volatile unsigned char usart3_have_data;


// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------
void TF_Led_Test (void);
void TF_In0_In1_Input (void);
void TF_Out2_Out1_Outputs (void);
void TF_PulseBed_PulseTable_Outputs (void);


void TF_UsartTop_Loop (void);
void TF_UsartBed_Loop (void);
void TF_UsartRpi_Loop (void);
void TF_UsartRpi_String (void);


// Module Functions ------------------------------------------------------------
void TF_Hardware_Tests (void)
{

    // TF_Led_Test ();

    // TF_In0_In1_Input ();

    // TF_Out2_Out1_Outputs ();

    // TF_PulseBed_PulseTable_Outputs ();

    // TF_UsartTop_Loop ();

    TF_UsartBed_Loop ();    

    // TF_UsartRpi_Loop ();

    // TF_UsartRpi_String ();    
}


void TF_Led_Test (void)
{
    while (1)
    {
	Led_Act_Table_On();
	Led_Act_Bed_On();
	Led1_On();
        Wait_ms(1000);

	Led_Act_Table_Off();
	Led_Act_Bed_Off();
	Led1_Off();
	Wait_ms(1000);
    }
}


void TF_In2_In1_Input (void)
{
    Led_Act_Table_Off();
    Led_Act_Bed_Off();
    Led1_Off();

    while (1)
    {
	if (In2_Pin())
	    Led_Act_Table_On();
	else
	    Led_Act_Table_Off();

	if (In1_Pin())
	    Led_Act_Bed_On();
	else
	    Led_Act_Bed_Off();
	

	Wait_ms(300);
    }
}


void TF_Out2_Out1_Outputs (void)
{
    Led_Act_Table_Off();
    Led_Act_Bed_Off();
    Led1_Off();

    Out2_Off();
    Out1_On();

    while (1)
    {
	Wait_ms(5000);

	if (Out2_Is_On())
	{
	    Out2_Off();
	    Led_Act_Bed_Off();
	}
	else
	{
	    Out2_On();
	    Led_Act_Bed_On();
	}

	if (Out1_Is_On())
	{
	    Out1_Off();
	    Led_Act_Table_Off();
	}
	else
	{
	    Out1_On();
	    Led_Act_Table_On();
	}
    }
}


void TF_PulseBed_PulseTable_Outputs (void)
{
    Led_Act_Table_Off();
    Led_Act_Bed_Off();
    Led1_Off();

    Pulse_Bed_Off();
    Pulse_Top_On();

    while (1)
    {
	Wait_ms(5000);

	if (Pulse_Top_Is_On())
	{
	    Pulse_Top_Off();
	    Led_Act_Top_Off();
	}
	else
	{
	    Pulse_Top_On();
	    Led_Act_Top_On();
	}

	if (Pulse_Bed_Is_On())
	{
	    Pulse_Bed_Off();
	    Led_Act_Bed_Off();
	}
	else
	{
	    Pulse_Bed_On();
	    Led_Act_Bed_On();
	}
    }
}


// place a shortcut Rx Tx on Top connector
void TF_UsartBed_Loop (void)
{
    char buff [100];
    
    UsartBedConfig ();
    
    while (1)
    {
        if (!timer_standby)
        {
            UsartBedSend ("Mariano\n");
            timer_standby = 2000;
            if (Led_Act_Bed_Is_On())
                Led_Act_Bed_Off();
        }

        if (UsartBedHaveData ())
        {
	    Led1_On();
            UsartBedHaveDataReset ();
            UsartBedReadBuffer (buff, 100);
            if (strncmp(buff, "Mariano", sizeof("Mariano") - 1) == 0)
                Led_Act_Bed_On();

	    Wait_ms(100);
	    Led1_Off();
        }
    }
}


// place a shortcut Rx Tx on Bed connector
void TF_UsartTop_Loop (void)
{
    char buff [100];
    
    UsartTopConfig ();
    
    while (1)
    {
        if (!timer_standby)
        {
            UsartTopSend ("Mariano\n");
            timer_standby = 2000;
            if (Led_Act_Top_Is_On())
                Led_Act_Top_Off();
        }

        if (UsartTopHaveData ())
        {
	    Led1_On();	    
            UsartTopHaveDataReset ();
            UsartTopReadBuffer (buff, 100);
            if (strncmp(buff, "Mariano", sizeof("Mariano") - 1) == 0)
                Led_Act_Top_On();

	    Wait_ms(100);
	    Led1_Off();
        }
    }
}


// place a shortcut Rx Tx on Rpi connector
void TF_UsartRpi_Loop (void)
{
    char buff [100];
    
    UsartRpiConfig ();
    
    while (1)
    {
        if (!timer_standby)
        {
            UsartRpiSend ("Mariano\n");
            timer_standby = 2000;
            if (Led1_Is_On())
                Led1_Off();

        }

        if (UsartRpiHaveData ())
        {
            UsartRpiHaveDataReset ();
            UsartRpiReadBuffer (buff, 100);
            if (strncmp(buff, "Mariano", sizeof("Mariano") - 1) == 0)
                Led1_On();
        }
    }
}


// Terminal Looping on Rpi connector
void TF_UsartRpi_String (void)
{
    char buff [100];

    UsartRpiConfig ();
    UsartRpiSend("rpi usart test... send a string:\n");
    
    while (1)
    {
        if (UsartRpiHaveData())
        {
            UsartRpiHaveDataReset();
            UsartRpiReadBuffer(buff, 100);

            Wait_ms(1000);

            int i = strlen(buff);
            if (i < 100 - 1 - 1)
            {
                buff[i] = '\r';
                buff[i+1] = '\n';		
                buff[i+2] = '\0';
                UsartRpiSend(buff);
            }
        }
    }
}

//--- end of file ---//
