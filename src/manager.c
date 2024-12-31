//------------------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### MANAGER.C ######################################
//------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "manager.h"
#include "hard.h"
#include "usart_channels.h"
#include "usart.h"

#include <string.h>

// Private Types Constants and Macros ------------------------------------------


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
volatile unsigned short manager_top_led_timer = 0;
volatile unsigned short manager_bed_led_timer = 0;


// Module Private Functions ----------------------------------------------------
void Manager_Top_Led_Toggle (void);
void Manager_Top_Led_On (void);
void Manager_Top_Led_Off (void);

void Manager_Bed_Led_Toggle (void);
void Manager_Bed_Led_On (void);
void Manager_Bed_Led_Off (void);

// void Master_Slave_In_Master (void);
// void Master_Slave_In_Slave (void);
unsigned char Manager_Top_Is_Active (void);
void Manager_Top_Active_On (void);
void Manager_Top_Active_Off (void);

unsigned char Manager_Bed_Is_Active (void);
void Manager_Bed_Active_On (void);
void Manager_Bed_Active_Off (void);


// Module Functions ------------------------------------------------------------
void Manager_Rpi_Loop (void)
{
    unsigned short len = 0;
    char buff [500];
    
    if (UsartRpiHaveData())
    {
	Led1_On();
	UsartRpiHaveDataReset();
	len = UsartRpiReadBuffer(buff, 500);

	if (len < (500 - 3))
	{
	    buff[len-1] = '\r';
	    buff[len+0] = '\n';		
	    buff[len+1] = '\0';

	    UsartRpiSend(buff);
	}
	Led1_Off();
    }
}

void Manager_Only_Top (void)
{
    unsigned short len = 0;
    char buff [500];
    
    if (UsartRpiHaveData())
    {
	Led1_On();
	UsartRpiHaveDataReset();
	len = UsartRpiReadBuffer(buff, 500);

	if (len < (500 - 3))
	{
	    buff[len-1] = '\r';
	    buff[len+0] = '\n';		
	    buff[len+1] = '\0';

	    UsartTopSend(buff);

	    // check if we are in start or stop
	    if (strncmp(buff, "start,", sizeof ("start,") - 1) == 0)
	    {
		Manager_Top_Active_On();
	    }
	    else if (strncmp(buff, "stop,", sizeof ("stop,") - 1) == 0)
	    {
		Manager_Top_Active_Off();
	    }
	}
	Led1_Off();
    }

    if (UsartTopHaveData())
    {
	UsartTopHaveDataReset();
	len = UsartTopReadBuffer(buff, 500);

	if (len < (500 - 3))
	{
	    buff[len-1] = '\r';
	    buff[len+0] = '\n';		
	    buff[len+1] = '\0';

	    UsartRpiSend(buff);

	    // check if tabletop stops the treat
	    if (strncmp(buff, "STOP", sizeof ("STOP") - 1) == 0)
	    {
		Manager_Top_Active_Off();
	    }
	}
    }
}


void Manager_Only_Bed (void)
{
    unsigned short len = 0;
    char buff [500];
    
    if (UsartRpiHaveData())
    {
	Led1_On();
	UsartRpiHaveDataReset();
	len = UsartRpiReadBuffer(buff, 500);

	if (len < (500 - 3))
	{
	    buff[len-1] = '\r';
	    buff[len+0] = '\n';		
	    buff[len+1] = '\0';

	    UsartBedSend(buff);

	    // check if we are in start or stop
	    if (strncmp(buff, "start,", sizeof ("start,") - 1) == 0)
	    {
		Manager_Bed_Active_On();
	    }
	    else if (strncmp(buff, "stop,", sizeof ("stop,") - 1) == 0)
	    {
		Manager_Bed_Active_Off();
	    }
	}
	Led1_Off();
    }

    if (UsartBedHaveData())
    {
	UsartBedHaveDataReset();
	len = UsartBedReadBuffer(buff, 500);

	if (len < (500 - 3))
	{
	    buff[len-1] = '\r';
	    buff[len+0] = '\n';		
	    buff[len+1] = '\0';

	    UsartRpiSend(buff);

	    // check if tablebed stops the treat
	    if (strncmp(buff, "STOP", sizeof ("STOP") - 1) == 0)
	    {
		Manager_Bed_Active_Off();
	    }
	}
    }    
}


void Manager_Top_Bed (void)
{
}


void Manager_Top_Led_Toggle (void)
{
    if (Led_Act_Top_Is_On())
	Led_Act_Top_Off();
    else
	Led_Act_Top_On();
}


void Manager_Top_Led_On (void)
{
    Led_Act_Top_On();
}


void Manager_Top_Led_Off (void)
{
    Led_Act_Top_Off();
}


void Manager_Bed_Led_Toggle (void)
{
    if (Led_Act_Bed_Is_On())
	Led_Act_Bed_Off();
    else
	Led_Act_Bed_On();
}


void Manager_Bed_Led_On (void)
{
    Led_Act_Bed_On();
}


void Manager_Bed_Led_Off (void)
{
    Led_Act_Bed_Off();
}


unsigned char Manager_Top_Is_Active (void)
{
    return Pulse_Top_Is_On();
}


void Manager_Top_Active_On (void)
{
    Pulse_Top_On();
}


void Manager_Top_Active_Off (void)
{
    Pulse_Top_Off();    
}


unsigned char Manager_Bed_Is_Active (void)
{
    return Pulse_Bed_Is_On();
}


void Manager_Bed_Active_On (void)
{
    Pulse_Bed_On();
}


void Manager_Bed_Active_Off (void)
{
    Pulse_Bed_Off();    
}


void Manager_Timeouts (void)
{
    if (manager_top_led_timer)
        manager_top_led_timer--;
    else
    {
	// Manager_Top_Led_Toggle();
	if (Manager_Top_Is_Active())
	    Manager_Top_Led_On();
	else
	    Manager_Top_Led_Off();
    }

    if (manager_bed_led_timer)
        manager_bed_led_timer--;
    else
    {
	// Manager_Bed_Led_Toggle();
	if (Manager_Bed_Is_Active())
	    Manager_Bed_Led_On();
	else
	    Manager_Bed_Led_Off();
    }
}

//---- end of file ----//
