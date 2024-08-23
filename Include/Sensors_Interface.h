

#ifndef SENSORS_INTERFACE_H_
#define SENSORS_INTERFACE_H_

#define LM35_CH     0
#define MPX4115_CH  7

u16 Map(u16 value,u16 in_max,u16 in_min,u16 out_max,u16 out_min);
u16 POT_Read(ADC_Channel_type channel);
u16 Temp_Read(void);
u16 Pressure_Read(void);


#endif /* SENSORS_INTERFACE_H_ */