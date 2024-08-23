

#ifndef FIRE_SYSTEM_H_
#define FIRE_SYSTEM_H_

extern u8*pass;
extern u8 in_pass[20];
extern u8 count;
typedef enum{
	WRONG,
	CORRECT
	}Password_Status_type;
	
	

void get_pass(void);
u8 get_length(u8*string);
Password_Status_type check_pass(u8* Password,u8* IN_Password);
void Fire_System(void);



#endif /* FIRE_SYSTEM_H_ */