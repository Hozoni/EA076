/* ###################################################################
**     Filename    : main.c
**     Project     : Roteiro 1
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-03-14, 09:25, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Temp.h"
#include "AdcLdd1.h"
#include "RTC1.h"
#include "PC.h"
#include "ASerialLdd1.h"
#include "ESP.h"
#include "ASerialLdd2.h"
#include "UTIL1.h"
#include "MCUC1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "conversion.h"
LDD_TDeviceData *MyRTCPtr;
LDD_RTC_TTime Time;
/* Defines */
#define CR 0x0D
#define LF 0x0A

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

/*Global variables */
volatile int PC = 0;
volatile int ESP = 0;
volatile int i = 0;

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  char c = '\0';
  int n = 0;
  unsigned int value = 0;
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  MyRTCPtr = RTC1_Init((LDD_TUserData *)NULL, FALSE);        /* Initialize the device, preserve time settings */
  inicializacao();  /* initiates SysTick */

  for(;;)
  {
	  if(i >= 1)
    {
      i--;
      n = 0;
      /* get adc value */
      Temp_Measure(TRUE);
      Temp_GetValue(&value);
      temp = conversion(value);
      /* get time */
      RTC1_GetTime(MyRTCPtr, &Time);
      /* create buffer */
      buffer[0] = (Time.Hour/10) + '0';
      buffer[1] = (Time.Hour%10) + '0';
      buffer[3] = ':';
      buffer[4] = (Time.Minute/10) + '0';
      buffer[5] = (Time.Minute%10) + '0';
      buffer[6] = ':';
      buffer[7] = (Time.Second/10) + '0';
      buffer[8] = (Time.Second%10) + '0';
      buffer[9] = ' ';
      buffer[10] = (temp/1000) + '0';
      buffer[11] = ((temp%1000)/100) + '0';
      buffer[12] = ((temp%100)/10) + '0';
      buffer[13] = '.';
      buffer[14] = (temp%10) + '0';
      buffer[15] = '\0';

      /* send to PC */
      while (buffer[n] != '\0')
      {
        PC_SendChar(buffer[n]);
        n++;
      }

    }

  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
