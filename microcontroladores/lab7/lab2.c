#include <stm32f10x.h>

#define OUTPUT 0x03
#define INPUT	0x04

void ioPinConfig(GPIO_TypeDef *portName, uint8_t pinNum, uint8_t configValue);
uint8_t GPIOWrite(GPIO_TypeDef* GPIOx, uint16_t Pin, uint8_t Level);
uint8_t GPIORead(GPIO_TypeDef* GPIOx, uint16_t Pin);
void delay_ms(uint32_t time_ms);


int main() {
  RCC->APB2ENR |= 0xFC; /* Enable GPIO ports clocks */

  GPIOB->CRH = 0x44444844; // pull-up PB10
  GPIOB->ODR |= (1<<10); //set bit 10 of ODR to pull-up
  GPIOC->CRH = 0x44344444; /* PC13 as output */
  while(1) {		
    if((GPIOB->IDR & (1<<10)) != 0) /* is PB10 high	*/
      GPIOC->ODR |= (1 << 13); /* make PC13 high */
    else
      GPIOC->ODR &= ~(1 << 13); /* make PC13 low */
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
        GPIOx->BSRR = (1 << Pin);
        return 1;
    }
    else if(Level == 0){
        GPIOx->BRR = (1 << Pin);
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
void delay_ms(uint32_t time_ms){
    
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
    TIM2->PSC = 7200 -1;
    TIM2->ARR = (uint16_t)(time_ms * 2); 
    TIM2->CR1 |= TIM_CR1_ARPE; 
    TIM2->EGR |= TIM_EGR_UG; 
    TIM2->CR1 |= TIM_CR1_CEN; 

    
    while((TIM2->SR & TIM_SR_UIF) == 0){}

    
    TIM2->CR1 &= ~TIM_CR1_CEN;
}
