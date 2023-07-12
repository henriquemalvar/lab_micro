#include <stm32f10x.h>

#define OUTPUT 0x03
#define INPUT	0x04

void delay_ms(uint16_t t);
void ioPinConfig(GPIO_TypeDef *portName, uint8_t pinNum, uint8_t configValue);

int main()
{
	RCC->APB2ENR |= 0xFC; //Enable GPIO ports clocks 
	
	ioPinConfig(GPIOC,13,OUTPUT);
	while(1)
	{		
		GPIOC->ODR ^= (1<<13);
		delay_ms(1000);
	}
}

void ioPinConfig(GPIO_TypeDef *portName, uint8_t pinNum, uint8_t configValue)
{
	if(pinNum < 8)
		portName->CRL = (portName->CRL&(~(0xF<<(4*pinNum))))|(configValue<<(4*pinNum));
	else
		portName->CRH = (portName->CRH&(~(0xF<<(4*(pinNum-8)))))|(configValue<<(4*(pinNum-8)));
}

void delay_ms(uint16_t t)
{
	volatile unsigned long l = 0;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 6000; l++)
		{
		}
}