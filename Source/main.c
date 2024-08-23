
#include "StdTypes.h"
#include "MemMap.h"
#include "Utlis.h"
#define f_cpu 80
#define F_CPU 8000000
#include <util/delay.h>
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "ADC_Interface.h"
#include "Motor_Interface.h"
#include "KeyPad_Interface.h"
#include "Sensors_Interface.h"
#include "Fire_System.h"
/*****************************************************************************/	
// u8*pass = "1234";
// u8 in_pass[20];
// u8 count;
int main(void)
{
	DIO_Init();
	LCD_Init();
	ADC_Init(VREF_VCC,ADC_SCALER_64);
   KEYPAD_Init();
   LCD_SetCursor(0,0);
   LCD_WriteString("Fire System");
   _delay_ms(1000);
   LCD_Clear();
   Dio_WritePin(PINB0,LOW);
   Dio_WritePin(PINB1,LOW);
   Dio_WritePin(PINB2,LOW);
   Dio_WritePin(PINB3,LOW);
    while (1) 
    {
		_delay_ms(100);
		Fire_System();
    }
}

