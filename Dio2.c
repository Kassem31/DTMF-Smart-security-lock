/*
 * Dio.c
 *
 * Created: 10/15/2021 7:49:12 PM
 *  Author: Mahmoud
 */ 
#include <avr/io.h>
#include "Dio2.h"



/*******************************************************************************************/
ReturnValueType Dio_PortSetDirection (PortType port,uint8 DirectionValue)
{
	ReturnValueType ReturnValue = OK ;
	switch (port)
	{
		case A:
			DDRA = DirectionValue;
			break;
		case B:
			DDRB = DirectionValue;
			break;
		case C:
			DDRC = DirectionValue;
			break;
		case D:
			DDRD = DirectionValue;
			break;
		default:
			ReturnValue = NOK ; 
			break;	
	}
	asm	volatile ("nop");  
	return ReturnValue;
}
ReturnValueType Dio_PinSetDirection (PortType port , uint8 PinNumber,PinDirectionType PinDirection)
{
	ReturnValueType  ReturnValue = OK;
	switch (port)
	{
		case A:
		if (PinDirection == PinInput) CLR_BIT(DDRA,PinNumber);
		else if (PinDirection == PinOutput) SET_BIT(DDRA,PinNumber);
		else ReturnValue = NOK ; 
		
		break;
		case B:
		if (PinDirection == PinInput) CLR_BIT(DDRB,PinNumber);
		else if (PinDirection == PinOutput) SET_BIT(DDRB,PinNumber);
		else ReturnValue = NOK ;
		break;
		case C:
		if (PinDirection == PinInput) CLR_BIT(DDRC,PinNumber);
		else if (PinDirection == PinOutput) SET_BIT(DDRC,PinNumber);
		else ReturnValue = NOK ;
		break;
		case D:
		if (PinDirection == PinInput) CLR_BIT(DDRD,PinNumber);
		else if (PinDirection == PinOutput) SET_BIT(DDRD,PinNumber);
		else ReturnValue = NOK ;
		break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop"); 
	return ReturnValue;
}
ReturnValueType Dio_GroupSetDirection(PortType port,uint8 GroupMask, uint8 GroupDirection)
{
	ReturnValueType ReturnValue = OK;
	switch(port)
	{
		case A:
			DDRA = (GroupDirection & GroupMask) | (DDRA & ~GroupMask) ;
			break;
		case B:
			DDRB = (GroupDirection & GroupMask) | (DDRB & ~GroupMask) ;
			break;
		case C:
			DDRC = (GroupDirection & GroupMask) | (DDRC & ~GroupMask) ;
			break;
		case D:
			DDRD = (GroupDirection & GroupMask) | (DDRD & ~GroupMask) ;
			break;
		default:
			 ReturnValue= NOK;		
	}
	asm	volatile ("nop"); 
	return ReturnValue;
}
ReturnValueType Dio_PortFlipDirection(PortType port)
{
	ReturnValueType ReturnValue = OK ;
	switch (port)
	{
		case A:
		DDRA ^= 0xFF;
		break;
		case B:
		DDRB ^= 0xFF;
		break;
		case C:
		DDRC ^= 0xFF;
		break;
		case D:
		DDRD ^= 0xFF;
		break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop");
	return ReturnValue;
}
ReturnValueType Dio_PinFlipDirection(PortType port,uint8 PinNumber)
{
ReturnValueType  ReturnValue = OK;
	switch (port)
	{
		case A:
			TOG_BIT(DDRA,PinNumber);
		break;
		case B:
			TOG_BIT(DDRB,PinNumber);
		break;
		case C:
			TOG_BIT(DDRC,PinNumber);
		break;
		case D:
			TOG_BIT(DDRD,PinNumber);
		break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop"); 
	return ReturnValue;	
}
ReturnValueType Dio_GroupFlipDirection(PortType port,uint8 GroupMask)
{
ReturnValueType ReturnValue = OK;
	switch(port)
	{
		case A:
			DDRA = ((DDRA ^ 0xFF) & GroupMask) | (DDRA & ~GroupMask) ;
			break;
		case B:
			DDRB = ((DDRB ^ 0xFF) & GroupMask) | (DDRB & ~GroupMask) ;
			break;
		case C:
			DDRC = ((DDRC ^ 0xFF) & GroupMask) | (DDRC & ~GroupMask) ;
			break;
		case D:
			DDRD = ((DDRD ^ 0xFF) & GroupMask) | (DDRD & ~GroupMask) ;
			break;
		default:
			 ReturnValue= NOK;		
	}
	asm	volatile ("nop"); 
	return ReturnValue;
	
}
/*******************************************************************************************/
ReturnValueType Dio_PortWrite(PortType port,uint8 WriteValue)
{
	ReturnValueType ReturnValue = OK ;
	switch (port)
	{
		case A:
		PORTA = WriteValue;
		break;
		case B:
		PORTB = WriteValue;
		break;
		case C:
		PORTC = WriteValue;
		break;
		case D:
		PORTD = WriteValue;
		break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop"); 
	return ReturnValue;
}
ReturnValueType Dio_PinWrite(PortType port,uint8 PinNumber ,PinStateType PinState )
{
	ReturnValueType  ReturnValue = OK;
	switch (port)
	{
		case A:
		if (PinState == PinLow) CLR_BIT(PORTA,PinNumber);
		else if (PinState == PinHigh) SET_BIT(PORTA,PinNumber);
		else ReturnValue = NOK ;
		
		break;
		case B:
		if (PinState == PinLow) CLR_BIT(PORTB,PinNumber);
		else if (PinState == PinHigh) SET_BIT(PORTB,PinNumber);
		else ReturnValue = NOK ;
		break;
		case C:
		if (PinState == PinLow) CLR_BIT(PORTC,PinNumber);
		else if (PinState == PinHigh) SET_BIT(PORTC,PinNumber);
		else ReturnValue = NOK ;
		break;
		case D:
		if (PinState == PinLow) CLR_BIT(PORTD,PinNumber);
		else if (PinState == PinHigh) SET_BIT(PORTD,PinNumber);
		else ReturnValue = NOK ;
		break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop"); 
	return ReturnValue;
}
ReturnValueType Dio_GroupWrite(PortType port , uint8 GroupMask, uint8 WriteValue )
{
	ReturnValueType ReturnValue = OK;
	switch(port)
	{
		case A:
		PORTA = (WriteValue & GroupMask) | (PORTA & ~GroupMask) ;
		break;
		case B:
		PORTB = (WriteValue & GroupMask) | (PORTB & ~GroupMask) ;
		break;
		case C:
		PORTC = (WriteValue & GroupMask) | (PORTC & ~GroupMask) ;
		break;
		case D:
		PORTD = (WriteValue & GroupMask) | (PORTD & ~GroupMask) ;
		break;
		default:
		ReturnValue= NOK;
		break;
	}
	asm	volatile ("nop"); 
	return ReturnValue;
}
ReturnValueType Dio_PortFlip(PortType port)
{
	ReturnValueType ReturnValue = OK ;
	switch (port)
	{
		case A:
		PORTA ^= 0xFF;
		break;
		case B:
		PORTB ^= 0xFF;
		break;
		case C:
		PORTC ^= 0xFF;
		break;
		case D:
		PORTD ^= 0xFF;
		break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop");
	return ReturnValue;

}
ReturnValueType Dio_PinFlip(PortType port,uint8 PinNumber)
{
	ReturnValueType  ReturnValue = OK;
	switch (port)
	{
		case A:
			ToggleBit(PORTA,PinNumber);
		break;
		case B:
			ToggleBit(PORTB,PinNumber);
		break;
		case C:
			ToggleBit(PORTC,PinNumber);
		break;
		case D:
			ToggleBit(PORTD,PinNumber);
		break;
		default:
			ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop");
	return ReturnValue;
	
}
ReturnValueType Dio_GroupFlip(PortType port , uint8 GroupMask)
{
ReturnValueType ReturnValue = OK;
	switch(port)
	{
		case A:
			PORTA = ((PORTA ^ 0xFF) & GroupMask) | (PORTA & ~GroupMask) ;
			break;
		case B:
			PORTB = ((PORTB ^ 0xFF) & GroupMask) | (PORTB & ~GroupMask) ;
			break;
		case C:
			PORTC = ((PORTC ^ 0xFF) & GroupMask) | (PORTC & ~GroupMask) ;
			break;
		case D:
			PORTD = ((PORTD ^ 0xFF) & GroupMask) | (PORTD & ~GroupMask) ;
			break;
		default:
			 ReturnValue= NOK;		
	}
	asm	volatile ("nop"); 
	return ReturnValue;
	
}
/*******************************************************************************************/
ReturnValueType Dio_PortRead(PortType port, uint8 * ReadValuePtr)
{
	ReturnValueType ReturnValue = OK ;
	switch (port)
	{
		case A:
		*ReadValuePtr = PINA ;
		break;
		case B:
		*ReadValuePtr = PINB ;
		break;
		case C:
		*ReadValuePtr = PINC ;
		break;
		case D:
		*ReadValuePtr = PIND ;
		break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop"); 
	return ReturnValue;
}
ReturnValueType Dio_PinRead (PortType port , uint8 PinNumber,PinStateType* PinState)
{
	ReturnValueType  ReturnValue = OK;
	switch (port)
	{
		case A:
			*PinState= Read_bIT(PINA,PinNumber);
			break;
		case B:
			*PinState= Read_bIT(PINB,PinNumber);
			break;
		case C:
			*PinState= Read_bIT(PINC,PinNumber);
			break;
		case D:
			*PinState= Read_bIT(PIND,PinNumber);
			break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop"); 
	return ReturnValue;
}
ReturnValueType Dio_GroupRead(PortType port , uint8 GroupMask ,uint8 * ReadValuePtr)
{
	ReturnValueType ReturnValue = OK;
	switch(port)
	{
		case A:
			*ReadValuePtr = (PINA & GroupMask) ;
			break;
		case B:
			*ReadValuePtr = (PINB & GroupMask) ;
			break;
		case C:
			*ReadValuePtr = (PINC & GroupMask) ;
			break;
		case D:
			*ReadValuePtr = (PIND & GroupMask) ;
			break;
		default:
		ReturnValue= NOK;
		break;
	}
	asm	volatile ("nop"); 
	return ReturnValue;
}
/*******************************************************************************************/
ReturnValueType Dio_PortPullupState (PortType port ,uint8 PullupState )
{
	ReturnValueType ReturnValue = OK ;
	switch (port)
	{
		case A:
		PORTA = PullupState;
		break;
		case B:
		PORTB = PullupState;
		break;
		case C:
		PORTC = PullupState;
		break;
		case D:
		PORTD = PullupState;
		break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop"); 
	return ReturnValue;
}
ReturnValueType Dio_PinPullupState (PortType port ,uint8 PinNumber ,PullupStateType PullupState)
{
	ReturnValueType  ReturnValue = OK;
	switch (port)
	{
		case A:
		if (PullupState == Deactive) CLR_BIT(PORTA,PinNumber);
		else if (PullupState == Active) SET_BIT(PORTA,PinNumber);
		else ReturnValue = NOK ;
		
		break;
		case B:
		if (PullupState == Deactive) CLR_BIT(PORTB,PinNumber);
		else if (PullupState == Active) SET_BIT(PORTB,PinNumber);
		else ReturnValue = NOK ;
		break;
		case C:
		if (PullupState == Deactive) CLR_BIT(PORTC,PinNumber);
		else if (PullupState == Active) SET_BIT(PORTC,PinNumber);
		else ReturnValue = NOK ;
		break;
		case D:
		if (PullupState == Deactive) CLR_BIT(PORTD,PinNumber);
		else if (PullupState == Active) SET_BIT(PORTD,PinNumber);
		else ReturnValue = NOK ;
		break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop"); 
	return ReturnValue;
}
ReturnValueType Dio_GroupPullupState (PortType port , uint8 GroupMask, uint8 PullupState)
{
	ReturnValueType ReturnValue = OK;
	switch(port)
	{
		case A:
		PORTA = (PullupState & GroupMask) | (PORTA & ~GroupMask) ;
		break;
		case B:
		PORTB = (PullupState & GroupMask) | (PORTB & ~GroupMask) ;
		break;
		case C:
		PORTC = (PullupState & GroupMask) | (PORTC & ~GroupMask) ;
		break;
		case D:
		PORTD = (PullupState & GroupMask) | (PORTD & ~GroupMask) ;
		break;
		default:
		ReturnValue= NOK;
		break;
	}
	asm	volatile ("nop"); 
	return ReturnValue;
}
ReturnValueType Dio_PortPullupStateFlip(PortType port )
{
	ReturnValueType ReturnValue = OK ;
	switch (port)
	{
		case A:
		PORTA ^= 0xFF;
		break;
		case B:
		PORTB ^= 0xFF;
		break;
		case C:
		PORTC ^= 0xFF;
		break;
		case D:
		PORTD ^= 0xFF;
		break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop");
	return ReturnValue;
	
}
ReturnValueType Dio_PinPullupStateFlip(PortType port,uint8 PinNumber )
{
	ReturnValueType  ReturnValue = OK;
	switch (port)
	{
		case A:
			TOG_BIT(PORTA,PinNumber);
		break;
		case B:
			TOG_BIT(PORTB,PinNumber);
		break;
		case C:
			TOG_BIT(PORTC,PinNumber);
		break;
		case D:
			TOG_BIT(PORTD,PinNumber);
		break;
		default:
		ReturnValue = NOK ;
		break;
	}
	asm	volatile ("nop");
	return ReturnValue;	
}
ReturnValueType Dio_GroupPullupStateFlip (PortType port , uint8 GroupMask)
{
	ReturnValueType ReturnValue = OK;
	switch(port)
	{
		case A:
		PORTA = ((PORTA ^ 0xFF) & GroupMask) | (PORTA & ~GroupMask) ;
		break;
		case B:
		PORTB = ((PORTB ^ 0xFF) & GroupMask) | (PORTB & ~GroupMask) ;
		break;
		case C:
		PORTC = ((PORTC ^ 0xFF) & GroupMask) | (PORTC & ~GroupMask) ;
		break;
		case D:
		PORTD = ((PORTD ^ 0xFF) & GroupMask) | (PORTD & ~GroupMask) ;
		break;
		default:
		ReturnValue= NOK;
		break;
	}
	asm	volatile ("nop");
	return ReturnValue;
	
}