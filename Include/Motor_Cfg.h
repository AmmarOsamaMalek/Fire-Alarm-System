

#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

/************* pin config******************/



#define   M1_IN1   PINC0
#define   M1_IN2   PIND5
#define   M1_EN   PIND0

#define   M2_IN1   PINC0
#define   M2_IN2   PIND5
#define   M2_EN   PIND0

#define   M3_IN1   PINC0
#define   M3_IN2   PIND5
#define   M3_EN   PIND0

#define   M4_IN1   PINC0
#define   M4_IN2   PIND5
#define   M4_EN   PIND0


#ifdef  MOTOR_PROG

DIO_Pin_type MotorPinsArray[TOTAL_MOTORS][TOTAL_MOTOR_PINS]={
	             /* IN1   IN2     EN  */
	/* motor 1*/{ M1_IN1,M1_IN2,M1_EN},
	/* motor 2*/{ M2_IN1,M2_IN2,M2_EN},
	/* motor 3*/{ M1_IN1,M1_IN2,M1_EN},
	/* motor 4*/{ M1_IN1,M1_IN2,M1_EN},
};

#endif





#endif /* MOTOR_CFG_H_ */