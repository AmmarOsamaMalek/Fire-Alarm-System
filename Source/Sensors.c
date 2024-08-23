

#include "StdTypes.h"
#include "ADC_Interface.h"
#include "Sensors_Interface.h"

u16 Map(u16 value,u16 in_max,u16 in_min,u16 out_max,u16 out_min)
{
	u16 n = ((u32)value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	return n;
}

u16 POT_Read(ADC_Channel_type channel)
{
	u16 P_Read = 0;
	P_Read = Map(ADC_Read(channel),1023,0,100,0);
	return P_Read;
}

u16 Temp_Read(void)
{
	u16 volt = ADC_Volt_Read(LM35_CH);
	u16 temp = volt;
	return temp;   /* Temperature in C*10 */
}


u16 Pressure_Read(void)
{
	u16 ADC = ADC_Read(MPX4115_CH);
	u16 pressure = ((u32)1000*(ADC-55))/921 + 150;
	return pressure;
}