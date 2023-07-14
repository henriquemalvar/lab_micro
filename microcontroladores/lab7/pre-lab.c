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
    TIM2->PSC = 72 - 1; 
    TIM2->ARR = (uint16_t)(time_ms * 2); 
    TIM2->CR1 |= TIM_CR1_ARPE; 
    TIM2->EGR |= TIM_EGR_UG; 
    TIM2->CR1 |= TIM_CR1_CEN; 

    
    while((TIM2->SR & TIM_SR_UIF) == 0){}

    
    TIM2->CR1 &= ~TIM_CR1_CEN;
}