#include <stm32f10x.h>

#define OUTPUT 0x03
#define INPUT	0x04

void delay_ms(uint16_t t);
void ioPinConfig(GPIO_TypeDef *portName, uint8_t pinNum, uint8_t configValue);
uint8_t GPIOWrite(GPIO_TypeDef* GPIOx, uint16_t Pin, uint8_t Level);

int main()
{
    RCC->APB2ENR |= 0xFC; //Enable GPIO ports clocks 
    
    ioPinConfig(GPIOC,13,OUTPUT);
    ioPinConfig(GPIOC,14,OUTPUT);
    ioPinConfig(GPIOC,15,OUTPUT);
    while(1)
    {		
        GPIOWrite(GPIOC, 13, 1);
        delay_ms(350);
        GPIOWrite(GPIOC, 13, 0);
        
        GPIOWrite(GPIOC, 14, 1);
        delay_ms(350);
        GPIOWrite(GPIOC, 14, 0);
        
        GPIOWrite(GPIOC, 15, 1);
        delay_ms(350);
        GPIOWrite(GPIOC, 15, 0);
        
        GPIOWrite(GPIOC, 13, 1);
        GPIOWrite(GPIOC, 14, 1);
        GPIOWrite(GPIOC, 15, 1);
        delay_ms(350);
        
        GPIOWrite(GPIOC, 15, 0);
        delay_ms(350);
        
        GPIOWrite(GPIOC, 15, 1);
        GPIOWrite(GPIOC, 14, 0);
        delay_ms(350);
        
        GPIOWrite(GPIOC, 14, 1);
        GPIOWrite(GPIOC, 13, 0);
        delay_ms(350);
        
        GPIOWrite(GPIOC, 14, 0);
        GPIOWrite(GPIOC, 13, 0);
        GPIOWrite(GPIOC, 15, 0);
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
        for(l = 0; l < 5000; l++)
        {
        }
}

uint8_t GPIOWrite(GPIO_TypeDef* GPIOx, uint16_t Pin, uint8_t Level)
{
    if(Level == 1){
        GPIOx->BSRR = (1 << Pin);
        return 1;
    }
    else if(Level == 0){
        GPIOx->BRR = (1 << Pin);
        return 0;
    }
    else{
        return 2; // Invalid level value
    }
}