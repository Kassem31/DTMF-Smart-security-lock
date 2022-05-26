/*
 * Final_Project.c
 *
 * Created: 5/25/2022 7:51:32 AM
 * Author : Mahmoud
 */ 
#include "main_config.h"
#include "LCD.h"
#include "EEPROM.h"
#include "keypad_driver.h"
#include "LED.h"
#include "Dio2.h"
#include <avr/io.h>
#define F_CPU_11059200UL
#include <util/delay.h>
#include <avr/interrupt.h>

uint8 key_pressed;
uint8 login_mode;
uint8 flag;
void timer1_init()              
{
	TCCR1B = (1<<CS10) | (1<<CS12);
	TCCR1A = 0X00;
	//OCR1A = 1562;
	TCNT1 = 63974;
	TIMSK = (1<<TOIE1);
	//sei();
}
void timer1_stop()         
{
	TCCR1B &= ~(1<<CS10);
	TCCR1B &= ~(1<<CS12);
}

uint8 ComparePass(const uint8* pass1,const uint8* pass2,const uint8 size)
{
	uint8 pin_counter=0;
	uint8 ret_value = TRUE;
	while (pin_counter<size)
	{
		if (*(pass1+pin_counter)!=*(pass2+pin_counter))
		{
			ret_value= FALSE;
			break;
		}
		pin_counter++;
	}
	return ret_value;
}

void Enter_Pass()
{
	key_pressed = NOT_PRESSED;
	uint8 pass_counter=0;
	uint8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
	uint8 stored_pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
	
	while(login_mode!=ADMIN)// while admin enters wrong password
	{
		key_pressed = NOT_PRESSED;
		LCD_clearscreen();
		LCD_vSend_string("Enter Pass:");
		_delay_ms(50);
		pass_counter=0;
		while(pass_counter<PASS_SIZE)
		{
			while (key_pressed == NOT_PRESSED)
			{
				key_pressed = keypad_u8check_press();
			}
			pass[pass_counter]=key_pressed;
			LCD_vSend_char(key_pressed);
			_delay_ms(CHARACTER_PREVIEW_TIME);
			LCD_movecursor(1,12+pass_counter);
			LCD_vSend_char(PASSWORD_SYMBOL);
			_delay_ms(20);
			pass_counter++;
			key_pressed = NOT_PRESSED;-------------------********-------------------------**//***************
			EEPROM_vReadBlockFromAddress(EEPROM_ADMIN_ADDRESS,stored_pass,PASS_SIZE);
			/*compare passwords*/
			if ((ComparePass(pass,stored_pass,pass_counter)) == TRUE)  // correct pass
			{
				login_mode = ADMIN;
			}
			else                                                   // wrong pass
			{
				login_mode = NO_MODE;
				LCD_clearscreen();
				LCD_vSend_string("Wrong Pass");
				_delay_ms(1000);
				LCD_clearscreen();
				break;
			}
		}
		if (login_mode==ADMIN)
		{
			LCD_clearscreen();
			LCD_vSend_string("correct pass");
			_delay_ms(500);
		}
	}
	
}

void Set_Pass()
{
	TCNT1=63974;
	LCD_clearscreen();
	//enter programming mode
	LCD_vSend_string("Set pass:");
	uint8 pass_counter=0;
	uint8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
	while (pass_counter<PASS_SIZE)
	{
		key_pressed = NOT_PRESSED;
		while (key_pressed == NOT_PRESSED)
		{
			key_pressed = keypad_u8check_press();
		}
		pass[pass_counter]=key_pressed;
		LCD_vSend_char(key_pressed);
		_delay_ms(CHARACTER_PREVIEW_TIME);
		LCD_movecursor(1,10+pass_counter);
		LCD_vSend_char(PASSWORD_SYMBOL);
		_delay_ms(50);
		pass_counter++;
	}
	EEPROM_vWriteBlockToAddress(EEPROM_ADMIN_ADDRESS,pass,PASS_SIZE);
	EEPROM_vWriteByteToAddress(ADMIN_PASS_STATUS_ADDRESS,PASS_SET);
	LCD_clearscreen();
	LCD_vSend_string("Pass Saved");
	_delay_ms(500);
	LCD_clearscreen();
}

int main(void)
{
	Dio_PinSetDirection(D,2,PinInput);
	Dio_PinSetDirection(D,3,PinInput);
	
	login_mode = NO_MODE; //Store the current user mode admin or guest or not logged in
	key_pressed = NOT_PRESSED;//
	/*****************  INITIALIZE  ***********************/
	LCD_vInit();
	keypad_vInit();
	
	GICR=1<<INT0 | 1<<INT1 | 1<<INT2;
	MCUCR|= 1<<ISC01 | 1<<ISC11 | 1<<ISC10;
	MCUCSR|=1<<ISC2;
	sei();
	flag=0;
	while (1)
	
	{
	}
}
ISR(INT0_vect)           //on falling
{
	sei();
	flag=1;
	timer1_init();
}
ISR(INT1_vect)         //on rising
{
	//exit programming mode
	sei();
	timer1_stop();
	LCD_clearscreen();
	LCD_movecursor(1,1);
	Enter_Pass();
}
ISR(TIMER1_OVF_vect)
{
	sei();
	if (flag==1)
	{
		flag=0;
		Set_Pass();
	}
}


