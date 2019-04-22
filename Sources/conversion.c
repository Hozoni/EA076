#include "conversion.h"
#include "Temp.h"
#include "derivative.h" /* include peripheral declarations */

void inicializacao(void) {
	SYST_RVR &= 0xFF000000;
	SYST_RVR |= 0x00033334;  // colocar frequencia desejada

	SYST_CSR |= 0xFF000007; //


}

void SysTick_Handler(void) {
  extern volatile int i;
  i++;
}

int conversion(unsigned int value )
{
  int temp = (value*3300/65535) - 600;
  return temp;
}
