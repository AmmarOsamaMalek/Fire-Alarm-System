
#include "StdTypes.h"
#include "MemMap.h"
#include "Utlis.h"
#define F_CPU 8000000
#include <util/delay.h>
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "ADC_Interface.h"
#include "KeyPad_Interface.h"
#include "Sensors_Interface.h"
#include "Fire_System.h"

u8*pass = "1234";
u8 in_pass[20];
u8 count;

void get_pass(void)
{
	u8 i = 0; 
	u8 k = NO_KEY ;
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_WriteString("Enter Password : ");
	LCD_SetCursor(1,0);
	while(k != '=')
	{
		k = KEYPAD_GetKey();
		if(k >= '0' && k <= '9')
		{
			LCD_WriteChar(k);
			in_pass[i] = k;
			i++;
		}
		if(k == 'c')
		{
			LCD_ClearLoc(1,0,16);
			LCD_SetCursor(1,0);
			i = 0;
		}
	}
	in_pass[i] = 0;
	
}

u8 get_length(u8*string)
{
	u8 i;
	for(i = 0;string[i];i++);
	
	return i;
}

Password_Status_type check_pass(u8* Password,u8* IN_Password)
{
	u8 l1 = get_length(Password);
	u8 l2 = get_length(IN_Password);
	if(l1 == l2)
	{
		for(u8 i = 0;i<l1;i++)
		{
			if(Password[i] != IN_Password[i])
			return WRONG;
		}
		return CORRECT;
	}
	else
	return WRONG;
}

void Fire_System(void)
{
	Password_Status_type s;
	count = 3;
	u16 T = Temp_Read();
	u16 smoke = POT_Read(CH_7);
	u8*Status[3] = {"Fine","Heat","Fire"};
	LCD_SetCursor(0,0);
	LCD_WriteString("T=");
	LCD_WriteNumber(T/10);
	LCD_WriteString(".");
	LCD_WriteNumber(T%10);
	LCD_WriteString("   ");
	LCD_SetCursor(0,8);
	LCD_WriteString("S=");
	LCD_WriteNumber(smoke);
	LCD_WriteString("%");
	LCD_WriteString("     ");
	LCD_SetCursor(1,0);
	if(T<450)
	{
		LCD_WriteString(Status[0]);
		LCD_SetCursor(1,7);
		LCD_WriteString("Fan:OFF");
		Dio_WritePin(PINB2,LOW);
		Dio_WritePin(PINB0,LOW);
		Dio_WritePin(PINB1,LOW);
		Dio_WritePin(PINB3,LOW);
	}
	else if(T>500 && smoke<45)
	{
		LCD_WriteString(Status[1]);
		LCD_SetCursor(1,7);
		LCD_WriteString("Fan:OFF");
		Dio_WritePin(PINB2,HIGH);
		Dio_WritePin(PINB0,LOW);
		Dio_WritePin(PINB1,LOW);
		Dio_WritePin(PINB3,LOW);
	}
	else if(T>500 && smoke>50)
	{
		LCD_WriteString(Status[2]);
		LCD_SetCursor(1,7);
		LCD_WriteString("Fan:ON ");
		Dio_WritePin(PINB0,HIGH);
		Dio_WritePin(PINB1,HIGH);
		Dio_WritePin(PINB2,LOW);
		Dio_WritePin(PINB3,HIGH);
		_delay_ms(1000);
		get_pass();
		s = check_pass(pass,in_pass);
		if(s == CORRECT)
		{
			Dio_WritePin(PINB3,LOW);
			LCD_Clear();
			LCD_WriteString("Correct Password");
			_delay_ms(1000);
			LCD_SetCursor(1,0);
			LCD_WriteString("Restarting");
			_delay_ms(1000);
			LCD_Clear();
		}
        else if (s == WRONG)
		{
			count--;
			LCD_Clear();
			LCD_WriteString("Wrong Password!!!");
			_delay_ms(500);
			LCD_SetCursor(1,0);
			LCD_WriteString("Tries Left :");
			LCD_WriteNumber(count);
			_delay_ms(1000);
			LCD_Clear();
			while(1)
			{
				get_pass();
				s = check_pass(pass,in_pass);
				if(s == WRONG)
				{
					count--;
					if(count == 0)
					{
						LCD_Clear();
						LCD_WriteString("Wrong Password!!!");
						_delay_ms(500);
						LCD_SetCursor(1,0);
						LCD_WriteString("Shutting Down!!!");
						_delay_ms(1000);
						LCD_Clear();
						break;
					}
					else
					{
						LCD_Clear();
						LCD_WriteString("Wrong Password!!!");
						_delay_ms(500);
						LCD_SetCursor(1,0);
						LCD_WriteString("Tries Left :");
						LCD_WriteNumber(count);
						_delay_ms(1000);
						LCD_Clear();
					}
					
				}
				else if(s == CORRECT)
				{
					Dio_WritePin(PINB3,LOW);
					LCD_Clear();
					LCD_WriteString("Correct Password");
					_delay_ms(1000);
					LCD_SetCursor(1,0);
					LCD_WriteString("Restarting");
					_delay_ms(1000);
					LCD_Clear();
					count = 3;
					break;
				}
				
			}
		}
		
	}
}

