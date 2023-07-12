// Função para controlar um pino de saída digital
// Entradas: Porto de saída (GPIOx), Pino(0 a 15) e Nível(0 ou 1)
// Saída: Nível ajustado (0 ou 1)
uint8_t GPIOWrite(GPIO_TypeDef* GPIOx, uint16_t Pin, uint8_t Level){
    if(Level == 1){
        GPIOx->BSRR = (1 << Pin);
        return 1;
    }
    else if(Level == 0){
        GPIOx->BRR = (1 << Pin);
        return 0;
    }
    else{
        return 2; // Valor inválido de nível
    }
}