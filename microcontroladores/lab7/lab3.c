#include <stm32f10x.h>

#define OUTPUT 0x03
#define INPUT	0x04

void ioPinConfig(GPIO_TypeDef *portName, uint8_t pinNum, uint8_t configValue);
uint8_t GPIOWrite(GPIO_TypeDef* GPIOx, uint16_t Pin, uint8_t Level);
uint8_t GPIORead(GPIO_TypeDef* GPIOx, uint16_t Pin);
void delay();


int main() {
	uint32_t color = 13;
  RCC->APB2ENR |= 0xFC; /* Enable GPIO ports clocks */

  GPIOB->CRH = 0x44444844; // pull-up PB10
  GPIOB->ODR |= (1<<10); //set bit 10 of ODR to pull-up
  GPIOC->CRH = 0x44344444; /* PC13 as output */
	ioPinConfig(GPIOC,13,OUTPUT);
  ioPinConfig(GPIOC,14,OUTPUT);
  ioPinConfig(GPIOC,15,OUTPUT);
  while(1) {		
    if((GPIOB->IDR & (1<<10)) != 0){ /* is PB10 high	*/
		
	}
    else
		{
			color = color + 1;
		if(color > 15){
			color = 13;
		}
	}
		
  GPIOWrite(GPIOC, color, 1);
  delay();
  GPIOWrite(GPIOC, color, 0);
	delay();
	}
	
}


void ioPinConfig(GPIO_TypeDef *portName, uint8_t pinNum, uint8_t configValue)
{
    if(pinNum < 8)
        portName->CRL = (portName->CRL&(~(0xF<<(4*pinNum))))|(configValue<<(4*pinNum));
    else
        portName->CRH = (portName->CRH&(~(0xF<<(4*(pinNum-8)))))|(configValue<<(4*(pinNum-8)));
}

uint8_t GPIOWrite(GPIO_TypeDef* GPIOx, uint16_t Pin, uint8_t Level)
{
    if(Level == 1){
        GPIOC->ODR |= (1 << Pin);
        return 1;
    }
    else if(Level == 0){
        GPIOC->ODR &= ~(1 << Pin);
        return 0;
    }
    else{
        return 2;
    }
}

// Função para identificar o nível lógico dos pinos digitais de entrada
// Entradas: Porto de entrada (GPIOx), Pino(0 a 15) e Nível(0 ou 1)
// Saída: Nível lógico de entrada do pino (0 ou 1)
uint8_t GPIORead(GPIO_TypeDef* GPIOx, uint16_t Pin){
    if((GPIOx->IDR & (1 << Pin)) != 0){
        return 1;
    }
    else{
        return 0;
    }
}

// Função delay usando um timer
// Entrada: tempo em milissegundos
void delay()
{
	SysTick->LOAD = 7199999;		/* STRELOAD = 7,199,999 */
	SysTick->CTRL = 0x05;		    /* Clock source = AHB clock, Enable = 1 */
	while((SysTick->CTRL&(1<<16)) == 0); /* wait until the COUNT flag is set */
	SysTick->CTRL = 0x00;		    /* stop the SysTick timer */
}
