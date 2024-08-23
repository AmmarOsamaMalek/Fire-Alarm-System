
#include "StdTypes.h"
#include "MemMap.h"
#include "Utlis.h"
#include "ADC_Interface.h"
#define F_CPU 8000000
#include <util/delay.h>


void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
	             /* V_ref */
switch(vref)
{
	case VREF_AREF:
	CLEAR_BIT(ADMUX,REFS1);
	CLEAR_BIT(ADMUX,REFS0);
	break;
	case VREF_VCC:
	CLEAR_BIT(ADMUX,REFS1);
	SET_BIT(ADMUX,REFS0);
	break;
	case VREF_256:
	SET_BIT(ADMUX,REFS1);
	SET_BIT(ADMUX,REFS0);
	break;
}
/********** clock *********************/
 ADCSRA = ADCSRA & 0xf8;
 scaler = scaler & 0x07;
 ADCSRA = ADCSRA | scaler;
 
/*********** Enable *******************/
SET_BIT(ADCSRA,ADEN);
}

u16 ADC_Read(ADC_Channel_type channel)
{
	u16 ADC_Reading = 0;
	/* select ch using mux*/
	ADMUX = ADMUX & 0xE0;
	channel = channel & 0x07;
	ADMUX = ADMUX | channel;
	/* start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*wait until end */
	while(READ_BIT(ADCSRA,ADSC));
	/* get reading from 2 registers*/
	ADC_Reading = (u16)(ADCL) | ((u16)ADCH << 8);
	return ADC_Reading;
}


u16 ADC_Volt_Read(ADC_Channel_type channel)
{
	u16 volt = (ADC_Read(channel)*(u32)5000)/1024;
	return volt; /* In mV */
}
